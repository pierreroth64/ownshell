/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#include "shell_cmd.h"
#include "shell_help_formatter.h"

namespace ownshell {

string ShellCmd::getHelp(void)
{
    ShellHelpFormatter* formatter = this->env->getHelpFormatter();
    if (this->detailed_help != "")
        return formatter->formatCmdHelp(this->detailed_help);
    else
        return formatter->formatCmdHelp(this->getDescription());
}

string ShellCmd::run(vector<string> args)
{
    args = args;
    return "";
}

} // namespace ownshell
