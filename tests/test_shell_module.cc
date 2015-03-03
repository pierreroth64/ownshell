/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#include "gtest/gtest.h"
#include "shell.h"
#include "shell_cmd_test.h"

class ShellModuleTest : public ::testing::Test {
    protected:
        ShellEnv* env;
        ShellModule* my_mod;
        virtual void SetUp(void) {
            this->env = new ShellEnv("my env");
            this->my_mod = new ShellModule(env, "my module", "description of my module");
        }
        virtual void TearDown(void) {
            delete this->my_mod;
            delete this->env;
        }
};

TEST_F(ShellModuleTest, add) {

    MyShellCmd* my_cmd_1 = new MyShellCmd(this->env, "my command 1", "my command 1 description");
    MyShellCmd* my_cmd_2 = new MyShellCmd(this->env, "my command 2", "my command 2 description");

    my_mod->add(my_cmd_1);
    my_mod->add(my_cmd_2);
    EXPECT_EQ(2, my_mod->getComponentsNb());

    delete my_cmd_1;
    delete my_cmd_2;
}

TEST_F(ShellModuleTest, addAlready) {

    MyShellCmd* my_cmd_1 = new MyShellCmd(this->env, "my command", "my command description");
    MyShellCmd* my_cmd_2 = new MyShellCmd(this->env, "my command", "same command name");

    my_mod->add(my_cmd_1);
    ASSERT_THROW(my_mod->add(my_cmd_2), shell_except_already);

    delete my_cmd_1;
    delete my_cmd_2;
}

TEST_F(ShellModuleTest, getHelp) {

    ShellModule* mod = new ShellModule(env, "mod", "mod description");
    EXPECT_EQ("mod description", mod->getHelp());
}

TEST_F(ShellModuleTest, getHelpMultiple) {

    ShellModule* mod = new ShellModule(env, "mod", "mod description");
    ShellModule* sub_mod = new ShellModule(env, "sub mod", "sub mod description");
    mod->add(sub_mod);
    EXPECT_EQ("mod description\n\nComponents:\n\t-sub mod: sub mod description\n", mod->getHelp());

    /* if we add a sub command to sub_mod leading "-" is changed to "+" */
    ShellCmd* cmd = new ShellCmd(env, "cmd", "cmd description");
    sub_mod->add(cmd);
    EXPECT_EQ("mod description\n\nComponents:\n\t+sub mod: sub mod description\n", mod->getHelp());
}
