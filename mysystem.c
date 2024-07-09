/*
 *  mysystem.c : system 関数のクローン
 */

#include <stdio.h>
#include <stdlib.h>    // exit, system のため
#include <unistd.h>    // fork, execXX のため
#include <sys/wait.h>  // wait のため
#include "mysystem.h"  // インタフェース

// system関数のクローン
int mysystem(char *command) {
  int pid = 0;
  int status = 0;
  if(command == NULL){
    return 1;
  }
  if((pid = fork()) < 0){
    return -1;
  }
  if(pid != 0){
    while(wait(&status) != pid);
  }else{
    execl("/bin/sh","sh","-c",command,NULL);
    exit(127);
  }

  return status;
}

/* 実行例
% make
cc -Wall -std=c99 -o mysysmain mysysmain.c  mysystem.c
% ls -l
total 616
-rw-r--r--  1 mitunoiyuusi  staff     143  7  4 09:47 Makefile
-rw-r--r--  1 mitunoiyuusi  staff    2795  7  4 09:47 README.md
-rw-r--r--  1 mitunoiyuusi  staff  238232  7  4 09:47 README.pdf
-rwxr-xr-x  1 mitunoiyuusi  staff   50358  7  9 09:02 mysysmain
-rw-r--r--  1 mitunoiyuusi  staff     925  7  4 09:47 mysysmain.c
-rw-r--r--  1 mitunoiyuusi  staff     638  7  9 09:02 mysystem.c
-rw-r--r--  1 mitunoiyuusi  staff      90  7  4 09:47 mysystem.h
% ./mysysmain "ls -l"
mysystem:
total 616
-rw-r--r--  1 mitunoiyuusi  staff     143  7  4 09:47 Makefile
-rw-r--r--  1 mitunoiyuusi  staff    2795  7  4 09:47 README.md
-rw-r--r--  1 mitunoiyuusi  staff  238232  7  4 09:47 README.pdf
-rwxr-xr-x  1 mitunoiyuusi  staff   50358  7  9 09:02 mysysmain
-rw-r--r--  1 mitunoiyuusi  staff     925  7  4 09:47 mysysmain.c
-rw-r--r--  1 mitunoiyuusi  staff     638  7  9 09:02 mysystem.c
-rw-r--r--  1 mitunoiyuusi  staff      90  7  4 09:47 mysystem.h
retval = 00000000
system:
total 616
-rw-r--r--  1 mitunoiyuusi  staff     143  7  4 09:47 Makefile
-rw-r--r--  1 mitunoiyuusi  staff    2795  7  4 09:47 README.md
-rw-r--r--  1 mitunoiyuusi  staff  238232  7  4 09:47 README.pdf
-rwxr-xr-x  1 mitunoiyuusi  staff   50358  7  9 09:02 mysysmain
-rw-r--r--  1 mitunoiyuusi  staff     925  7  4 09:47 mysysmain.c
-rw-r--r--  1 mitunoiyuusi  staff     638  7  9 09:02 mysystem.c
-rw-r--r--  1 mitunoiyuusi  staff      90  7  4 09:47 mysystem.h
retval = 00000000
% ./mysysmain
使い方 : ./mysysmain コマンド文字列
% ./mysysmain "A"
mysystem:
sh: A: command not found
retval = 00007f00
system:
sh: A: command not found
retval = 00007f00
% ./mysysmain "rm"  
mysystem:
usage: rm [-f | -i] [-dIPRrvWx] file ...
       unlink [--] file
retval = 00004000
system:
usage: rm [-f | -i] [-dIPRrvWx] file ...
       unlink [--] file
retval = 00004000
*/
