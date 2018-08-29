--------------------------------------------------------------------------------

Sun Aug 26 12:00:00 2018 Akorn Farmer <cantata@gmail.com> (qqKookie@GitHub)

* tinexpr.c

1) 24 bit true color color code
24 bit colr can be specified with 6 hexadecimal digits.
Use "<xhhhhhh>" (lowercase 'x' prefix) for foreground RGB888 color, 
"<Xhhhhhh>" (uppercase 'X' prefix) for background RGB888 color.
Hexdecimal digits 'h' are 0-9, a-f, A-F, upper/lowcase ignored.

Example: #highlight {^The Temple Of Midgaard$} {<XFFFF00><188>} 

2) Custom, user-defined, numbered color code. 
Similar to "<g32>" or "<G32>" color code for gray colors,
user can define color of "<K00>"-"<K99>" color code and use it. 
To set actual color for "<Kdd>" color code with other color code, 
set global variable ${_TKT00}-${_KT99}. For example:

#var {_TK14} {<X0000ff><188>} ==> <K14> code to bold blue BG color.

#highlight {^The Temple Of Midgaard$} {<K14>}

<K81>~<K85>codes  are pre-defined for help strings and chat color code. 
<K86>~<K99> are reserved for future internal use.

* net.c:
* parse.c:

- "MIXED" CHARSET option for #CONFIG CHARSET. 
Option for player uses UTF-8 charset terminal to play MUD in MBCS encoding.
With this mixed charset option, player plays old MUD that uses legacy multibyte 
codepage (ISO-8859-x, double byte DBCS EUC-KR, EUC-JP, etc) 
with terminal setting to use UTF-8 charset to display/enter UTF-8 text. 
To use the mode: #CONFIG CHARSET {MIXED}

- By using UTF-8, instead of MBCS EUC-KR, various patterns for #action, #highlight,
written in MBCS text can be successfully matched and triggred.
MUD codepage is assumed to be same as player's ANSI codepage like CP949.	
Tintin text file also uses UTF-8 encoding. 
This feature is avaiable only on MS Windows WinTin++.

config.c
- Add "MIXED" option for #CONFIG CHARSET

help.c:
- User can modify #HELP display color. 
Using the custom <Kdd> color code, user can set colrs of help text 
and chatting. Useful for player uses black text on white background.
<K81>, <K82>, <K83> for help text colors, <K84>, <K85> for chat color.

- Shorten "Example:" and "Comment:" to be less stand out.
- Text color reset to nomal default color after displaying #HELP text.
- Add help text for 24 bit color and help/chat color. 

chat.c:
- User can modify chatting text color.
- Minor change to silence gcc buffer overflow warning.

main.c:
- Default help text / chatting colors are defined here.

input.c:
- Allow vertical scroll bar, even in #split mode, if top row is 0.
 Example: #SPLIT 0 2; #PROMPT {[%1,%2,%3]} {[%1, %2, %3] } {1}

tintin.h:
- session flags are defined explicitly as 64 bit long long integer.
- tentative version number

Makefile.in
- Add BUILDDIR and *.o file dependacy on header files.

.gitignore:
- Add new file for GitHub source file control.

File name and ext of mods/*.mods files are changed from *.mods to mods.*.md,
and they all are moved to docs/ directory for better organization.
ex) mods/igr.mods => docs/mods.igr.md

Add files from WnTin++ installation. Credit to WinTin++, not Akorn Farmer.

- docs/wintin.COPYIMG.txt	(for CygWin/mintty)
- docs/wintin.FAQ.txt		(addtional Window FAQs)
- docs/wintin.mintty.con	(mintty config file)
- docs/wintin.tt.ico		(Wintin++ icon file) 

Added aditinal 16 ANSI color definition entries in wintin.mintty.con.

-----------------------------------------------------------

Wed Aug 29 12:00:00 2018 Akorn Farmer

system.c:
    * Lua 5.2 interpreter integration.
    * Added do_lua() command code.

Configure.h.in:
Configure.h.in:
Configure:
    * To add lua header/library/DLL dependancy and clean up.

tintin.h:
tables.h:
    * Added new #LUA command.

help.h:
    * Added #LUA command help.

--------------------------------------------------------------------------------
<EOT>
