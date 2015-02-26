/* Copyright (C) 2015 Legrand
   All rights reserved

   Shell library - command interface */

#ifndef _SHELL_LIB_I_CMD_H
#define _SHELL_LIB_I_CMD_H

#include <string>
#include <list>
#include "shell_env.h"

/**
 *  ShellCmd is an interface that has to be implemented by concrete commands
 */

class ShellCmd
{
    private:
        ShellEnv* env;
        std::string name;
        std::string description;
    public:
        ShellCmd(ShellEnv* env, std::string name, std::string description);
        virtual ~ShellCmd();
        std::string getName(void);
        virtual void run(char** argv, int argc) = 0;
};
#endif
