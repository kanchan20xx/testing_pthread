#include <iostream>
#include <pthread.h>
#include <thread>
#include <chrono>

void *threadFunc(void* arg)
{
    int n = *((int*)arg);
    int i;

    for(int i = 0; i < n; i++) {
        std::cout << "I'm threadFunc." << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    return nullptr;
}

int main(int argc, char* argv[])
{
    pthread_t thread;
    int n = 8;

    if(pthread_create(&thread, nullptr, threadFunc, (void*)&n) != 0) {
        exit(1);
    }

    for(int i = 0; i < 5; ++i) {
        std::cout << "I'm main" << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    // 終了まで待ってくれる。
    if(pthread_join(thread, nullptr) != 0) {
        std::cout << "Error" << std::endl;
        exit(1);
    }

    std::cout << "End." << std::endl;
    return 0;
}