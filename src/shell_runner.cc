/* Copyright (C) 2015 Legrand
   All rights reserved

   Shell library - runner implementation */

#include "shell_except.h"
#include "shell_runner.h"

ShellRunner::ShellRunner(ShellEnv* env, std::string name)
{
    this->env = env;
    this->name = name;
}

ShellModule* ShellRunner::findModuleByName(std::string name)
{
    ShellModule * mod;
    for (std::list<ShellModule *>::iterator it = this->modules.begin(); it != this->modules.end(); ++it) {
        mod = (*it);
        if (mod->getName() == name)
            return mod;
    }
    throw shell_except_not_found("Module not found");
}
void ShellRunner::registerModule(ShellModule* module)
{
    try {
        this->findModuleByName(module->getName());
        throw shell_except_already("Module with such a name already registered");
    } catch (shell_except_not_found e) {
        this->modules.push_back(module);
    }
}

std::string ShellRunner::getAllModulesHelp(void)
{
    ShellModule* mod;
    std::string help;
    for (std::list<ShellModule *>::iterator it = this->modules.begin(); it != this->modules.end(); ++it) {
        mod = (*it);
        help += "\t" + mod->getName() + ": " + mod->getHelp() + "\n";
    }
    return help;
}

std::string ShellRunner::getModuleCmdHelp(std::string module, std::string cmd)
{
    ShellModule* mod = this->findModuleByName(module);
    return mod->getCmdHelp(cmd);
}

std::string ShellRunner::getAllModuleCmdsHelp(std::string module)
{
    ShellModule * mod = this->findModuleByName(module);
    return mod->getAllCmdsHelp();
}

std::string ShellRunner::runCmd(std::string module, std::string name, char **argv, int argc)
{
    ShellModule* mod;
    mod = this->findModuleByName(module);
    return mod->runCmd(name, argv, argc);
}
