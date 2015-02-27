/* Copyright (C) 2015 Legrand
   All rights reserved

   Shell library - shell app interface */

#ifndef _SHELL_LIB_I_APP_H
#define _SHELL_LIB_I_APP_H

#include "shell_env.h"
#include "shell_runner.h"
#include <vector>
/**
 * A ShellApp implements an interactive shell
 */
class ShellApp
{
    private:
        ShellEnv* env;
        ShellRunner* runner;
        std::string welcome_banner;
        std::string prompt;
        std::string exit_cmd;
        bool exit_cmd_set;

        void displayWelcomeBanner(void);
        void displayPrompt(void);
        void displayError(std::string error);
        void displayHelp(std::vector<std::string> tokens);
        std::vector<std::string> getCmdLineTokens(void);

    public:
        ShellApp(ShellEnv* env, std::string prompt, ShellRunner* runner);
        void loop(void);
        void setExitCommand(std::string name);
        void setWelcomeBanner(std::string banner);
};

#endif
