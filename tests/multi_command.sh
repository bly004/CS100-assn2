#!/bin/sh

LS_CMD=./bin/ls
ECHO_CMD=./bin/echo
CAL_CMD=./bin/cal
DATE_CMD=./bin/date
TEST="# testing"

# $1 = message of what we're testing
# $2 = command to be executed
function printcmd {
    echo -e "$TEST $1 $2"
    $2
}


echo -e "\n# testing multiple ls\n" 
printcmd "ls and ls -a:" "$LS_CMD; $LS_CMD -a"
printcmd "ls and ls -l:" "$LS_CMD && $LS_CMD -l"
printcmd "ls -a and ls -l:" "$LS_CMD -a; $LS_CMD -l"
printcmd "ls and ls -l or ls -a:" "$LS_CMD && $LS_CMD -a || $LS_CMD -l"


echo -e "\n# testing multiple echo\n"
printcmd "\"this is a test\":" "$ECHO_CMD this; $ECHO_CMD is && $ECHO_CMD a; $ECHO_CMD test"
printcmd "\"hello world!\":" "$ECHO_CMD hello && $ECHO_CMD world!"
printcmd "\"hello world!\" or \"hello there\":" "$ECHO_CMD hello; $ECHO_CMD world! || $ECHO_CMD there"


echo -e "\n# testing calendar, date, and time"
printcmd "calendar and date:" "$CAL_CMD && $DATE_CMD %D"
printcmd "date and time:" "$DATE_CMD %D; $DATE_CMD %X"

echo -e "\n# done testing\n"