//
// Created by konghang on 2024/5/17.
//

#ifndef EXECV_H
#define EXECV_H
int main_execv(void);
int clone_namespace_uts(int argc, char *argv[]);
int clone_namespace_user(int argc, char *argv[]);
int clone_namespace_pid(int argc, char *argv[]);
int exec_setns(int argc, char *argv[]);
struct clone_params {
    char *hostname;
};

#endif //EXECV_H
