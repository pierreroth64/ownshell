/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#ifndef _OWNSHELL_I_ENV_H
#define _OWNSHELL_I_ENV_H

#include <string>
#include <list>

#include "shell_except.h"
#include "shell_help_formatter.h"

using namespace std;

namespace ownshell {

class ShellEnvDataEntry;

/**
 *  ShellEnv describes the shell environment and stores data that can be retrieved later
 */

class ShellEnv
{
    private:
        list<ShellEnvDataEntry *> entries;
        string name;
        ShellHelpFormatter* formatter;
    public:
        ShellEnv(string name);
        ~ShellEnv();
        void setHelpFormatter(ShellHelpFormatter* formatter) {
            if (!this->formatter)
                throw shell_except_unsupported("Help formatter must be set");
            this->formatter = formatter;
        };
        ShellHelpFormatter* getHelpFormatter(void) { return this->formatter; };
        void addEntry(string name, void* entry);
        void removeEntry(string name);
        void * getEntry(string name);
        unsigned int getEntriesNumber(void);
};

} // namespace ownshell
#endif
