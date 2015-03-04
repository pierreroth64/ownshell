/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#ifndef _OWNSHELL_I_APP_H
#define _OWNSHELL_I_APP_H

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
        ShellApp(ShellEnv* env, string name, string prompt, ShellComponent* root);
        ~ShellApp();
        void loop(void);
        void setExitCommand(string name);
        void setHelpCommand(string name);
        void setTopHelp(string msg);
        void setWelcomeBanner(string banner);

    private:
        ShellEnv* env;
        ShellComponent* root;
        string name;
        string welcome_banner;
        string prompt;
        string exit_cmd;
        string help_cmd;
        string top_help_msg;

        void displayWelcomeBanner(void);
        void displayPrompt(void);
        void displayError(string error);
        void displayInfo(string msg);
        void displayHelp(std::vector<string> tokens);
        string getTopHelp(void);
        vector<string> getCmdLineTokens(void);
};

#endif
