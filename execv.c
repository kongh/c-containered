//
// Created by konghang on 2024/5/17.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include "execv.h"

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

int clone_namespace_uts(void)
{
    fork()
}
