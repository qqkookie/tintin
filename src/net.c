/******************************************************************************
*   TinTin++                                                                  *
*   Copyright (C) 2004 (See CREDITS file)                                     *
*                                                                             *
*   This program is protected under the GNU GPL (See COPYING)                 *
*                                                                             *
*   This program is free software; you can redistribute it and/or modify      *
*   it under the terms of the GNU General Public License as published by      *
*   the Free Software Foundation; either version 2 of the License, or         *
*   (at your option) any later version.                                       *
*                                                                             *
*   This program is distributed in the hope that it will be useful,           *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of            *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
*   GNU General Public License for more details.                              *
*                                                                             *
*   You should have received a copy of the GNU General Public License         *
*   along with this program; if not, write to the Free Software               *
*   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA *
*******************************************************************************/

/******************************************************************************
*                (T)he K(I)cki(N) (T)ickin D(I)kumud Clie(N)t                 *
*                                                                             *
*                         coded by Peter Unold 1992                           *
******************************************************************************/


#include "tintin.h"

#include <errno.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>

/*
	IPv6 compatible connect code, doesn't work on several platforms.
*/

#ifdef HAVE_GETADDRINFO

int connect_mud(struct session *ses, char *host, char *port)
{
	int sock, error;
	struct addrinfo *address;
	static struct addrinfo hints;
	char ip[100];

	if (!is_number(port))
	{
		tintin_puts(ses, "#THE PORT SHOULD BE A NUMBER.");
		return -1;
	}

//	hints.ai_family   = AF_UNSPEC;
	hints.ai_family   = AF_INET;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_socktype = SOCK_STREAM;

	error = getaddrinfo(host, port, &hints, &address);

	if (error)
	{
		hints.ai_family = AF_INET6;

		error = getaddrinfo(host, port, &hints, &address);

		if (error)
		{
			tintin_printf(ses, "#SESSION '%s' COULD NOT CONNECT - UNKNOWN HOST.", ses->name);

			return -1;
		}
	}

	sock = socket(address->ai_family, address->ai_socktype, address->ai_protocol);

	if (sock < 0)
	{
		syserr("socket");
	}

	ses->connect_error = connect(sock, address->ai_addr, address->ai_addrlen);

	if (ses->connect_error)
	{
		close(sock);
		freeaddrinfo(address);

		return 0;
	}

	if (fcntl(sock, F_SETFL, O_NDELAY|O_NONBLOCK) == -1)
	{
		perror("connect_mud: fcntl O_NDELAY|O_NONBLOCK");
	}

	getnameinfo(address->ai_addr, address->ai_addrlen, ip, 100, NULL, 0, NI_NUMERICHOST);

	RESTRING(ses->session_ip, ip);

	freeaddrinfo(address);

	return sock;
}

#else

int connect_mud(struct session *ses, char *host, char *port)
{
	int sock, d;
	struct sockaddr_in sockaddr;

	if (sscanf(host, "%d.%d.%d.%d", &d, &d, &d, &d) == 4)
	{
		sockaddr.sin_addr.s_addr = inet_addr(host);
	}
	else
	{
		struct hostent *hp;

		if (!(hp = gethostbyname(host)))
		{
			tintin_puts2(ses, "#ERROR - UNKNOWN HOST.");

			return -1;
		}
		memcpy((char *)&sockaddr.sin_addr, hp->h_addr, sizeof(sockaddr.sin_addr));
	}

	if (is_number(port))
	{
		sockaddr.sin_port = htons(atoi(port));
	}
	else
	{
		tintin_puts(ses, "#THE PORT SHOULD BE A NUMBER.");
		return -1;
	}

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		syserr("socket");
	}

	sockaddr.sin_family = AF_INET;

	ses->connect_error = connect(sock, (struct sockaddr *)&sockaddr, sizeof(sockaddr));

	if (ses->connect_error)
	{
		close(sock);

		return 0;
	}

	if (fcntl(sock, F_SETFL, O_NDELAY|O_NONBLOCK) == -1)
	{
		perror("connect_mud: fcntl O_NDELAY|O_NONBLOCK");
	}

	RESTRING(ses->ip, inet_ntoa(sockaddr.sin_addr));

	return sock;
}

#endif

void write_line_mud(struct session *ses, char *line, int size)
{
	static int retry;

	push_call("write_line_mud(%p,%p)",line,ses);

	if (ses == gts)
	{
		tintin_printf2(ses, "#NO SESSION ACTIVE. USE: %csession {name} {host} {port} TO START ONE.", gtd->tintin_char);

		pop_call();
		return;
	}

	if (!HAS_BIT(ses->flags, SES_FLAG_CONNECTED))
	{
		tintin_printf2(ses, "#THIS SESSION IS NOT CONNECTED, CANNOT SEND: %s", line);

		pop_call();
		return;
	}

#ifdef HAVE_GNUTLS_H

	if (ses->ssl)
	{
		int result;

		result = gnutls_record_send(ses->ssl, line, size);

		while (result == GNUTLS_E_INTERRUPTED || result == GNUTLS_E_AGAIN)
		{
			result = gnutls_record_send(ses->ssl, 0, 0);
		}
	}
	else

#endif

	if (write(ses->socket, line, size) == -1)
	{
		if (retry++ < 10)
		{
			usleep(100000);

			write_line_mud(ses, line, size);

			pop_call();
			return;
		}
		perror("write in write_line_mud");

		cleanup_session(ses);

		pop_call();
		return;
	}

	retry = 0;

	check_all_events(ses, SUB_ARG|SUB_SEC, 0, 1, "SEND OUTPUT", line);

	pop_call();
	return;
}


int read_buffer_mud(struct session *ses)
{
	unsigned char buffer[BUFFER_SIZE];
	int size;

	push_call("read_buffer_mud(%p)",ses);

#ifdef HAVE_GNUTLS_H

	if (ses->ssl)
	{
		do
		{
			size = gnutls_record_recv(ses->ssl, buffer, BUFFER_SIZE - 1);
		}
		while (size == GNUTLS_E_INTERRUPTED || size == GNUTLS_E_AGAIN);

		if (size < 0)
		{
			tintin_printf2(ses, "#SSL ERROR: %s", gnutls_strerror(size));
		}
	}
	else
#endif
	size = read(ses->socket, buffer, BUFFER_SIZE - 1);
	
	if (size <= 0)
	{
		pop_call();
		return FALSE;
	}
	ses->read_len = translate_telopts(ses, buffer, size);

	pop_call();
	return TRUE;
}


void readmud(struct session *ses)
{
	char *line, *next_line;
	char linebuf[STRING_SIZE];

	push_call("readmud(%p)", ses);

	if (gtd->mud_output_len < BUFFER_SIZE)
	{
		check_all_events(ses, SUB_ARG|SUB_SEC, 0, 1, "RECEIVED OUTPUT", gtd->mud_output_buf);
	}

	gtd->mud_output_len = 0;

	/* separate into lines and print away */

	if (HAS_BIT(gtd->ses->flags, SES_FLAG_SPLIT))
	{
		save_pos(gtd->ses);
		goto_rowcol(gtd->ses, gtd->ses->bot_row, 1);
	}

	SET_BIT(gtd->ses->flags, SES_FLAG_READMUD);

	for (line = gtd->mud_output_buf ; line && *line ; line = next_line)
	{
		next_line = strchr(line, '\n');

		if (next_line)
		{
			*next_line = 0;
			next_line++;
		}
		else if (*line == 0)
		{
			break;
		}

		if (next_line == NULL && strlen(ses->more_output) < BUFFER_SIZE / 2)
		{
			if (!HAS_BIT(gtd->ses->telopts, TELOPT_FLAG_PROMPT))
			{
				if (gts->check_output)
				{
					strcat(ses->more_output, line);
					ses->check_output = utime() + gts->check_output;
					break;
				}
			}
		}

		if (ses->more_output[0])
		{
			if (ses->check_output)
			{
				sprintf(linebuf, "%s%s", ses->more_output, line);

				ses->more_output[0] = 0;
			}
			else
			{
				strcpy(linebuf, line);
			}
		}
		else
		{
			strcpy(linebuf, line);
		}

		process_mud_output(ses, linebuf, next_line == NULL);
	}
	DEL_BIT(gtd->ses->flags, SES_FLAG_READMUD);

	if (HAS_BIT(gtd->ses->flags, SES_FLAG_SPLIT))
	{
		restore_pos(gtd->ses);
	}

	pop_call();
	return;
}


void process_mud_output(struct session *ses, char *linebuf, int prompt)
{
	char line[STRING_SIZE];

	push_call("process_mud_output(%p,%p,%d)",ses,linebuf,prompt);

	ses->check_output = 0;

	strip_vt102_codes(linebuf, line);

	check_all_events(ses, SUB_ARG|SUB_SEC, 0, 2, "RECEIVED LINE", linebuf, line);

	if (prompt)
	{
		check_all_events(ses, SUB_ARG|SUB_SEC, 0, 2, "RECEIVED PROMPT", linebuf, line);
	}

	if (HAS_BIT(ses->flags, SES_FLAG_COLORPATCH))
	{
		sprintf(line, "%s%s%s", ses->color, linebuf, "\033[0m");

		get_color_codes(ses->color, linebuf, ses->color);

		linebuf = line;
	}

	if ( HAS_BIT(ses->flags, SES_FLAG_U8CONV) && HAS_BIT(ses->flags, SES_FLAG_UTF8))
	{
		utf8convert(FALSE, linebuf, -1);
	}

	do_one_line(linebuf, ses);   /* changes linebuf */

	/*
		Take care of gags, vt102 support still goes
	*/

	if (HAS_BIT(ses->flags, SES_FLAG_GAG))
	{
		strip_non_vt102_codes(linebuf, ses->more_output);

		printf("%s", ses->more_output);

		ses->more_output[0] = 0;

		DEL_BIT(ses->flags, SES_FLAG_GAG);

		pop_call();
		return;
	}

	add_line_buffer(ses, linebuf, prompt);

	if (ses == gtd->ses)
	{
		char *output = str_dup(linebuf);

		printline(ses, &output, prompt);

		str_free(output);
	}
	else if (HAS_BIT(ses->flags, SES_FLAG_SNOOP))
	{
		strip_vt102_codes_non_graph(linebuf, linebuf);

		tintin_printf2(gtd->ses, "[%s] %s", ses->name, linebuf);
	}
	pop_call();
	return;
}

#if defined(__CYGWIN__) && !defined(HAVE_ICONV_H)

// For Cywin Wintin++ only. CyWin iconv(3) not woking without iconv DLL.
#include <windows.h>

int utf8convert(int fromutf, char *linebuf, int inlen)
{
	static char *cpname = NULL;
	static int CPid = -1;

	if (gtd->hostcp && gtd->hostcp != cpname)
	{
		cpname = gtd->hostcp;
		CPid = CPNameToCPID(cpname);
	}
	
	if (!cpname || CPid == CP_UTF8)
		return 0;

	wchar_t wcbuf[STRING_SIZE];

	int wlen = MultiByteToWideChar((fromutf ? CP_UTF8 : CPid ), 0, linebuf, inlen, wcbuf, STRING_SIZE);
		
	int  olen = -1;
	if ( wlen > 0 )
	{
		olen = WideCharToMultiByte((fromutf ? CPid : CP_UTF8), 0, wcbuf, wlen, linebuf, STRING_SIZE, NULL, NULL);
	}

	return olen;
}

#else

#include <iconv.h>

int utf8convert(int fromutf, char *linebuf, int inlen) 
{
	static char *cpname = NULL;
	static iconv_t cd_to = (iconv_t)-1, cd_from = (iconv_t)-1;

	if (gtd->hostcp != cpname)
	{
		if ( cd_to != (void*)-1)
		{
			 iconv_close(cd_to);
			 iconv_close(cd_from);
		}

		cpname = gtd->hostcp;

		if ( cpname && *cpname && strcmp(cpname, "UTF-8" ) != 0 )
		{
			cd_from  = iconv_open(cpname, "UTF-8");
			cd_to = iconv_open("UTF-8", cpname);			
		}
		else
		{
 			cd_to = (iconv_t)-1;
			cd_from = (iconv_t)-1;
		}
	}

	if (!cpname || cd_to == (iconv_t)-1)
	{
		return 0;
	}

	char buf[STRING_SIZE];	
	char *inbuf = linebuf, *outbuf = buf;
	size_t conv, inleft, outleft = sizeof buf -1;;

	inleft = (inlen >= 0 ? inlen : strlen(linebuf)+1);

	conv = iconv((fromutf ? cd_from : cd_to), &inbuf, &inleft, &outbuf, &outleft );
	// conv += iconv((fromutf ? cd_from : cd_to), NULL, NULL, &outbuf, &outleft );

	if ( conv == (size_t)-1)
	{
		return 0;
	}	
	strcpy(linebuf, buf);

	return (outbuf-buf);
}

#endif

/*
	Test string : "이것은 한글입니다. Happy life! 안녕"

	static char str_euc_kr[] = { 	// Encoded in EUC-KR 
		0xc0, 0xcc, 0xb0, 0xcd, 0xc0, 0xba, 0x20, 0xc7, 0xd1, 0xb1, 0xdb, 0xc0,
		0xd4, 0xb4, 0xcf, 0xb4, 0xd9, 0x2e, 0x20, 0x48, 0x61, 0x70, 0x70, 0x79,
		0x20, 0x6c, 0x69, 0x66, 0x65, 0x21, 0x20, 0xbe, 0xc8, 0xb3, 0xe7, 0x00,
	};

	static char str_utf8[] = {		// Encoded in UTF-8 
		0xec, 0x9d, 0xb4, 0xea, 0xb2, 0x83, 0xec, 0x9d, 0x80, 0x20, 0xed, 0x95,
		0x9c, 0xea, 0xb8, 0x80, 0xec, 0x9e, 0x85, 0xeb, 0x8b, 0x88, 0xeb, 0x8b,
		0xa4, 0x2e, 0x20, 0x48, 0x61, 0x70, 0x70, 0x79, 0x20, 0x6c, 0x69, 0x66,
		0x65, 0x21, 0x20, 0xec, 0x95, 0x88, 0xeb, 0x85, 0x95, 0x00,
	};
*/

struct cp_map {
	char *name;
	int cpid;
};

struct cp_map cp_table[] =
{
	{ "CP437",	 			437		},	// US ASCII
	{ "ASCII", 				437		},
	{ "ANSI_X3.4-1968",		437		},	
	{ "CP1252",	 			1252	},	// MS Windows US/Europe
	{ "CP850",	 			850		},	// Latin-1, Western Europe
	{ "ISO-8859-1",	 		850		},

	{ "CP936",	 			936		},	// Simplified Chinese
	{ "GB2312",	 			936		},
	{ "EUC-CN",	 			936		},
	{ "CP950",	 			950		},	// Traditional Chinese, Big5
	{ "BIG5",	 			950		},
	{ "CP932",	 			932		},	// SHift JIS Japanese
	{ "SJIS",	 			932		},
	{ "EUC-JP",	 			932		},
	{ "CP949",	 			949		},	// Korean KSC-5601
	{ "EUC-KR",	 			949		},	

	{ "UTF-8",	 			65001	},
	{ "UTF8",	 			65001	},

	{ "C",	 				0		},
	{ "ACP",	 			0		},
	{ NULL,	 				0		},
};

int CPNameToCPID(char *arg)
{
	struct cp_map *cpp;
	int cpid = -1;;

	for ( cpp = cp_table; cpp->name; cpp++ )
	{
		if ( strcasecmp(cpp->name, arg) == 0 )
		{
			cpid = cpp->cpid;
			break;
		}
	}

	if (cpid < 0)
	{
		if (strncasecmp(arg, "CP", 2 ) == 0 || atoi(arg+2) > 0)
		{
			cpid = atoi(arg+2);
		}
	}

	return cpid; 
}
