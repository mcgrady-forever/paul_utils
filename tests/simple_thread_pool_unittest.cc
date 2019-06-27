//
// Created by Apple on 2019-06-27.
//

#include <iostream>
#include <string>

#include <gtest/gtest.h>

#include <simple_thread_pool.h>

TEST(SimpleThreadPool, Test1) {
    SimpleThreadPool pool(4);

    int i = 10;
    auto task = [&] { std::cout << "add task, i = " << i << std::endl; return i; };
    bool res = pool.AddTask(task);

    EXPECT_EQ(res, true);
}

#include <simple_thread_pool.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}