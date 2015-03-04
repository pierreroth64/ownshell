/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#include <iostream>
#include <cstdlib>
#include "ownshell.h"

/* This Hooked Shell shows how to hook into the shell application
 *
 * Once in shell:
 *
 * hooked> simple fail    ----> shows your on_error hook
 * hooked> unknown        ----> shows your on_critical hook
 * hooked> help unknown   ----> shows your on_error and on_info hook
 * */

using namespace std;

class MyShellSuccessCmd : public ShellCmd {
    public:
        MyShellSuccessCmd(ShellEnv* env, string name, string description):  ShellCmd(env, name, description) {};
        virtual string run(vector<string> args) {
            args = args; /* to avoid warnings */
            return "good ! :-)";
        };
};

class MyShellFailCmd : public ShellCmd {
    public:
        MyShellFailCmd(ShellEnv* env, string name, string description):  ShellCmd(env, name, description) {};
        virtual string run(vector<string> args) {
            args = args; /* to avoid warnings */
            string error = this->getName() + " failed ! :-(";
            throw runtime_error(error.c_str());
        };
};


class MyShellHooks: public ShellHooks
{
    public:
        MyShellHooks(ShellEnv* env, void* user_data): ShellHooks(env, user_data) {};
        virtual void on_error(runtime_error* error, ShellComponent * component) {
            component = component; /* to avoid warnings */
            cerr << "My 'error' hook - " << error->what() << endl ;
        };
        virtual void on_info(string msg, ShellComponent * component) {
            component = component; /* to avoid warnings */
            cerr << "My 'info' hook - " << msg << endl ;
        };
        virtual void on_critical(string msg) {
            cerr << "My 'critical' hook - " << msg << endl ;
        };
};


int main(void) {

    /* Create environment for your shell */
    ShellEnv* env = new ShellEnv("my environment");

    /* Create your modules/commands tree */
    ShellCmd* success_cmd = new MyShellSuccessCmd(env, "success", "cmd that suceeds");
    ShellCmd* fail_cmd = new MyShellFailCmd(env, "fail", "cmd that fails");

    ShellModule* mod = new ShellModule(env, "simple", "simple commands");
    mod->add(success_cmd);
    mod->add(fail_cmd);


    /* Start your shell application */
    ShellApp* my_shell = new ShellApp(env, "Hooked Shell", "hooked>", mod);
    my_shell->setExitCommand("exit");
    string banner = "Welcome to Hooked Shell";
    banner += " (based on " + ShellInfo::getName() + " - " + ShellInfo::getVersion() + ")\n";
    my_shell->setWelcomeBanner(banner);
    my_shell->setHooks(new MyShellHooks(env, (void *) NULL));
    my_shell->loop();

    exit(0);
}

