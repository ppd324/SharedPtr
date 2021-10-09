#include <iostream>
#include <thread>
#include <chrono>
#include "SharedPtr.h"
using std::thread;

int main() {
    SharedPtr<int> ptr(new int(4));
    {
        SharedPtr<int> p1(ptr);
        std::cout<<"p1:"<<p1.use_count()<<std::endl;
        SharedPtr<int> p2(ptr);
        std::cout<<"p2:"<<p2.use_count()<<std::endl;
    }
    std::cout<<"p2:"<<ptr.use_count()<<std::endl;
    ptr = SharedPtr<int> (new int(5));
    std::cout<<"=============================="<<std::endl;
    {
        SharedPtr<int> p1(ptr);
        std::cout<<"p1:"<<p1.use_count()<<std::endl;
        std::cout<<"ptr use_count:"<<ptr.use_count()<<std::endl;
        SharedPtr<int> p2(ptr);
        std::cout<<"p2:"<<p2.use_count()<<std::endl;
        std::cout<<"ptr use_count:"<<ptr.use_count()<<std::endl;
    }
    thread t1([&](SharedPtr<int> &s) {
            SharedPtr<int> p3(s);
            std::cout<<"thread :: "<<*p3<<std::endl;
            std::cout<<"p use_count:"<<p3.use_count()<<std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(10));
    },std::ref(ptr));
    std::cout<<"ptr use_count:"<<ptr.use_count()<<std::endl;
    std::cout<<*ptr<<std::endl;
    t1.join();
    return 0;
}
