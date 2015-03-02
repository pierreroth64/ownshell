/* Copyright (C) 2015 Legrand
   All rights reserved

   Shell library - module interface */

#ifndef _SHELL_LIB_I_MODULE_H
#define _SHELL_LIB_I_MODULE_H

#include <string>
#include <list>
#include "shell_env.h"
#include "shell_component.h"

/**
 *
 * A ShellModule is a composite (includes ShellComponents)
 */

class ShellModule: public ShellComponent
{
    public:
        ShellModule(ShellEnv* env, std::string name, std::string description) : ShellComponent(env, name, description){};
        virtual ~ShellModule() {};

        virtual std::string run(char** argv, int argc);
        virtual std::string getHelp();

        virtual void add(ShellComponent * component);
        virtual void remove(ShellComponent * component);
        unsigned int getComponentsNb(void);

    private:
        std::list<ShellComponent* > components;
        virtual ShellComponent* findComponent(ShellComponent * component);
};

#endif
