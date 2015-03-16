/* Copyright (C) 2015 the ownShell authors and contributors
 * <see AUTHORS file>
 *
 * This module is part of ownShell and is released under
 * the MIT License: http://www.opensource.org/licenses/mit-license.php
*/

#include "gtest/gtest.h"
#include "ownshell.h"
#include "shell_cmd_test.h"

using namespace ownshell;

class TestTree {

    public:
        TestTree() {};
        ~TestTree() {};
        static void createTree(ShellModule* root, ShellEnv* env) {

                /*   Commands tree:
                 *
                 *   root .......................................
                 *     |_ "mod 1"
                 *     |_ "mod 2"                        level 1
                 *     |_ "mod 3" ...............................
                 *     |     |_ "command 1"               level 2
                 *     |     |_ "mod 2" ..........................
                 *     |          |_ "command 2"          level 3
                 *     |          |_ "mod 4" .....................
                 *     |               |_ "command 1"
                 *     |               |_ "command 3"     level 4
                 *     |               |_ "command 4" ............
                 *     |
                 *     |_ "last" ........................ level 1
                 */
                /* level 1 */
                root->add(new ShellModule(env, "mod 1", "root/mod 1/ description"));
                root->add(new ShellModule(env, "mod 2", "root/mod 2/ description"));
                ShellModule* mod_3 = new ShellModule(env, "mod 3", "root/mod 3/ description");
                root->add(mod_3);

                /* level 2 */
                mod_3->add(new ShellCmd(env, "command 1", "root/mod 3/command 1 help"));
                ShellModule* mod_2 = new ShellModule(env, "mod 2", "root/mod 3/mod 2/ description");
                mod_3->add(mod_2);

                /* level 3 */
                mod_2->add(new ShellCmd(env, "command 2", "root/mod 3/mod 2/command 2 help"));
                ShellModule* mod_4 = new ShellModule(env, "mod 4", "root/mod 3/mod 2/mod 4 description");
                mod_2->add(mod_4);

                /* level 4 */
                mod_4->add(new ShellCmd(env, "command 1", "root/mod 3/mod 2/mod 4/command 1 help"));
                mod_4->add(new ShellCmd(env, "command 3", "root/mod 3/mod 2/mod 4/command 3 help"));
                mod_4->add(new ShellCmd(env, "command 4", "root/mod 3/mod 2/mod 4/command 4 help"));

                /* level 1 again */
                root->add(new ShellCmd(env, "zlast", "root/last/last help"));
        }
};

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
    EXPECT_EQ(2, my_mod->getChildrenNb());

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
    EXPECT_EQ("mod description\n\nModules ([+]) and commands:\n\t  - sub mod: sub mod description\n", mod->getHelp());

    /* if we add a sub command to sub_mod leading "-" is changed to "+" */
    ShellCmd* cmd = new ShellCmd(env, "cmd", "cmd description");
    sub_mod->add(cmd);
    EXPECT_EQ("mod description\n\nModules ([+]) and commands:\n\t[+] sub mod: sub mod description\n", mod->getHelp());
}

class ShellModuleComplexTest : public ::testing::Test {
    protected:
        ShellEnv* env = new ShellEnv("my env");
        ShellModule * root = new ShellModule(env, "root", "my root module description");

        virtual void SetUp(void) {
            TestTree::createTree(this->root, this->env);
        }
};

TEST_F(ShellModuleComplexTest, findComponentFromTokens) {

    ShellComponent* component;
    vector<string> tokens {"mod 3", "mod 2", "mod 4"};

    component = this->root->findComponentFromTokens(tokens);
    EXPECT_EQ("root/mod 3/mod 2/mod 4 description", component->getDescription());
    EXPECT_EQ(3, component->getParentsNb());

    vector<string> other_tokens {"mod 3", "mod 2", "mod 4", "command 1"};
    component = this->root->findComponentFromTokens(other_tokens);
    EXPECT_EQ("root/mod 3/mod 2/mod 4/command 1 help", component->getDescription());
    EXPECT_EQ(4, component->getParentsNb());
}

TEST_F(ShellModuleComplexTest, run) {

    ShellComponent* component;
    vector<string> tokens {"mod 3", "mod 2", "mod 4"};
    component = this->root->findComponentFromTokens(tokens);
    vector<string> args {"first", "second"};
    EXPECT_EQ("/!\\ You cannot run this module directly\n\nroot/mod 3/mod 2/mod 4 description\n\nModules ([+]) and commands:\n\t  - command 1: root/mod 3/mod 2/mod 4/command 1 help\n\t  - command 3: root/mod 3/mod 2/mod 4/command 3 help\n\t  - command 4: root/mod 3/mod 2/mod 4/command 4 help\n", component->run(args));
}

TEST_F(ShellModuleComplexTest, getChildAt) {

    ShellComponent* component;

    component = this->root->getChildAt(0);
    EXPECT_EQ("mod 1", component->getName());
}

TEST_F(ShellModuleComplexTest, getFullPath) {

    ShellComponent* component;
    vector<string> tokens {"mod 3", "mod 2", "mod 4"};
    component = this->root->findComponentFromTokens(tokens);
    EXPECT_EQ("root/mod 3/mod 2/mod 4 description", component->getDescription());

    EXPECT_EQ("mod 4 mod 2 mod 3", component->getFullPath());
}


class ShellModuleIteratorTest : public ::testing::Test {
    protected:
        ShellEnv* env = new ShellEnv("my env");
        ShellModule * root = new ShellModule(env, "root", "my root module description");

        virtual void SetUp(void) {
            TestTree::createTree(this->root, this->env);
        }
};

TEST_F(ShellModuleIteratorTest, findComponentFromTokens) {

    ShellComponentIterator* it = this->root->createIterator();
    ShellComponent* component;

    component = it->next();
    EXPECT_EQ("mod 1", component->getName());

    component = it->next();
    EXPECT_EQ("mod 2", component->getName());

    component = it->next();
    EXPECT_EQ("mod 3", component->getName());

    component = it->next();
    EXPECT_EQ("command 1", component->getName());

    component = it->next();
    EXPECT_EQ("mod 2", component->getName());

    component = it->next();
    EXPECT_EQ("command 2", component->getName());
}

