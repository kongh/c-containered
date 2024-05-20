//
// Created by konghang on 2024/5/17.
//
#include <signal.h>
#include <sys/syscall.h>
#include <unistd.h>

       int
       main(void)
       {
           pid_t tid;

           tid = syscall(SYS_gettid);
           syscall(SYS_tgkill, getpid(), tid, SIGHUP);
       }