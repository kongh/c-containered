#include "chroot.h"
#include "execv.h"

int main(void)
{
    printcwd("Running in the directory");
    // return main_chroot();
    return main_execv();
}
