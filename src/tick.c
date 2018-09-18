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
*                     recoded by Igor van den Hoven 2004                      *
******************************************************************************/


#include "tintin.h"


DO_COMMAND(do_tick)
{
	char arg1[BUFFER_SIZE], arg2[BUFFER_SIZE], arg3[BUFFER_SIZE];

	arg = sub_arg_in_braces(ses, arg, arg1, 0, SUB_VAR|SUB_FUN);
	arg = get_arg_in_braces(ses, arg, arg2, 1);
	arg = get_arg_in_braces(ses, arg, arg3, 1);

	if (*arg1 == 0)
	{
		show_list(ses->list[LIST_TICKER], 0);
	}
	else if (*arg2 && !strcasecmp(arg2, "SHOW"))
	{
		if (show_node_with_wild(ses, arg1, ses->list[LIST_TICKER]) == FALSE)
			goto not_found;
	}
	else if (!*arg2 || !strcasecmp(arg2, "TIME"))
	{
		struct listnode *node = search_node_list(ses->list[LIST_TICKER], arg1);
		if (!node)
			goto not_found;

		tintin_printf(ses, "#TICKER {%s} TIME: %.2f", node->left, (node->data - gtd->time) / 1000000.0);
	}
	else if (!strcasecmp(arg2, "SYNC") || !strcasecmp(arg2, "DIFF"))
	{	
		struct listnode *node = search_node_list(ses->list[LIST_TICKER], arg1);
		if (!node)
			goto not_found;			

		int tick = get_number(ses, node->pr) * 100;

		int dif = (node->data - gtd->time) / 10000L; 		// in 1/100 sec.
		if (dif > tick * 2 / 3)
			dif -= tick;

		if (!strcasecmp(arg2, "DIFF"))
		{
			tintin_printf(ses, "#TICKER {%s} DIFF: %+.2f", node->left, dif / 100.0);
		}					

		if (tick >= 1000)
		{
			if (dif < 0 && -dif < (tick/10 + 100))
			{
				node->data = gtd->time + tick * 10000LL;
			}
			else if (dif > 100 || dif < 0 )
			{
				node->data = gtd->time + 100;
			}
		}
	}
	else 
	{
		get_number_string(ses, arg3, arg3);

		if (*arg3 == 0 || !strcmp(arg3, "0"))
		{
			strcpy(arg3, "60");
		}

		update_node_list(ses->list[LIST_TICKER], arg1, arg2, arg3);

		show_message(ses, LIST_TICKER, "#OK {%s} NOW EXECUTES {%s} EVERY {%s} SECONDS.", arg1, arg2, arg3);
	}		
	return ses;

not_found:
	show_message(ses, LIST_TICKER, "#TICK, NO MATCH(ES) FOUND FOR {%s}.", arg1);
	return ses;
}


DO_COMMAND(do_untick)
{
	delete_node_with_wild(ses, LIST_TICKER, arg);

	return ses;
}


DO_COMMAND(do_delay)
{
	char arg1[BUFFER_SIZE], arg2[BUFFER_SIZE], arg3[BUFFER_SIZE], temp[BUFFER_SIZE];

	arg = sub_arg_in_braces(ses, arg, arg1, GET_ONE, SUB_VAR|SUB_FUN);
	arg = get_arg_in_braces(ses, arg, arg2, 1);
	arg = sub_arg_in_braces(ses, arg, arg3, GET_ALL, SUB_VAR|SUB_FUN);

	if (*arg1 == 0)
	{
		show_list(ses->list[LIST_DELAY], 0);
	}
	else if (*arg2 == 0)
	{
		if (show_node_with_wild(ses, arg1, ses->list[LIST_DELAY]) == FALSE)
		{
			show_message(ses, LIST_DELAY, "#DELAY: NO MATCH(ES) FOUND FOR {%s}.", arg1);
		}
	}
	else
	{
		if (*arg3 == 0)
		{
			sprintf(arg3, "%lld", utime());

			get_number_string(ses, arg1, temp);

			update_node_list(ses->list[LIST_DELAY], arg3, arg2, temp);

			show_message(ses, LIST_TICKER, "#OK, IN {%s} SECONDS {%s} IS EXECUTED.", temp, arg2);
		}
		else
		{
			get_number_string(ses, arg3, temp);

			update_node_list(ses->list[LIST_DELAY], arg1, arg2, temp);

			show_message(ses, LIST_TICKER, "#OK, IN {%s} SECONDS {%s} IS EXECUTED.", temp, arg2);
		}
	}
	return ses;
}

DO_COMMAND(do_undelay)
{
	delete_node_with_wild(ses, LIST_DELAY, arg);

	return ses;
}
