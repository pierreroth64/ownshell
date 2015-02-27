/* Copyright (C) 2015 Legrand
   All rights reserved

   CCTV Library */

#include <iostream>
#include <cstdlib>
#include "shell.h"

/* My concrete shell command */
class MyShellCmd : public ShellCmd {
    public:
        MyShellCmd(ShellEnv* env, std::string name, std::string description):  ShellCmd(env, name, description) {};
        virtual std::string run(char** argv, int argc);
};
std::string MyShellCmd::run(char** argv, int argc)
{
    argv = argv;
    std::cout << "Hello called with " << argc << " arguments" << std::endl;
    return "Hello result";
}

int main(void) {

    /* Create environment for your shell */
    ShellEnv* env = new ShellEnv("my environment");

    /* Create a command */
    MyShellCmd* my_cmd = new MyShellCmd(env, "hello", "displays a Hello string on output");

    /* Create a module and register the command */
    ShellModule* my_mod = new ShellModule(env, "newbie", "newbie commands");
    my_mod->registerCmd(my_cmd);

    /* Finally, create the runner and regsiter modules*/
    ShellRunner* runner = new ShellRunner(env, "my shell");
    runner->registerModule(my_mod);

    /* Play! */
    runner->runCmd("newbie", "hello", (char **) 0, 0);

    try {
        runner->runCmd("newbie", "missing", (char **) 0, 0);
    } catch (shell_except e) {
        std::cerr << "Error: unknown command" << std::endl;
    }

    exit(0);
}

