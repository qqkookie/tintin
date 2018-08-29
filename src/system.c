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
*                     coded by Igor van den Hoven 2007                        *
******************************************************************************/

#include "tintin.h"

#ifdef HAVE_PTY_H
#include <pty.h>
#else
#ifdef HAVE_UTIL_H
#include <util.h>
#endif
#endif

DO_COMMAND(do_run)
{
	char left[BUFFER_SIZE], right[BUFFER_SIZE], temp[BUFFER_SIZE], file[BUFFER_SIZE];
	int desc, pid;
	struct winsize size;

	char *argv[4] = {"sh", "-c", "", NULL};

	arg = sub_arg_in_braces(ses, arg, left,  GET_ONE, SUB_VAR|SUB_FUN);
	arg = sub_arg_in_braces(ses, arg, right, GET_ALL, SUB_VAR|SUB_FUN);
	arg = sub_arg_in_braces(ses, arg, file,  GET_ONE, SUB_VAR|SUB_FUN);

	if (*left == 0 || *right == 0)
	{
		return show_error(ses, LIST_COMMAND, "#SYNTAX: #RUN {NAME} {SYSTEM SHELL COMMAND}");
	}

	size.ws_row = get_scroll_size(ses);
	size.ws_col = ses->cols;

	pid = forkpty(&desc, temp, &gtd->old_terminal, &size);
//	pid = forkpty(&desc, temp, &gtd->new_terminal, &size);

	switch (pid)
	{
		case -1:
			perror("forkpty");
			break;

		case 0:
			sprintf(temp, "exec %s", right);
			argv[2] = temp;
			execv("/bin/sh", argv);
			break;

		default:
			sprintf(temp, "{%s} {%d} {%s}", right, pid, file);

			ses = new_session(ses, left, temp, desc, 0);

			break;
	}
	return gtd->ses;
}

DO_COMMAND(do_scan)
{
	FILE *fp;
	char filename[BUFFER_SIZE];

	get_arg_in_braces(ses, arg, filename, TRUE);
	substitute(ses, filename, filename, SUB_VAR|SUB_FUN);

	if ((fp = fopen(filename, "r")) == NULL)
	{
		return show_error(ses, LIST_COMMAND, "#ERROR: #SCAN {%s} - FILE NOT FOUND.", filename);
	}

	SET_BIT(ses->flags, SES_FLAG_SCAN);

	if (STRING_SIZE > gtd->mud_output_max)
	{
		gtd->mud_output_max  = STRING_SIZE;
		gtd->mud_output_buf  = (char *) realloc(gtd->mud_output_buf, gtd->mud_output_max);
	}

	while (fgets(gtd->mud_output_buf, STRING_SIZE, fp))
	{
		gtd->mud_output_len = 1;

		readmud(ses);
	}

	DEL_BIT(ses->flags, SES_FLAG_SCAN);

	show_message(ses, LIST_COMMAND, "#OK. FILE SCANNED.", filename);

	fclose(fp);

	return ses;
}

DO_COMMAND(do_script)
{
	char arg1[BUFFER_SIZE], arg2[BUFFER_SIZE], *cptr, buf[BUFFER_SIZE], var[BUFFER_SIZE], tmp[BUFFER_SIZE];
	FILE *script;
	int index;

	arg = sub_arg_in_braces(ses, arg, arg1, GET_ONE, SUB_VAR|SUB_FUN);
	arg = sub_arg_in_braces(ses, arg, arg2, GET_ALL, SUB_VAR|SUB_FUN);

	if (*arg1 == 0)
	{
		show_error(ses, LIST_COMMAND, "#SCRIPT: ONE ARGUMENT REQUIRED.");
	}
	else if (*arg2 == 0)
	{
		script = popen(arg1, "r");

		while (fgets(buf, BUFFER_SIZE - 1, script))
		{
			cptr = strchr(buf, '\n');

			if (cptr)
			{
				*cptr = 0;
			}

			ses = script_driver(ses, LIST_COMMAND, buf);
		}

		pclose(script);
	}
	else
	{
		index = 1;

		script = popen(arg2, "r");

		var[0] = 0;

		while (fgets(buf, BUFFER_SIZE - 1, script))
		{
			cptr = strchr(buf, '\n');

			if (cptr)
			{
				*cptr = 0;
			}

			substitute(ses, buf, tmp, SUB_SEC);

			cat_sprintf(var, "{%d}{%s}", index++, tmp);
		}


		set_nest_node(ses->list[LIST_VARIABLE], arg1, "%s", var);

		pclose(script);
	}
	refresh_terminal();

	return ses;
}

DO_COMMAND(do_system)
{
	char left[BUFFER_SIZE];

	get_arg_in_braces(ses, arg, left, TRUE);
	substitute(ses, left, left, SUB_VAR|SUB_FUN);

	if (*left == 0)
	{
		return show_error(ses, LIST_COMMAND, "#SYNTAX: #SYSTEM {COMMAND}.");
	}

	show_message(ses, LIST_COMMAND, "#OK: EXECUTING '%s'", left);

	if (!HAS_BIT(gtd->ses->flags, SES_FLAG_READMUD) && IS_SPLIT(gtd->ses))
	{
		save_pos(gtd->ses);
		goto_rowcol(gtd->ses, gtd->ses->bot_row, 1);
	}
	fflush(stdout);

	system(left);

	if (!HAS_BIT(gtd->ses->flags, SES_FLAG_READMUD) && IS_SPLIT(gtd->ses))
	{
		restore_pos(gtd->ses);
	}
	fflush(stdout);

	refresh_terminal();

	return ses;
}


DO_COMMAND(do_textin)
{
	FILE *fp;
	char left[BUFFER_SIZE], right[BUFFER_SIZE], buffer[BUFFER_SIZE], *cptr;

	arg = get_arg_in_braces(ses, arg, left, FALSE);
	substitute(ses, left, left, SUB_VAR|SUB_FUN);

	arg = get_arg_in_braces(ses, arg, right, TRUE);

	if ((fp = fopen(left, "r")) == NULL)
	{
		return show_error(ses, LIST_COMMAND, "#ERROR: #TEXTIN {%s} - FILE NOT FOUND.", left);
	}

	while (fgets(buffer, BUFFER_SIZE - 1, fp))
	{
		cptr = strchr(buffer, '\n');

		if (cptr)
		{
			*cptr = 0;
		}

		write_mud(ses, buffer, SUB_EOL);

		if (*right)
		{
			usleep((long long) (get_number(ses, right) * 1000000));
		}
	}
	fclose(fp);

	show_message(ses, LIST_COMMAND, "#OK. FILE READ.");

	return ses;
}

#ifdef HAVE_LUA_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

// 	#lua {<return_variable>} {<LUA_script>} arg1, arg2, ... 
//	EX) #lua {aaa} {$script} a b c d ...

DO_COMMAND(do_lua)
{
	int argc, error;
	char var[BUFFER_SIZE], script[BUFFER_SIZE], arglist[20][BUFFER_SIZE], buf[BUFFER_SIZE];

	arg = sub_arg_in_braces(ses, arg, var, GET_ONE, SUB_VAR|SUB_FUN);

	arg = sub_arg_in_braces(ses, arg, script, GET_ONE, SUB_VAR|SUB_FUN);	

	if ( *var == '\0' ||  *script == '\0')
	{
		return show_error(ses, LIST_COMMAND, "#LUA: VAR, SCRIPT REQUIRED.");
	}
		
	for ( argc = 0 ; *arg != '\0' && argc < 20 ; argc++ )
	{
		arg = sub_arg_in_braces(ses, arg, arglist[argc], GET_ONE, SUB_VAR|SUB_FUN);
	}

	lua_State *Lx = luaL_newstate();	// opens Lua VM
	while(Lx != NULL) 
	{
		luaL_openlibs(Lx);            	// opens libraries

		error = luaL_loadstring(Lx, script); 
		if (error) break;

		// add arg[1]-arg[20] global vars.
		lua_createtable(Lx, argc, 0);

		if ( argc > 0 && *arglist[0] != '\0') 
		{
			for (int  i = 0; i < argc ; i++ ) 
			{
				lua_pushinteger(Lx, i+1); 
				lua_pushstring(Lx, arglist[i]);
				lua_settable(Lx, -3);
			}
		}
		lua_setglobal(Lx,"arg");

		error = lua_pcall(Lx, 0, 1, 0);
		if (error) break; 

		if (lua_type( Lx, 0) == LUA_TTABLE )
		{
			lua_pushvalue(Lx, 0);	// copy return value table
			lua_pushnil(Lx);		// dummy key
			buf[0] = '\0';

			while (lua_next(Lx, -2))
			{
				lua_pushvalue(Lx, -2);	// copy key to convert string

				const char *key = lua_tostring(Lx, -1);
				const char *value = lua_tostring(Lx, -2);
				
				if ( key )
					cat_sprintf(buf, "{%s}{%s}", key , value ? value : "" );

				lua_pop (Lx, 2);
			}			
		}
		else
			sprintf(buf, "{%s}", lua_tostring(Lx, 0));			
	
		set_nest_node(ses->list[LIST_VARIABLE], var, "%s", buf);
		
		// tintin_printf2(ses, "#var %s", buf);
		break;
	}
	
	if ( error )
	{
		show_error(ses, LIST_COMMAND, "#LUA: SCRIPT ERROR: %s", lua_tostring(Lx, -1) );
		lua_pop(Lx, 1);  // pop error message from the stack
	}

	lua_close(Lx);

	refresh_terminal();

	return ses;
}

#else

DO_COMMAND(do_lua) 
{
	return show_error(ses, LIST_COMMAND, "#LUA: UNSUPPORTED.");
}
#endif // HAVE_LUA_H
