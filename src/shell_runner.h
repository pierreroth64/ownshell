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
 * It is the primary interface to run - previously registered - shell commands
 *
 */
class ShellCmdRunner
{
    private:
        std::list<ShellModule *> modules;

    public:
        ShellCmdRunner(ShellEnv* env);
        ~ShellCmdRunner();
        void registerModule(ShellModule* module);
        void run(void);
};

#endif
