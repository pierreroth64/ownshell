/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#include <iostream>
#include <cstdlib>
#include "ownshell.h"

/* This Env Shell shows how transmit data from a shell command to another using the environment container
 *
 * args 12 foo bar   --> will add 12, foo & bar to the env-stored args list
 * args list         --> will show 12, foo and bar in the list
 * args rm           --> will remove all items in the list
 * args list         --> this call should show you an empty list
 * */

using namespace std;

/* Command that adds its args to a list stored in env */
class MyAddCmd : public ShellCmd {
    public:
        MyAddCmd(ShellEnv* env, string name, string description):  ShellCmd(env, name, description) {};
        virtual string run(vector<string> args) {
            list<string> *my_list = (list<string> *) env->getEntry("args");
            for (vector<string>::iterator it = args.begin(); it != args.end(); ++it) {
                my_list->push_back(*it);
            }
            return "";
        }
};

/* Command that removes all the args from the list stored in env */
class MyRemoveAllCmd : public ShellCmd {
    public:
        MyRemoveAllCmd(ShellEnv* env, string name, string description):  ShellCmd(env, name, description) {};
        virtual string run(vector<string> args) {
            args = args; /* to avoid warnings */
            list<string> *my_list = (list<string> *) env->getEntry("args");
            while (!my_list->empty()) {
                my_list->pop_front();
            }
            return "";
        }
};

/* Command that lists all the args from the list stored in env */
class MyListCmd : public ShellCmd {
    public:
        MyListCmd(ShellEnv* env, string name, string description):  ShellCmd(env, name, description) {};
        virtual string run(vector<string> args) {
            args = args; /* to avoid warnings */
            string output;
            list<string> *my_list = (list<string> *) env->getEntry("args");
            for (list<string>::iterator it = my_list->begin(); it != my_list->end(); ++it) {
                output += (*it) + "\n";
            }
            return output;
        }
};


int main(void) {

    /* Create environment for your shell */
    ShellEnv* env = new ShellEnv("my environment");

    /* Create your modules/commands tree and create entry in your env*/
    list<string> my_data;
    env->addEntry("args", &my_data);

    ShellCmd* add_cmd = new MyAddCmd(env, "add", "adds args to env");
    ShellCmd* rm_cmd = new MyRemoveAllCmd(env, "rm", "remove all args from env");
    ShellCmd* list_cmd = new MyListCmd(env, "list", "list all args from env");

    ShellModule* mod = new ShellModule(env, "args", "args commands");

    mod->add(add_cmd);
    mod->add(rm_cmd);
    mod->add(list_cmd);

    /* Start your shell application */
    ShellApp* my_shell = new ShellApp(env, "Env", "env>", mod);
    my_shell->setExitCommand("exit");
    string banner = "Welcome to Env Shell";
    banner += " (based on " + ShellInfo::getName() + " - " + ShellInfo::getVersion() + ")\n";
    my_shell->setWelcomeBanner(banner);
    my_shell->loop();

    exit(0);
}

