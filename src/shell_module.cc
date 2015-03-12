/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#include "shell_except.h"
#include "shell_module.h"
#include "iterators/shell_module_default_iterator.h"

namespace ownshell {

ShellComponent* ShellModule::findComponent(ShellComponent * component)
{
    if (component == 0)
        throw shell_except_not_found("Component not found");

    return findComponentByName(component->getName());
}

ShellComponent* ShellModule::findComponentByName(string name)
{
    ShellComponent* component;
    for (list<ShellComponent *>::iterator it = components_.begin(); it != components_.end(); ++it) {
        component = (*it);
        if (component->getName() == name)
             return component;
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
        findComponent(component);
        throw shell_except_already("Component with such a name already exists");
    } catch (shell_except_not_found e) {
        components_.push_back(component);
        component->setParent(this);
    }
}

void ShellModule::remove(ShellComponent* component)
{
    for (list<ShellComponent *>::iterator it = components_.begin(); it != components_.end(); ) {
        if ((*it)->getName() == component->getName()) {
            component->setParent(NULL);
            it = components_.erase(it);
            break;
        } else {
            ++it;
        }
    }
}

unsigned int ShellModule::getComponentsNb(void)
{
    /* We do not iterate over components: just want first level ones in tree */
    return components_.size();
}

string ShellModule::getHelp(void)
{
    ShellComponent * component;
    ShellHelpFormatter* formatter = env_->getHelpFormatter();
    string help = formatter->formatTitle(getDescription());

    if (getComponentsNb()) {
        help += formatter->formatSubTitle();
    }
    for (list<ShellComponent *>::iterator it = components_.begin(); it != components_.end(); ++it) {
        component = (*it);
        if (component->getComponentsNb())
            help += formatter->formatModuleHelp(component->getName(), component->getDescription());
        else
            help += formatter->formatModuleCmdHelp(component->getName(), component->getDescription());
    }
    return help;
}

string ShellModule::run(vector<string> args)
{
    args = args;
    ShellHelpFormatter* formatter = env_->getHelpFormatter();
    string help = formatter->formatWarning("You cannot run this module directly");
    /* Running a module returns help */
    return help + getHelp();
}

ShellComponent* ShellModule::getFirstChild()
{
    return components_.front();
}

ShellComponentIterator* ShellModule::createIterator()
{
    return new ShellModuleDefaultIterator(this);
}


} // namespace ownshell
