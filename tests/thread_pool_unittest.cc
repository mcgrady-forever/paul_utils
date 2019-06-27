//
// Created by Apple on 2019-06-26.
//

#include <iostream>
#include <string>

#include <gtest/gtest.h>

#include <thread_pool.h>

//TEST(MyTest, Test1) {
//    int a = 1;
//    EXPECT_EQ(a, 0);
//}
//
//TEST(MyTest, Test2) {
//    int a = 1;
//    EXPECT_EQ(a, 1);
//}

TEST(ThreadPool, Test1) {
    ThreadPool pool(4);

    auto result = pool.enqueue([](int answer) { return answer; }, 42);

    auto res_val = result.get();
    std::cout << res_val << std::endl;
    EXPECT_EQ(res_val, 42);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}