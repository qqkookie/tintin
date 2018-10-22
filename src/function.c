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
******************************************************************************/

/******************************************************************************
*               (T)he K(I)cki(N) (T)ickin D(I)kumud Clie(N)t                  *
*                                                                             *
*                       coded by Sverre Normann 1999                          *
*                    recoded by Igor van den Hoven 2004                       *
******************************************************************************/

#include "tintin.h"


DO_COMMAND(do_function)
{
	char arg1[BUFFER_SIZE], arg2[BUFFER_SIZE];

	arg = sub_arg_in_braces(ses, arg, arg1, 0, SUB_VAR|SUB_FUN);
	arg = get_arg_in_braces(ses, arg, arg2, 1);

	if (*arg1 == 0)
	{
		show_list(ses->list[LIST_FUNCTION], 0);
	}

	else if (*arg1 && *arg2 == 0)
	{
		if (show_node_with_wild(ses, arg1, ses->list[LIST_FUNCTION]) == FALSE)
		{
			show_message(ses, LIST_FUNCTION, "#FUNCTION: NO MATCH(ES) FOUND FOR {%s}.", arg1);
		}
	}
	else
	{
		update_node_list(ses->list[LIST_FUNCTION], arg1, arg2, "");

		show_message(ses, LIST_FUNCTION, "#OK. FUNCTION {%s} HAS BEEN SET TO {%s}.", arg1, arg2);
	}
	return ses;
}


DO_COMMAND(do_unfunction)
{
	delete_node_with_wild(ses, LIST_FUNCTION, arg);

	return ses;
}

// get tail part of string
char *strright(struct session *ses, char *str, int off)
{
	while (*str && off > 0)
	{
		off--;
		str++;
		if (HAS_BIT(ses->flags, SES_FLAG_UTF8) && (str[-1] & 192) == 192)
			while ((*str & 192) == 128)
				str++;
	}
	return str;
}

enum { LF_NONE = 0, LF_ISLIST, LF_ISARRAY, LF_ISDEF, LF_KEY, LF_VALUE,
	LF_PAIR, LF_INDEX, LF_FIRST, LF_LAST, LF_KLEN,
	LF_LLEN, LF_VARID, LF_FIND, LF_SUBSTR };

void lib_function(struct session *ses, char *arg, int func)
{
	enum { IX_NO = 0, IX_VAL, IX_KEY, IX_ALL };

	char result[BUFFER_SIZE], exp[BUFFER_SIZE], name[256], brak[256], *str;
	char te[BUFFER_SIZE], tr[BUFFER_SIZE];
	char *arg1 = gtd->vars[1];
	int ixt;
	*exp = '\0'; *result ='\0';

	switch (func)
	{
		case LF_ISLIST: case LF_ISARRAY: case LF_ISDEF: case LF_INDEX:
		case LF_FIRST: case LF_LAST: case LF_KLEN: case LF_LLEN: case LF_VARID:
			strcpy(result, "0");
			break;
	}

	set_nest_node(ses->list[LIST_VARIABLE], "result", result);

	str = get_arg_to_brackets(ses, arg1, name);
	get_arg_at_brackets(ses, str, brak);

	if (func == LF_VARID || func == LF_ISDEF )
	{
		sprintf(exp, "&{%s}", name);

		substitute(ses, exp, result, SUB_VAR);

		set_nest_node(ses->list[LIST_VARIABLE], "result", result);

		return;
	}
	else if (func == LF_FIND)
	{
		int off = atoi(gtd->vars[3]);

		str = off > 0 ? strright(ses, arg1, off) : arg1;

		char *found = strstr(str, gtd->vars[2]);

		if (found)
		{
			*found = '\0';
			off += strip_vt102_strlen(ses, str);
		}
		else
		{
			off = -1;
		}
		set_nest_node(ses->list[LIST_VARIABLE], "result", "%d", off + 1);

		return;
	}
	else if (func == LF_SUBSTR)
	{
		int off = atoi(gtd->vars[2]);
		int len = atoi(gtd->vars[3]);

		str = off > 0 ? strright(ses, arg1, off) : arg1;

		if ( len > 0)
		{
			*strtail(ses, str, len) = '\0';
		}
		set_nest_node(ses->list[LIST_VARIABLE], "result", "%s", str);

		return;
	}

	sprintf(te, "&{%s}[+1]", name);
	substitute(ses, te, tr, SUB_VAR);

	if (strcmp(tr, "1") != 0 )
	{
		return;
	}

	if (!*brak)
	{
		ixt = IX_NO;
	}
	else if ( strcmp(brak, "[]") == 0)
	{
		ixt = IX_KEY;
	}
	else if ( strcmp(brak, "[%*]") == 0)
	{
		ixt = IX_ALL;
	}
	else
	{
		ixt = IX_VAL;
	}

	if (func == LF_KEY && ixt == IX_NO)
	{
		sprintf(exp, "${%s}[]", name);
	}
	else if(func == LF_KEY )
	{
		sprintf(exp, "*{%s}", arg1 );
	}
	else if (func == LF_VALUE && (ixt == IX_NO || ixt == IX_ALL))
	{
		sprintf(exp, "${%s}[%%*]", name);
	}
	else if (func == LF_VALUE && ixt == IX_VAL )
	{
		sprintf(exp, "{${%s}}", arg1);
	}
	else if (func == LF_PAIR && ixt == IX_VAL )
	{
		sprintf(exp, "{*{%s}}{${%s}}", arg1, arg1);
	}
	else if (func == LF_PAIR)
	{
		sprintf(exp, "${%s}", name);
	}
	else if ( (func == LF_INDEX && ixt == IX_VAL))
	{
		sprintf(exp, "&{%s}", arg1);
	}
	else if (func == LF_FIRST && ixt == IX_ALL)
	{
		sprintf(exp, "${%s}[+1]", name);
	}
	else if (func == LF_FIRST && ixt != IX_VAL)
	{
		sprintf(exp, "*{%s}[+1]", name);
	}
	else if (func == LF_LAST && ixt == IX_ALL)
	{
		sprintf(exp, "${%s}[-1]", name);
	}
	else if (func == LF_LAST && ixt != IX_VAL)
	{
		sprintf(exp, "*{%s}[-1]", name);
	}
	else if ((func == LF_ISLIST && ixt == IX_NO)
	|| (func == LF_KLEN && ixt != IX_VAL))
	{
		sprintf(exp, "&{%s}[]", name);
	}
	else if (func == LF_ISARRAY && ixt == IX_NO)
	{
		sprintf(te, "*{%s}[]", name);
		substitute(ses, te, tr, SUB_VAR);

		str = tr;
		int n, old = 0;
		do {
			str = get_arg_in_braces(ses, str, te, GET_ONE);
			n = atoi(te);
			if (n <= old)
				break;
			old = n;
		} while (*str);

		if (*str)
			return;

		sprintf(exp, "&{%s}[]", name );
	}
	else if (func == LF_LLEN && ixt == IX_NO)
	{
		sprintf(te, "${%s}", name);
		substitute(ses, te, tr, SUB_VAR);

		str = tr;
		int n = 0;
		do {
			str = get_arg_in_braces(ses, str, te, GET_ONE);
			n++;
		} while (*str);

		sprintf(result, "%d", n );
		return;
	}
	else
	{
	}

	if (*exp)
	{
		substitute(ses, exp, result, SUB_VAR);
	}

	if (strcmp(result, exp) == 0 || strcmp(result, arg1) == 0)
	{
		*result ='\0';
	}

	set_nest_node(ses->list[LIST_VARIABLE], "result", result);
}
