/* Copyright (C) 2015 Legrand
   All rights reserved

   Shell library - component interface */

#ifndef _SHELL_LIB_I_COMPONENT_H
#define _SHELL_LIB_I_COMPONENT_H

#include <string>
#include <list>
#include "shell_env.h"

/**
 *  ShellComponent is an interface for objects in the composition (ShellCmds and ShellModules)
 */

class ShellComponent
{
    public:
        ShellComponent(ShellEnv* env, std::string name, std::string description);
        virtual ~ShellComponent() {};

        std::string getName();
        virtual std::string run(char** argv, int argc);
        virtual std::string getHelp();

        virtual void add(ShellComponent * component);
        virtual void remove(ShellComponent * component);
        unsigned int getComponentsNb(void);
    protected:
        std::string getDescription();
    private:
        ShellEnv* env;
        std::string name;
        std::string description;
};
#endif
