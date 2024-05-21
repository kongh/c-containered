//
// Created by konghang on 2024/5/17.
//
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <string.h>
#include "execv.h"

#define STACK_SIZE (1024 * 1024)    /* Stack size for cloned child */
static char child_stack[STACK_SIZE];

// 将当前进程替换成bash
int main_execv(void)
{
    // 定义要执行的命令和参数数组
    char *cmd = "/bin/bash";
    char *argv[] = { cmd, NULL }; // 注意：参数列表必须以NULL终止
    // 使用 execv 替换当前进程的映像为 "/bin/bash"
    execv(cmd, argv);

    // 如果 execv 调用成功，下面的代码将不会被执行
    // 如果有错误发生，将打印错误消息
    perror("execv failed");
    exit(EXIT_FAILURE);
}

#define STACK_SIZE (1024 * 1024)    /* Stack size for cloned child */

static char child_stack[STACK_SIZE];

/* A simple error-handling function: print an error message based
   on the value in 'errno' and terminate the calling process */

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)

static int              /* Start function for cloned child */
childFunc(void *arg)
{
    struct utsname uts;

    /* Change hostname in UTS namespace of child */

    if (sethostname(arg, strlen(arg)) == -1)
        errExit("sethostname");

    /* Retrieve and display hostname */

    if (uname(&uts) == -1)
        errExit("uname");
    printf("uts.nodename in child:  %s\n", uts.nodename);

    /* Keep the namespace open for a while, by sleeping.
       This allows some experimentation--for example, another
       process might join the namespace. */
     
    sleep(100);

    return 0;           /* Terminates child */
}

int
clone_namespace_uts(int argc, char *argv[])
{
    pid_t child_pid;
    struct utsname uts;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <child-hostname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Create a child that has its own UTS namespace;
       the child commences execution in childFunc() */

    child_pid = clone(childFunc, 
                    child_stack + STACK_SIZE,   /* Points to start of 
                                                   downwardly growing stack */ 
                    CLONE_NEWPID| CLONE_NEWUTS | SIGCHLD, argv[1]);
    if (child_pid == -1)
        errExit("clone");
    printf("PID of child created by clone() is %ld\n", (long) child_pid);

    /* Parent falls through to here */

    sleep(1);           /* Give child time to change its hostname */

    /* Display the hostname in parent's UTS namespace. This will be 
       different from the hostname in child's UTS namespace. */

    if (uname(&uts) == -1)
        errExit("uname");
    printf("uts.nodename in parent: %s\n", uts.nodename);

    if (waitpid(child_pid, NULL, 0) == -1)      /* Wait for child */
        errExit("waitpid");
    printf("child has terminated\n");

    exit(EXIT_SUCCESS);
}
