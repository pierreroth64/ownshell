/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/
#include <iostream>
#include "shell_module_default_iterator.h"

using namespace std;

namespace ownshell {

void ShellModuleDefaultIterator::reset()
{
    position_ = 0;
}
ShellComponent* ShellModuleDefaultIterator::next()
{
    ShellComponent* current;

    if (hasNext()) {
        current = root_->getChildAt(position_);
        position_++;
        return current;
    }
    return NULL;
}


bool ShellModuleDefaultIterator::hasNext()
{
    if (position_ <= root_->getChildrenNb()) {
        return true;
    } else {
        return false;
    }
}

} // namespace ownshell
