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
                 *     |_ "zlast" ....................... level 1
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

class ShellModuleIteratorTest : public ::testing::Test {
    protected:
        ShellEnv* env = new ShellEnv("my env");
        ShellModule * root = new ShellModule(env, "root", "my root module description");

        virtual void SetUp(void) {
            TestTree::createTree(this->root, this->env);
        }
};

TEST_F(ShellModuleIteratorTest, next) {

    ShellComponentIterator* it = this->root->createIterator();
    ShellComponent* component;

    component = it->next();
    EXPECT_EQ("mod 1", component->getName());

    component = it->next();
    EXPECT_EQ("mod 2", component->getName());

    component = it->next();
    EXPECT_EQ("mod 3", component->getName());

    component = it->next();
    EXPECT_EQ("zlast", component->getName());

    component = it->next();
    EXPECT_EQ("command 1", component->getName());

    component = it->next();
    EXPECT_EQ("mod 2", component->getName());

    component = it->next();
    EXPECT_EQ("command 2", component->getName());
}

TEST_F(ShellModuleIteratorTest, destroyBeforeEnd) {

    ShellComponentIterator* it = this->root->createIterator();
    ShellComponent* component;

    component = it->next();
    EXPECT_EQ("mod 1", component->getName());

    delete it;
}

TEST_F(ShellModuleIteratorTest, hasNext) {

    unsigned int children_nb = this->root->getAllChildrenNb();
    unsigned int count = 0;
    ShellComponentIterator* it = this->root->createIterator();
    ShellComponent* component;

    while(it->hasNext()) {
        count++;
        component = it->next();
    }

    EXPECT_EQ(children_nb, count);

    delete it;
}

