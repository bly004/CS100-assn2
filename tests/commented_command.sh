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

echo -e "\n# testing ls\n"
printcmd "No flags:" "$CMD1"
printcmd "-a flag:" "$CMD1 -a # listing all files and directories"
printcmd "-l flag:" "$CMD1 -l # long-listing format"
printcmd "-R flag:" "$CMD1 -R # listing subdirectories recursively"


echo -e "\n# testing echo\n"
printcmd "a test message:" "$CMD2 \"this is a test\""
printcmd "hello world!:" "$CMD2 \"hello world!\""


echo -e "\n# testing calendar, date, and time\n"
printcmd "calendar:" "$CAL_CMD # displays a calendar and the date of Easter"
printcmd "calendar month for July 2010:" "$CAL_CMD 7 2010 # displays July 2010"
printcmd "this year's calendar:" "$CAL_CMD -y # displays calendar for entire year"
printcmd "today's date:" "$DATE_CMD %D # displays date in m/d/y format"
printcmd "today's date in diff format:" "$DATE_CMD %b %d, %Y # displays date in MMM DD, YYYY format"
printcmd "current time:" "$DATE_CMD %X # displays time in hh:mm:ss format"

echo -e "\n# done testing\n"