/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#include "shell_except.h"
#include "shell_module.h"

namespace ownshell {

ShellComponent* ShellModule::findComponent(ShellComponent * component)
{
    if (component == 0)
        throw shell_except_not_found("Component not found");

    return this->findComponentByName(component->getName());
}

ShellComponent* ShellModule::findComponentByName(string name)
{
    ShellComponent* _component;
    for (list<ShellComponent *>::iterator it = this->components.begin(); it != this->components.end(); ++it) {
        _component = (*it);
        if (_component->getName() == name)
             return _component;
    }
    throw shell_except_not_found("Component not found");
}

ShellComponent* ShellModule::findComponentFromTokens(vector<string> tokens)
{
    ShellComponent* last_found = this;
    string name;
    for(std::vector<string>::iterator it = tokens.begin(); it != tokens.end(); ++it) {
        name = *it;
        try {
            last_found = last_found->findComponentByName(name);
        } catch (shell_except_not_found e) {

        }
    }
    if (last_found != this)
        return last_found;
    throw shell_except_not_found("Component not found");
}

void ShellModule::add(ShellComponent* component)
{
    try {
        this->findComponent(component);
        throw shell_except_already("Component with such a name already exists");
    } catch (shell_except_not_found e) {
        this->components.push_back(component);
        component->setParent(this);
    }
}

void ShellModule::remove(ShellComponent* component)
{
    for (list<ShellComponent *>::iterator it = this->components.begin(); it != this->components.end(); ) {
        if ((*it)->getName() == component->getName()) {
            component->setParent(NULL);
            it = this->components.erase(it);
            break;
        } else {
            ++it;
        }
    }
}

unsigned int ShellModule::getComponentsNb(void)
{
    /* We do not iterate over components: just want first level ones in tree */
    return this->components.size();
}

string ShellModule::getHelp(void)
{
    ShellComponent * component;
    string help = this->getDescription();

    if (this->getComponentsNb()) {
        help += "\n\nModules ([+]) and commands:\n";
    }
    for (list<ShellComponent *>::iterator it = this->components.begin(); it != this->components.end(); ++it) {
        component = (*it);
        if (component->getComponentsNb())
            help += "\t[+] ";
        else
            help += "\t  - ";
        help += component->getName() + ": " + component->getDescription() + "\n";
    }
    return help;
}

string ShellModule::run(vector<string> args)
{
    args = args;
    string help = "You cannot run this module directly.\n\n";
    /* Running a module returns help */
    return help + this->getHelp();
}

} // namespace ownshell
