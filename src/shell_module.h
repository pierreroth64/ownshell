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
        std::string name;
        std::string description;
        std::list<ShellCmd* > commands;
    public:
        ShellModule(ShellEnv* env, std::string name);
        ShellModule(ShellEnv* env, std::string name, std::string description);
        std::string getName(void);
        void registerCmd(ShellCmd* cmd);
        unsigned int getRegisteredCmdsNb(void);
        ShellCmd* findCmdByName(std::string name);
        std::string getHelp(void);
        std::string getCmdHelp(std::string name);
        std::string getAllCmdsHelp(void);
        std::string runCmd(std::string name, char **argv, int argc);
};

#endif
