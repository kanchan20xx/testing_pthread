#include <iostream>
#include <thread>
#include <pthread.h>
#include <chrono>

void *threadFunc(void *arg)
{
    int i;
    for(i = 0; i < 3; i++) {
        std::cout << "I'm threadFunc:" << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return nullptr;
}

int main()
{
    pthread_t thread;
    int i;

    if(pthread_create(&thread, nullptr, threadFunc, nullptr) != 0) {
        exit(1);
    }

    for(i = 0; i < 5; i++) {
        std::cout << "I'm main:" << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}