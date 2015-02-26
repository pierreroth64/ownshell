/* Copyright (C) 2015 Legrand
   All rights reserved

   Shell library - module interface */

#ifndef _SHELL_LIB_I_MODULE_H
#define _SHELL_LIB_I_MODULE_H

#include <string>
#include <list>
#include "shell_env.h"
#include "shell_cmd.h"

/**
 *
 * A ShellModule embeds several shell commands
 */

class ShellModule
{
    private:
        ShellEnv* env;
        std::string description;
        std::list<ShellCmd> commands;
    public:
        ShellModule(ShellEnv* env, std::string description);
        void registerCmd(ShellCmd* cmd);
        std::string getHelp(void);
        std::string getHelp(ShellCmd* cmd);
        void runCmd(std::string name, char **argv, int argc);
};

#endif
