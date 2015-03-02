/* Copyright (C) 2015 Legrand
   All rights reserved

   CCTV Library */

#include <iostream>
#include <cstdlib>
#include "shell.h"

/* My concrete shell command */
class MyShellCmd : public ShellCmd {
    public:
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
    ShellCmd* my_cmd = new ShellCmd(env, "hello", "displays a Hello string on output");

    /* Create a module and register the command */
    ShellModule* my_mod = new ShellModule(env, "newbie", "newbie commands");
    my_mod->add(my_cmd);

    /* Start your shell application */
    ShellApp* my_shell = new ShellApp(env, "my_shell>", (ShellComponent *) my_mod);
    my_shell->setExitCommand("exit");
    my_shell->setWelcomeBanner("Welcome to my simple shell");
    my_shell->loop();

    exit(0);
}

