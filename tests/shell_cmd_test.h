/* Copyright (C) 2015 Legrand
   All rights reserved

   Shell Library - concrete shell cmd class for testing */

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

