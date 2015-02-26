/* Copyright (C) 2015 Legrand
   All rights reserved

   Shell library - module implementation */

#include "shell_module.h"

ShellModule::ShellModule(ShellEnv* env, std::string description)
{
    this->env = env;
    this->description = description;
}

void ShellModule::registerCmd(ShellCmd* cmd)
{
    this->commands.push_back(cmd);
}

unsigned int ShellModule::getRegisteredCmdsNb(void)
{
    return this->commands.size();
}

