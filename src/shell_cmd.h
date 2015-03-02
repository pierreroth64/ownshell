/* Copyright (C) 2015 Legrand
   All rights reserved

   Shell library - command interface */

#ifndef _SHELL_LIB_I_CMD_H
#define _SHELL_LIB_I_CMD_H

#include <string>
#include <list>
#include "shell_component.h"
#include "shell_env.h"

/**
 *  ShellCmd is an interface that has to be implemented by concrete commands
 *  It is also a ShellComponent as it can be part of a composite
 */

class ShellCmd: public ShellComponent
{
    public:
        ShellCmd(ShellEnv* env, std::string name, std::string description) : ShellComponent(env, name, description){};
        virtual ~ShellCmd(){};
        virtual std::string getHelp(void);
        virtual std::string run(char** argv, int argc);

};
#endif
