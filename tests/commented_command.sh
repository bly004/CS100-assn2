#!/bin/sh

ls #-a
mkdir test #making test file
echo hello
clear
ls -l
git status # making sure branch is up-to-date
ls; cd test #going into test file
cd .. && clear # returning to parent directory and clearing terminal
