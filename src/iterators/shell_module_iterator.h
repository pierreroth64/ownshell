/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#ifndef _OWNSHELL_I_MODULE_ITERATOR_H
#define _OWNSHELL_I_MODULE_ITERATOR_H

#include "shell_except.h"
#include "shell_component.h"
#include "shell_module.h"
#include "shell_module_memento.h"

namespace ownshell {

class ShellModuleIterator {
    public:
       ShellModuleIterator( ShellModule* _root );
       ShellComponent* first();
       ShellComponent* next();
       int isDone();
    private:
       ShellModule* root_;
       ShellModuleMemento memento_;
       int isDone_;
};

} // namespace ownshell

#endif
