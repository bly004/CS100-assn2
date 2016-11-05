#!/bin/sh

LS_CMD=./bin/ls
ECHO_CMD=./bin/echo
EXIT_CMD=./bin/exit
CAL_CMD=./bin/cal
DATE_CMD=./bin/date
TEST="# testing"

# $1 = message of what we're testing
# $2 = command to be executed
function printcmd {
    echo -e "$TEST $1 $2"
    $2
}


echo -e "\n# testing ls and exit\n"
printcmd "No flag ls and exit:" "$LS_CMD; $EXIT_CMD"
printcmd "-a flag ls and exit:" "$LS_CMD -a && $EXIT_CMD"
printcmd "-l flag ls and exit:" "$LS_CMD -l"
printcmd "No flag ls and exit or -R flag ls:" "$LS_CMD && $EXIT_CMD || $LS_CMD -R"


echo -e "\n# testing echo and exit\n"
printcmd "a test message and exit:" "$ECHO_CMD \"this is a test\"; $EXIT_CMD"
printcmd "\"hello world!\" and exit:" "$ECHO_CMD hello && $ECHO_CMD world!"
printcmd "\"hello world!\" or \"hello there\" and exit:" "$ECHO_CMD hello; $ECHO_CMD world! || $ECHO_CMD there; $EXIT_CMD"


echo -e "\n# testing calendar, date, and time"
printcmd "calendar and exit:" "$CAL_CMD && $EXIT_CMD"
printcmd "today's date and exit:" "$DATE_CMD %D; $EXIT_CMD"
printcmd "current time and exit:" "$DATE_CMD %X && $EXIT_CMD"
printcmd "calendar and date and exit:" "$CAL_CMD && $DATE_CMD %D; $EXIT_CMD"
printcmd "date and time and exit:" "$DATE_CMD %D; $DATE_CMD %X && $EXIT_CMD"

echo -e "\n# done testing\n"