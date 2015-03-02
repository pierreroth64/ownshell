/* Copyright (C) 2015 Legrand
   All rights reserved

   Shell library - command implementation */

#include "shell_cmd.h"

string ShellCmd::getHelp(void)
{
    return this->getDescription();
}

string ShellCmd::run(char** argv, int argc)
{
    argv = argv;
    argc = argc;
    return "";
}
