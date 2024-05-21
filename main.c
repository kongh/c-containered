#include "chroot.h"
#include "execv.h"

int main(int argc, char *argv[])
{
    printcwd("Running in the directory");
    // return main_chroot();
    // return main_execv();
    clone_namespace_uts(argc, argv);
}
