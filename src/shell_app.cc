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


ShellApp::ShellApp(ShellEnv* env, std::string prompt, ShellComponent* root)
{
    this->env = env;
    this->prompt = prompt;
    this->root = root;
    this->exit_cmd_set = 0;
    this->welcome_banner = "";
}

std::string ShellApp::getGeneralHelp(void)
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
    std::cout << this->prompt << " " ;
}

void ShellApp::displayError(std::string error)
{
    std::cerr << "Error: " << error << std::endl ;
}

void ShellApp::displayInfo(std::string msg)
{
    std::cerr << msg << std::endl ;
}

void ShellApp::displayWelcomeBanner(void)
{
    if (this->welcome_banner != "")
        std::cout << this->welcome_banner << std::endl ;
}

void ShellApp::setExitCommand(std::string name)
{
    this->exit_cmd = name;
    this->exit_cmd_set = 1;
}

void ShellApp::setWelcomeBanner(std::string banner)
{
    this->welcome_banner = banner;
}

std::vector<std::string> ShellApp::getCmdLineTokens(void)
{
    std::string full_cmd;
    std::getline(std::cin, full_cmd);
    std::string buf;
    std::stringstream ss(full_cmd);
    std::vector<std::string> tokens;

    while (ss >> buf) {
        tokens.push_back(buf);
    }
    return tokens;
}

void ShellApp::displayHelp(std::vector<std::string> tokens)
{
    std::string help;
    int size = tokens.size();

    try {
        /* help was typed without any additional arg, display general help */
        help = this->getGeneralHelp();
        std::cout << help << std::endl;
    } catch (shell_except& e) {
        this->displayError(e.what());
        this->displayInfo("Type help for general help");
    } catch (...) {
        this->displayError("help not found. Type help for general help");
    };
}

void ShellApp::loop(void)
{
    this->displayWelcomeBanner();
    while (1) {

        this->displayPrompt();
        std::vector<std::string> tokens = this->getCmdLineTokens();

        /* Check for exit command */
        if (this->exit_cmd_set && (tokens.size() >= 1) && (tokens[0] == this->exit_cmd))
            exit(0);

        /* Check for help commands */
        if ((tokens.size() >= 1) && (tokens[0] == "help")) {
            this->displayHelp(tokens);
            continue;
        }


        try {
            // TODO find component and run it!
            //this->runner->runCmd(tokens[0], tokens[1], (char **) 0, tokens.size() - 2);
        } catch (shell_except e) {
            this->displayError("command error");
        }
    };
}
