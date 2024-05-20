//
// Created by konghang on 2024/5/17.
//
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <stdlib.h>
#include "chroot.h"

void printcwd(const char* name)
{
    char buffer[1024];
    char *cwd;
    // 获取当前工作目录
    cwd = getcwd(buffer, sizeof(buffer));
    if (cwd != NULL) {
        printf("%s: %s\n", name, cwd);
    } else {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }
}

int main_chroot(void)
{
    printcwd("Started workdir");

    //以root用户权限运行
    //grant privileged process
    if (getuid() != 0 && setuid(0) == -1) {
        perror("privileged failed");
        exit(EXIT_FAILURE);
    }

    // change root
    // Only a privileged process (Linux: one with the CAP_SYS_CHROOT capability) may call chroot()
    if (chdir("./rootfs") != 0 || chroot("./") != 0)
    {
        perror("chroot failed");
        exit(EXIT_FAILURE);
    }

    printcwd("Rootfs");
    return 0;
}