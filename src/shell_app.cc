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


ShellApp::ShellApp(ShellEnv* env, std::string prompt, ShellRunner* runner)
{
    this->env = env;
    this->prompt = prompt;
    this->runner = runner;
    this->exit_cmd_set = 0;
    this->welcome_banner = "";
}

void ShellApp::displayPrompt(void)
{
    std::cout << this->prompt << " " ;
}

void ShellApp::displayError(std::string error)
{
    std::cerr << "Error: " << error << std::endl ;
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
    if (tokens.size() == 1) {
        /* help was taped without any extra arg, display general help */
        std::cout << this->runner->getAllModulesHelp() << std::endl;
    }
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

        /* It's a command, check for module and command name and run it! */
        if (tokens.size() < 2 ) {
            this->displayError("Number of args must be at least 2 (module and cmd names)");
            continue;
        }

        try {
            this->runner->runCmd(tokens[0], tokens[1], (char **) 0, tokens.size() - 2);
        } catch (shell_except e) {
            this->displayError("command error");
        }
    };
}
