/* Copyright (C) 2015 Legrand
   All rights reserved

   Shell library - shell app interface */

#ifndef _SHELL_LIB_I_APP_H
#define _SHELL_LIB_I_APP_H

#include "shell_env.h"
#include "shell_component.h"
#include <vector>

using namespace std;

/**
 * A ShellApp implements an interactive shell
 */
class ShellApp
{
    public:
        ShellApp(ShellEnv* env, string prompt, ShellComponent* root);
        void loop(void);
        void setExitCommand(string name);
        void setWelcomeBanner(string banner);
        void findComponentAndArgsFromTokens(vector<string> tokens, ShellComponent** component, vector<string> * args);
    private:
        ShellEnv* env;
        ShellComponent* root;
        string welcome_banner;
        string prompt;
        string exit_cmd;
        bool exit_cmd_set;

        void displayWelcomeBanner(void);
        void displayPrompt(void);
        void displayError(string error);
        void displayInfo(string msg);
        void displayHelp(std::vector<string> tokens);
        string getGeneralHelp(void);
        vector<string> getCmdLineTokens(void);
};

#endif
