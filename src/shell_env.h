/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#ifndef _SHELL_LIB_I_ENV_H
#define _SHELL_LIB_I_ENV_H

#include <string>
#include <list>

using namespace std;

class ShellEnvDataEntry;

/**
 *  ShellEnv describes the shell environment and stores data that can be retrieved later
 */

class ShellEnv
{
    private:
        list<ShellEnvDataEntry *> entries;
        string name;
    public:
        ShellEnv(string name);
        void addEntry(string name, void* entry);
        void removeEntry(string name);
        void * getEntry(string name);
        unsigned int getEntriesNumber(void);
};
#endif
