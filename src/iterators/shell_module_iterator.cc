/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#include "shell_module_iterator.h"

namespace ownshell {

ShellModuleIterator::ShellModuleIterator(ShellModule* root)
{
    root_ = root;
    isDone_= 0;
}

ShellComponent* ShellModuleIterator::first()
{
    isDone_= 0;
    memento_.initialize( root_ );
    return root_;
}

ShellComponent* ShellModuleIterator::next()
{
    ShellModule* module;
    int        indx;
    memento_.getAndIncrement( &module, &indx );
    // if (and while) you are at end-of-moduleosite, go back up
    while (indx == module->index_)
    {
        int ret = memento_.popCurrent();
        if (ret) {
            isDone_ = 1;
            return 0;
        }
        memento_.getAndIncrement( &module, &indx );
    }
    if (module->children_[indx]->getComponentType() == ShellComponent::composite_e)
        memento_.pushCurrent( (ShellModule*) module->children_[indx], -1 );
    return module->children_[indx];
}

int ShellModuleIterator::isDone()
{
    return isDone_;
}

} // namespace ownshell
