/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#include "gtest/gtest.h"
#include "shell_cmd_test.h"

std::string MyShellCmd::run(char** argv, int argc)
{
    this->was_called = 1;
    this->arg_nb = argc;
    argv = argv;
    return "yeah!";
}

void MyShellCmd::reset(void)
{
    this->was_called = 0;
    this->arg_nb = 0;
}

int MyShellCmd::lastArgNumber(void)
{
    return this->arg_nb;
}
