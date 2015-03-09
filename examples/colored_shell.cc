/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#include <iostream>
#include <cstdlib>
#include "ownshell.h"

using namespace ownshell;

/* This Colored Shell shows how to create to change help output */

using namespace std;

/* My concrete shell command */
class MyShellCmd : public ShellCmd {
    private:
        string result_;
    public:
        MyShellCmd(ShellEnv* env, string name, string description, string result=""):  ShellCmd(env, name, description) {
            result_ = result;
        };
        virtual string run(vector<string> args);
};

string MyShellCmd::run(vector<string> args)
{
    cout << getName() << " called with " << args.size() << " arguments" << endl;
    if (args.size()) {
        cout << "Args: ";
        for(vector<string>::iterator it = args.begin(); it != args.end(); ++it) {
            cout << *it << " ";
        }
        cout << endl;
    }
    return result_;
}

int main(void) {

    /* Create environment for your shell */
    ShellEnv* env = new ShellEnv("my environment");

    /* Add a help formatter: you may implement your by subclassing ShellHelpFormatter interface */
    env->setHelpFormatter(new ShellHelpColoredFormatter());

    /* Create your modules/commands tree */
    ShellCmd* cmd_hello = new MyShellCmd(env, "hello", "displays a hello string on output", "hello!");

    ShellModule* mod_newbie = new ShellModule(env, "newbie", "newbie commands");
    mod_newbie->add(cmd_hello);

    ShellModule* mod_extra = new ShellModule(env, "extra", "extra commands");
    ShellCmd* cmd_extra = new MyShellCmd(env, "extra", "displays an extra string on output", "extra");
    mod_extra->add(cmd_extra);
    mod_newbie->add(mod_extra);

    /* Start your shell application */
    ShellApp* my_shell = new ShellApp(env, "Colored Shell", "colored>", mod_newbie);
    my_shell->setExitCommand("exit");
    string banner = "Welcome to Colored Shell";
    banner += " (based on " + ShellInfo::getName() + " - " + ShellInfo::getVersion() + ")\n";
    my_shell->setWelcomeBanner(banner);
    my_shell->loop();

    exit(0);
}

