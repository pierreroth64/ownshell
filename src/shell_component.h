/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#ifndef _OWNSHELL_I_COMPONENT_H
#define _OWNSHELL_I_COMPONENT_H

#include <string>
#include <vector>
#include <list>
#include "shell_env.h"

using namespace std;

namespace ownshell {

/**
 *  ShellComponent is an interface for objects in the composition (ShellCmds and ShellModules)
 */

class ShellComponent
{
    public:
        ShellComponent(ShellEnv* env, string name, string description);
        virtual ~ShellComponent() {};

        string getName();
        virtual string run(vector<string> args);
        virtual string getHelp();
        virtual string getDescription();

        virtual void add(ShellComponent * component);
        virtual void remove(ShellComponent * component);
        virtual unsigned int getComponentsNb(void);
        virtual ShellComponent* findComponentByName(string name);
        virtual ShellComponent* findComponentFromTokens(vector<string> tokens);
        void setParent(ShellComponent* parent) { this->parent = parent; };
        unsigned int getParentsNb(void);
    protected:
        ShellComponent* parent;
        ShellEnv* env;
    private:
        string name;
        string description;
};

} // namespace ownshell

#endif
