#!/bin/sh

ls && ls -a || ls -l
ls -a; echo hello; mkdir test
ls -a; echo hello && mkdir test || echo world; git status
cd test; echo testing cd; cd .. && echo "returned to parent directory" || echo "returning to parent directory failed"
