/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#include "shell_module_memento.h"

void ShellModuleMemento::initialize(ShellModule* root)
{
    compArr_[0] = root;
    indxArr_[0] = -1;
    index_ = 0;
}

void ShellModuleMemento::pushCurrent(ShellModule* module, int index)
{
    compArr_[index_+1] = module;
    indxArr_[++index_] = index;
}

int ShellModuleMemento::popCurrent()
{
    if (index_ == 0) return 1;
    index_--;
    return 0;
}

void ShellModuleMemento::getAndIncrement(ShellModule** module, int* index)
{
    *module = compArr_[index_];
    *index = indxArr_[index_];
    (*index)++;
    indxArr_[index_]++;
}
