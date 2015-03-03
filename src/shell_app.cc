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

ShellApp::ShellApp(ShellEnv* env, string prompt, ShellComponent* root)
{
    this->env = env;
    this->prompt = prompt;
    this->root = new ShellModule(env, "/", "");
    this->root->add(root);
    this->exit_cmd = "exit";
    this->help_cmd = "help";
    this->welcome_banner = "";
}

ShellApp::~ShellApp()
{
    if (this->root)
        delete this->root;
}
string ShellApp::getGeneralHelp(void)
{
    return "*** General help ***\n"\
           "Commands must provide one (or more!) <module> name(s) and a <command> name such as:\n"\
           "    device list \n"\
           "    extra utilities gettime \n"\
           "    datas set_output dev1 ON \n"\
           "To display module commands, type help <module>\n"\
           "To display command help, type help <module> <command>\n\n";
}

void ShellApp::displayPrompt(void)
{
    cout << this->prompt << " " ;
}

void ShellApp::displayError(string error)
{
    cerr << "Error: " << error << endl ;
}

void ShellApp::displayInfo(string msg)
{
    cerr << msg << endl ;
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
    if (tokens.size() == 1)
        help = this->getGeneralHelp();
    else {
        try {
            component = this->root->findComponentFromTokens(tokens);
            help = component->getHelp();
        } catch (shell_except& e) {
            this->displayError(e.what());
            this->displayInfo("Type help for general help");
        } catch (...) {
            this->displayError("help not found. Type help for general help");
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
            component->run(NULL, 0);
        } catch (shell_except e) {
            this->displayError("command error");
        }
    };
}
