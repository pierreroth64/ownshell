/* Copyright (C) 2015 Legrand
   All rights reserved

   Shell library - module implementation */

#include "shell_except.h"
#include "shell_module.h"

ShellModule::ShellModule(ShellEnv* env, std::string name)
{
    this->env = env;
    this->name = name;
}

ShellModule::ShellModule(ShellEnv* env, std::string name, std::string description)
{
    this->env = env;
    this->name = name;
    this->description = description;
}

ShellCmd* ShellModule::findCmdByName(std::string name)
{
    ShellCmd * cmd;
    for (std::list<ShellCmd *>::iterator it = this->commands.begin(); it != this->commands.end(); ++it) {
        cmd = (*it);
        if (cmd->getName() == name)
            return cmd;
    }
    throw shell_except_not_found("Command not found");
}
void ShellModule::registerCmd(ShellCmd* cmd)
{
    try {
        this->findCmdByName(cmd->getName());
        throw shell_except_already("Command with such a name already registered");
    } catch (shell_except_not_found e) {
        this->commands.push_back(cmd);
    }
}

unsigned int ShellModule::getRegisteredCmdsNb(void)
{
    return this->commands.size();
}

std::string ShellModule::runCmd(std::string name, char **argv, int argc)
{
    ShellCmd* cmd;
    cmd = this->findCmdByName(name);
    return cmd->run(argv, argc);
}
