/* Copyright (C) 2015 Legrand
   All rights reserved

   Shell library - environment implementation */

#include "shell_except.h"
#include "shell_env.h"

class ShellEnvDataEntry
{
    public:
        std::string name;
        void* data;
        ShellEnvDataEntry(std::string name, void* data);
};

ShellEnvDataEntry::ShellEnvDataEntry(std::string name, void* data)
{
    this->name = name;
    this->data = data;
}

ShellEnv::ShellEnv(std::string name)
{
    this->name = name;
}

void ShellEnv::addEntry(std::string name, void* entry)
{
    this->entries.push_back(new ShellEnvDataEntry(name, entry));
}

void ShellEnv::removeEntry(std::string name)
{
    for (std::list<ShellEnvDataEntry *>::iterator it = this->entries.begin(); it != this->entries.end(); ) {
        if ((*it)->name == name) {
            it = this->entries.erase(it);
            break;
        } else {
            ++it;
        }
    }
}

void * ShellEnv::getEntry(std::string name)
{
    void * found = 0;
    ShellEnvDataEntry * entry;
    for (std::list<ShellEnvDataEntry *>::iterator it = this->entries.begin(); it != this->entries.end(); ++it) {
        entry = (*it);
        if (entry->name == name)
            found = entry->data;
    }
    if (!found)
        throw shell_except_not_found("Environment entry not found");
    return found;
}

unsigned int ShellEnv::getEntriesNumber(void)
{
    return this->entries.size();
}
