#!/bin/sh

CMD1=./bin/ls
CMD2=./bin/echo
CAL_CMD=./bin/cal
DATE_CMD=./bin/date
TEST="# testing"


# $1 = message of what we're testing
# $2 = command to be executed
function printcmd {
    echo -e "$TEST $1 $2"
    $2
}

echo -e "\n# testing ls\n"
printcmd "No flags:" "$CMD1"
printcmd "-a flag:" "$CMD1 -a"
printcmd "-l flag:" "$CMD1 -l"
printcmd "-R flag:" "$CMD1 -R"


echo -e "\n# testing echo\n"
printcmd "a test message:" "$CMD2 \"this is a test\""
printcmd "hello world!:" "$CMD2 \"hello world!\""


echo -e "\n# testing calendar, date, and time\n"
printcmd "calendar:" "$CAL_CMD"
printcmd "calendar month for July 2010:" "$CAL_CMD 7 2010"
printcmd "this year's calendar:" "$CAL_CMD -y"
printcmd "today's date:" "$DATE_CMD %D"
printcmd "today's date in diff format:" "$DATE_CMD %b %d, %Y"
printcmd "current time:" "$DATE_CMD %X"

echo -e "\n# done testing\n"