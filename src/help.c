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
*                (T)he K(I)cki(N) (T)ickin D(I)kumud Clie(N)t                 *
*                                                                             *
*                      coded by Igor van den Hoven 2004                       *
******************************************************************************/

#include "tintin.h"


struct help_type
{
	char                  * name;
	char                  * text;
};

/*
	This help table is a mess, but I got better things to do - Igor
*/

struct help_type help_table[] =
{
	{
		"ACTION",
		"<K82>Command<K81>: #action <K82>{<K81>search string<K82>}<K81> <K82>{<K81>commands<K82>}<K81> <K82>{<K81>priority<K82>}<K81>\n"
		"\n"
		"         Have tintin search for a certain string of text from the mud, if the\n"
		"         string is found it will execute the commands.  Variables %1 to %99\n"
		"         are substituted from the input string, and can be used in the command.\n"
		"\n"
		"         If the search string starts with ~, color codes must be matched, which\n"
		"         you can see by enabling: #config {convert meta} on.\n"
		"\n"
		"         The following Perl compatible regular expression options are available:\n"
		"\n"
		"       ^ force match of start of line.\n"
		"       $ force match of end of line.\n"
		"       \\ escape one character.\n"
		"  %1-%99 lazy match of any text, available at %1-%99.\n"
		"      %0 should be avoided in triggers, and if left alone lists all matches.\n"
		"     { } embed a raw regular expression, available at %1-%99 + 1.\n"
		"         [ ] . + | ( ) ? * are treated as normal text unlessed used within\n"
		"         braces. Keep in mind that { } is replaced with ( ) automatically.\n"
		"\n"
		"         Of the following the (lazy) match is available at %1-%99 + 1\n"
		"\n"
		"      %w match zero to any number of letters.\n"
		"      %W match zero to any number of non letters.\n"
		"      %d match zero to any number of digits.\n"
		"      %D match zero to any number of non digits.\n"
		"      %s match zero to any number of spaces.\n"
		"      %S match zero to any number of non spaces.\n"
		"\n"
		"      %? match zero or one character.\n"
		"      %. match one character.\n"
		"      %+ match one to any number of characters.\n"
		"      %* match zero to any number of characters.\n"
		"\n"
		"      %i matching becomes case insensitive.\n"
		"      %I matching becomes case sensitive (default).\n"
		"\n"
		"         Actions can be triggered by the showme command.\n"
		"\n"
		"<K82>Example<K81>: #act {^You are hungry$} {get bread backpack;eat bread}\n"
		"         Performs 2 commands as you get the hunger message, tintin will not\n"
		"         be fooled by someone saying 'You are hungry'.\n"
		"\n"
		"<K82>Example<K81>: #act {%1 tells you 'hello'} {tell %1 Hello %1. How are you today?}\n"
		"         This allows you to seem like a nice, attentive, fast typing gentleman.\n"
		"\n"
		"<K82>Example<K81>: #act {A puppy barks at you, wagging {his|her|its} tail.} {pat puppy}\n"
		"         This allows you to be nice to puppies regardless of their sex.\n"
		"\n"
		"<K82>Comment<K81>: You can remove an action with the #unaction command.\n"
	},
	{
		"ALIAS",
		"<K82>Command<K81>: #alias <K82>{<K81>word<K82>} {<K81>command<K82>}<K81>\n"
		"\n"
		"         Defines a word that when entered executes the given command. If\n"
		"         any arguments are given they are appended to the end of the command."
		"\n"
		"         If the command includes variables %0-99, these are substituted as\n"
		"         part of the parsing.  %0 is set to all text after the word was input,\n"
		"         %1 is set to the first word following the aliased word, and %2 is the\n"
		"         second, and so on. If you use %0-99 no arguments are automatically\n"
		"         appended.\n"
		"\n"
		"         The word can include the %1 to %99 variables making an alias behave\n"
		"         like an action, allowing more complex input matching.\n"
		"\n"
		"<K82>Example<K81>: #alias gb get bread bag\n"
		"         Typing gb at the prompt would be sent as 'get bread bag'.\n"
		"\n"
		"<K82>Example<K81>: #alias ws {wake;stand}\n"
		"         Since ws aliases a multiple command, you must use the braces.\n"
		"\n"
		"<K82>Example<K81>: #alias heal cast 'heal' %1\n"
		"         Typing 'heal valgar' would be sent as 'cast 'heal' valgar'.\n"
		"\n"
		"<K82>Comment<K81>: See '#help action', for more information about triggers.\n"
		"\n"
		"<K82>Comment<K81>: You can remove an alias with the #unalias command.\n"
	},
	{
		"ALL",
		"<K82>Command<K81>: #all <K82>{<K81>string<K82>}<K81>\n"
		"\n"
		"         Sends a command to all active sessions.\n"
		"\n"
		"<K82>Example<K81>: #all quit\n"
		"         Sends 'quit' to all active sessions.\n"
	},
	{
		"BELL",
		"<K82>Command<K81>: #bell\n"
		"\n"
		"         Sends a beep to your terminal.\n"
		"\n"
		"<K82>Example<K81>: #action {tells you} {#bell}\n"
		"         Will chime every time someone gives you a tell.\n"
	},
	{
		"BREAK",
		"<K82>Command<K81>: #break\n"
		"\n"
		"         The break command can be used inside the #FOREACH, #LOOP, #PARSE,\n"
		"         #WHILE and #SWITCH statements. When #BREAK is found, tintin will stop\n"
		"         executing the statement it is currently in and move on to the next.\n"
		"\n"
		"<K82>Example<K81>: #while {1} {#math cnt $cnt + 1;#if {$cnt == 20} {#break}}\n"
	},
	{
		"BUFFER",
		"<K82>Command<K81>: #buffer <K82>{<K81>home<K82>|<K81>up<K82>|<K81>down<K82>|<K81>end<K82>|<K81>lock<K82>|<K81>clear<K82>|<K81>info<K82>}<K81>\n"
		"         The buffer command allows you to add macros to scroll in case the\n"
		"         default bindings do not work. The lock options toggles the\n"
		"         scrolling state of the screen.\n"
		"\n"
		"         #buffer {find} {number} {text} Jump to the first occasion of text\n"
		"         or the given occasion by providing the optional number argument.\n"
		"\n"
		"         #buffer {get} {variable} {line} {range} Store the given line or\n"
		"         range in the given variable.\n"
		"\n"
		"         #buffer {write} {filename} Write the buffer to the given file.\n"
		"\n"
		"<K82>Example<K81>: #macro {(press ctrl-v)(press F1)} {#buffer end}\n"
		"         Associates F1 key to 'scroll buffer to its end' command.\n"
	},
	{
		"CASE",
		"<K82>Command<K81>: #case <K82>{<K81>conditional<K82>}<K81> <K82>{<K81>arguments<K82>}<K81>\n"
		"\n"
		"         The case command must be used within the switch command. When the\n"
		"         conditional argument of the case command matches the conditional\n"
		"         argument of the switch command the body of the case is executed.\n"
	},
	{
		"CHAT",
		"<K82>Command<K81>: #chat <K82>{<K81>option<K82>}<K81> <K82>{<K81>argument<K82>}<K81>\n"
		"\n"
		"         #chat {init}       {port}             Initilizes a chat port.\n"
		"         #chat {name}       {name}             Sets your chat name.\n"
		"         #chat {message}    {buddy|all} {text} Sends a chat message\n"
		"\n"
		"         #chat {accept}     {buddy}            Accept a file transfer\n"
		"         #chat {call}       {address} {port}   Connect to a buddy\n"
		"         #chat {cancel}     {buddy}            Cancel a file transfer\n"
		"         #chat {color}      {color names}      Set the default color\n"
		"         #chat {decline}    {buddy}            Decline a file transfer\n"
		"         #chat {dnd}                           Decline new connections\n"
		"         #chat {download}   {directory}        Set your download directory\n"
		"         #chat {emote}      {buddy|all} {text} Send an emote message\n"
		"         #chat {forward}    {buddy}            Forward all chat messages\n"
		"         #chat {forwardall} {buddy}            Forward all session output\n"
		"         #chat {filestat}   {buddy}            Show file transfer data\n"
		"         #chat {group}      {buddy} {name}     Assign a chat group\n"
		"         #chat {ignore}     {buddy}            Ignores someone\n"
		"         #chat {info}                          Displays your info\n"
		"         #chat {ip}         {address}          Changes your IP address\n"
		"         #chat {paste}      {buddy|all} {text} Pastes a block of text\n"
		"         #chat {peek}       {buddy}            Show one's public connections\n"
		"         #chat {ping}       {buddy}            Display response time\n"
		"         #chat {private}    {buddy|all}        Make a connection private\n"
		"         #chat {public}     {buddy|all}        Make a connection public\n"
		"         #chat {reply}      {text}             Reply to last private message\n"
		"         #chat {request}    {buddy}            Request one's public connections\n"
		"         #chat {send}       {buddy|all} {text} Sends a raw data string\n"
		"         #chat {sendfile}   {buddy} {filename} Start a file transfer\n"
		"         #chat {serve}      {buddy}            Forward all public chat messages\n"
		"         #chat {uninitialize}                  Uninitialize the chat port.\n"
		"         #chat {who}                           Show all connections\n"
		"         #chat {zap}        {buddy}            Close a connection\n"
		"\n"
		"         Display color of chat text can be changed by user.\n" 
		"         <<888>K84> and <<888>K85> are user-defined color code used to display chat text.\n"
		"         #var {_TK84}  {<<888>007>} will display black on white chat text.\n"
	},
	{
		"CLASS",
		"<K82>Command<K81>: #class <K82>{<K81>name<K82>}<K81> <K82>{<K81>open<K82>|<K81>close<K82>|<K81>list<K82>|<K81>read filename<K82>|<K81>write filename<K82>|<K81>kill<K82>}<K81>\n"
		"\n"
		"         The {open} option will open a class, closing a previously opened\n"
		"         class. All triggers added afterwards are assigned to this class.\n"
		"         The {close} option will close the given class.\n"
		"         The {list} option will show the given list of the class.\n"
		"         The {read} option will open the class, read, and close afterwards.\n"
		"         The {write} option will write all triggers of the given class to file.\n"
		"         The {kill} option will delete all triggers of the given class.\n"
		"\n"
		"         Keep in mind that the kill and read option are very fast allowing\n"
		"         them to be used to enable and disable classes.\n"
		"\n"
		"<K82>Example<K81>: #class extra kill;#class extra read extra.tin\n"
		"         Deletes all triggers of 'extra' class if any. Read 'extra.tin' file,\n"
		"         all triggers loaded will be assigned to the fresh new 'extra' class.\n"
	},
	{
		"COLORS",
		"<K82>Syntax<K81>:  <<888>xyz>  with x, y, z being parameters\n"
		"\n"
		"         Parameter 'x': VT100 code\n"
		"\n"
		"         0 - Reset all colors and codes to default\n"
		"         1 - Bold\n"
		"         2 - Dim\n"
		"         4 - Underscore\n"
		"         5 - Blink\n"
		"         7 - Reverse\n"
		"         8 - Skip (use previous code)\n"
		"\n"
		"         Parameter 'y':  Foreground color\n"
		"         Parameter 'z':  Background color\n"
		"\n"
		"         0 - Black                5 - Magenta\n"
		"         1 - Red                  6 - Cyan\n"
		"         2 - Green                7 - White\n"
		"         3 - Yellow               8 - Skip\n"
		"         4 - Blue                 9 - Default\n"
		"\n"
		"         For xterm 256 colors support use <<888>aaa> to <<888>fff> for RGB foreground\n"
		"         colors and <<888>AAA> to <<888>FFF> for RGB background colors. For the grayscale\n"
		"         foreground colors use <<888>g00> to <<888>g23>, for grayscale background colors\n"
		"         use <<888>G00> to <<888>G23>.\n"
		"\n"
		"         The tertiary colors are as follows:\n"
		"\n"
		"         <<888>acf> - Azure            <<888>afc> - Jade\n"
		"         <<888>caf> - Violet           <<888>cfa> - Lime\n"
		"         <<888>fac> - Pink             <<888>fca> - Orange\n"
		"\n"
		"<K82>Example<K81>: #showme <<888>acf>Azure    <<888>afc>Jade     <<888>caf>Violet\n"
		"<K82>Example<K81>: #showme <<888>cfa>Lime     <<888>fac>Pink     <<888>fca>Orange\n"
		"\n"
		"         To use 24 bit true colors on termimal that supports it, use <<888>xhhhhhh> code\n" 
		"         for foreground RGB color and  <<888>Xhhhhhh> code for background RGB color.\n"
		"         hhhhhh is 3 bytes RGB color in six digits hexadecimal number. \n"
		"         Hex digit is 0-9, a-f, A-F range and case-ignored.\n"
		"\n"
		"         Color code <<888>K00>-<<888>K99> are user-definded color code.\n"
		"         User can set actual color of <<888>K00>-<<888>K99> color code by setting \n"
		"         ${_TK00}-${_TK99} global variables. <<888>K80>-<<888>K99> codes are resrved\n"
		"         for help / chat colors and future internal use.\n"
		"\n"
		"<K82>Example<K81>: #showme <<888>xFF69B4>Pink text and  <<888>XE0FFFF>Light cyan BG\n"
		"<K82>Example<K81>: #var {_TK04} {<<888>118>}; #showme <<888>K04>Bold Red color\n"
	},
	{
		"CONFIG",
		"<K82>Command<K81>: #config <K82>{<K81>option<K82>}<K81> <K82>{<K81>argument<K82>}<K81>\n"
		"\n"
		"         This allows you to configure various settings, the settings can be\n"
		"         written to file with the #write or #writesession command.\n"
		"\n"
		"         If you configure the global session (the one you see as you start up\n"
		"         tintin) all sessions started will inherite these settings.\n"
		"\n"
		"         It's advised to make a configuration file to read on startup if you\n"
		"         do not like the default settings.\n"
		"\n"
		"         Config options which aren't listed by default:\n"
		"\n"
		"         #CONFIG {CONVERT META} {ON|OFF} Shows color codes and key bindings.\n"
		"         #CONFIG {COLOR PATCH}  {ON|OFF} Fixes color code usage on some muds.\n"
		"         #CONFIG {DEBUG TELNET} {ON|OFF} Shows telnet negotiations y/n.\n"
		"         #CONFIG {LOG LEVEL}  {LOW|HIGH} LOW logs mud output before triggers.\n"
		"         #CONFIG {MCCP}         {ON|OFF} Enable or disable MCCP support.\n"
	},
	{
		"CONTINUE",
		"<K82>Command<K81>: #continue\n"
		"\n"
		"         The continue command can be used inside the #FOREACH, #LOOP, #PARSE,\n"
		"         #WHILE and #SWITCH commands. When #CONTINUE is found, tintin will go\n"
		"         to the end of the command and proceed as normal, which may be to\n"
		"         reiterate the command.\n"
		"\n"
		"<K82>Example<K81>: #loop 1 10 cnt {#if {$cnt % 2 == 0} {#continue} {say $cnt}}\n"
	},
	{
		"CR",
		"<K82>Command<K81>: #cr\n"
		"\n"
		"         Sends a carriage return to the session.  Useful for aliases that need\n"
		"         extra carriage returns.\n"
	},
	{
		"CURSOR",
		"<K82>Command<K81>: #cursor <K82>{<K81>option<K82>}<K81> <K82>{<K81>argument<K82>}<K81>\n"
		"\n"
		"         Typing #cursor without an option will show all available cursor\n"
		"         options. The cursor command's primarly goal is adding customizable\n"
		"         input editing with macros.\n"
	},
	{
		"DEBUG",
		"<K82>Command<K81>: #debug <K82>{<K81>listname<K82>}<K81> <K82>{<K81>on<K82>|<K81>off<K82>|<K81>log<K82>}<K81>\n"
		"\n"
		"         Toggles a list on or off. With no argument it shows your current\n"
		"         settings, as well as the list names that you can debug.\n"
		"\n"
		"         If you for example set ACTIONS to ON you will get debug information\n"
		"         whenever an action is triggered.\n"
		"\n"
		"         #debug {listname} {log} will silently write debugging information to\n"
		"         the log file, you must be logging in order for this to work.\n"
		"\n"
		"         Not every list has debug support yet.\n"
	},
	{
		"DEFAULT",
		"<K82>Command<K81>: #default <K82>{<K81>commands<K82>}<K81>\n"
		"\n"
		"         The default command can only be used within the switch command. When\n"
		"         the conditional argument of non of the case commands matches the switch\n"
		"         command's conditional statement the default command is executed.\n"
	},
	{
		"DELAY",
		"<K82>Command<K81>: #delay <K82>{<K81>seconds<K82>}<K81> <K82>{<K81>command<K82>}<K81>\n"
		"<K82>Command<K81>: #delay <K82>{<K81>name<K82>}<K81> <K82>{<K81>command<K82>}<K81> <K82>{<K81>seconds<K82>}<K81> \n"
		"\n"
		"         Delay allows you to have tintin wait the given amount of seconds\n"
		"         before executing the given command. tintin won't wait before\n"
		"         executing following input commands if any.\n"
		"\n"
		"         Floating point precision for miliseconds is possible.\n"
		"\n"
		"<K82>Example<K81>: #showme first;#delay {1} {#showme last}\n"
		"         This will print 'first', and 'last' around one second later.\n"
		"\n"
		"<K82>Comment<K81>: If you want to remove a delay with the #undelay command you can add\n"
		"         a name as the first argument, be aware this changes the syntax.\n"
	},
	{
		"ECHO",
		"<K82>Command<K81>: #echo <K82>{<K81>format<K82>}<K81> <K82>{<K81>argument1<K82>} {<K81>argument2<K82>} {<K81>etc<K82>}<K81>\n"
		"\n"
		"         Echo command displays text on the screen with formatting options. See\n"
		"         the help file for the format command for more informations.\n"
		"\n"
		"         The echo command does not trigger actions.\n"
		"\n"
		"         As with the #showme command you can split the {format} argument up into\n"
		"         two braced arguments, in which case the 2nd argument is the row number.\n"
		"\n"
		"<K82>Example<K81>: #echo {The current date is %t.} {%Y-%m-%d %H:%M:%S}\n"
		"         #echo {[%38s][%-38s]} {Hello World} {Hello World}\n"
		"         #echo {{this is %s on the top row} {-1}} {printed}\n"
	},
	{
		"ELSE",
		"<K82>Command<K81>: #else <K82>{<K81>commands<K82>}<K81>\n"
		"\n"
		"         The else statement should follow an #IF or #ELSEIF statement and is\n"
		"         only called if the proceeding #IF or #ELSEIF is false.\n"
		"\n"
		"<K82>Example<K81>: #if {1d2 == 1} {smile};#else {grin}\n"
	},
	{
		"ELSEIF",
		"<K82>Command<K81>: #elseif <K82>{<K81>conditional<K82>}<K81> <K82>{<K81>commands<K82>}<K81>\n"
		"\n"
		"         The elseif statement should follow an #IF or #ELSEIF statement and is\n"
		"         only called when the statement is true and the proceeding #IF and\n"
		"         #ELSEIF statements are false.\n"
		"\n"
		"<K82>Example<K81>: #if {1d3 == 1} {smirk};#elseif {1d2 == 1} {snicker}\n"
	},
	{
		"END",
		"<K82>Command<K81>: #end {<message>}\n"
		"\n"
		"         Terminates tintin and return to unix.  On most systems, ctrl-c has\n"
		"         the same result.\n"
		"\n"
		"         The message is optional and is printed before tintin exits. When\n"
		"         using #end {\\} tintin will terminate silently.\n"
	},
	{
		"ESCAPE CODES",
		"         You may use the escape character \\ for various special characters.\n"
		"\n"
		"         \\a   will beep the terminal.\n"
		"         \\c   will send a control character, \\ca for ctrl-a.\n"
		"         \\e   will start an escape sequence.\n"
		"         \\n   will send a line feed.\n"
		"         \\r   will send a carriage return.\n"
		"         \\t   will send a tab.\n"
		"         \\x   will print a hexadecimal value, \\xFF for example.\n"
		"         \\x7B will send the '{' character.\n"
		"         \\x7D will send the '}' character.\n"
		"\n"
		"         Ending a line with \\ will stop tintin from appending a line feed.\n"
		"         To escape arguments in an alias or action use %%0 %%1 %%2 etc.\n"
	},
	{
		"EVENT",
		"<K82>Command<K81>: #event <K82>{<K81>event type<K82>}<K81>\n"
		"\n"
		"         Events allow you to create triggers for predetermined client events.\n"
		"         Use #event without an argument to see a list of possible events with\n"
		"         a brief description. Use #event %* to see the current list of defined\n"
		"         events.\n"
		"\n"
		"         CHAT MESSAGE          %0 default %1 plain\n"
		"         DATE                  %1 month - %3 day   %4 hour : %5 minute\n"
		"         DAY                   %3 day\n"
		"         END OF PATH\n"
		"         HOUR                  %4 hour\n"
		"         IAC <VAR> <VAR>\n"
		"         IAC SB GMCP <MODULE>  %0 data     %1 raw data\n"
		"         IAC SB MSSP           %0 variable %1 value\n"
		"         IAC SB MSDP           %0 variable %1 value\n"
		"         IAC SB MSDP <VAR>     %1 value\n"
		"         IAC SB NEW-ENVIRON    %0 variable %1 value\n"
		"         IAC SB ZMP <VAR>      %0 value\n"
		"         IAC SB <VAR>          %0 raw text %1 raw data\n"
		"         MAP ENTER ROOM        %0 new vnum %1 old vnum\n"
		"         MAP ENTER ROOM <VAR>  %0 new vnum %1 old vnum\n"
		"         MAP EXIT ROOM         %0 old vnum %1 new vnum\n"
		"         MAP EXIT ROOM <VAR>   %0 old vnum %1 new vnum\n"
		"         MINUTE                %5 minute\n"
		"         MONTH                 %1 month\n"
		"         PORT CONNECTION       %0 name %1 ip %2 port\n"
		"         PORT DISCONNECTION    %0 name %1 ip %2 port\n"
		"         PORT MESSAGE          %0 name %1 ip %2 port %3 data %4 raw data\n"
		"         PROGRAM START         %0 client name %1 client version\n"
		"         PROGRAM TERMINATION\n"
		"         RECEIVED INPUT        %0 raw text\n"
		"         RECEIVED LINE         %0 raw text %1 plain text\n"
		"         RECEIVED OUTPUT       %0 raw text\n"
		"         RECEIVED PROMPT       %0 raw text %1 plain text\n"
		"         SCREEN RESIZE         %0 cols %1 rows\n"
		"         SECOND                %6 second\n"
		"         SEND OUTPUT           %0 raw text\n"
		"         SESSION ACTIVATED     %0 name\n"
		"         SESSION CONNECTED     %0 name %1 host %2 ip %3 port\n"
		"         SESSION CREATED       %0 name %1 host %2 ip %3 port\n"
		"         SESSION DEACTIVATED   %0 name\n"
		"         SESSION DISCONNECTED  %0 name %1 host %2 ip %3 port\n"
		"         SESSION TIMED OUT     %0 name %1 host %2 ip %3 port\n"
		"         TIME                  %4 hour : %5 minute : %6 second\n"
		"         VARIABLE UPDATE <VAR> %0 name %1 value\n"
		"         WEEK                  %2 week\n"
		"         YEAR                  %0 year\n"
		"\n"
		"<K82>Example<K81>: #event {SESSION CONNECTED} {#read mychar.tin}\n"
		"\n"
		"<K82>Comment<K81>: You can remove an event with the #unevent command.\n"
	},
	{
		"FORALL",
		"<K82>Command<K81>: #forall <K82>{<K81>list<K82>}<K81> <K82>{<K81>commands<K82>}<K81>\n"
		"\n"
		"         List elements must either be separated by braces or semicolons.\n"
		"\n"
		"<K82>Example<K81>: #forall {a;b;c;d} {say &0}\n"
		"<K82>Example<K81>: #forall {{a}{b}{c}{d}} {say &0}\n"
		"         Both equal: say a;say b;say c;say d\n"
	},
	{
		"FOREACH",
		"<K82>Command<K81>: #foreach <K82>{<K81>list<K82>} {<K81>variable<K82>} {<K81>commands<K82>}<K81>\n"
		"\n"
		"         For each item in the provided list the foreach statement will update\n"
		"         the given variable and execute the command part of the statement. List\n"
		"         elements must be separated by braces or semicolons.\n"
		"\n"
		"<K82>Example<K81>: #foreach {bob;tim;kim} {name} {tell $name Hello}\n"
		"<K82>Example<K81>: #foreach {{bob}{tim}{kim}} {name} {tell $name Hello}\n"
	},
	{
		"FORMAT",
		"<K82>Command<K81>: #format <K82>{<K81>variable<K82>}<K81> <K82>{<K81>format<K82>}<K81> <K82>{<K81>argument1<K82>} {<K81>argument2<K82>} {<K81>etc<K82>}<K81>\n"
		"\n"
		"         Allows you to store a string into a variable in the exact same way\n"
		"         C's sprintf works with a few enhancements and limitations such as\n"
		"         no integer operations and a maximum of 20 arguments. If you use format\n"
		"         inside an alias or action you must escape the %0-9 like: %+4s.\n"
		"\n"
		"         #format {test} {%+9s} {string}  pad string with up to 9 spaces\n"
		"         #format {test} {%-9s} {string}  post pad string with up to 9 spaces\n"
		"         #format {test} {%.8s} {string}  copy at most 8 characters\n"
		"         #format {test} {%a}   {number}  print corresponding ascii character\n"
		"         #format {test} {%c}   {string}  use a highlight color name\n"
		"         #format {test} {%d}   {number}  print a number with integer formatting\n"
		"         #format {test} {%f}   {string}  perform floating point math\n"
		"         #format {test} {%g}   {number}  perform thousand grouping on {number}\n"
		"         #format {test} {%h}   {string}  turn text into a header line\n"
		"         #format {test} {%l}   {string}  lowercase text\n"
		"         #format {test} {%m}   {string}  perform mathematical calculation\n"
		"         #format {test} {%n}     {name}  capitalize the first letter\n"
		"         #format {test} {%p}   {string}  strip leading and trailing spaces\n"
		"         #format {test} {%r}   {string}  reverse text, hiya = ayih\n"
		"         #format {test} {%s}   {string}  print given string\n"
		"         #format {test} {%t}   {format}  display time with strftime format\n"
		"                                         optional {{format}{time}} syntax\n"
		"         #format {test} {%u}   {string}  uppercase text\n"
		"         #format {list} {%w}   {string}  store wordwrapped text in {list}\n"
		"                                         optional {{string}{width}} syntax\n"
		"         #format {test} {%A}     {char}  print corresponding ascii value\n"
		"         #format {cols} {%C}         {}  store the screen width in {cols}\n"
		"         #format {hash} {%H}   {string}  store a 32 bit string hash in {hash}\n"
		"         #format {test} {%L}   {string}  store the string length in {test}\n"
		"         #format {rows} {%R}         {}  store the screen height in {rows}\n"
		"         #format {time} {%T}         {}  store the epoch time in {time}\n"
		"         #format {time} {%U}         {}  store the micro epoch time in {time}\n"
	},
	{
		"FUNCTION",
		"<K82>Command<K81>: #function <K82>{<K81>name<K82>}<K81> <K82>{<K81>operation<K82>}<K81>\n"
		"\n"
		"         Functions allow you to execute a script within a line of text, and\n"
		"         replace the function call with the line of text generated by the\n"
		"         function.\n"
		"\n"
		"         Be aware that each function should set the $result variable at the\n"
		"         end of the function, or call #return with the given result.\n"
		"\n"
		"         To use a function use the @ character before the function name.\n"
		"         The function arguments should be placed between braces behind the\n"
		"         function name with argument separated by semicolons.\n"
		"\n"
		"         The function itself can use the provided arguments which are stored\n"
		"         in %1 to %9, with %0 holding all arguments.\n"
		"\n"
		"<K82>Example<K81>: #function {rnd} {#math {result} {1 d (%2 - %1 + 1) + %1 - 1}}\n"
		"         #showme A random number between 100 and 200: @rnd{100;200}\n"
		"\n"
		"<K82>Example<K81>: #function gettime {#format result %t %H:%M}\n"
		"         #showme The current time is @gettime{}\n"
		"\n"
		"<K82>Comment<K81>: You can remove a function with the #unfunction command.\n"
	},
	{
		"GAG",
		"<K82>Command<K81>: #gag <K82>{<K81>string<K82>}<K81>\n"
		"\n"
		"         Removes any line that contains the string.\n"
		"\n"
		"<K82>Comment<K81>: See '#help action', for more information about triggers.\n"
		"\n"
		"<K82>Comment<K81>: You can remove a gag with the #ungag command.\n"
	},
/*
	{
		"GREETING",
		"<068>      #<068>##################################################################<068>#\n"
		"<068>      #<078>                                                                  <068>#\n"
		"<068>      #<078>                     T I N T I N + +   "CLIENT_VERSION"                   <068>#\n"
		"<068>      #<078>                                                                  <068>#\n"
		"<068>      #<078>           (<068>T<078>)he k(<068>I<078>)cki(<068>N<078>) (<068>T<078>)ickin d(<068>I<078>)kumud clie(<068>N<078>)t <068>          #\n"
		"<068>      #<078>                                                                  <068>#\n"
		"<068>      #<078>     Code by Peter Unold, Bill Reis, and Igor van den Hoven.      <068>#\n"
		"<068>      #<078>                                                                  <068>#\n"
		"<068>      #<078>                             1992, 2012                           <068>#\n"
		"<068>      #<068>##################################################################<068>#<088>\n"
	},
*/

	{
		"GREETING",
		"<K83>      #<K83>##################################################################<K83>#\n"
		"<K83>      #<K81>                     T I N T I N + +   "CLIENT_VERSION"                   <K83>#\n"
		"<K83>      #<K81>                                                                  <K83>#\n"
//		"<068>      #<078>           (<068>T<078>)he k(<068>I<078>)cki(<068>N<078>) (<068>T<078>)ickin d(<068>I<078>)kumud clie(<068>N<078>)t <068>          #\n"
		"<K83>      #<K81>                 <K83>T<K81>he K<K83>i<K81>cki<K83>n<K81> <K83>T<K81>ickin D<K83>i<K81>kuMUD Clie<K83>n<K81>t <K83>                #\n"
		"<K83>      #<K81>                                                                  <K83>#\n"
		"<K83>      #<K81>      Code by Peter Unold, Bill Reis, and Igor van den Hoven      <K83>#\n"
		"<K83>      #<K83>##################################################################<K83>#<088>\n"
	},
	{
		"GREP",
		"<K82>Command<K81>: #grep <K82>[<K81>page<K82>]<K81> <K82>{<K81>search string<K82>}<K81>\n"
		"\n"
		"         This command allows you to search for matching lines in your scroll\n"
		"         back buffer. The amount of matches shown equals your screen size. If\n"
		"         you want to search back further use the optional page number. You can\n"
		"         use wildcards for better search results. Be aware the search string\n"
		"         is case sensitive, which can be disabled by using %i.\n"
		"\n"
		"         By default grep searches from the end of the scrollback buffer to the\n"
		"         beginning, this can be reversed by using a negative page number.\n"
		"\n"
		"<K82>Example<K81>: #grep Bubba tells you\n"
		"         This will show all occasions where bubba tells you something.\n"
	},
	{
		"HELP",
		"<K82>Command<K81>: #help <K82>{<K81>subject<K82>}<K81>\n"
		"\n"
		"         Without an argument #help will list all available help subjects.\n"
		"\n"
		"         Using #help %* will display all help entries.\n"
		"\n"
		"         Display color of help keyword and text can be changed by user.\n" 
		"         <<888>K81>, <<888>K82>, <<888>K83> are user-defined color code used to display help text.\n"
		"         #var {_TK81}  {<<888>007>} will display black on white help text.\n"
	},
	{
		"HIGHLIGHT",
		"<K82>Command<K81>: #highlight <K82>{<K81>string<K82>}<K81> <K82>{<K81>color names<K82>}<K81>\n"
		"\n"
		"         The highlight command is used to allow you to highlight strings of text\n"
		"         from the mud.  Available ANSI color names are:\n"
		"\n"
		"         reset, light, dark, underscore, blink, reverse\n"
		"\n"
		"         black, red, green, yellow, blue, magenta, cyan, white,\n"
		"         b black, b red, b green, b yellow, b blue, b magenta, b cyan, b white\n"
		"\n"
		"         Available XTERM 256 color names are:\n"
		"\n"
		"         azure, ebony, jade, lime, orange, pink, silver, tan, violet,\n"
		"         light azure, light ebony, light jade, light lime, light orange,\n"
		"         light pink, light silver, light tan, light violet.\n"
		"\n"
		"         The %1-99 variables can be used as 'wildcards' that will match with any\n"
		"         text. They are useful for highlighting a complete line. The %0 variable\n"
		"         should never be used in highlights.\n"
		"\n"
		"         You may start the string to highlight with a ^ to only highlight text\n"
		"         if it begins the line.\n"
		"\n"
		"         Besides color names also <<888>abc> color codes can be used.\n"
		"\n"
		"<K82>Example<K81>: #high {Valgar} {reverse}\n"
		"         Prints every occurrence of 'Valgar' in reverse video.\n"
		"\n"
		"<K82>Example<K81>: #high {^You %1} {bold cyan}\n"
		"         Boldfaces any line that starts with 'You' in cyan.\n"
		"\n"
		"<K82>Example<K81>: #high {Bubba} {red underscore blink}\n"
		"         Highlights the name Bubba as blinking, red, underscored text\n"
		"\n"
		"<K82>Comment<K81>: See '#help action', for more information about triggers.\n"
		"\n"
		"<K82>Comment<K81>: See '#help substitute', for more advanced color substitution.\n"
		"\n"
		"<K82>Comment<K81>: This command only works with ANSI/VT100 terminals or emulators.\n"
		"\n"
		"<K82>Comment<K81>: You can remove a highlight with the #unhighlight command.\n"
	},
	{
		"HISTORY",
		"<K82>Command<K81>: #history <K82>{<K81>delete<K82>}<K81>                 Delete the last command.\n"
		"         #history <K82>{<K81>insert<K82>}    {<K81>command<K82>}<K81>    Insert a command.\n"
		"         #history <K82>{<K81>list<K82>}<K81>                   Display the entire command history.\n"
		"         #history <K82>{<K81>read<K82>}      {<K81>filename<K82>}<K81>   Read a command history from file.\n"
		"         #history <K82>{<K81>write<K82>}     {<K81>filename<K82>}<K81>   Write a command history to file.\n"
		"\n"
		"         Without an argument all available options are shown.\n"
	},
	{
		"IF",
		"<K82>Command<K81>: #if <K82>{<K81>conditional<K82>}<K81> <K82>{<K81>commands if true<K82>}<K81> <K82>{<K81>commands if false<K82>}<K81>\n"
		"\n"
		"         The 'if' command is one of the most powerful commands added since\n"
		"         TINTIN III. It works similar to an 'if' statement in other languages,\n"
		"         and is strictly based on the way C handles its conditional statements.\n"
		"         When an 'if' command is encountered, the conditional statement is\n"
		"         evaluated, and if TRUE (any non-zero result) the commands are executed.\n"
		"\n"
		"         The 'if' statement is only evaluated if it is read, so you must nest\n"
		"         the 'if' statement inside another statement (most likely an 'action'\n"
		"         command). The conditional is evaluated exactly the same as in the\n"
		"         'math' command only instead of storing the result, the result is used\n"
		"         to determine whether to execute the commands.\n"
		"\n"
		"<K82>Example<K81>: #action {%0 gives you %1 gold coins.} {#if {%1>5000} {thank %0}}\n"
		"         If someone gives you more than 5000 coins, thank them.\n"
		"\n"
		"<K82>Comment<K81>: See '#help math', for more information.\n"
	},
	{
		"IGNORE",
		"<K82>Command<K81>: #ignore <K82>{<K81>listname<K82>}<K81> <K82>{<K81>on<K82>|<K81>off<K82>}<K81>\n"
		"\n"
		"         Toggles a list on or off. With no arguments it shows your current\n"
		"         settings, as well as the list names that you can ignore.\n"
		"\n"
		"         If you for example set ACTIONS to OFF actions will no longer trigger.\n"
		"         Not every list can be ignored.\n"
	},
	{
		"INFO",
		"<K82>Command<K81>: #info\n"
		"\n"
		"         Displays all the settings of every tintin list available.\n"
		"\n"
		"Trivia:  Typing: #info cpu will show information about tintin's cpu usage.\n"
	},
	{
		"KILL",
		"<K82>Command<K81>: #kill <K82>{<K81>list<K82><K82>} {<K81>pattern<K82>}<K81>\n"
		"\n"
		"         Without an argument, the kill command clears all lists.  Useful if\n"
		"         you don't want to exit tintin to reload your command files.\n"
		"\n"
		"         With one argument a specific list can be cleared.\n"
		"\n"
		"         With two arguments the triggers in the chosen list that match the\n"
		"         given pattern will be removed.\n"
		"\n"
		"<K82>Example<K81>: #kill alias %*test*\n"
	},
	{
		"LINE",
		"<K82>Command<K81>: #line <K82>{<K81>option<K82>}<K81> <K82>{<K81>argument<K82>}<K81>\n"
		"\n"
		"         #line log {filename} {[text]}          Log the current or given line to\n"
		"                                                file.\n"
		"\n"
		"         #line logverbatim {filename} {[text]}  Like log with no substitutions.\n"
		"\n"
		"         #line gag                              Gag the next line.\n"
		"\n"
		"         #line ignore {argument}                Argument is executed without\n"
		"                                                any triggers being checked.\n"
		"\n"
		"         #line quiet {argument}                 Argument is executed with\n"
		"                                                suppression of system messages.\n"
		"\n"
		"         #line strip {argument}                 Strips the argument of color\n"
		"                                                codes next executes it as a\n"
		"                                                command.\n"
		"\n"
		"         #line substitute {options} {argument}  Substitutes the given options:\n"
		"                                                variables, functions, colors,\n"
		"                                                escapes, secure, in the given\n"
		"                                                argument next executes it as a\n"
		"                                                command.\n"
		"\n"
		"         #line verbose {argument}               Argument is executed verbose.\n"
		"\n"
		"         When using #line log and logging in html format use \\c< \\c> \\c& \\c\" to\n"
		"         log a literal < > & and \".\n"
	},
	{
		"LIST",
		"<K82>Command<K81>: #list <K82>{<K81>variable<K82>}<K81> <K82>{<K81>option<K82>}<K81> <K82>{<K81>argument<K82>}<K81>\n"
		"\n"
		"         #list {var} {add} {item}               Add {item} to the list\n"
		"         #list {var} {clear}                    Empty the given list\n"
		"         #list {var} {create} {item}            Create a list using {items}\n"
		"         #list {var} {delete} {index} {number}  Delete the item at {index},\n"
		"                                                the {number} is optional.\n"
		"         #list {var} {insert} {index} {string}  Insert {string} at given index\n"
		"         #list {var} {find} {string} {variable} Return the found index\n"
		"         #list {var} {get} {index} {variable}   Copy an item to {variable}\n"
		"         #list {var} {set} {index} {string}     Change the item at {index}\n"
		"         #list {var} {simplify} {variable}      Copy simple list to {variable}\n"
		"         #list {var} {size} {variable}          Copy list size to {variable}\n"
		"         #list {var} {sort} {string}            Insert item in alphabetic order\n"
		"         #list {var} {tokenize} {string}        Create a character list\n"
		"\n"
		"         The index should be between 1 and the list's length. You can also give\n"
		"         a negative value, in which case -1 equals the last item in the list, -2\n"
		"         the second last, etc.\n"
		"\n"
		"         When inserting an item a positive index will prepend the item at the\n"
		"         given index, while a negative index will append the item.\n"
		"\n"
		"         The add and create options allow using multiple items, as well\n"
		"         as semicolon separated items.\n"
		"\n"
		"         A length of 0 is returned for an empty or non existant list.\n"
		"\n"
		"         You can directly access elements in a list variable using $var[1],\n"
		"         $var[2], $var[-1], etc.\n"
	},

	{
		"LOCAL",
		"<K82>Command<K81>: #local <K82>{<K81>variable name<K82>}<K81> <K82>{<K81>text to fill variable<K82>}<K81>\n"
		"\n"
		"         The local command sets a local variable. Unlike a regular variable\n"
		"         a local variable will only stay in memory for the duration of the\n"
		"         event that created it. They are accessed in the same way as a\n"
		"         regular variable.\n"
		"\n"
		"         Commands that store information to a variable will use a local variable\n"
		"         if it exists.\n"
		"\n"
		"         Avoid setting the result variable as local in a function.\n"
		"\n"
		"<K82>Example<K81>: #alias {swap} {#local x %0;#replace x {e} {u};#showme $x}\n"
	},

	{
		"LOG",
		"<K82>Command<K81>: #log <K82>{<K81>append<K82>|<K81>overwrite<K82>}<K81> <K82>{<K81>filename<K82>}<K81>\n"
		"\n"
		"         Logs session to a file, you can set the data type to either plain,\n"
		"         raw, or html with the config command.\n"

	},

	{
		"LOOP",
		"<K82>Command<K81>: #loop <K82>{<K81><start><K82>} {<K81><finish><K82>} {<K81><variable><K82>} {<K81>commands<K82>}<K81>\n"
		"\n"
		"         Like a for statement, loop will loop from start to finish incrementing\n"
		"         or decrementing by 1 each time through.  The value of the loop counter\n"
		"         is stored in the provided variable, which you can use in the commands.\n"
		"\n"
		"<K82>Example<K81>: #loop 1 3 loop {get all $loop\\.corpse}\n"
		"         This equals 'get all 1.corpse;get all 2.corpse;get all 3.corpse'.\n"
		"\n"
		"         The . needs to be escaped so it's not treated as part of the variable.\n"
		"\n"
		"<K82>Example<K81>: #loop 3 1 cnt {drop $cnt\\.key}\n"
		"         This equals 'drop 3.key;drop 2.key;drop 1.key'.\n"
	},
	{
		"MACRO",
		"<K82>Command<K81>: #macro <K82>{<K81>key sequence<K82>}<K81> <K82>{<K81>commands<K82>}<K81>\n"
		"\n"
		"         Macros allow you to make tintin respond to function keys.\n"
		"\n"
		"         The key sequence send to the terminal when pressing a function key\n"
		"         differs for every OS and terminal. To find out what sequence is send\n"
		"         you can enable the CONVERT META config option.\n"
		"\n"
		"         Another option is pressing ctrl-v, which will enable CONVERT META for\n"
		"         the next key pressed.\n"
		"\n"
		"<K82>Example<K81>: #macro {(press ctrl-v)(press F1)} {#showme \\e[2J;#buffer lock}\n"
		"         Clear the screen and lock the window when you press F1, useful when the\n"
		"         boss is near.\n"
		"\n"
		"<K82>Example<K81>: #macro {\\eOM} {#cursor enter}\n"
		"         Makes the keypad's enter key work as an enter in keypad mode.\n"
		"\n"
		"<K82>Comment<K81>: Not all terminals properly initialize the keypad key sequences.\n"
		"         If this is the case you can still use the keypad, but instead of the\n"
		"         arrow keys use ctrl b, f, p, and n.\n"
		"\n"
		"<K82>Comment<K81>: You can remove a macro with the #unmacro command.\n"
	},
	{
		"MAP",
		"<K82>Command<K81>: #map\n"
		"\n"
		"         The map command is the backbone of the auto mapping feature. In order\n"
		"         to use mapping for muds using 'ne' 'se' 'sw' 'nw' directions, you need\n"
		"         to create a #pathdir for each direction.\n"
		"\n"
		"         #map at <location> <command>: Execute the command at the location.\n"
		"\n"
		"         #map color <field> value: Sets the map color for the given field.\n"
		"\n"
		"         #map create <size>: Creates a new map and room 1, required to start\n"
		"                  mapping. Default size is 50000 rooms.\n"
		"\n"
		"         #map destroy: Deletes the map.\n"
		"\n"
		"         #map delete <direction|vnum>: Deletes the room in the given direction.\n"
		"\n"
		"         #map dig <direction|vnum> [new|<vnum>]: Creates an exit in the given\n"
		"                  direction. If no valid direction is given or no existing room\n"
		"                  is found a new room is created. Useful for portal links and\n"
		"                  other alternative forms of transportation. If the 'new'\n"
		"                  argument is provided all existing rooms are ignored. If a\n"
		"                  room vnum is given as the second argument an exit will be\n"
		"                  created to the given room vnum. If the direction argument is\n"
		"                  a valid unused vnum that room is created.\n"
		"\n"
		"         #map exit <exit> <COMMAND|DIRECTION|FLAG|GET|NAME|SAVE|SET|VNUM> <arg>\n"
		"                  Set the exit data. Useful with a closed door where you can\n"
		"                  set the exit command: '#map exit e command {open east;e}'.\n"
		"\n"
		"         #map exitflag <exit> <HIDE|AVOID> [on|off]\n"
		"                  Set exit flags. See #map roomflag for more info.\n"
		"\n"
		"         #map explore <direction>: Follows the direction until a dead end or an\n"
		"                  intersection is found. The route is stored in #path and can\n"
		"                  subsequently be used with #walk\n"
		"\n"
		"         #map find <name> <exits> <desc> <area> <note> <terrain> <flag>\n"
		"                  searches for the given room name. If found the shortest path\n"
		"                  from your current location to the destination is calculated.\n"
		"                  The route is stored in #path and can subsequently be used with\n"
		"                  the various #path commands. If <exits> is provided all exits\n"
		"                  must be matched, if <roomdesc>, <roomarea> or <roomnote> or\n"
		"                  <roomterrain> or <roomflag> is provided these are matched as\n"
		"                  well against the room to be found.\n"
		"                  These options are also available to the goto, run, delete, at\n"
		"                  and link commands.\n"
		"\n"
		"         #map flag asciigraphics: Draws a smaller but more detailed map that\n"
		"                  displays the ne se sw nw exits and room symbols.\n"
		"\n"
		"         #map flag asciivnums: Display room vnums if asciigraphics is enabled.\n"
		"\n"
		"         #map flag nofollow: When you enter movement commands the map will no\n"
		"                  longer automatically follow along. Useful for MSDP and GMCP\n"
		"                  automapping scripts.\n"
		"\n"
		"         #map flag static: Will make the map static so new rooms are no longer\n"
		"                  created when walking into an unmapped direction. Useful when\n"
		"                  you're done mapping and regularly bump into walls accidentally\n"
		"                  creating a new room. #map dig etc will still work.\n"
		"\n"
		"         #map flag vtgraphics: Enables vt line drawing on some terminals\n"
		"\n"
		"         #map flag vtmap: Will enable the vtmap which is shown in the top split\n"
		"                  screen if you have one. You can create a 16 rows high top\n"
		"                  screen by using '#split 16 1'.\n"
		"\n"
		"         #map goto <room vnum> [dig]: Takes you to the given room vnum, with the\n"
		"                  dig argument a new room will be created if non exists.\n"
		"\n"
		"         #map goto <name> <exits> <desc> <area> <note> <terrain>: Takes you to\n"
		"                  the given room name, if you provide exits those must match.\n"
		"\n"
		"         #map get <option> <variable> [vnum]: Store a map value into a\n"
		"                    variable, if no vnum is given the current room is used.\n"
		"\n"
		"         #map get roomexits <variable>: Store all room exits into variable.\n"
		"\n"
		"         #map info: Gives information about the map and room you are in.\n"
		"\n"
		"         #map insert <direction> [roomflag]: Insert a room in the given\n"
		"                  direction. Most useful for inserting void rooms.\n"
		"\n"
		"         #map jump <x> <y> <z>: Jump to the given coordinate, which is relative\n"
		"                  to your current room.\n"
		"\n"
		"         #map leave: Makes you leave the map. Useful when entering a maze. You\n"
		"                  can return to your last known room using #map return.\n"
		"\n"
		"         #map legenda <symbols>: The legend exists of 17 decimal numbers which\n"
		"                  represent character symbols used for drawing a map. Binary\n"
		"                  order is used with the n e s w representing bit 1 to 4. The\n"
		"                  first number stands for a no exit room. Number 2 to 16 stand\n"
		"                  for n e ne s ns es nes w nw ew new sw nsw esw nesw. The 17th\n"
		"                  number stands for the room the player is currently in.\n"
		"                  The legenda is set by default, but can be adjusted to take\n"
		"                  advantage of fonts with line drawing characters. To check your\n"
		"                  font for drawing characters use:\n"
		"                  #loop 32 255 cnt {#echo {%-3s  %a} $cnt $cnt}\n"
		"\n"
		"         #map link <direction> <room name> [both]: Links two rooms. If the both\n"
		"                  argument and a valid direction is given the link is two ways.\n"
		"\n"
		"         #map list <name> <exits> <desc> <area> <note> <terrain>\n"
		"                  Lists all matching rooms and their distance.\n"
		"\n"
		"                  Use {variable} {<variable>} to save the output to a variable.\n"
		"                  {roomname} {<name>}, {roomarea} {<area>}, etc, are valid too.\n"
		"\n"
		"         #map map {<x>x<y>} {filename} {a|v}: shows a map of surrounding rooms.\n"
		"                  The {horizontal x vertical} argument i.e 80x25 is optional,\n"
		"                  and so is the filename argument to log the map output to\n"
		"                  file. The {a} argument causes data to be appended so it can\n"
		"                  easily be tailed with the tail -f <file> shell command.\n"
		"                  The {v} argument causes the map to be stored as a variable,\n"
		"                  with filename being used as the variable name.\n"
		"\n"
		"         #map move <direction>: This does the same as an actual movement\n"
		"                  command, updating your location on the map and creating new\n"
		"                  rooms. Useful when you are following someone and want the map\n"
		"                  to follow. You will need to create actions using '#map move',\n"
		"                  for this to work.\n"
		"\n"
		"         #map read <filename>: Will load the given map file.\n"
		"\n"
		"         #map resize <size>: Resize the map, setting the maximum number of\n"
		"                  rooms.\n"
		"\n"
		"         #map return: Returns you to your last known room after leaving the map\n"
		"                  or loading a map.\n"
		"\n"
		"         #map roomflag avoid: When set, '#map find' will avoid a route leading\n"
		"                  through that room. Useful when you want to avoid death traps.\n"
		"         #map roomflag hide: When set, '#map' will not display the map beyond\n"
		"                  this room. When mapping overlapping areas or areas that aren't\n"
		"                  build consistently you need this flag as well to stop\n"
		"                  auto-linking, unless you use void rooms.\n"
		"         #map roomflag leave: When entering a room with this flag, you will\n"
		"                  automatically leave the map. Useful when set at the entrance\n"
		"                  of an unmappable maze.\n"
		"         #map roomflag void: When set the room becomes a spacing room that can\n"
		"                  be used to connect otherwise overlapping areas. A void room\n"
		"                  should only have two exits. When entering a void room you are\n"
		"                  moved to the connecting room until you enter a non void room.\n"
		"         #map roomflag static: When set the room will no longer be autolinked\n"
		"                  when walking around. Useful for mapping mazes.\n"
		"\n"
		"         #map run <room name> [delay]: Calculates the shortest path to the\n"
		"                  destination and walks you there. The delay is optional and\n"
		"                  requires using braces. Besides the room name a list of\n"
		"                  exits can be provided for more precise matching.\n"
		"\n"
		"         #map set <option> <value> [vnum]: Set a map value for your current\n"
		"                  room, or given room if a room vnum is provided.\n"
		"\n"
		"         #map travel <direction> <delay>: Follows the direction until a dead end\n"
		"                  or an intersection is found. Use braces around the direction\n"
		"                  if you use the delay, which will add the given delay between\n"
		"                  movements\n"
		"                  Use #undelay PATH %* to abort delayed movement.\n"
		"\n"
		"         #map undo: Will undo your last move. If this created a room or a link\n"
		"                  they will be deleted, otherwise you'll simply move back a\n"
		"                  room. Useful if you walked into a non existant direction.\n"
		"\n"
		"         #map uninsert <direction>: Exact opposite of the insert command.\n"
		"\n"
		"         #map unlink <direction> [both]: Will remove the exit, this isn't two\n"
		"                  way so you can have the map properly display no exit rooms and\n"
		"                  mazes.\n"
		"                  If you use the both argument the exit is removed two-ways.\n"
		"\n"
		"         #map vnum <low> [high]: Change the room vnum to the given number, if\n"
		"                  a range is provided the first available room in that range\n"
		"                  is selected.\n"
		"\n"
		"         #map write <filename>: Will save the map.\n"
	},
	{
		"MATH",
		"<K82>Command<K81>: #math <K82>{<K81>variable<K82>}<K81> <K82>{<K81>expression<K82>}<K81>\n"
		"\n"
		"         Performs math operations and stores the result in a variable.  The math\n"
		"         follows a C-like precedence, as follows, with the top of the list\n"
		"         having the highest priority.\n"
		"\n"
		"         Operators       Priority     Function\n"
		"         ------------------------------------------------\n"
		"         !               0            logical not\n"
		"         ~               0            bitwise not\n"
		"         *               1            integer multiply\n"
		"         **              1            integer power\n"
		"         /               1            integer divide\n"
		"         //              1            integer sqrt // 2 or cbrt // 3\n"
		"         %               1            integer modulo\n"
		"         d               1            integer random dice roll\n"
		"         +               2            integer addition\n"
		"         -               2            integer subtraction\n"
		"         <<              3            bitwise shift\n"
		"         >>              3            bitwise shift\n"
		"         >               4            logical greater than\n"
		"         >=              4            logical greater than or equal\n"
		"         <               4            logical less than\n"
		"         <=              4            logical less than or equal\n"
		"         ==              5            logical equal (can use regex)\n"
		"         !=              5            logical not equal (can use regex)\n"
		"          &              6            bitwise and\n"
		"          ^              7            bitwise xor\n"
		"          |              8            bitwise or\n"
		"         &&              9            logical and\n"
		"         ^^             10            logical xor\n"
		"         ||             11            logical or\n"
		"\n"
		"         True is any non-zero number, and False is zero.  Parentheses () have\n"
		"         highest precedence, so inside the () is always evaluated first.\n"
		"         Strings must be enclosed in \" \" and use regex with == and !=,\n"
		"         in the case of <= and >= the alphabetic order is compared.\n"
		"\n"
		"         The #if and #switch commands use #math. Several commands accepting\n"
		"         integer input allow math operations as well.\n"
		"\n"
		"         Floating point precision is added by using the decimal . operator.\n"
		"         Time in seconds is calculated using [day]:[hour]:<minute>:<second>.\n"
		"\n"
		"<K82>Example<K81>: #math {heals} {$mana / 40}\n"
		"         Assuming there is a variable $mana, divides its value by 40 and stores\n"
		"         the result in $heals.\n"
		"\n"
		"<K82>Example<K81>: #action {^You receive %0 experience} {updatexp %0}\n"
		"         #alias updatexp {#math {xpneed} {$xpneed - %0}\n"
		"         Let's say you have a variable which stores xp needed for your next\n"
		"         level.  The above will modify that variable after every kill, showing\n"
		"         the amount still needed.\n"
		"\n"
		"<K82>Example<K81>: #action {%0 tells %1}\n"
		"           {#if {\"\%0\" == \"Bubba\" && $afk} {reply I'm away, my friend.}}\n"
		"         When you are away from keyboard, it will only reply to your friend.\n"
	},
	{
		"MESSAGE",
		"<K82>Command<K81>: #message <K82>{<K81>listname<K82>}<K81> <K82>{<K81>on<K82>|<K81>off<K82>}<K81>\n"
		"\n"
		"         This will show the message status of all your lists if typed without an\n"
		"         argument. If you set for example VARIABLES to OFF you will no longer be\n"
		"         spammed when correctly using the #VARIABLE and #UNVARIABLE commands.\n"
	},
	{
		"NOP",
		"<K82>Command<K81>: #nop <K82>{<K81>whatever<K82>}<K81>\n"
		"\n"
		"         Short for 'no operation', and is ignored by the client.  It is useful\n"
		"         for commenting in your coms file, any text after the nop and before a\n"
		"         semicolon or end of line is ignored. You shouldn't put braces { } in it\n"
		"         though, unless you close them properly.\n"
		"\n"
		"<K82>Comment<K81>: By using braces you can comment out multiple lines of code in a script\n"
		"         file.\n"
		"\n"
		"         For commenting out an entire trigger and especially large sections of\n"
		"         triggers you would want to use /* text */\n"
		"\n"
		"<K82>Example<K81>: #nop This is the start of my script file.\n"
	},
	{
		"PARSE",
		"<K82>Command<K81>: #parse <K82>{<K81>string<K82>} {<K81>variable<K82>} {<K81>commands<K82>}<K81>\n"
		"\n"
		"         Like the loop statement, parse will loop from start to finish through\n"
		"         the given string.  The value of the current character is stored in the\n"
		"         provided variable.\n"
		"\n"
		"<K82>Example<K81>: #parse {hello world} {char} {#showme $char}\n"
	},
	{
		"PATH",
		"<K82>Command<K81>: #path <K82>{<K81>del<K82>|<K81>end<K82>|<K81>ins<K82>|<K81>load<K82>|<K81>map<K82>|<K81>new<K82>|<K81>run<K82>|<K81>save<K82>|<K81>walk<K82>}<K81> <K82>{<K81>argument<K82>}<K81>\n"
		"\n"
		"         #path del:   Will delete the last move of the path.\n"
		"         #path end:   Movement commands are no longer added to the path.\n"
		"         #path ins:   Add the given argument to the path.\n"
		"         #path load:  Load the given variable as the new path.\n"
		"         #path new:   Movement commands will be added to the path.\n"
		"         #path run:   Enter all the steps of the current path, with\n"
		"                      an optional given delay.\n"
		"         #path save:  Save the created path to a variable. You must specify\n"
		"                      whether you want to save the path forward or backward.\n"
		"         #path show:  Display the so far created path.\n"
		"         #path unzip: Load the given speedwalk as the new path.\n"
		"         #path walk:  Take one step forward of the current path. You can\n"
		"                      walk backwards using #path walk backwards.\n"
		"         #path zip:   Turn loaded path into a speedwalk.\n"
		"\n"
		"<K82>Example<K81>: #path ins {unlock n;open n} {unlock s;open s}\n"
	},
	{
		"PATHDIR",
		"<K82>Command<K81>: #pathdir <K82>{<K81>dir<K82>}<K81> <K82>{<K81>reversed dir<K82>}<K81> <K82>{<K81>coord<K82>}<K81>\n"
		"\n"
		"         By default tintin sets the most commonly used movement commands\n"
		"         meaning you generally don't really have to bother with pathdirs.\n"
		"         Pathdirs are used by the #path and #map commands.\n"
		"\n"
		"         The first argument is a direction, the second argument is the reversed\n"
		"         direction.  The reverse direction of north is south, etc.\n"
		"\n"
		"         The third argument is a spatial coordinate. In general, each cardinal\n"
		"         direction should have a unique value which is a power of two (1, 2,\n"
		"         4, 8, 16, 32, 64, etc). The exception is for compound directions, whose\n"
		"         value should be the sum of the values for each component direction. For\n"
		"         example, if the third value for 'n' is 1, and 'e' is 2, then you would\n"
		"         want 'ne' to have a value of 3 (1 + 2). This value is required for the\n"
		"         #map functionality to work.\n"
		"\n"
		"<K82>Example<K81>: #pathdir {ue} {dw} {18}\n"
		"         #pathdir {dw} {ue} {40}\n"
		"\n"
		"<K82>Comment<K81>: You can remove a pathdir with the #unpathdir command.\n"		
	},
	{
		"PORT",
		"<K82>Command<K81>: #port <K82>{<K81>option<K82>}<K81> <K82>{<K81>argument<K82>}<K81>\n"
		"\n"
		"         #port {init} {name} {port} {file}     Initilize a port session.\n"
		"\n"
		"         #port {call}       {address} {port}   Connect to a remote socket\n"
		"         #port {color}      {color names}      Set the default color\n"
		"         #port {dnd}                           Decline new connections\n"
		"         #port {group}      {name} {group}     Assign a socket group\n"
		"         #port {ignore}     {name}             Ignore a socket\n"
		"         #port {info}                          Display your info\n"
		"         #port {name}       {name}             Change socket name.\n"		
		"         #port {prefix}     {text}             Set prefix before each message.\n"		
		"         #port {send}       {name|all} {text}  Send data to socket\n"
		"         #port {uninitialize}                  Unitialize the port session.\n"
		"         #port {who}                           Show all connections\n"
		"         #port {zap}        {name}             Close a connection\n"
		"\n"
		"         The port command is very similar to chat except that it creates a\n"
		"         new session dedicated to receiving socket connections at the given\n"
		"         port number without built-in support for a communication protocol.\n"
	},
	{
		"PROMPT",
		"<K82>Command<K81>: #prompt <K82>{<K81>text<K82>}<K81> <K82>{<K81>new text<K82>}<K81> <K82>{<K81>row #<K82>}<K81>\n"
		"\n"
		"         Prompt is a feature for split window mode (see #help split), which\n"
		"         will take the status prompt from the mud, and display it on the status\n"
		"         line of the split window.  You would define <string> the same way you\n"
		"         would a substitution (see #help substitute).  The row number is\n"
		"         optional if you use a non standard split mode.  In which case a\n"
		"         positive number draws #row lines above your cursor, and a negative\n"
		"         number draws #row lines below your topline.\n"
		"\n"
		"<K82>Comment<K81>: See '#help action', for more information about triggers.\n"
		"\n"
		"<K82>Comment<K81>: You can remove a prompt with the #unprompt command.\n"
	},
	{
		"READ",
		"<K82>Command<K81>: #read <K82>{<K81>filename<K82>}<K81>\n"
		"\n"
		"         Reads a commands file into memory.  The coms file is merged in with\n"
		"         the currently loaded commands.  Duplicate commands are overwritten.\n"
		"\n"
		"         If you uses braces, { and } you can use several lines for 1 commands.\n"
		"         This however means you must always match every { with a } for the read\n"
		"         command to work.\n"
		"\n"
		"         You can comment out triggers using /* text */\n"
	},
	{
		"REGEXP",
		"<K82>Command<K81>: #regexp <K82>{<K81>string<K82>}<K81> <K82>{<K81>expression<K82>}<K81> <K82>{<K81>true<K82>}<K81> <K82>{<K81>false<K82>}<K81>\n"
		"\n"
		"         Compares the string to the given regular expression.\n"
		"\n"
		"         Variables are stored in &1 to &99 with &0 holding the matched substring.\n"
		"\n"
		"       ^ force match of start of string.\n"
		"       $ force match of end of string.\n"
		"       \\ escape one character.\n"
		"  %1-%99 lazy match of any text, available at &1-&99.\n"
		"      %0 should be avoided in triggers, and if left alone &0 lists all matches.\n"
		"     { } embed a raw regular expression, available at last &1-&99 + 1.\n"
		"         [ ] . + | ( ) ? * are treated as normal text unlessed used within\n"
		"         braces. Keep in mind that { } is replaced with ( ) automatically.\n"
		"\n"
		"         Of the following the lazy match is available at last &1-&99 + 1.\n"
		"\n"
		"      %w match zero to any number of letters.\n"
		"      %W match zero to any number of non letters.\n"
		"      %d match zero to any number of digits.\n"
		"      %D match zero to any number of non digits.\n"
		"      %s match zero to any number of spaces.\n"
		"      %S match zero to any number of non spaces.\n"
		"\n"
		"      %? match zero or one character.\n"
		"      %. match one character.\n"
		"      %+ match one to any number of characters.\n"
		"      %* match zero to any number of characters.\n"
		"\n"
		"      %i matching becomes case insensitive.\n"
		"      %I matching becomes case sensitive (default).\n"
		"\n"
		"<K82>Example<K81>: #regexp {bli bla blo} {bli {.*} blo} {#showme &1}\n"
	},
	{
		"REPLACE",
		"<K82>Command<K81>: #replace <K82>{<K81>variable<K82>}<K81> <K82>{<K81>oldtext<K82>}<K81> <K82>{<K81>newtext<K82>}<K81>\n"
		"\n"
		"         Searches the variable text replacing each occurance of 'oldtext' with\n"
		"         'newtext'.\n"
	},
	{
		"RETURN",
		"<K82>Command<K81>: #return <K82>{<K81>text<K82>}<K81>\n"
		"\n"
		"         This command can be used to break out of a command string being executed.\n"
		"         If used inside a #function you can use #return with an argument to both\n"
		"         break out of the function and set the result variable.\n"
	},
	{
		"RUN",
		"<K82>Command<K81>: #run <K82>{<K81>name<K82>}<K81> <K82>{<K81>shell command<K82>} {<K81>file<K82>}<K81>\n"
		"\n"
		"         The run command works much like the system command except that it\n"
		"         runs the command in a pseudo terminal. The run command also creates\n"
		"         a session that treats the given shell command as a mud server. This\n"
		"         allows you to run ssh, as well as any other shell application, with\n"
		"         full tintin scripting capabilities. If a file name is given the file\n"
		"         is loaded prior to execution.\n"
		"\n"
		"<K82>Example<K81>: #run {somewhere} {ssh someone@somewhere.com}\n"
		"<K82>Example<K81>: #run {something} {tail -f chats.log}\n"
	},
	{
		"SCAN",
		"<K82>Command<K81>: #scan <K82>{<K81>filename<K82>}<K81>\n"
		"\n"
		"         The scan command reads in a file and sends its content to the screen\n"
		"         as if it was send by a mud. After using scan you can use page-up and\n"
		"         down to view the file.\n"
		"\n"
		"         This command is useful to convert ansi color files to html or viewing\n"
		"         raw log files.\n"
		"\n"
		"         Reads in a file and sends it to the screen as if it was send by a mud.\n"
		"         This is useful to convert ansi color file to html or viewing log file.\n"
		
	},
	{
		"SCRIPT",
		"<K82>Command<K81>: #script <K82>{<K81>variable<K82>}<K82> {<K81>shell command<K82>}<K81>\n"
		"\n"
		"         The script command works much like the system command except that it\n"
		"         treats the generated echos as commands if no variable is provided.\n"
		"\n"
		"         This is useful for running php, perl, ruby, and python scripts. You\n"
		"         can run these scrips either from file or from within tintin if the\n"
		"         scripting language allows this.\n"
		"\n"
		"         If you provide a variable the output of the script is stored as a list.\n"
		"\n"
		"<K82>Example<K81>: #script {ruby -e 'print \"#showme hello world\"'}\n"
		"<K82>Example<K81>: #script {python -c 'print \"#showme hello world\"'}\n"
		"<K82>Example<K81>: #script {php -r 'echo \"#showme hello world\"'}\n"
		"<K82>Example<K81>: #script {path} {pwd};#showme The path is $path[1].\n"
	},

	{
		"SEND",
		"<K82>Command<K81>: #send <K82>{<K81>text<K82>}<K81>\n"
		"\n"
		"         Sends the text directly to the MUD, useful if you want to start with an\n"
		"         escape code.\n"
		"\n"
		"<K82>Related<K81>: textin\n"
	},
	{
		"SESSION",
		"<K82>Command<K81>: #session <K82>{<K81>name<K82>} {<K81>host<K82>} {<K81>port<K82>} {<K81>file<K82>}\n"
		"\n"
		"         Starts a telnet session with the given name, host, port, and optional\n"
		"         file name. The name can be anything you want, except the name of an\n"
		"         already existant session. If a file name is given the file is only\n"
		"         read if the session succesfully connects.\n"
		"\n"
		"         Without an argument #session shows the currently defined sessions.\n"
		"\n"
		"         If you have more than one session, you can use the following commands:\n"
		"         #session {-|+|number}:  Switches between sessions.\n"
		"         #{name}:  Switches to a session with the given name.\n"
		"         #{name} {command}:  Executes a command with the given session without\n"
		"                             changing the active session.\n"
		"         @<name>{text}:      Parse text in the given session, substituting the\n"
		"                             variables and functions, and print the result in\n"
		"                             the current active session.\n"
		"\n"
		"         The startup session is named 'gts' and can be used for relog scripts.\n"
		"\n"
		"<K82>Example<K81>: #event {SESSION DISCONNECTED} {#gts #delay 10 #ses %0 mymud.com 4321}\n"
		"\n"
		"<K82>Related<K81>: all, snoop, and zap.\n"
		"<K82>Related<K81>: port, run, ssl, \n"
	},
	{
		"SHOWME",
		"<K82>Command<K81>: #showme <K82>{<K81>string<K82>}<K81> <K82>{<K81>row<K82>}<K81>\n"
		"\n"
		"         Display the string to the terminal, do not send to the mud.  Useful for\n"
		"         status, warnings, etc.  The {row} number is optional and works the same\n"
		"         way as the row number of the #prompt trigger.\n"
		"\n"
		"         Actions can be triggered by the showme command.\n"
		"\n"
		"<K82>Example<K81>: #action {%0 ultraslays you.}\n"
		"           {#showme {###### ARGH! We were ultraslayed by %0 ######};#gagline}\n"
		"         Emphasis ultraslaying.\n"
	},
	{
		"SNOOP",
		"<K82>Command<K81>: #snoop <K82>{<K81>session name<K82>}<K81>\n"
		"\n"
		"         If there are multiple sessions active, this command allows you to see\n"
		"         what is going on the the sessions that are not currently active.  The\n"
		"         line of text from other sessions will be prefixed by the session's name.\n"
		"\n"
		"         You can toggle off snoop mode by executing #snoop a second time.\n"
	},
	{
		"SPEEDWALK",
		"         <K81>Speedwalking allows you to type multiple directions not separated by\n"
		"         semicolons, and now it lets you prefix a direction with a number, to\n"
		"         signify how many times to go that direction. You can turn it on/off\n"
		"         with #config.\n"
		"\n"
		"<K82>Example<K81>: Without speedwalk, you have to type:\n"
		"         s;s;w;w;w;w;w;s;s;s;w;w;w;n;n;w\n"
		"         With speedwalk, you only have to type:\n"
		"         2s5w3s3w2nw\n"
	},
	{
		"SPLIT",
		"<K82>Command<K81>: #split <K82>{<K81>top border height<K82>}<K81> <K82>{<K81>bottom border height<K82>}<K81>\n"
		"\n"
		"         This option only works with a VT100 emulator, this allows you to set up\n"
		"         a screen.  The keyboard input will be displayed in the bottom line,\n"
		"         while mud text is displayed in the main window.  This requires a fairly\n"
		"         decent emulator, but works on most I have tested.\n"
		"\n"
		"         | Top border   (can be ommited, height customizable)\n"
		"         | Mud text\n"
		"         | Bottom border   (height customizable, at least one line)\n"
		"         | Input line\n"
		"\n"
		"         If used without an argument, the top border will be ommited, and the\n"
		"         bottom border's height will be set to one line.\n"
		"\n"
		"         If you want a different split setting, because you want a two lines\n"
		"         thick split, or like having a blank line at the top of the screen\n"
		"         to display something you can set the top and bottom line with the\n"
		"         additional arguments.\n"
		"\n"
		"<K82>Example<K81>: #split\n"
		"         If tintin has determined that you have a screen of 30 rows, it will\n"
		"         set the main window from line #1 to line #28.\n"
		"\n"
		"<K82>Comment<K81>: You can display text on the split line(s) with the #prompt and\n"
		"         #showme {line} {row} command.\n"
		"\n"
		"<K82>Comment<K81>: You can remove split mode with the #unsplit command.\n"
	},
	{
		"SSL",
		"<K82>Command<K81>: #ssl <K82>{<K81>name<K82>} {<K81>host<K82>} {<K81>port<K82>} {<K81>file<K82>}\n"
		"\n"
		"         Starts a secure socket telnet session with the given name, host, port,\n"
		"         and optional file name.\n"
	},
	{
		"STATEMENTS",
		"         TinTin++ knows the following statements.\n"
		"<K81>\n"
		"         #break\n"
		"         #case {value} {true}\n"
		"         #continue\n"
		"         #default {commands}\n"
		"         #else {commands}\n"
		"         #elseif {expression} {true}\n"
		"         #foreach {list} {variable} {commands}\n"
		"         #if {expression} {true}\n"
		"         #loop {min} {max} {variable} {commands}\n"
		"         #parse {string} {variable} {commands}\n"
		"         #return {value}\n"
		"         #switch {expression} {commands}\n"
		"         #while {expression} {commands}\n"
	},
	{
		"SUBSTITUTE",
		"<K82>Command<K81>: #substitute <K82>{<K81>text<K82>}<K81> <K82>{<K81>new text<K82>}<K81>\n"
		"\n"
		"         Allows you to replace original text from the mud with different text.\n"
		"         This is helpful for complex coloring and making things more readable.\n"
		"         The %1-%99 variables can be used to capture text and use it as part of\n"
		"         the new output, and the ^ char is valid to only check the beginning of\n"
		"         the line for the text specified.\n"
		"\n"
		"         If only one argument is given, all active substitutions that match the\n"
		"         strings are displayed.  The '%*' char is valid in this instance.  See\n"
		"         '#help regex', for advanced wildcard information.\n"
		"\n"
		"         If no argument is given, all subs are displayed.\n"
		"\n"
		"<K82>Example<K81>: #sub {Zoe} {ZOE}\n"
		"         Any instance of Zoe will be replaced with ZOE.\n"
		"\n"
		"<K82>Example<K81>: #sub {~\\e[0;34m} {\\e[1;34m}\n"
		"         Replace generic dark blue color codes with bright blue ones.\n"
		"\n"
		"<K82>Example<K81>: #sub {%1massacres%2} {<<888>018>%1<<888>118>MASSACRES<<888>018>%2}\n"
		"         Replaces all occurrences of 'massacres' with 'MASSACRES' in red.\n"
		"\n"
		"<K82>Comment<K81>: See '#help action', for more information about triggers.\n"
		"\n"
		"<K82>Comment<K81>: See '#help colors', for more information.\n"
		"\n"
		"<K82>Comment<K81>: You can remove a substitution with the #unsubstitute command.\n"
	},
	{
		"SUSPEND",
		"<K82>Command<K81>: #suspend\n"
		"\n"
		"         Temporarily suspends tintin and returns you to your shell.  The\n"
		"         effect of this command is exactly as if you had typed control-z.\n"
		"         To return to tintin, type 'fg' at the shell prompt.\n"
		"\n"
		"         While suspended your tintin sessions will freeze. To keep a\n"
		"         suspended session running use the screen utility program and\n"
		"         have it detach the session.\n"
	},
	{
		"SWITCH",
		"<K82>Command<K81>: #switch <K82>{<K81>conditional<K82>}<K81> <K82>{<K81>arguments<K82>}<K81>\n"
		"\n"
		"         The switch command works similar to the switch statement in other\n"
		"         languages. When the 'switch' command is encountered its body is parsed\n"
		"         and each 'case' command found will be compared to the conditional\n"
		"         argument of the switch and executed if there is a match.\n"
		"\n"
		"         When comparing strings the switch and case arguments must be enclosed\n"
		"         in quote characters.\n"
		"\n"
		"         If the 'default' command is found and no 'case' statement has been\n"
		"         matched the default command's argument is executed.\n"
		"\n"
		"<K82>Example<K81>: #switch {1d4} {#case 1 cackle;#case 2 smile;#default giggle}\n"
	},
	{
		"SYSTEM",
		"<K82>Command<K81>: #system <K82>{<K81>command<K82>}<K81>\n"
		"\n"
		"         Executes the command specified as a shell command.\n"
	},
	{
		"TAB",
		"<K82>Command<K81>: #tab <K82>{<K81>word<K82>}<K81>\n"
		"\n"
		"         Adds a word to the tab completion list, alphabetically sorted.\n"
		"\n"
		"         If no tabs are defined tintin will use the scrollback buffer\n"
		"         for auto tab completion.\n"
		"\n"
		"<K82>Comment<K81>: You can remove a tab with the #untab command.\n"
	},
	{
		"TEXTIN",
		"<K82>Command<K81>: #textin <K82>{<K81>filename<K82>}<K81> <K82>{<K81>delay<K82>}<K81>\n"
		"\n"
		"         Textin allows the user to read in a file, and send its contents\n"
		"         directly to the mud.  Useful for doing online creation, or message\n"
		"         writing.\n"
		"\n"
		"         The delay is in seconds and takes a floating point number which is\n"
		"         cumulatively applied to each outgoing line.\n"
		"\n"
		"<K82>Related<K81>: scan and send\n"
	},
	{
		"TICKER",
		"<K82>Command<K81>: #ticker <K82>{<K81>name<K82>}<K81> <K82>{<K81>commands<K82>}<K81> <K82>{<K81>interval in seconds<K82>}<K81>\n"
		"\n"
		"         Executes given command every # of seconds.\n"
		"\n"
		"<K82>Comment<K81>: Tickers don't work in the startup session.\n"
		"\n"
		"<K82>Comment<K81>: You can remove a ticker with the #unticker command.\n"
	},
	{
		"VARIABLE",
		"<K82>Command<K81>: #variable <K82>{<K81>variable name<K82>}<K81> <K82>{<K81>text to fill variable<K82>}<K81>\n"
		"\n"
		"         Variables differ from the %0-99 arguments in the fact that you can\n"
		"         specify a full word as a variable, and they stay in memory for the\n"
		"         full session unless they are changed.  They can be saved in the\n"
		"         coms file, and can be set to different values if you have two or\n"
		"         more sessions running at the same time.  Variables are global for\n"
		"         each session and can be accessed by adding a $ before the variable\n"
		"         name.\n"
		"\n"
		"<K82>Example<K81>: #alias {target} {#var target %0}\n"
		"         #alias {x}      {kick $target}\n"
		"\n"
		"         The name of a variable must exist of only letters, numbers and\n"
		"         underscores in order to be substituted.  If you do not meet these\n"
		"         requirements do not panic, simply encapsulate the variable in braces:\n"
		"\n"
		"<K82>Example<K81>: #variable {cool website} {http://tintin.sourceforge.net}\n"
		"         #chat I was on ${cool website} yesterday!.\n"
		"\n"
		"         Variables can be nested using brackets or dots:\n"
		"\n"
		"<K82>Example<K81>: #var hp[self] 34;#var hp[target] 46\n"
		"<K82>Example<K81>: #var hp.self  34;#var hp.target  46\n"
		"\n"
		"         You can see the first nest of a variable using $variable[+1] and the\n"
		"         last nest using $variable[-1]. Using $variable[-2] will report the\n"
		"         second last variable, and so on. To show all indices use $variable[].\n"
		"         To show all values use $variable[%*] or a less generic regex.\n"
		"\n"
		"         Nested variables are also known as tables, table generally being used\n"
		"         to refer to several variables nested within one specific variable.\n"
		"\n"
		"<K82>Example<K81>: #showme {Targets starting with the letter A: $targets[A%*]\n"
		"\n"
		"         To see the internal index of a variable use &<variable name>. To see\n"
		"         the size of a table you would use: &targets[] or &targets[%*]. A non\n"
		"         existent nested variable will report itself as 0.\n"
		"\n" 
		"<K82>Example<K81>: #showme {Number of targets starting with A: &targets[A%*]\n"
		"\n"
		"         In some scripts you need to know the name of a nested variable. This\n"
		"         is also known as the key, and you can get it using *variable. For\n"
		"         example *target[+1]. To get the first variable's name use *{+1}.\n"
		"\n"
		"<K82>Comment<K81>: Related commands are local, math, format, and list.\n"
		"\n"
		"<K82>Comment<K81>: You can remove a variable with the #unvariable command.\n"
	},
	{
		"WHILE",
		"<K82>Command<K81>: #while <K82>{<K81>conditional<K82>} {<K81>commands<K82>}<K81>\n"
		"\n"
		"         This command works similar to a 'while' statement in other languages.\n"
		"\n"
		"         When a 'while' command is encourated, the conditional is evaluated,\n"
		"         and if TRUE (any non-zero result) the commands are executed. The\n"
		"         'while' loop will be repeated indefinitely until the conditional is\n"
		"         FALSE or the #BREAK or #RETURN commands are found.\n"
		"\n"
		"         The 'while' statement is only evaluated if it is read, so you must\n"
		"         nest it inside a trigger, like an alias or action.\n"
		"\n"
		"         The conditional is evaluated exactly the same as in the 'math' command.\n"
                "\n"
                "<K82>Example<K81>: #math cnt 0;#while {$cnt < 20} {#math cnt $cnt + 1;say $cnt}\n"
		"\n"
		"<K82>Comment<K81>: See '#help math', for more information.\n"
	},
                                                                                                   
	{
		"WRITE",
		"<K82>Command<K81>: #write <K82>{<K81>filename<K82>}<K81>\n"
		"\n"
		"         Writes all current actions, aliases, subs, highlights, and variables\n"
		"         to a command file, specified by filename.\n"
	},
	{
		"ZAP",
		"<K82>Command<K81>: #zap {[session]}\n"
		"\n"
		"         Kill your current session.  If there is no current session, it will\n"
		"         cause the program to terminate. If you provide an argument it'll zap\n"
		"         the given session instead.\n"
	},
	{
		"",
		""
	}
};


DO_COMMAND(do_help)
{
	char left[BUFFER_SIZE], add[BUFFER_SIZE], buf[BUFFER_SIZE], *ptf, *pto;
	int cnt, found;

	arg = get_arg_in_braces(ses, arg, left, TRUE);

	if (*left == 0)
	{
		for (cnt = add[0] = 0 ; *help_table[cnt].name != 0 ; cnt++)
		{
			if ((int) strlen(add) + 19 > ses->cols)
			{
				tintin_puts2(ses, add);
				add[0] = 0;
			}
			cat_sprintf(add, "%19s", help_table[cnt].name);
		}
		tintin_puts(ses, add);
	}
	else
	{
		found = FALSE;

		for (cnt = 0 ; *help_table[cnt].name != 0 ; cnt++)
		{
			if (is_abbrev(left, help_table[cnt].name) || atoi(left) == cnt + 1 || match(ses, help_table[cnt].name, left, SUB_VAR|SUB_FUN))
			{
				substitute(ses, help_table[cnt].text, buf, SUB_COL);

				pto = buf;

				while (*pto)
				{
					ptf = strchr(pto, '\n');

					if (ptf == NULL)
					{
						break;
					}
					*ptf++ = 0;

					tintin_puts3(ses, pto);

					pto = ptf;
				}
//				tintin_puts2(ses, "");
				found = TRUE;

				if (is_abbrev(left, help_table[cnt].name))
				{
					break;
				}
			}
		}
		if (found == FALSE)
		{
			tintin_printf2(ses, "No help found for '%s'", left);
		}
		else
			tintin_puts2(ses, "\e[0m");	// Reset terminal back to normal default
	}
	return ses;
}
