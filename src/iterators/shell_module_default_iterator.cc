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

ShellComponent* ShellModuleDefaultIterator::next()
{
    if (hasNext()) {
        cout << "Looking for iterator... (next())" << endl;
        ShellComponentIterator* iterator = (ShellComponentIterator* ) iterators_.back();
        cout << "iterator: " << iterator->getName() << endl;

        ShellComponent* component = iterator->next();
        if (component->getComponentsNb()) {
            iterators_.push_back(component->createIterator());
        }
        return component;
    }
    return NULL;
}


bool ShellModuleDefaultIterator::hasNext()
{
    if (iterators_.empty())
        return false;
    else {
        cout << "Looking for iterator... (hasNext())" << endl;
        ShellComponentIterator* iterator = (ShellComponentIterator*) iterators_.back();
        if (!iterator->hasNext()) {
            iterators_.pop_back();
            return hasNext();
        } else {
            return true;
        }
    }
}

} // namespace ownshell
