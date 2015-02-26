/* Copyright (C) 2015 Legrand
   All rights reserved

   Shell library - environment */

#ifndef _SHELL_LIB_I_ENV_H
#define _SHELL_LIB_I_ENV_H

#include <string>
#include <list>

class ShellEnvDataEntry;

/**
 *  ShellEnv describes the shell environment and stores data that can be retrieved later
 */

class ShellEnv
{
    private:
        std::list<ShellEnvDataEntry *> entries;
        std::string name;
    public:
        ShellEnv(std::string name);
        void addEntry(std::string name, void* entry);
        void removeEntry(std::string name);
        void * getEntry(std::string name);
        unsigned int getEntriesNumber(void);
};
#endif
