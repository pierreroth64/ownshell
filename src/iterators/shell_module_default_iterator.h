/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#ifndef _OWNSHELL_I_MODULE_DEFAULT_ITERATOR_H
#define _OWNSHELL_I_MODULE_DEFAULT_ITERATOR_H

#include <list>
#include "shell_component_iterator.h"
#include "shell_module.h"
#include <iostream>

using namespace std;

namespace ownshell {

/**
 *  ShellModuleDefaultIterator is the default iterator when traversing a module
 */

class ShellModuleDefaultIterator : public ShellComponentIterator
{
    public:
        ShellModuleDefaultIterator(ShellComponent* component) : ShellComponentIterator(component) {
                cout << "Creating Iterator for module: " << component->getName() << endl;
                name_ = "ModuleDefaultIterator";
                ShellComponent* child = root_->getFirstChild();
                iterators_.push_back(child->createIterator());
            };
        virtual ~ShellModuleDefaultIterator() {};

        virtual ShellComponent* next();
        virtual bool hasNext();
    protected:
        list<ShellComponentIterator* > iterators_;
};

} // namespace ownshell

#endif
