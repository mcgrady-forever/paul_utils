//
// Created by Apple on 2019-06-27.
//

#include <iostream>
#include <thread>
#include <string>
#include <vector>

int main() {
    std::vector<std::thread> works;
    for (int i = 0; i < 4; ++i) {
        works.emplace_back([]() {
            std::cout << "thread1" << std::endl;
        });
    }
    for (auto& t : works) {
        t.join();
    }

//    std::thread t1([]() {
//        std::cout << "thread1" << std::endl;
//    });
//    t1.join();
    return 0;
}