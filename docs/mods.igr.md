Jan 2018       2.01.5
--------------------------------------------------------------------------------

tinexp.c       Added exception for %*{text} to be parsed as a regex and not
               as a *{text} variable.

variable.c     Added the %H #format option to generate a 32 bit hash for the
               given string.

substitute.c   Fixed argument substitution problem, never a good idea to
               substitute arguments and functions at the same time, because
               functions will access and overwrite the argument stack.

main.c         Can use #end {\} to terminate tintin silently.

Oct 2017       2.01.4
--------------------------------------------------------------------------------

main.c         Added proper greeting handling for narrow terminals, mainly for
               people using tt++ on an android phone.

variable.c     Added proper \ handling in string length calculations.

variable.c     #unvariable takes additional arguments to unvar several
               variables at once.

tinexp.c       Added support for *{variable} to show variable/table keys. This
               is useful when low level data processing is needed.

               For example, *{+1} shows the key of the first variable.

list.c         Added #list {var} simplify {variable} option which saves a
               list (which internally is a table) as a semi-colon separated
               list to the provided destination variable.
               {{1}{bli}{2}{bla}{3}{blo}} becomes {bli;bla;blo}


May 2017       2.01.3
--------------------------------------------------------------------------------

mapper.c       Added #map legend support to assign custom characters for
               the #map flag MUD FONT display mode. By default they're set
               to map to the unicode private use area.

mapper.c       By default an UTF-8 #map legend is created for those who do
               not use ASCII graphics. The ANSI legend was pretty much
               unusable and most terminals are supporting UTF-8 now. Windows
               does not support all box drawing characters, hopefully this
               will be fixed in the future.

mapper.c       Removed support for the vtgraphics drawing mode which worked
               on very few terminals.

utils.c        Verbosity is automatically enabled for debug mode to avoid
               logging inconsistencies.

port.c         Added #port command, similar to netcat.

chat.c         #chat prefix works now

math.c         Better #math debug through #debug VARIABLE on

mapper.c       Added map exit <dir> dir <number> option.

action.c       Fixed action crash bug that slipped in

telopt.c       Added telnet events for IAC GA and IAC EOR


Jun 2015       2.01.2
--------------------------------------------------------------------------------

mapper.c       Added map <radius> <variable name> {v} option to save the map
               output to a variable.

log.c          html log files now correctly set the charset to utf-8 or big5
               if applicable.

tokenize.c     Added support for local variables with the #LOCAL command. Most
               commands that manipulate variables will use a local variable
               if it has been declared.

utils.c        Fixed crash bug on substitutions on system messages.

session.c      Showing all connect retry attempts and seconds left.

session.c      Any manual input while connecting will cancel connect retry.

main.c         Can create macros for ctrl-d and ctrl-z again.

mapper.c       Added #map color background option to set a background color
               for the map display.

variable.c     Added optional width argument to #format %w. Also added UTF-8
               support to %w.

variable.c     Attempt to fix %p crash bug on OS X.

               Fixed compilation issue for OS X.


Jan 2014       2.01.1
--------------------------------------------------------------------------------

chat.c         Added CHAT MESSAGE event, %0 contains the chat color and prefix,
               %1 omits chat color and prefix.

chat.c         Added #chat prefix option.

mapper.c       Can now provide multiple flags at once when using
               #map roomflag and #map insert.

line.c         Added #line quiet option.

cursor.c       Fixed tab bug with multi-word tabs.

event.c        Fixed bug with events defined in multiple sessions.

tinexp.c       Added @<session name>{<substitution>} option to perform a
               function-like substitution in another session and retreive
               the result. Primarily useful for getting variables.

highlight.c    Added no-blink no-underscore and no-reverse #highlight options.

highlight.c    Added option to use escape codes in the #highlight color field.

class.c        Added #class {<class>} list {<list>} option.

map.c          Added #map list {roomflag} option.

list.c         Fixed bug with using #list clear on a nested variable.

substitute.c   Added patch by Nya to properly handle colored substitutions.

math.c         Added // operator to calculate sqrt // 2 or cbrt // 3

math.c         Added ** operator to calculate power

tinexp.c       Added IGNORE options to variables and functions.

main.c         The command history is automatically saved again.

ssl.c          Added SSL support based on KBTin code by Adam Borowski.

tinex.c        $ @ and & are now escaped when received as part of an action for
               added security.

session.c      Added SESSION CREATED event.

parse.c        Fixed command echoing when executing commands in another session.

Mar 2013       2.01.0
--------------------------------------------------------------------------------

session.c      #session takes a filename as an additional argument, if the
               session succesfully connects the file will be read.

variable.c     Fixed #echo {%f} {5 / 3} handling.

cursor.c       Added #cursor get and #cursor set options.

parse.c        Added support for nesting using the . argument.

mapper.c       Added map_search_compile option, increasing search speed.

list.c         Added #list TOKENIZE option.

cursor.c       Fixed the cursor PASTE BUFFER option.

event.c        Added the VARIABLE UPDATE <VAR> event.

cursor.c       Added stripping of semi-colons when auto tabbing.

configure.in   Better error handling by Slysven.

Mar 2012       2.00.9
--------------------------------------------------------------------------------

line.c         Added a #line strip option to strip color and escape codes.

mapper.c       Fixed the handling of colored symbols in the ascii map.

input.c        RECEIVED INPUT now triggers before input is parsed.

mapper.c       Fixed #map undo handling for #map insert.

nest.c         Fixed crash when using #var a[b]c x

tokenize.c     Fixed crash when using #case outside a #switch.

cursor.c       Added stripping of tailing dots and commas when auto tabbing.

variables.c    #format %A now properly handles BIG5 and UTF-8.

session.c      Added SESSION TIMED OUT event.

variable.c     Fixed substitution problem with #unvariable.

mapper.c       Added support for a {variable} argument to #map list to store
               the returned data into a variable. Using {roomname} and
               other keywords from #map set will work as well.

mapper.c       Added #map exit <dir> save to store exit data in a variable.

mapper.c       Added basic color compression support.

mapper.c       Fixed the #map legend display in vtgraphics mode.

mapper.c       Added automatic initialization of a UTF-8 based legend when
               creating a map with #config CHARSET set to UTF-8.

mapper.c       Fixed unnecessary redrawing of the VT map.

list.c         Now properly handles nested arguments.

telopt.c       Disabled telnet handling when using #run.

mapper.c       Added better UTF-8 handling for room symbols.

net.c          Added the RECEIVED PROMPT event.

variable.c     Fixed a bug in #format with left aligning meta text.

mapper.c       Fixed a bug with path finding related to weighted rooms.

mapper.c       Added #map flag symbolgraphics option to display the room symbol
               instead of a drawing symbol when in non asciigrahpics mode.

mapper.c       Added #map color here option to set the color of the current
               location.

mapper.c       Fixed a path finding issue related to the avoid flag.

Sep 2011       2.00.8
--------------------------------------------------------------------------------

main.c         No more advertisements.

mapper.c       Back to void rooms only being allowed two exits, as handling
               multi-exit void rooms adds too much complexity.

mapper.c       Updated the fill_map routine to use breadth-first initialization
               which should significantly improve execution times.

prompt.c       Added proper UTF-8 string length checking for prompt drawing.

mapper.c       Room names are no longer automatically set on creation.

mapper.c       Added the #map vnum command to change the current vnum.

mapper.c       #map link now requires the 'both' argument for a two-way exit
               to be created.

variable.c     Added support to #format for %f to print floating point numbers.

variable.c     Fixed color spacing bug in #format's %s handling.

mapper.c       Added terrain as a searchable option to #map list, goto, find,
               and run.

mapper.c       Added roomweight to the #map get and #map set options. By
               default the weight of a room is set to 1.0 and can be anywhere
               from 0.001 to 1000. The path finder will favor rooms with a low
               weight.

mapper.c       Made the layout of #map info more aesthetically pleasing and
               added the listing of entrances.

substitute.c   Fixed bug where functions could overwrite the original
               substitution's arguments.

highlight.c    Added support for xterm 256 color names, dark azure, dark ebony,
               dark jade, dark lime, dark orange, dark tan, dark silver, dark
               violet, light azure, light ebony, light jade, light lime, light
               orange, light tan, light silver, light violet.

variables.c    Added the %A #format option which prints the corresponding ASCII
               value of the given character. Useful for low level string
               handling.

Apr 2011       2.00.7
--------------------------------------------------------------------------------

main.c         Added -s option to launch tt++ with a custom seed, undocumented
               till I get to think it over.

math.c         Improvements to #switch.

telopt.c       Added basic low level VT100 stripping for answer back codes.

telopt.c       Added MSDP array support.

mapper.c       Added a set and get option to #map exit that stores and
               retrieves from a data field.

mapper.c       Added the terrain and data fields to #map set and #map get. The
               data field is intended to contain a table, eliminating the need
               for future extensions.

system.c       When using #run followed by #zap the created child process will
               be properly killed instead of left to hang as a zombie process.

tick.c         When setting a delay the final delay time is echoed.

event.c        Added some extra security to event triggers.

telopt.c       Added MTTS support. On a third TTYPE request MTTS will be
               reported followed by a bitvector that indicates whether ANSI,
               VT100, UTF-8, and 256 colors are enabled. The UTF-8 and 256
               color settings can be configured by the user. VT100 is reported
               as disabled if #split mode is enabled - this because the split
               screen mode needs to be disabled for server side VT100
               interfaces to work.

system.c       Added some extra security to the #script command.

system.c       Changed the #script command to behave like a two argument
               command in preperation of removing the rather awkward
               single argument support.

line.c         Added #line ignore option to execute a command without
               checking any triggers.

config.c       Added a 256 COLOR option. When called with auto it'll guess at
               the terminal's 256 color capabilities.

variable.c     When setting a variable the final variable definition is echoed.

variable.c     Added support for BIG5 and UTF8 string formatting.

cursor.c       Added support for BIG5 and UTF8 input handling.

config.c       Added session based BIG5 and UTF8 #config CHARSET option.

substitute.c   Fixed word boundary matching for substitutions.

highlight.c    Fixed word boundary matching for highlights.

nest.c         Math is no longer performed on table keys, mainly to reduce
               annoying false positives, and because the behavior can be
               scripted with math functions. Math is still performed when
               looking up an index.

path.c         Renamed #path map to #path show, #path map still works, but it
               doesn't properly describe what the command does.

path.c         Added #path unzip option that'll load a speedwalk.

line.c         #line logverbatim is now fully verbatim.

log.c          Added a #log off option. #log append and overwrite can now be
               called while logging is already enabled.


Jan 2011       2.00.6
--------------------------------------------------------------------------------

buffer.c       Added better multi-line scroll back handling when word wrap is
               disabled.

telopt.c       Braces are now properly converted in raw gmcp data.

highlight.c    Fixed a bug causing only the first highlight on a line to
               trigger.

line.c         Added a #line {verbose} {<commands>} option which forces
               verbosity on the given commands.

buffer.c       The first match for #buffer find is now 1 instead of 0.

buffer.c       Added support for negative page numbers, causing #grep to search
               from the beginning to the end of the scroll back buffer. The
               first page is now page 1 instead of page 0.

buffer.c       Added a NULL check to prevent possible crashes, not ideal as it
               hides an underlying bug.

net.c          Added the RECEIVED OUTPUT event with %0 containing the received
               output from the server. Can be used to create multi-line
               triggers, though it wouldn't be very efficient.

main.c         No longer enabling DECCKM on startup so keypad mode works
               correctly with MinTTY, it should also result in more reliable
               cross-terminal behavior. This might change the sequence of key
               presses on some systems, so remap macros that stop working.

mapper.c       Added #map resize <size> option to increase the maximum number
               of rooms.

mapper.c       Added #map get worldsize option.

mapper.c       Added #map get worldflags option and fixed some displaying issues
               in the #map exit command.

update.c       Added several time events, YEAR, MONTH, WEEK, DAY, HOUR, MINUTE,
               SECOND, DATE mm-dd, DATE mm-dd hh:mm, TIME hh:mm, TIME hh:mm:ss.

               Events like YEAR 2012, MONTH 04, HOUR 13, are valid as well.

               %0 to %6 hold year, month, week, day, hour, minute, and second
               for each event.

math.c         Added support for automatic dd:hh:mm:ss time to second
               conversion. For example, #math test 1:12:32:17 would store
               131537 in test. #delay 10:00 #bell would ring the terminal bell
               after 10 minutes. This change will effect associative arrays
               consisting of numbers and colons.

tinexp.c       Updated #replace to support regular expressions. Like with the
               #regex command the &1..&99 arguments can be used.


Oct 2010       2.00.5
--------------------------------------------------------------------------------

session.c      Fixed split settings not getting properly inherited from the
               startup session.

advertise.c    Updated with 2011 sponsors.

system.c       do_script() and do_system() now call refresh_terminal(), this
               due to php calls messing up the terminal settings.

terminal.c     Added the refresh_terminal() function which will reset the
               terminal settings to the tintin default.

mapper.c       Fixed the MAP EXIT ROOM event, it was reporting the next room
               rather than the current room for %0. %1 now holds the new room,
               and MAP ENTER ROOM will hold the old room in %1.

mapper.c       Added the option to make vnum specific events, like MAP EXIT ROOM
               42 or MAP ENTER ROOM 27.

vt102.c        Fixed bug in the VT102 state handler.

mapper.c       Added the option to provide a vnum for #map delete.

tokenize.c     Fixed a bug with the verbose state being lost when starting a
               new session using an alias.

tinexp.c       Fixed a bug with embedded variables not getting substituted when
               used in nested variables.

Aug 2010       2.00.4
--------------------------------------------------------------------------------

tokenize.c     Added a better verbatim and verbosity handler to more
               generically deal with aliases and input triggered events.

mapper.c       Several mapper messages are no longer displayed when used in
               scripts.

vt102.c        Added proper \e[0;0r VT100 handling.

telopt.c       Added IAC DONT TTYPE handling, allowing servers to reset the
               TTYPE negotiation state.

telopt.c       Added support for cycling through terminal types. On the first
               TTYPE request TINTIN++ is reported, on the second request the
               TERM environment variable is reported.

misc.c         #zap now takes an optional argument to zap a specific session.

text.c         When UTF8 is defined in tintin.h UTF8 characters should get
               wordwrapped correctly.

telopt.c       Added support for module like MSDP events.

mapper.c       Added #map uninsert <direction> command which does the exact
               opposite of the insert command.

mapper.c       Added #map at <location> <command> command which executes the
               given commands at the given location.

variable.c     Allowing math in #format %t time seeds.

path.c         Fixed #path zip command.

prompt.c       Added better #prompt {line} {substitution} {0} support to print
               a mud prompt and pending input on the 0 line.

mapper.c       Added #map map 80x20 <filename> {a} option to log in append
               mode, by default an overwrite is performed.

path.c         Added the option to use #path load {n;e;s;w;u;d}

path.c         When using #path run {delay} you can remove pending run commands
               (fairly) safely using: #undelay PATH %d
               This will also work for #map run {location} {delay}

Jul 2010       2.00.3
--------------------------------------------------------------------------------

mapper.c       When path finding the path will be highlighted on the map.

telopt.c       Added support for GMCP events and JSON to TINTIN conversion.

mapper.c       Merged the #map exit and #map exitdir into the #map exit command,
               adding options for COMMAND, DIRECTION, FLAG, NAME, and VNUM.

mapper.c       Added support for exit flags, no actual exit flags have been
               implemented yet.

mapper.c       Added #map goto {vnum} {dig} option to have goto dig a room
               if the room does not exist.

mapper.c       Added #map dig {dir} {<vnum>} option to dig an exit to the
               specified vnum.

mapper.c       Added NOFOLLOW flag support to stop auto following of the
               mapper.

nest.c         Fixed freeze bug caused by using a semi-colon between
               associative array elements.

variables.c    Statements like %+10s now ignore colors.

variable.c     Escapes are now handled correctly by %L in #format.

input.c        Fixed an issue in echo_command causing broken packets to
               be echoed without triggering any actions or events.

mapper.c       When setting an exit command it will work like an alias when
               in that room.

list.c         #list {var} add now allows semi-colon separated arguments.

list.c         #list {var} create now allows semi-colon separated arguments.

variable.c     #variable allows additional arguments which can be used to
               merge nested variables.

nest.c         Added add_nest_node function which is a copy of set_nest_node
               except that it doesn't clear the variable.

telopt.c       Added MSDP_OPEN and MSDP_CLOSE support.

telopt.c       MSDP arrays no longer generate an event for each item, instead
               a list is generated.

tintin.h       Lowered BUFFER_SIZE to 20000 because of crash reports.

files.c        #write now only saves triggers that do not belong to a class.

mapper.c       Added MAP ENTER MAP and MAP EXIT MAP events.

split.c        Redrawing the VTMAP whenever the split settings are reset,
               typically on session switch and screen resize.

Apr 2010       2.00.2
--------------------------------------------------------------------------------

line.c         Added the #line substitute options which allows the
               substitution of variables, functions, colors, and
               escape codes in the given argument.

config.c       Added a config option to enable BIG5 support.

mapper.c       Added an optional vnum argument to #map get and #map set,
               calling #map get on an invalid vnum results in the variable
               being set to 0 while #map set calls on invalid vnums do
               nothing.

terminal.c     Added SCREEN RESIZE event.

session.c      Added SESSION ACTIVATED and SESSION DEACTIVATED events.

nest.c         Nested variable calls to non existing nests now return
               "" rather than "0", this to allow $var[%*] calls to work
               correctly with empty variables. I originally added the "0"
               response for if checks, but this is obsolete with the
               much more reliable &variable[] call.

buffer.c       Added a check to avoid a potential crash on displaying the
               scrollback buffer in show_buffer(), needs a better fix but I
               don't have the time and patience.

tables.c       Removed #suspend command, #cursor suspend is available instead.

tokenize.c     Added BIG5 handling for #parse

tintin.h       Fixed an error in the SCROLL macro that determines whether
               something is printed inside or outside of the scrolling region.

tinexp.c       Function arguments are no longer space but semicolon separated.

mapper.c       Updated messages to be non triggerable and to only echo on manual
               input.

Feb 2010       2.00.1
--------------------------------------------------------------------------------

help.c         Added documentation for #map exitdir

net.c          Fixed a bug with color patch prepending the current line's color
               rather than the previous line's color.

vt102.c        Improved 256 color patching handling.

vt102.c        Added better \b handling, so muds using backspaces won't cause
               wrapping or scrollback issues.

path.c         #path load and #path save now load and save to variables, rather
               than aliases.

mapper.c       Added #map dig {<direction>} {new} option.

mapper.c       Added support for loading map files edited in Windows.

tinexp.c       Added support for separating function arguments using semicolons.

buffer.c       Now only stores a buffer line as a simple variable if no upper
               bound argument is given. Added support for dealing with a
               lower upper bound to store the lines in reverse.

math.c         Fixed floating point handling.

data.c         Fixed floating point associative array handling.

Jan 2010       2.00.0
--------------------------------------------------------------------------------

list.c         Changed substitution order for #list add to substitute before
               breaking up the arguments.

tinexp.c       Added escaping of existing functions using @@

tokenize.c     Added tokenization of #regex.

data.c         A trigger's priority can now be a floating point numbers.

tinexp.c       Fixed COMMAND_SEPARATOR related bug introduce in 1.99.9.

misc.c         Added escape substitutions to vt row echo calls.

buffer.c       Added #buffer get option.

Nov 2009       1.99.9
--------------------------------------------------------------------------------
update.c       Fixed crash bug with delays.

math.c         Fixed issue with negative numbers.

main.c         Fixed infinite reconnect trigger loop with #end.

tintin.h       Can now alter the COMMAND_SEPARATOR definition in tintin.h to
               change the command separator character.

buffer.c       Added #buffer clear option.

math.c         Fixed bug with ~ handling.

tick.c         Fixed a bug with delays not substituting variables right away.


Sep 2009       1.99.8
--------------------------------------------------------------------------------
math.c         Added check to bypass inf and nan in tintoi.

update.c       Fixed a potential memory overflow in the input parser.

misc.c         Fixed displaying bug with semi-colons in echos.

nest.c         Added support for $variable[regex] to return lists. For
               example $variable[%*]

tinexp.c       No longer required to escape literal ^ and $ signs.
               So #regex {A ^ B} {A ^ B} returns true now instead of false.

net.c          Instead of exiting, tintin tries for 1 second to write data
               to a session before closing the session.

tinexp.c       $$<string> only gets converted to $<string> if $<string> makes
               a valid variable. Same for &&<string>.

tokenize.c     Added support for using ; in #foreach.

misc.c         Added support for using ; in #forall.

mapper.c       Updated the map grid to allocate memory for a future
               #map dump 99x99 <file> command.

Jul 2009       1.99.7
--------------------------------------------------------------------------------
mapper.c       Added #map color <rooms|exits> <color> option.

mapper.c       #map list uses all location fields now, displays distance, and
               no longer displays exits.

mapper.c       Added desc, area, and note field to rooms.

mapper.c       Added checking for exits as well as desc, area, and note for
               the map goto and map find commands.

tokenize.c     Substituting the arguments of #return.

nest.c         $variable[] returns "" if the variable exists but has no nests

*.c            Updated triggers to substitute variables.

tinexp.c       Added %i and %I to toggle case in-sensitive matching.

misc.c         Added #echo {{spam}{row}} support.

parse.c        Yet another attempt to get verbatim mode working properly.

variable.c     Renamed #replacestring to #replace

tinexp.c       All commands now use tintin regular expressions. Instead of
               * and ? use %* and %? - for perfect matches uses ^string$.

               This change affects the #regexp and #if commands.

tokenize.c     Added #write support for #loop and #foreach.

tokenize.c     Added #foreach {list} {variable} {commands}

tokenize.c     #loop syntax is now: #loop {min} {max} {variable} {commands}

variables.c    The argument list of #format and #echo are no longer nested,
               this probably requires many scripts to be updated.

nest.c         Now only showing non existing nested variables as 0, unnested
               variables will be shown as $variable if they do not exist.

files.c        Added support for saving nested variables.

list.c         Updated list support for nested variables.

data.c         The kill command now takes a 2nd argument allowing to kill
               specific items in the chosen list.

nest.c         Added support for math within brackets.

math.c         Added get_alnum routine.

nest.c         Added support for $variable[] showing all indices.

nest.c         Added support for $variable showing all nested variables.

nest.c         Can now assign nested variables directly nested pairs of braces.

nest.c         Added support for &variable reporting the variable's index.

tokenize.c     Added #else command.

parse.c        brackets now provide nesting so #var bla[bli bli] x will
               execute as #var {bla[bli bli]} instead of #var {bla[bli}

data.c         Accessing an variable index now requires +1 instead of 1.

mapper.c       Added MAP EXIT ROOM event.

tokenize.c     Added #switch #case and #default commands.

math.c         Fixed crash bug with #math.

list.c         Added list srt and ins support for nested list variables.

data.c         Sorting numeric variables as integers instead of as strings.

text.c         Fixed crash bug in wordwrap code.

net.c          Fixed double action triggering on prompts in split mode.

variables.c    $1 now references the first variable, $2 the second, etc.

variable.c     Uninitialized variables now return 0.

data.c         Added nested variables. As in #var $bla[this][that] 1

data.c         Changing from linked lists to sorted arrays.

cursor.c       Replaced #cursor echo with 'echo on' and 'echo off'

cursor.c       Modifying the input buffer while tabbing will reset the
               tab finder.

May 2009       1.99.6
--------------------------------------------------------------------------------
cursor.c       Added forward and backward tab completion patch by Ben Love.

forkpty.c      Added forkpty patch by David Champion. It allows tintin to
               run on Solaris and other systems that lack forkpty().

April 2009     1.99.5
--------------------------------------------------------------------------------
*.c            Made code c++ compatible.

system.c       Added 2nd argument to textin for a cumulative per line delay.

telopt.c       Added event handlers for MSDP, NEW-ENVIRON, and ZMP.

substitute.c   #sub {trigger} {.} no longer gags text, use #gag instead.

substitute.c   Now allowing multiple substitutions per line which are
               automatically substring substitutions.

March 2009     1.99.4
--------------------------------------------------------------------------------
utils.c        Fixed 100 move map crash bug.

input.c        Now sending \r on enter when using #run, seems to give the best
               behavior.

log.c          Added xterm 256 color html logging.

terminal.c     Disabled default ctrl-s and ctrl-q behavior.

March 2009     1.99.3
--------------------------------------------------------------------------------
data.c         Now properly inheriting triggers from the startup session.

net.c          Now fetching IP address when connecting to a server.

variable.c     Now possible to use escape codes in #replace

vt100.c        Tabs are no longer stripped in the scrollback buffer.

help.c         Updated event helpfile with event arguments.

telopt.c       Added generic telnet subnegotiation event.

telopt.c       Added better broken packet support for telnet negotiations.

variable.c     now possible to use #var bla {} to set an empty variable.

event.c        Extended the event handler to easily accept additional arguments.

tinexp.c       Now possible to send NUL bytes with #send using \x00 or \c@.
               This is as far as the support for non strings goes though.

tinexp.c       Can use #regex on an empty string now.

input.c        Resetting command color at end of command.

tinexp.c       %%w, %%*, etc, should escape properly now.

parse.c        Fixed VERBATIM behavior, aliases can now be used in verbatim
               mode.

alias.c        Now possible to #ignore aliases.

highlight.c    Fixed highlights.

March 2009     1.99.2
--------------------------------------------------------------------------------
tinexp.c       Added pre-compiler for triggers, making them execute much faster.

input.c        Macros now default to \ca to \cz for control characters instead
               of readline's \C-a to \C-z. This because PCRE uses \c and it
               makes sense to use a universal system. Old control codes still
               work.

mapper.c       Can now use #map create {number of rooms}, by default the number
               of rooms is set to 15000. World size is stored as C <number> in
               map files.

February 2009  1.99.1
--------------------------------------------------------------------------------

telopt.c       Added MSSP support, use: #config {debug telnet} on, to see the
               output from a MUD server supporting MSSP.

tinexp.c       Added pre-parser to convert tintin globs to regexps.

tinexp.c       Now using PCRE (Perl Compatible Regular Expressions)

tinexp.c       Added \cx "control-x", where x is any character.

tinexp.c       Added \0xx, where x is an octal number.


February 2009  1.99.0
--------------------------------------------------------------------------------

misc.c         #showme and #echo now can have a / as a suffix to stop a
               linefeed from being added.

vt100.c        Added an extra measure to prevent losing track of the cursor
               position.

documentation  Updated the credits file and my mods file.

tables.c       Added a full telnet option table.

tables.c       Added END OF PATH event.

tokenize.c     Now shows debug info for triggers with #debug enabled.

buffer.c       No longer reprinting screen using page-up at the top of the
               scrollback buffer to stop refresh lag with slow terminals.

tinexp.c       Fixed incorrect displaying of xterm 256 background colors.

config.c       Removed timestamp config option, a scripted #event based
               alternative has been added to the SCRIPT file.

cursor.c       Added cursor option for auto tab.

config.c       Added auto tab option to set the amount of lines of the scroll
               back buffer used for auto tab completion.


January 2009   1.98.9
--------------------------------------------------------------------------------

variable.c     Rewrote the 'd' format option to use a digit, mainly to enable
               the + option of normal digit formatting.

parse.c        Fixed speedwalk toggle bug.

tinexp.c       Added <g00> to <g23> xterm 256 color codes to support the
               greyscale colors.

history.c      Updated history command with the list, size and character
               options.

tokenize.c     Fixed ; issue sending out enters in the pre-parser.

action.c       Fixed ; issue in actions, which managed to unfixed itself.

history.c      Updated the history command, now takes #history list to view
               the command history.

buffer.c       Updated the buffer command to use generic command interface.


December 2008  1.98.8
--------------------------------------------------------------------------------

tokenize.c     New pre-parser to deal with nesting issues.

misc.c         Added #while {var} {commands} command.

misc.c         #loop no longer works like a while loop.

misc.c         The $loop, $parse, and $forall variables are no longer
               automatically set.

Makefile.in    Added tokenize.o

files.c        #write now formats its output.

tinexp.c       Casting regex arguments to integers so it works properly on os x.

config.c       Added a config option to enable/disable MCCP support.

variable.c     Changed %t format option to use a strftime format instead to
               print the current time.

telopt.c       Streamlined telopt handling slightly to deal with MCCP errors.


October 2008   1.98.7
--------------------------------------------------------------------------------

alias.c        Variables can be used in alias triggers, working pretty much
               the same way as they do in actions.

mapper.c       When leaving a map a last room is set, which can be returned
               to with #map return. The last room is stored when saving a map,
               and #map return will work as well after reading in a map.

help.c         Updated the math helpfile with available bit operations.

misc.c         #echo no longer triggers actions.

help.c         Updated the showme and echo help entries.

mapper.c       #map map now takes an optional <x>x<y> size argument and an
               optional filename argument to log the map output to file.
               Useful for people who want to tail -f -s 0.1 a map window.

config.c       Added a timestamp config option to add timestamps to log
               files using the strftime format.


September 2008 1.98.6
--------------------------------------------------------------------------------

mapper.c       No longer need braces to use the delay option in map travel
               and map run.

mapper.c       Added static room flag.

mapper.c       Can now specify on/off for setting global flags and room flags.

mapper.c       Added breadth first support for the map drawing routine, based
               on code by Bryan Turner.

mapper.c       Added support for 3 letter room symbols.

alias.c        Variables passed along as an alias argument now go by value
               instead of by reference.

mapper.c       Added the asciivnums flag which displays room vnums in the ascii
               map. 


August 2008    1.98.5
--------------------------------------------------------------------------------

mapper.c       Added #map jump <x> <y> to goto rooms using coordinates
               relative to the user's current room.

list.c         Added #script {var} {command} option.

input.c        Fixed bug with the first input character being ignored in
               character mode.

tinexp.c       Can now escape variables using 2 or more dollar signs.

cursor.c       Fixed bug with ctrl-w

cursor.c       Fixed bug with ctrl-r's input offset.

mapper.c       When using #map find, run, and goto and there are multiple
               matching rooms the nearest room will be returned.


July 2008      1.98.4
--------------------------------------------------------------------------------

cursor.c       Added glob/regex support to reverse history searches.

tinexp.c       wildcard searches should work as old again, and regexp searches
               work more like old wildcard searches.

tick.c         Can use variables for ticker names.

mapper.c       Changed #map exit to #map exitcmd

mapper.c       Added #map exitdir command, which allows setting a direction
               for unusual exits so they can be displayed on the map.

mapper.c       Changed #map walk to #map run, and fixed the optional delay
               argument.

mapper.c       Fixed optional delay argument for the #map travel command.

mapper.c       Void rooms can have more than two exits again if the exits form
               a straight line.

mapper.c       Fixed going through void rooms with #map travel.

variable.c     #format will use the current time if no time value is provided
               for the %M %Y %D %d and %t arguments.

mapper.c       asciigraphics is now the default map display setting.

terminal.c     Enabled the ISIG flag allowing ctrl-c to be mapped.

cursor.c       Updated ctrl-d to allow exiting tintin.

cursor.c       Updated ctrl-c to clear the line rather than exiting tintin.

config.c       Changed #config {echo command} to #config {command echo}

config.c       Added the #config {command color} {<000>} option.

mapper.c       #map insert now allows adding a roomflag as the 2nd argument.

tinexp.c       Can now use %{variable} besides %0 - %99 in actions.


June 2008      1.98.3
--------------------------------------------------------------------------------

mapper.c       It's now possible to use strings in the map legenda, mainly for
               terminals supporting UTF-8.

mapper.c       Void rooms now work with unusual exits as well.

mapper.c       Added some unlisted map commands to the #map and #help listing.

input.c        Verbatim mode now only works on manual input, actions and macros
               will have their commands processed normally.

mapper.c       #map map now accepts a given radius.

config.c       #config packet patch now takes a floating point seconds argument
               instead of milli seconds. The valid input range is between 0.00
               and 10.00 seconds.

config.c       Added the #config regexp on/off option.

input.c        Added the RECEIVED INPUT event.

tinexp.c       Added the match function to work with #config regexp.

cursor.c       Added support for deleting words forwards using alt-d

path.c         Added #path zip option to format a created path into
               speedwalk notation.

tinexp.c       \[ and \] no longer escape to { and }, instead \x can
               be used, the values are shown in #help escape.

tinexp.c       All regexp's should substitute escape codes.

tintin19.txt   Rewrote the large manual file to contain a brief up to date
               manual instead. #help remains the primary help source.


May 2008       1.98.2
--------------------------------------------------------------------------------

tables.c       Home and End now use cursor home and end.

input.c        Added support for \x and \b in macros.

net.c          Fixed a bug with stacking prompts.

cursor.c       Pressing ctrl-r (history search) while searching will place
               the found search in the input field.

cursor.c       Added left_word and right_word for alt b and f behavior.


March 2008     1.98.1
--------------------------------------------------------------------------------

main.c         Command history is no longer automatically saved and loaded.

history.c      Added history read and write option.

cursor.c       Fixed displaying of ctrl-r reverse command history search.

*.c            Added punctuation to most messages.

*.c            Fixed function arguments overwriting action arguments.

tinexp.c       { and } in triggers will be translated to \x codes.

line.c         Added the line command to group #gagline and #logline.

tables.c       Added the 'program termination' and 'received line' events.


February 2008  1.98.0
--------------------------------------------------------------------------------

cursor.c       Added the #cursor enter option

input.c        Fixed #macro usage in character mode.

chat.c         Fixed an exploit to erase files with #chat.

chat.c         Fixed a crash bug in the negatiation routine, apparently
               sscanf doesn't check line feeds.

chat.c         Lowered the maximum read from socket size to half of
               BUFFER_SIZE to prevent buffer overflows.

log.c          Fixed a coloring bug with html logging.

alias.c        Fixed a bug with alias parsing.


December 2007  1.97.9
--------------------------------------------------------------------------------

highlight.c    Added 'dark' as a valid color name.

vt102.c        Added get_color_codes function.

text.c         Now printing the previous color code on each new line.

config.c       Added a color patching option.

log.c          Fixed append logging in html mode for cygwin.

parse.c        Went back to the more robust old school memory usage with
               some changes to still allow for recursion.

telopt.c       re-enabled GA prompt handling.

main.c         Fixed a bug with the startup argument routine.


November 2007  1.97.8
--------------------------------------------------------------------------------

input.c        Fixed some chinese character related issues.

parse.c        Fixed some chinese character related issues.

tinexp.c       Added the option to use %00 to %99

tinexp.c       Must now escape using %% rather than %%90

path.c         Added #path run <delay> option.

highlights.c   #highlight now colors all matches on a line.

tinexp.c       Functions now only use %0 to %99 rather than &*


October 2007   1.97.7
--------------------------------------------------------------------------------

variable.c     Fixed some coloring issues with the %w format option.

input.c        Macros no longer trigger with config convert meta enabled.

net.c          Fixed prompt handling issue for triggers in split mode.

tinexp.c       Added the regexp command to use regexp string comparisons.


August 2007    1.97.6
--------------------------------------------------------------------------------

input.c        Fixed some server side VT issues with command echoing.

text.c         Tintin no longer line wraps when word wrap is disabled, this to
               fix pasting issues, and assuming that most terminals will line
               wrap correctly.

history.c      No longer add input with less than 2 bytes to the history.

cursor.c       Added prefix history searching.

files.c        Fixed verbose behavior when reading a file which reads a file.

net.c          Fixed address reporting in #session.

variable.c     Added %w option to wrap text.


August 2007    1.97.5
--------------------------------------------------------------------------------

               Fixed some bugs in socket handling.

               #run now shows the stderr when failing to run.

               Fixed a bug with #config {packet patch}.


July 2007      1.97.4
--------------------------------------------------------------------------------

               Added the #run command to run various applications inside tintin.

               Added packet defragmentation at the socket level.

               Fixed a buffer overflow in the scrollback buffer's prompt
               handling.


July 2007      1.97.3
--------------------------------------------------------------------------------

               Added the #script command to run any kind of script client side.

               Fixed a variety of minor bugs.


June 2007      1.97.2
--------------------------------------------------------------------------------

               Fixed buffer overflow with receiving several prompts.

               Fixed bug with scrollback lines not being properly deleted.

               Added #map explore and #map travel options.


May 2007       1.97.1
--------------------------------------------------------------------------------

               Added #map insert

               Fixed bug with #list fnd

               Fixed bug with prompts in buffer

               Set #delay {name} {command} {delay} as alternative syntax
               opposed to #delay {delay} {command}

April 2007     1.97.0
--------------------------------------------------------------------------------

chat.c         Configure now detects a missing pthread library.

tick.c         Delay now takes a name argument as the 3rd argument.

tick.c         Added #undelay command.

cursor.c       Added the option to paste deleted input with ctrl-y


March 2007     1.96.9
--------------------------------------------------------------------------------

list.c         Added #list {list} clr option to empty a list.

list.c         Added #list {list} srt option to insert in alphabetic order.

parse.c        Defined a COMMAND_SEPARATOR variable instead of ';' checks.

utils.c        Fixed some display issues for #showme and untriggered prompts
               in split mode.
session.c      Now uses #session {name} {host} {port}

tinexp.c       Can now use %0 (all args) and %1 to %9 in functions.

memory.c       Increased the maximum internal memory size from 10 to 50KB.

debug.c        Set the maximum number of iterations to 10K.


February 2007  1.96.7
--------------------------------------------------------------------------------

mapper.c       Fixed fast forwarding shortest path searches through void rooms.

mapper.c       Fixed #map link not deleting old links.

mapper.c       Fixed drawing of void rooms.

help.c         Added a cleaned up version by Simon.

cursor.c       History next and prev now put the cursor at the end of the line.

gag.c          Seperated gags from substitutions.

files.c        Inproved accuracy of #read's error report.

path.c         Merged all path commands into one generic path command.


March 2007     1.96.8
--------------------------------------------------------------------------------

main.c         Added getopt supported command-line argument handling.

main.c         Added [-t title] option to set the title bar.

files.c        Now stripping all trailing spaces and tabs in #read.

utils.c        Added show_debug command to display debug messages a bit easier.

net.c          Added IPv6 support.

cursor.c       Added cursor_echo function to toggle local echo.

cursor.c       Added cursor_insert function to toggle insert mode.

tinexp.c       Using $variable[index] now works with lists.

variable.c     Can set list indexes with #var {variable[index]} {text}


January 2007   1.96.6
--------------------------------------------------------------------------------

cursor.c       Fixed behavior of ctrl-e for osx.

log.c          Fixed newly introduced crashbug with #logline

highlight.c    Now parses <###> color codes to allow for 256 colors.

function.c     Can now use undescores in function names.

tables.c       Added map list for #map undo and message handling.

main.c         Added pathdirs for diagonal exits and spatial coordinate info.

mapper.c       Now using spatial coordinates from pathdirs. This requires
               users to reset their saved pathdirs. If used correctly mapping
               should work for muds with a non standard exit system.
mapper.c       Added movement history for #map undo

mapper.c       Updated #map undo to use the map movement history

cursor.c       Fixed bug in ctrl-e behavior

misc.c         Removed old debug message in #send.

mapper.c       Added room symbols.

mapper.c       Added #map set to set various attributes

mapper.c       Added #map get to get various attributes and store them as
               variables.

mapper.c       #map walk {location} {0.5} will now run to the location with
               0.5 second delays between commands.

input.c        Added input_printf for consistent echo handling

tables.c       Added generic variable and function substitution for #map

input.c        Now checking for negative characters when converting meta
               characters. Should fix issues when creating macros with
               swedish and german characters.

buffer.c       Can now use #buffer f with negative numbers to find the first
               instead of last occurance of a string. Also made the no match
               found string triggerable.

mapper.c       Can now use case insenstive room finding with wildcards in
               #map find and other room search related commands.

tintin.h       Placed lists in alphabetical order.

event.c        Added a basic event system, check #event


December 2006  1.96.5
--------------------------------------------------------------------------------

buffer.c       fixed up color handling of commands.
*.c            Put on my dirty boots and annihilated all lib readline related
               stuff. Readline sucks donkey balls. You can quote me on that.
terminal.c     Merger of echo.c and scrsize.c
terminal.c     Added init_terminal to force character mode for input handling.
terminal.c     Added custom screensize handling.
rl.c           Now forwarding data on stdin to input.c
input.c        Added basic command parsing options.
history.c      Added tintin-esque command history support.
cursor.c       Deals with cursor handling for input.c
tables.c       Added a command table for cursor.c
cursor.c       Added support for some readline-esque input handling.
tab.c          Added my own (improved) tab handling.
tab.c          Moved tab handling to cursor.c
vt102.c        Made some improvements to the VT102 support.
cursor.c       Added history browsing with up, down, ctrl-p and ctrl-n. Made
               some minor improvements over the readline version.
utils.c        Added ins_sprintf function that properly inserts a string
               within another strong. Has formatting capabilities.
input.c        Added process_input as the main input function.
input.c        Added read_line function for default command parsing.
input.c        Added read_key function for character mode.
main.c         Moved suspend and exit functions to main.c
main.c         Fixed #suspend handling.
split.c        Now adjusting NAWS when changing split screen.
cursor.c       Added do_cursor for using cursor features in macros.
history.c      Added do_history for history manipulation.
rl.c           Moved to update.c
*.c            Tintin is now officially lib readline free. Good riddance.
               The binaries are 40% smaller.
tinexp.c       Added 256 xterm color support using <aaa> to <fff> with rgb
               values. Background colors are set with <AAA> to <FFF>
tintin.h       Added gtd->flags for global flags instead of using cludgy
               flags on gts->flags.
cursor.c       Added cursor_redraw_line routine which adds readline input
               scrolling behavior. Tintin will probably work quite poorly on
               non VT100 terminals now.
tables.c       Added list flags to work around the fact that I use lists for
               stuff they weren't originally intended for. Updated list parsers
               throughout the source code.
main.c         Added a signal handler for SIG_TSTP to handle ctrl-z smoothly.
input.c        Escaped unmatched sequences are now automagically meta converted.
cursor.c       history prev and next can now be used in combination with the
               history search function.
mapper.c       Improved map drawing by using virtual coordinates. 
mapper.c       Added a flag to enable vt graphics mode. A hopefully universal
               legenda is: 250 223 222 200 220 186 201 204 221 188 205 202 187
               185 203 206 246
mapper.c       Added a flag to draw 6x3 ascii graphics which allows displaying
               rooms going ne, nw, se, sw, u, and d.
misc.c         Can no longer use commas in #loop. When using 1 argument with
               #loop it's assumed 
misc.c         Can now use math in delays, as in #delay 1d5 smile.
mapper.c       Added the void roomflag which can be used to turn rooms into
               links. This is mainly useful to fit overlapping areas on the
               same map without using the hide flag.


December 2006  1.96.4
--------------------------------------------------------------------------------

class.c        classes are now properly inherited from the main session.
misc.c         fixed chinese character issue with #parse.
parse.c        fixed parsing issues introduced in 1.96.3.
mapper.c       debugged and updated alpha mapping code to beta.
tables.c       added a mapping related sub-command table.


November 2006  1.96.3
--------------------------------------------------------------------------------

telopt.c       Updated telopts to login on globalvillage bbs.
buffer.c       Added buffer find option, which works much like grep but instead
               places the scrollback buffer at the given search string.
tinexp.c       Can now add lists of keywords between square brackets divided
               by seperators, for example [his|her|its] in actions. The actual
               text is stored in the next %0-9. Cannot be used for highlights.
list.c         array_fnd function allows searching for words in lists.
path.c         can now save loaded paths backward.


August 2006    1.96.2
--------------------------------------------------------------------------------

variables.c    Removed #getitemnr, obsolete with the #list command.
variables.c    Removed #getlistlength, obsolete with the #list command.
variables.c    Removed #removestring, obsolete with the #replacestring command.
math.c         Added tineval to properly evaluate == and !=
chat.c         Now setting NONBLOCK on the chat port due to reports about
               disconnects hanging tintin.
config.c       Added #config {log level} {low|high} which is a hidden config
               option. Defaults to high, when set to low tintin will log the
               raw mud output.


August 2006    1.96.1
--------------------------------------------------------------------------------

misc.c         Fixed a spacing issue in do_showme.
mapper.c       Fixed map drawing.
telopt.c       Fixed telnet negotations to login on ISCA BBS.
math.c         Commas are now stripped from numbers.
math.c         Added support for floating point math.
tick.c         Can use 1d10 etc for the times in #delay.
main.c         Added -h and -e as startup options.


June 2006      1.96.0
--------------------------------------------------------------------------------

data.c         Rewrote #killall to accept arguments to kill specific lists.
chat.c         Added #chat unitialize.
chat.c         Added basic support for group chats.
chat.c         Added support for colored names.
highlight.c    Fixed crash bug for invalid highlights.
class.c        Fixed crash bug with #killall related to classes.
chat.c         Added #chat send which allows sending custom chat commands.
chat.c         Fixed link lost crash bug.


April 2006     1.95.9
--------------------------------------------------------------------------------

input.c        Fixed some bugs in the character mode support.
misc.c         Placed the functions in alphabetic order and added #SEND which
               will send the given argument directly to the mud. Useful for
               sending escape sequences because you cannot start a mud
               command with an escape sequence.
scrsize.c      If in character mode tintin depreps the terminal temporarily
               when sending NAWS. Yet another annoying readline bug.
chat.c         Added DND (do not disturb) feature. When enabled tintin will
               no longer accept new chat connections.
               Fixed a bug in the DNS lookup routine for addresses starting
               with a number.
               Can now chat to people by entering their ip address. Useful to
               deal with auto ip bans.
parse.c        Complex multi words aliasses are now possible.
data.c         Priority lists are now sorted alphabetically per priority level
class.c        #class class read <file> no longer parses files for the given
               class. The code was too messy to maintain. Instead it'll open
               the class, read the file, and close the file.
alias.c        Added support for complex multi word aliasses.
chat.c         Added #chat public option, accepts the all argument.
chat.c         Added #forward all which included session output
chat.c         Added #color which sets the default color
chat.c         Added a boost option for #chat accept to quadruple download
               speeds, might cause file corruption on bad connections.
class.c        Rewrote some code, #unclass should work now.
data.c         Issueing #tick {name} twice will now reset the ticker.
math.c         Fixed invalid input handling.
misc.c         Snooping a non existant session no longer crashes tintin.


March 2006     1.95.8
--------------------------------------------------------------------------------

buffer.c       While the concept works the code should be more solid. Fixed
               some bugs in the buffer code causing scrolling to crash
               on long help files.
buffer.c       Added a #buffer lock option which resembles scroll lock.
log.c          Fixed a bug in #log append which caused it to not generate
               html headers.
chat.c         Modified the threaded chat functions to minimize accessing
               global data.
chat.c         Fixed formatting bug causing chat messages containing %s to
               crash the client.
chat.c         #chat who now shows user flags
parse.c        Removed old code that allowed using " " instead of { } in
               a couple of commands such as #format. While I used it in
               some example scripts the code is causing problems.
data.c         Can now use #unmacro by exactly matching the macro instead of
               having to use \\ for a single \.
input.c        TinTin now enables character mode with echo off and SGA enabled.


December 2005  1.95.7
--------------------------------------------------------------------------------

main.c         Added a command reference table to speed up the processing of
               commands slightly.
tinexp.c       The body of a by braces surrounded variable name will be
               substituted now, allowing variables as variable names.
parse.c        No longer sending message spam when using an alias
buffer.c       Fixed a long standing crash bug in the buffer cleanup routine.
tinexp.c       Now matching arguments in triggers like the old tintin did. This
               will interfere with a couple of triggers but shouldn't be too
               big a problem. %0 to %9 will capture the smallest possible
               amount of text instead of the biggest.
telopt.c       IAC EOR and GA spams are dealt with better with {debug telnet}
               enabled.
telopt.c       Dealing with packet fragmentation in the odd case an IAC EOR or
               GA code is split, not sure if it works since it's hard to test.


October 2005   1.95.6
--------------------------------------------------------------------------------

chat.c         Added multi threading for opening new chat connections.
parse.c        Added protection for infinite loops.
utils.c        Added hex_number translation function.
tinexp.c       Can now use \x?? where ?? is a hexadecimal number.
*.c            Changed usage of \e with \033 since \e isn't supported on all
               systems.
misc.c         #debug all log, logs debug info without displaying it.
Makefile.in    make install now copies tt++ to /usr/bin
parse.c        Can now disable verbatim mode after enabling it.
tables.c       Got rid of unneeded table size for the command, help, and
               config table.
variable.c     Added %D %M %Y options to print the day month year
misc.c         Added parse command to parse strings
misc.c         Fixed double variable substitution for #echo

August 2005    1.95.5
--------------------------------------------------------------------------------

chat.c         Added some extra chat functionality: paste, serve, forward,
               ignore and peek.
tinexp.c       Fixed parsing of function arguments some more.
list.c         Added #list command with basic list support.


August 2005    1.95.4
--------------------------------------------------------------------------------

tinexp.c       Fixed some bugs in substitute that slipped in.
tinexp.c       Added skipping of chinese characters in regexp functions.
data.c         Fixed crash bug with killing classes
function.c     Fixed an issue with #return in fuctions stopping the execution
               of multiple commands.
rl.c           pressing control-c while connecting will abort the connection
               instead of exiting the program.
chat.c         Added back the chat module that was originally included with
               version 1.86. I pretty much rewrote it while at it.
configure      BIG5 configuration was giving me issues on slackware.
               Since I didn't feel like figuring out how the script works
               I changed it from --enable-big5 to --big5 and fiddled with
               the script till it seemed to work again.

July 2005      1.95.3
--------------------------------------------------------------------------------

tinexp.c       Now substituting functions and arguments (if needed) in a
               function's argument list.
tinexp.c       Ending a command with \ will escape the EOL (\r\n) which won't
               be appended to the end of the line. Same story for #showme.
telopt.c       Added negotiating of EOR (end of record)
telopt.c       IAC GA and EOR will now be seen as prompt markers.
files.c        Now skipping chinese characters in #read

July 2005      1.95.2
--------------------------------------------------------------------------------

data.c         Added option to use 'all' in #message, #ignore, and #debug to
               toggle everything at once.
files.c        Removed the #writesession command, it's obsolete with the new
               #class command.
class.c        #class write now adds #class open/close to the begin and end
               of the file.
files.c        Cleaned up a bunch of confirmation messages and made them
               gaggable.
tab.c          Variables and functions in a #tab are now substituted at
               evaluation time.

Juny 2005      1.95.1
--------------------------------------------------------------------------------

files.c        If the bracing level is off in the last line tintin reports
               the correct line instead of 0.
rl.c           reading the default readline init file when leaving tintin.
               Should help with a couple of shells not handling this properly.
echo.c         removed some experimental code that ended up causing double
               echoing when switching between sessions.
split.c        fixed screen switching for muds with native vt102 interfaces.
session.c      added #session {-|+|number} options to switch between sessions.
files.c        no longer showing output while using #scan to speed things up
               for huge log files.
misc.c         Added #return which used in an #if check allows bailing out of
               a semicolon seperated command string. If used in a #function
               you can also add an argument to it to set the result, as
               opposed to setting the $result variable directly.


June 2005      1.95.0
--------------------------------------------------------------------------------

macro.c        Added prompt handling for macro's. Still not perfect.
scrsize.c      Fixed resetting of split data when resizing the screen.
split.c        Now drawing split lines on all static regions to increase
               clarity for newbies.
misc.c         Can now use #showme {text} {row}, with a row number given
               #showme will act like #prompt.
misc.c         Can use #echo {{format} {row}} {{arguments}} as well.
rl.c           Fixed #snoop messing up in #split mode.
parse.c        Got rid of the code seperating high and low priority actions,
               no longer valid with the #gagline command.
antisubstitute Removed antisubstitutions since there seems little reason to
               ever need them.
rl.c           Checking internal messages for prompt gags now

May 2005       1.94.9
--------------------------------------------------------------------------------

files.c        Added #scan {filename} which will read in a file and send it to
               the screen as if it was send by a mud. This allows one to view
               raw color logs, turn on logging and save the file in a different
               format, as well as adding gags and other text filters to make
               things more readable. I set the default logging mode to raw
               since ansi log files can now be converted to html ones.
data.c         updatenode_list was acting odd, fiddled with it till it stopped
               crashing. Not sure what the problem was.


May 2005       1.94.8
--------------------------------------------------------------------------------

rl.c           Fixed packet patch, and added a default patcher for split mode.
               Fixed the displaying of #alias, #action, etc.

May 2005       1.94.7
--------------------------------------------------------------------------------

main.c         Fixed #split mode being handled correctly when suspending a
               session.
data.c         Removed excessive color usage when displaying triggers which was
               resulting in crashes.
rl.c           No longer clearing the screen when exiting tintin++.
table.c        Added flags for commands, so far only automatically substituting
               variables and functions for commands that have the sub flag.

May 2005       1.94.6
--------------------------------------------------------------------------------

rl.c           Now adding all keyboard input to the scrollback buffer.
rl.c           When in #split mode with no #prompt defined tintin tries to
               mimic normal behavior, which includes placing input at the
               end of the prompt.
prompt.c       #prompt matched lines are now written to the scrollback buffer,
               to simulate the old behavior make an #action executing #gagline.


May 2005       1.94.5
--------------------------------------------------------------------------------

rl.c           Fixed a bug that caused prompts to be printed twice.
debug.c        Fixed possible crash from overloading the debug stack.
variable.c     Added #debug messages for #replacestring and #format.
split.c        Fixed various #split bugs when creating or switching sessions.
buffer.c       #buffer {i} will now give some info about the scrollback buffer.
tick.c         #delay now works in the startup session. Tickers are still 
               disabled.
class.c        #class <class> read <file>, now only reads in stuff that belongs
               to the given class name. Hence in order for this to work you
               need #class <class> open, and #class <class> close, calls in
               the file itself for this to work.
help.c         Removed David Chan from the credit screen shown when starting
               up TinTin++. I'm sure he had the best intentions, but he spend
               two years making insignificant changes, fiddling with variables,
               adding patches written by others, before vanishing into thin air.


April 2005     1.94.4
--------------------------------------------------------------------------------

tintin.h       Now using strtoll instead of atoll since old platforms only
               support strtoll.
telopt.c       With #config {CONVERT META} set to ON mud output will have
               it's meta characters translated, this to aid in making color
               triggers.
split.c        Using #split 0 0 will create an input line without the split
               line. Useful for people who don't use #prompt.


April 2005     1.94.3
--------------------------------------------------------------------------------

log.c          Now flushing the log stream after every call so tailing a log
               file is an option.
class.c        Finished the #class command.
split.c        placed #prompt stuff in prompt.c
tinexp.c       Added option to start a trigger with ~ in which case colors
               are included in string comparisons and substitutions.
buffer.c       Removed the #writebuffer command, must now use:
               #buffer {write} {filename}

May 2005       1.94.2
--------------------------------------------------------------------------------

rl.c           Internal messages are now printed to both the logfile and
               scrollback buffer.
rl.c           Fixed internal messages bumping the screen while scrolling in
               locked mode.
rl.c           Fixed a bug with displaying text that slipped in.
buffer.c       Added the option to use #buffer h/u/d/e for scrolling.

tintin.h       Removed unused macro DEFAULT_FILE_DIR
utils.c        utime() function doesn't work correctly on cygwin, changed it's
               behavior to guarantee unique time stamps.
buffer.c       No longer writing #grep output the the scrollback buffer
main.c         Now clearing last command (often quit) when starting up tintin++


config.c       Turned #debugtelnet command into a hidden config option.
               Added a hidden config option named CONVERT META, which turns key
               presses into macro readable keyboard input.
class.c        Added basic support for classes, which is grouping for real.
tables.c       Set substitute priority to save correctly.


May 2005       1.94.1
--------------------------------------------------------------------------------

log.c          Added the option for a second argument to the #logline command.
               If second argument is used it will instead print the given line
               to file.
variable.c     Added %G thousandgroupingstring function to format to change
               for example 1000 into 1,000.


May 2005       1.94.0
--------------------------------------------------------------------------------

rl.c           mainloop now uses a threaded call for the old mainloop. This
               because the readline() function is blocking and I'm too lazy
               to code the stuff readline takes care of.
               The new mainloop tries to go at 100 loops per second.
session.c      Got rid of connect_delay for connecting sessions. Now using
               1 timer.
tick.c         Changed #ticker to use floating point precision.
               Added delay command: #delay {seconds delay} {command}
variable.c     #format, added %L to print the argument's string length, and
               %U to print the number of micro seconds since epoch, increased
               the number of arguments from 10 to 20.
misc.c         Removed the #sleep command, never worked well and should be
               obsolete with the #delay command.
misc.c         #gagline, when called within an action it will gag the line.
rl.c           The #snoop code wasn't working, fixed it up.
data.c         Increased the buffer of show_list a little to avoid an overflow
macro.h        Changed how macros work, fixing problems like needing a \n at
               the end, needing an empty line, macros being added to the
               command history. Still can't find a way to have rl erase macros.
               Players can enter a command within a line of text using
               [[ command ]].
               Example: tell bubba (long line) [[chat hi bibbi]] (more text)
rl.c           Added the option to delay displaying and parsing possibly broken
               packets. Delay in micro seconds can be set with the PACKET PATCH
               config option. By default it's set to 0 (disabled).
variables.c    Fixed #replacestring which got messed up while I added variable
               substitution to it.
rl.c           Fixed echoing of commands in split mode.
split.c        Changes split and prompt to work more logical, people might
               have to change their scripts, new syntax:
               #split {number of top lines} {number of bottom lines}
               default equals: #split {0} {1}
               Fixed possible color bleeding in the split line, this for noobs
               who don't know how to use tintin's color codes.
files.c        /* and */ now only work when used outside braces.
rl.c           No more threading, made tintin crashy as well.
variable.c     Added %n (name) to #format, which capitalizes the first letter
               of the given string.
buffer.c       No longer resetting the buffer if the new scrollback size 
               is the same as the old one.
rl.c           prompts automatically get a newline added in split mode.
session.c      Fixed problem with aliasses changing focus.
rl.c           Made #snoop output non triggerable.
misc.c         Added the $loop and $forall variables set in the #loop and
               #forall commands. Avoids dodgy &0 behavior in #functions.
telopt.c       Added dynamic allocation of buffer space for mccp and the
               normal output buffer.
rlhist.c       1 character long commands are once again added to the command
               history.
files.c        If a bracket is missing TinTin gives a hint at what line the
               error might be.
tinexp.c       Added option to surround a variable with brackets.
variables.c    Removed restrictions on variable names.
math.c         Fixed bug with #if returning the wrong session pointer.
log.c          Added #logline command for actions to log 1 line of text
rlhist.c       If no repeat match is found an error message is printed.
parse.c        Added a check to ingore a trailing ';'.
data.c         Increased buffer size for displaying aliasses.
config.c       Changed packet patch config option from micro to milli seconds.
files.c        Changed calls to isblank() (GNU only) with isspace()
files.c        Only stripping leading spaces now, so #var bla { } will work
               once again.
files.c        I got tired of confusing readnew and readold, so I removed
               readold.


February 2005  1.93.9
--------------------------------------------------------------------------------

split.c        Fixed infinite loop in do_unprompt
rl.c           Added the option to call show_message() with a NULL argument
               for more generic usage.
tintin.h       Set BUFFER_SIZE to 10000 OUTPUT_SIZE to 65000
               and FILE_SIZE to 150000
files.c        Added option to #read and #write using a variable
buffer.c       Fixed some dodgy behavior of the scroll back buffer, it should
               scroll ultra fast as well now.
               The buffer command now only prints the last screen worth of
               text, too lazy to re-code floating screen indexes atm.
               Added scroll lock to the config menu, to freeze the screen
               while scrolling.


February 2005  1.93.8
--------------------------------------------------------------------------------

tick.c         Took care of uninitalized tickers firing prematurely.
session.c      Added option to make a trigger on session termination.
files.c        Added a check for #read being used on a directory.
rl.c           Fixed home/end keys being bound correctly
split.c        Allowing multiple prompt triggers to fire on the same line
               Fixed split line being 4 '-' short


December 2004  1.93.7
--------------------------------------------------------------------------------

tinexp.c       Now only converting ; to : for actions, not for aliasses etc.
path.c         Made END OF PATH message triggerable.
variable.c     added the do_internal_variable command, which does the same
               as do_variable, but allows to set a blank variable. Used by
               do_format and do_replacestring.
rl.c           added the show_message function which only shows messages from
               setting aliasses, variables, etc when called from the command
               line, unless debug is enabled.
rl.c           Now using the more_output buffer previously only used by the
               scrollback buffer to double check actions.

December 2004  1.93.6
--------------------------------------------------------------------------------

net.c          Fixed a crash bug that slipped in with hiding passwords.
net.c          Commands are now added to the buffer/log files while in split
               mode.
highlight.c    Fixed bug with variables and functions not being used.
               Finished highlight code, it no longer messes up old colors.


October 2004   1.93.5
--------------------------------------------------------------------------------

files.c        Added the option to comment using /* comment */ in script files.
math.c         Upgraded to do 64 bit instead of 32 bit operations.
variables.c    Added the replacestring command.
mapper.c       Added the function find_coord, which tries to find a room at the
               given coordinate, starting room being 0,0,0

October 2004   1.93.4
--------------------------------------------------------------------------------

math.c         Fixed a crash bug that slipped in
tinexp.c       Set \[ to escape as { and \] to escape as }
main.c         Now setting application keypad mode and ESC 0 prefix on startup
telopt.c       Changed dont_oldenviron response to wont_oldenviron response,
               reported to fix the ability to login on some server types.

September 2004 1.93.3
--------------------------------------------------------------------------------

log.c          Fixed a typo that broke the log command, as well as adding
               newlines to plain logging.
rlhist.c       one letter commands are no longer added to the history.


August 2004    1.93.2
--------------------------------------------------------------------------------

mapper.c       added the redit command, for basic mapper manipulation, still
               needs a bit more work.
telopts.c      Added a telnet patch from Julia Longtin which adds the basic
               telopt negotiations to initialize a telnet session when
               connecting to port 23.
rl.c           Seeming the readline_echoing_p is reset to TRUE whenever
               something is written to the terminal, so I simply set it to
               whatever it should be several times a second now in the main
               loop.


July 2004      1.93.1
--------------------------------------------------------------------------------

tintin.h       added a room and exit structure for an auto mapper
mapper.c       added a creation functions for rooms and exits
files.c        added the #readmap function to read in a map
mapper.c       added a routine to display an ascii map
mapper.c       added an algorithm to calculate the shortest path between two
               rooms
main.c         the verbatimchar is set as \\ instead of \ as default, this to
               allow escaping braces at a later date with this config option
               causing trouble.


June 2004      1.93.0
--------------------------------------------------------------------------------

log.c          added variable substitution to *arg
misc.c         added variable substitution to *arg
parse.c        changed escape character behavior, #format will need %+4s
               instead of %4s if used in an argument or action. Used to
               be possible to use \%4s but that's no good.
tinexp.c       \a \e \n \r \t are now translated to the according characters.
               (\a equals what #bell does, \r\n would equal #cr, \e is ESC)
parse.c        removed premature stripping of '\' character in the parsing
               routines. Escaped characters are dealt with when data is send
               to the mud or screen.


April 2004     1.92.0
--------------------------------------------------------------------------------

misc.c         removed speedwalk command, it's a config option anyways.


March 2004     1.91.0
--------------------------------------------------------------------------------

parse.c        made sure $variables are substituted in the parsing command,
               as well as $vars being substituted as session A passes a
               command to session B. Otherwise variables remain variable
               untill the final execution stage.
data.c         Added nesting syntax highlighting for lists.
math.c         Added support for "T" and "F" (feature was lost in rewrite)
math.c         Added the 'd' operator for a random dice roll
config.c       rewrote some basic stuff in the configuration routines,
               the original setup was a bit dodgy.
highlight.c    Added priorities to highlighting
substitute.c   Added priorities to substitutions
split.c        Added check so a prompt isn't shown for background sessions.
variable.c     Added %R and %C to #format for nr of rows and columns


March 2004     1.90.0
--------------------------------------------------------------------------------

-misc.c        added a higher precision to the #sleep command, you can now
               enter #sleep 0.5 to sleep for half a second, precision is in
               miliseconds. Also using nanosleep now, with additional support
               to continue sleeping
-variables.c   added %t to #format, which will print the epoch time.
               added %T to #format, which will print the military time
               of the provided number as: hours:minuts
               added %d to #format, which will print the military data of the
               provided number as: day:month:year (if there's no such thing
               as a military date I hope you still know what I mean)
-rl.c          set tintin to 100 loops per second, might seem too much, but
               it doesn't matter cpu wise, and it's always fun when tintin's
               triggers beat those of most other client.
-math.c        added + - ! and ~ to the mathexp interpreter.
-regexp.c      added color support. codes are entered as <abc> and is pretty
               much translated as : \e[a;b+30;c+40m with '8' counting as
               a skipped color code. People can write their own functions to
               make tintin display colors of their own choice.
-variables.c   added %R to #format, which will print a number between 1 and
               the given number in the argument. Removed #random command.
               added %m to #format, which will do the same as #math
-regexp.c      added option for end of line terminator ^ so adding ^ to the
               end of the line will make tintin return false if the regexp
               returns with an unfinished match string.
-main.c        I update the credit screen, figured it would appropriate to
               put my own name on it after all this work. I turned it into
               a helpfile while at it, #help credits should show it.
-regexp.c      made the substitute recursively double check variables and
               functions if they hold a variable of a different kind, useful
               for variables or functions holding color codes.
-misc.c        added ignore and debug commands, debug won't do an aweful lot
               as of yet though.
-variable.c    figured I should add some more color support, so added a way
               to format tintin color names, using #format %c {name}
-variable.c    #format again, %h will create a tintin header line
-variable.c    fixed how variable assignment was being dealt with in triggers,
               can now change and display variables correctly on the fly.
-rlhist.c      changed command repeation behavior.
-rlhist.c      removed the history command, no longer needed to look up the
               index, just a working short memory.
-config.c      added repeat on enter option in config
-parse.c       the command part of a line received by parse input
               has vars and functions substituted right away.
               If passing a command to another session the functions and
               variables are substituted as well, setting the values of
               the controlling session.
-math.c        Added the tintoi and tincmp functions, which are enhanced
               versions of atoi and strcmp.
net.c          Added some code to stop enters being written to the scrollback
               buffer, useful for people using #cr to bust a prompt.
rl.c           Got rid of the prompt saving stuff, now using brute force,
               refresh the prompt everytime the screen is updated. This to
               work around a bug in readline that gives odd behavior with
               cursor movement.


March 2004     1.89.0
--------------------------------------------------------------------------------

- math.c       Added a close to complete mathematical expression routine.
               Needs some work still but it works. Also allows for comparing
               strings <= >= == != if you enclose the strings in " ". It's
               quite a bit better than the old one, though it's not supporting
               T, F, and '!' since it's string based, shouldn't be too hard
               adding some better string support.
- ivars.c      stripped all the stuff that is now covered by math.c or
               variables.c only leaving #ifexits. And then it occured to me
               that #if {"$variable" != "$*"} {true} {false} would
               very well replace the 'ifexits' check. So ivars.c is no more.
- data.c       deletenode_list now properly keeps track of a global update
               node. Can only use one noderoot->update per program state.
- session.c    cleanup_session now properly keeps track of a global update
               node. Can only use one gtd->update per program state.
- rl.c         fixed up the split screen behavior, should be a stable prompt
               and correct text presentation in split mode now.


February 2004  1.88.0
--------------------------------------------------------------------------------
- net.c        added telopt negotiations in net.c for naws, terminal type,
               and mccp (version 2)
- tintin.h     added the zlib library and a session buffer for mccp
- tintin.h     added a 64KB output buffer, I'll just asume that the mud
               output contains a linefeed before BUFFER_SIZE is reached. This
               should make output processing a bit smoother, and saves me
               from fiddling too much with chopped up data.
- rl.c         added the tintin_printf and tintin_printf2 functions which
               format the argument list and pass the data on to tintin_puts
               or tintin_puts2
- tintin.h     changed the node list struct to work with a head/tail pointer,
               and turned it into a double linked list, updated all .c files
               affected by this change.
- *.c          cleaned up the code, using tabs instead of spaces and aligning
               the brackets.
- main.c       switched from rand to rand48, it's seeded once upon startup
               which is sufficient.
- main.c       added a global tintin session (gts) the idea is to get rid of
               most global variables.
- tintin.h     added a bitvector to the session structure which will contain
               all session flags, various changes throughout the code changing
               global variables into flags.
- rl.c         fixed up the cursor positioning for split mode and fixed the
               linewrap routine which was off by 1 character, resulting in
               extra lines on a perfect match.
               added a special flag for mud output for split mode, to avoid
               color loss when restoring the cursor (which also restores the
               cursor color, hence the color loss)
- tables.c     new c file, which will contain some tables, the current setup
               is a bit tedious.
- tintin.h     moved all header files into tintin.h cause the old setup with
               40 headerfiles was giving me a headache (literally).
               Grouped it into typedefs, globals, constants, macros,
               structures and functions
- tintin.h     changed all commands to use the COMMAND typedef, as well as
               all commands now use universal arguments and naming, this to
               make a command table.
- *.c          There's always a session now, with a few checks for gts (global
               tintin session) which cannot send or receive data. Passing
               session data along with a couple of functions which should
               make background sessions less spammy.
- strhash.c    Added a simple string hash routines which I'll be using for a
               scroll back buffer. It uses a bit of memory, but should save a
               lot more for big scroll back buffers.
- main.c       changed tstphandler to call kill with a null pid, otherwise it
               wouldn't work when tintin was started from a script
- ivars.c      removed backwards compatibility for fixedmath
- buffer.c     scroll back buffer and a grep command added
- rl.c         made the init_readline function actually initilize readline,
               added 4 default keybinds for the scrollback buffer.
- tintin.h     added a keymap to the tintin_data structure, which will be
               used for keybinding.
- text.c       got rid of the linewrapper in rl.c and added a word wrap
               routine instead.
- log.c        all vt102 codes cept the linefeed are stripped for logged data,
               the lowlog thingie can still be used.
- chat.c       Removed this entirely, it's a mess and there are many stand
               alone p2p chat programs available.
- *.c          moved some more global data to the session and data structures
- rltick.c     removed entirely
- ticks.c      removed entirely
- tick.c       wrote a new ticker from scratch, uses alarm(1) to sleep 1
               second, the user can now define a list of tickers, pretty much
               like aliasses, they'll trigger when the timer expires. Added
               the 'tick' and 'untick' command for manipulation.
- macro.c      added 'macro' and 'unmacro' commands for keybinding, I couldn't
               figure out how to actually undo the real macro's though
               without using a messy hack, so I just skipped that till later
               for now.
- session.c    Got rid of the zombi code, will try to add a better connection
               handler at a later data, but the zombi code is not the answer.
- tintin.h     Changed architecture further turning the lists from individual
               lists into an array of lists. Added an array in tables.c for
               additional data.
- substitute.c Changed the default #gag char from '.' to character 255, this
               to prevent weird behavior when a dot is displayed on an empty
               line for any kind of reason.
- config.c     Added a configuration menu, defaults are loaded upon startup.
- walk.c       Removed, didn't really look into it deeply, but I adjusted
               path.c to allow user progged walking using a ticker.
- parse.c      Added 2 action checkers, first one checks priority 0 to 4,
               after that substitutions are checked, priority 5 to 9 is
               checked after substitutions.
- parse.c      do_one_line now strips colors per default before passing the
               text on to check_one_action
- action.c     rewrote the %0 - %9 check_one_action regexp routine, it's
               a bit cleaner and slightly faster now.
- action.c     rewrote substitute_vars, ';' is changed to : per default
- variable.c   rewrote subsitute_myvariables, no longer supporting $number
               variables. ';' is stripped per default. This also easily 
               allows a change so variables can contain numbers.
- variable.c   #format {variable} {format} {arguments}
               This allows string formatting, numbers are not supported.
               Added a format parser for further functionality, for now %l
               will lowercase, %u will upper, and %r will reverse the
               argument given. There's a maximum of 10 arguments.
- variable.c   Due to the format command, prepad, postpad, tolower, and
               toupper are no longer required, so I removed the commands.
               I realise this generates a backward compatibility issue, but
               it's easier to find the new commands without 70 old commands
               spamming the help files and command lists.
- split.c      moved the split screen stuff from rl.c to this new file, and
               placed the prompt commands/routines there as well.
