/* Copyright (C) 2015 Legrand
   All rights reserved

   Shell library - module implementation */

#include "shell_except.h"
#include "shell_component.h"

ShellComponent::ShellComponent(ShellEnv* env, std::string name, std::string description)
{
    this->env = env;
    this->name = name;
    this->description = description;
}

std::string ShellComponent::getName(void)
{
    return this->name;
}

std::string ShellComponent::getDescription(void)
{
    return this->description;
}

std::string ShellComponent::getHelp(void)
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

std::string ShellComponent::run(char** argv, int argc)
{
    throw shell_except_unsupported("Operation not supported");
}
