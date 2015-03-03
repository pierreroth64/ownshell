/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#include <iostream>
#include <cstdlib>
#include "shell.h"

using namespace std;

/* My concrete shell command */
class MyShellCmd : public ShellCmd {
    public:
        MyShellCmd(ShellEnv* env, std::string name, std::string description):  ShellCmd(env, name, description) {};
        virtual string run(vector<string> args);
};

string MyShellCmd::run(vector<string> args)
{
    cout << "Hello called with " << args.size() << " arguments" << endl;
    cout << "Args: ";
    for(vector<string>::iterator it = args.begin(); it != args.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    return "Hello result";
}

int main(void) {

    /* Create environment for your shell */
    ShellEnv* env = new ShellEnv("my environment");

    /* Create a command */
    ShellCmd* my_cmd = new MyShellCmd(env, "hello", "displays a Hello string on output");

    /* Create a module and register the command */
    ShellModule* my_mod = new ShellModule(env, "newbie", "newbie commands");
    my_mod->add(my_cmd);

    /* Start your shell application */
    ShellApp* my_shell = new ShellApp(env, "my_shell>", (ShellComponent *) my_mod);
    my_shell->setExitCommand("exit");
    my_shell->setWelcomeBanner("Welcome to my simple shell");
    my_shell->loop();

    exit(0);
}

