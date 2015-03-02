/* Copyright (C) 2015 Legrand
   All rights reserved

   Shell library - app implementation */

#include "shell_except.h"
#include "shell_app.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>


ShellApp::ShellApp(ShellEnv* env, string prompt, ShellComponent* root)
{
    this->env = env;
    this->prompt = prompt;
    this->root = root;
    this->exit_cmd_set = 0;
    this->welcome_banner = "";
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
    this->exit_cmd_set = 1;
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
    int size = tokens.size();

    try {
        /* help was typed without any additional arg, display general help */
        help = this->getGeneralHelp();
        cout << help << endl;
    } catch (shell_except& e) {
        this->displayError(e.what());
        this->displayInfo("Type help for general help");
    } catch (...) {
        this->displayError("help not found. Type help for general help");
    };
}

void ShellApp::findComponentAndArgsFromTokens(vector<string> tokens, ShellComponent** component, vector<string> * args)
{
    /* from given tokens:
     *  - find the corresponding ShellComponent
     *  - find the args */

     throw shell_except_not_found("Component not found");

}

void ShellApp::loop(void)
{
    this->displayWelcomeBanner();
    while (1) {

        this->displayPrompt();
        vector<string> tokens = this->getCmdLineTokens();

        /* Check for exit command */
        if (this->exit_cmd_set && (tokens.size() >= 1) && (tokens[0] == this->exit_cmd))
            exit(0);

        /* Check for help commands */
        if ((tokens.size() >= 1) && (tokens[0] == "help")) {
            this->displayHelp(tokens);
            continue;
        }

        try {
            //ShellComponent * component;
            //vector<string> args;
            //this->findComponentAndArgsFromTokens(tokens, &component, &args);
            //component->run(tokens)
            // TODO find component and run it!
            //this->runner->runCmd(tokens[0], tokens[1], (char **) 0, tokens.size() - 2);
        } catch (shell_except e) {
            this->displayError("command error");
        }
    };
}
