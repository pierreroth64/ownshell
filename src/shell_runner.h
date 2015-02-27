/* Copyright (C) 2015 Legrand
   All rights reserved

   Shell library - runner interface */

#ifndef _SHELL_LIB_I_RUNNER_H
#define _SHELL_LIB_I_RUNNER_H

#include <string>
#include <list>
#include "shell_env.h"
#include "shell_module.h"


/**
 * A SellCmdRunner embeds ShellCmd objects.
 * It is the primary interface to run - previously registered - shell modules
 *
 */
class ShellRunner
{
    private:
        ShellEnv* env;
        std::string name;
        std::list<ShellModule *> modules;
    public:
        ShellRunner(ShellEnv* env, std::string name);
        void registerModule(ShellModule* module);
        ShellModule* findModuleByName(std::string name);
        std::string runCmd(std::string module, std::string name, char **argv, int argc);
        std::string getAllModulesHelp(void);
        std::string getAllModuleCmdsHelp(std::string module);
        std::string getModuleCmdHelp(std::string module, std::string cmd);
};

#endif
