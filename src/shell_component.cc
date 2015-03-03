/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#include "shell_except.h"
#include "shell_component.h"

ShellComponent::ShellComponent(ShellEnv* env, string name, string description)
{
    this->env = env;
    this->name = name;
    this->description = description;
}

string ShellComponent::getName(void)
{
    return this->name;
}

string ShellComponent::getDescription(void)
{
    return this->description;
}

string ShellComponent::getHelp(void)
{
    return this->getDescription();
}

unsigned int ShellComponent::getComponentsNb(void)
{
    return 0;
}

void ShellComponent::add(ShellComponent* component)
{
    component = component;
    throw shell_except_unsupported("Operation not supported");
}

void ShellComponent::remove(ShellComponent* component)
{
    component = component;
    throw shell_except_unsupported("Operation not supported");
}

ShellComponent* ShellComponent::findComponentFromTokens(vector<string> tokens)
{
    tokens = tokens;
    throw shell_except_not_found("Component not found");
}

ShellComponent* ShellComponent::findComponentByName(string name)
{
    name = name;
    throw shell_except_not_found("Component not found");
}

string ShellComponent::run(char** argv, int argc)
{
    throw shell_except_unsupported("Operation not supported");
}
