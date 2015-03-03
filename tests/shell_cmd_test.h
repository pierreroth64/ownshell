/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#include "gtest/gtest.h"
#include "shell.h"

/* Shell command concrete class for testing */
class MyShellCmd : public ShellCmd {
    public:
        MyShellCmd(ShellEnv* env, std::string name, std::string description):  ShellCmd(env, name, description) {
            this->was_called = 0;
            this->arg_nb = 0;
        };
        bool was_called;
        unsigned int arg_nb;
        virtual std::string run(char** argv, int argc);
        void reset(void);
        int lastArgNumber(void);
};

