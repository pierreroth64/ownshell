/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#ifndef _SHELL_LIB_I_COMPONENT_H
#define _SHELL_LIB_I_COMPONENT_H

#include <string>
#include <list>
#include "shell_env.h"

using namespace std;

/**
 *  ShellComponent is an interface for objects in the composition (ShellCmds and ShellModules)
 */

class ShellComponent
{
    public:
        ShellComponent(ShellEnv* env, string name, string description);
        virtual ~ShellComponent() {};

        string getName();
        virtual string run(char** argv, int argc);
        virtual string getHelp();
        virtual string getDescription();

        virtual void add(ShellComponent * component);
        virtual void remove(ShellComponent * component);
        virtual unsigned int getComponentsNb(void);
    private:
        ShellEnv* env;
        string name;
        string description;
};
#endif
