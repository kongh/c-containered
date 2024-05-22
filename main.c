#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include "chroot.h"
#include "execv.h"
#include "unshare.h"

int main(int argc, char *argv[])
{
    printcwd("Running in the directory");
    printf("Run user:%d\n", getuid());
    // return main_chroot();
    // return main_execv();
    clone_namespace_uts(argc, argv);
    // exec_setns(argc, argv);
    // main_unshare(argc, argv);
    // clone_namespace_user(argc, argv);
}
