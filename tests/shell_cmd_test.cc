/* Copyright (C) 2015 Legrand
   All rights reserved

   Shell Library - concrete shell cmd class for testing */

#include "gtest/gtest.h"
#include "shell.h"
#include "shell_cmd_test.h"

void MyShellCmd::run(char** argv, int argc)
{
    this->was_called = 1;
    this->arg_nb = argc;
}

void MyShellCmd::reset(void)
{
    this->was_called = 0;
    this->arg_nb = 0;
}
