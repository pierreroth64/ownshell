/* Copyright (C) 2015 Legrand
   All rights reserved

   Shell library - module implementation */

#include "shell_except.h"
#include "shell_module.h"

ShellComponent* ShellModule::findComponent(ShellComponent * component)
{
    ShellComponent * _component;

    if (component == 0)
        throw shell_except_not_found("Component not found");

    for (list<ShellComponent *>::iterator it = this->components.begin(); it != this->components.end(); ++it) {
        _component = (*it);
        if (_component->getName() == component->getName())
            return _component;
    }
    throw shell_except_not_found("Component not found");
}

void ShellModule::add(ShellComponent* component)
{
    try {
        this->findComponent(component);
        throw shell_except_already("Component with such a name already exists");
    } catch (shell_except_not_found e) {
        this->components.push_back(component);
    }
}

void ShellModule::remove(ShellComponent* component)
{
    for (list<ShellComponent *>::iterator it = this->components.begin(); it != this->components.end(); ) {
        if ((*it)->getName() == component->getName()) {
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

    if (component->getComponentsNb()) {
        help += "\n\nComponents:\n";
    }
    for (list<ShellComponent *>::iterator it = this->components.begin(); it != this->components.end(); ++it) {
        component = (*it);
        if (component->getComponentsNb())
            help += "\t+";
        else
            help += "\t-";
        help += component->getName() + ": " + component->getDescription() + "\n";
    }
    return help;
}

string ShellModule::run(char** argv, int argc)
{
    string help = "You cannot run this module directly.\n\n";
    /* Running a module returns help */
    return help + this->getHelp();
}
