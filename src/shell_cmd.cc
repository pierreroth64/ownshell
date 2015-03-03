/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#include "shell_cmd.h"

string ShellCmd::getHelp(void)
{
    return this->detailed_help;
}

string ShellCmd::run(vector<string> args)
{
    args = args;
    return "";
}
