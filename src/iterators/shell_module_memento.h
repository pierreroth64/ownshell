/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#ifndef _OWNSHELL_I_MODULE_MEMENTO_H
#define _OWNSHELL_I_MODULE_MEMENTO_H

#include "shell_module.h"

namespace ownshell {

class ShellModuleMemento {
    public:
       void initialize(ShellModule* root);
       void pushCurrent(ShellModule* module, int index);
       int popCurrent();
       void getAndIncrement(ShellModule** module, int* index);
    private:
       ShellModule*  compArr_[10];
       int         indxArr_[10];
       int         index_;
};

} // namespace ownshell

#endif
