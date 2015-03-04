/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#include "shell_except.h"
#include "shell_app.h"
#include "shell_module.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>

namespace ownshell {

class DefaultShellHooks: public ShellHooks
{
    public:
        DefaultShellHooks(ShellEnv* env, void* user_data): ShellHooks(env, user_data) {};
        virtual void on_error(runtime_error* error, ShellComponent * component) {
            component = component; /* to avoid warnings */
            cerr << "Error: " << error->what() << endl ;
        };
        virtual void on_info(string msg, ShellComponent * component) {
            component = component; /* to avoid warnings */
            cerr << msg << endl ;
        };
        virtual void on_critical(string msg) {
            cerr << msg << endl ;
        };
};

ShellApp::ShellApp(ShellEnv* env, string name, string prompt, ShellComponent* root)
{
    this->env = env;
    this->name = name;
    this->prompt = prompt;
    this->root = new ShellModule(env, "/", "");
    this->root->add(root);
    this->exit_cmd = "exit";
    this->help_cmd = "help";
    this->welcome_banner = "";
    this->top_help_msg = "";
    this->hooks = new DefaultShellHooks(env, (void *) NULL);
}

ShellApp::~ShellApp()
{
    if (this->root)
        delete this->root;
    if (this->hooks)
        delete this->hooks;
}

void ShellApp::setTopHelp(string msg)
{
    this->top_help_msg =  msg;
}

string ShellApp::getTopHelp(void)
{
    if (this->top_help_msg != "")
        return this->top_help_msg;
    else
        return "*** " + this->name + " help ***\n"\
               "Commands must provide one (or more!) <module> name(s) and a <command> name such as:\n"\
               "    device list \n"\
               "    extra utilities gettime \n"\
               "    device output set dev1 ON \n"\
               "To display module commands, type help <module 1>...<module N>\n"\
               "To display command help, type help <module 1>...<module N> <command>";
}

void ShellApp::displayPrompt(void)
{
    cout << this->prompt << " " ;
}

void ShellApp::displayWelcomeBanner(void)
{
    if (this->welcome_banner != "")
        cout << this->welcome_banner << endl ;
}

void ShellApp::setExitCommand(string name)
{
    this->exit_cmd = name;
}

void ShellApp::setHelpCommand(string name)
{
    this->help_cmd = name;
}

void ShellApp::setWelcomeBanner(string banner)
{
    this->welcome_banner = banner;
}

vector<string> ShellApp::getCmdLineTokens(void)
{
    string full_cmd;
    getline(cin, full_cmd);
    string buf;
    stringstream ss(full_cmd);
    vector<string> tokens;

    while (ss >> buf) {
        tokens.push_back(buf);
    }
    return tokens;
}

void ShellApp::displayHelp(vector<string> tokens)
{
    string help;
    ShellComponent* component;

    /* help was typed without any additional arg, display general help */
    if (tokens.size() == 1) {
        help = this->getTopHelp();
        help += this->root->getHelp();
    }
    else {
        try {
            component = this->root->findComponentFromTokens(tokens);
            help = component->getHelp();
        } catch (shell_except& e) {
            this->hooks->on_error(&e, component);
            this->hooks->on_info("Type help for general help", component);
        } catch (...) {
            this->hooks->on_critical("help not found. Type help for general help");
        };
    }
    cout << help << endl;
}

void ShellApp::loop(void)
{
    this->displayWelcomeBanner();
    while (1) {

        this->displayPrompt();
        vector<string> tokens = this->getCmdLineTokens();

        /* Check for exit command */
        if ((tokens.size() >= 1) && (tokens[0] == this->exit_cmd))
            exit(0);

        /* Check for help commands */
        if ((tokens.size() >= 1) && (tokens[0] == this->help_cmd)) {
            this->displayHelp(tokens);
            continue;
        }

        try {
            ShellComponent* component = this->root->findComponentFromTokens(tokens);
            /* We now need to separate args from module(s)/cmd path
             * Just play with number of parents */
            unsigned int nb = component->getParentsNb();
            vector<string> args(tokens.begin() + nb, tokens.end());
            cout << component->run(args) << endl;
        } catch (runtime_error e) {
            this->hooks->on_error(&e, (ShellComponent*) NULL);
        }
    };
}

} // namespace ownshell
