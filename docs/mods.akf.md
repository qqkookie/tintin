================================================================================

Sun Aug 26 12:00:00 2018 Akorn Farmer <cantata@gmail.com> (qqKookie@GitHub)

GitHub repository:https://github.com/qqkookie/tintin/tree/cookie

* tinexpr.c:
- 24 bit true color color code
  24 bit colr can be specified with 6 hexadecimal digits.
  Use "<xhhhhhh>" (lowercase 'x' prefix) for foreground RGB888 color,
  "<Xhhhhhh>" (uppercase 'X' prefix) for background RGB888 color.
  Hexdecimal digits 'h' are 0-9, a-f, A-F, upper/lowcase ignored.

  Example: #highlight {^The Temple Of Midgaard$} {<XFFFF00><188>}

- Custom, user-defined, numbered color code
  Similar to "<g32>" or "<G32>" color code for gray colors,
  user can define color of "<K00>"-"<K99>" color code and use it.
  To set actual color for "<Kdd>" color code with other color code,
  set global array variable ${_TK[00]}-${_KT[99]}. For example:

  #var {_TK[14]} {<X0000ff><188>} ==> <K14> code to bold blue BG color.

  #highlight {^The Temple Of Midgaard$} {<K14>}

  <K81>~<K85>codes are pre-defined for help strings and chat color code.
  <K86>~<K99> are reserved for future internal use.

* net.c:
* parse.c:
- "MIXED" CHARSET option for #CONFIG CHARSET
  Option for player uses UTF-8 charset terminal to play MUD in MBCS encoding
  With this mixed charset option, player plays old MUD that uses legacy
  multibyte codepage (ISO-8859-x, double byte DBCS EUC-KR, EUC-JP, etc)
  with terminal setting to use UTF-8 charset to display/enter UTF-8 text.
  To use the mode: #CONFIG CHARSET {MIXED}

- By using UTF-8, instead of MBCS EUC-KR, various patterns for
  #action, #highlight, written in Asian UTF-8 text can be successfully
  matched and triggred. MUD codepage is assumed to be same as player's
  ANSI codepage like CP949.	Tintin text file also uses UTF-8 encoding.
  This feature is avaiable only on MS Windows WinTin++.

* config.c:
- Add "MIXED" option for #CONFIG CHARSET

* help.c:
- User can modify #HELP display color.
  Using the custom <Kdd> color code, user can set colrs of help text
  and chatting. Useful for player uses black text on white background.
  <K81>, <K82>, <K83> for help text colors, <K84>, <K85> for chat color.

- Shorten "Example:" and "Comment:" to be less stand out.
- Text color reset to nomal default color after displaying #HELP text.
- Add help text for 24 bit color and help/chat color

* chat.c:
- User can modify chatting text color.
- Minor change to silence gcc buffer overflow warning

* main.c:
- Default help text / chatting colors are defined here.

* input.c:
- Allow vertical scroll bar, even in #split mode, if top row is 0.
 Example: #SPLIT 0 2; #PROMPT {[%1,%2,%3]} {[%1, %2, %3] } {1}

* tintin.h:
- Session flags are defined explicitly as 64 bit long long integer.
- Tentative version number

* Makefile.in:
- Add BUILDDIR and *.o file dependacy on header files

* .gitignore:
- Add new file for GitHub source file control

* File name and ext of mods/*.mods files are changed from *.mods to mods.*.md,
  and they all are moved to docs/ directory for better organization.
  ex) mods/igr.mods => docs/mods.igr.md

* Add files from WnTin++ installation. Credit to WinTin++, not Akorn Farmer

- docs/wintin.COPYING.txt	(for CygWin/mintty)
- docs/wintin.FAQ.txt		(addtional Window FAQs)
- docs/wintin.mintty.con	(mintty config file)
- docs/wintin.tt.ico		(Wintin++ icon file)

* Add aditinal 16 ANSI color definition entries in wintin.mintty.con

--------------------------------------------------------------------------------

Sun Sep 2 12:00:00 2018 Akorn Farmer

* system.c:
- Lua 5.2 interpreter integration
- Add do_lua() command code

* Configure.h.in:
* Configure.h.in:
* Configure:
- To add lua header/library/DLL dependancy and clean up

* tintin.h:
* tables.h:
- Add new #LUA command

* help.h:
- Add #LUA command help
- Add group #action / #unaction, #read, #history

* net.c:
* parse.c:
* system.c:
- Port to freebsd, minor fix

* data.c:
- Named group action/unaction
  ex) #action {...} {...} {grp_name} ;  #unaction {GROUP {grp_name}}

* file.c:
- /// starts single-line comment in C++ // comment style in command file.
- Better #read file handing on MS Windows CygWin environment.
- #read will remembers old filename and use it as default filename.
- If #read can't find named file first, files in the .tintin directory
  will be tried as second guess.

* ssl.c:
- #ssl will trys to find certificate in the .tintin dir itself.

* session.c:
- History of non-starting sessions are also preserve in history.txt file
  and shared across/among non-starting sessions.

--------------------------------------------------------------------------------

Sat Sep 9 12:00:00 2018 Akorn Farmer

* math.c:
* utils.c:
* tokenize.c:
- For #math, #if, #elseif and #while statement, non-empty string is evaluated
  as non-zero number value. This can be enabled by setting #config math eval.
  Default is compat.
- Better handling of unquoted single word string in #math and others.
- Add ? unary operator to test non-zero numbers. Opposite of ! operator.
  ! and ? operators work for string too to test empty/non-empty string.
- Add + opeator for string to test it is string or number

* config.c:
* tables.c:
* tintin.h:
- Add #config mathstr option for above #math behavior

* help.h:
- #math change

--------------------------------------------------------------------------------

Wed Sep 12 12:00:00 2018 Akorn Farmer

* main.c:
- More graceful exit on SIGHUP (Windows mintty close)
- History save file directory fix
- Set $_TTDIR variable
- On MS Windows CygWin environment and not run on CygWin bash shell,
  (i.e. on Windows Explorer), tintin trys to change directory to .tintin
  directory and run there, instead of WinTin++ install bin directory.

* log.c:
- Set $_filelog variable
- Relative log file name is relatieve to uer's .tintin directory.

* line.c:
- #line log sets $_linelog variable. If first argument is empty ({}),
  it uses $_linelog or $_filelog as default filename argument.

* file.c:
- Sets $_fileread variable
- Add check_filepath() using stat() and access()

* highlight.c:
* table.c:
- More flexible multiple highlight color args
- Some highlight name change: none, normal, unreverse, default, bg, lt, etc
- Remove confusing highlight names: faint, dark, light, no-reverse, etc
- While reading tintin file, if highligh color is missing, default is bold.

* tinexp.c:
- Add <6dd> spercial color code.
- Change custom color varible name from $_TKdd to array varibale $_TK[dd]

* help.c:
- #highlight, special color code change

--------------------------------------------------------------------------------

Sat Sep 15 12:00:00 2018 Akorn Farmer

* table.c:
- More portable and less cryptic control characters
  in config_table[] in table.c source code
- Better config_table[] organization.

* main.c:
- Remove "\e" escape from source code, use "\033" for consistency.

* net.c:
- Use gtd->hostcp instead of static variable
- Use iconv() library routine for UTF8 conversion on Windows CygWin
  envioronment. iconv-2.dll is needed.
- Add CPNameToCPID()

* cursor.c:
* variable.c:
* text.c:
- Handle cursor movement and word wrapping of double-width CJK characters
  in UTF-8 encording

* config.c:
- Rename #config math option to #config mathstr <on/off>
- New #config utf8dw option supershading #config charset mixed

  Usage :   #config utf8dw <on|off|<host codepage>>
  This config works only when #config charset is set to UTF8.
- If utf8dw option is on, double-width (or full-width) CJK character is
  handled correctly on input line cursor movement.
- <host codepage> is codepage of remote MUD host. It is used when host
  does not supports UTF-8 code, but uses legacy MBCS code.
  If host codepage is specified, input/output are converted from/to UTF-8
  and double-width option is turn on for CJK codepage.
  Supported codepage names:
  CP1252 CP850 ISO-8859-1 and most CPXXX codepage names
  CP936 GB2312 EUC-CN CP950 BIG5 CP932 SJIS EUC-JP CP949 EUC-KR

* tintin.h:
- Add global data gtd->hostcp, gtd->fileread

* Configigure.in:
* config.h:
- Fix to add HAVE_ICONV_H and -liconv libray autoconfigure.

--------------------------------------------------------------------------------

Wed Sep 19 12:00:00 2018 Akorn Farmer

* cursor.c:
* input.c:
- Fix input position error for double-width characters in input line

* system.c:
- Lua print()/write() output is processed as tintin command script.

* README:
- Apply spelling correction and clean up of README document by icedwater@GITHUB
- Add #math change summary.

* text.c:
- Add INDENT wordwrap option by rfrancis@GITHUB.
  But not separate option, but sub-option as #config wordwrap {indent}

* tintin.h:
- Add SES_FLAG_INDENT
- Reorganize SES_FLAG_* ordering

* ticker.c:
- #TICKER special command: {SHOW}, {TIME}, {SYNC}, {DIFF}
  auto syncing and time reporting

* table.c:
- Move codepage table from net.c to table.c

* list.c:
* tokenize.c:
- #foreach and #list add/create option accepts space or comma separated list
  as item list.

--------------------------------------------------------------------------------
Sun Sep 30 12:00:00 2018 Akorn Farmer

* main.c:
- User can set tintin directory (default: $HOME/.tintin)
  by setting $TINTIN (Unix/Windows) environment variable.

* tokenize.c:
- #foreach list bug fix

* parser.c:
- get_arg_stop_spaces() will not stop at spaces in quoted string.
- Quote has the highest precedence over brace or semicolon ({}[];\)
- Quoted string is tread as single token/argument.
- So no more need to enclose multi-word string in #case label.
- Old : #case {"my apple"} New: #case "my apple"

--------------------------------------------------------------------------------
<EOT>
