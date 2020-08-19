#include <iostream>
#include <pthread.h>
#include <thread>
#include <chrono>

// pthread_exit()によるスレッドの終了

// n=1の時のみ出力し、スレッドを終了する。
void anotherFunc(int n)
{
    if(n != 1) return;
    std::cout << "Hasta la vista, baby" << std::endl;
    // 現在のスレッドを終了。
    pthread_exit(nullptr);
}

void* threadFunc(void* arg)
{
    for(int i = 0; i < 3; ++i) {
        std::cout << "threadFunc :" << i << std::endl;
        anotherFunc(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    return nullptr;
}

int main()
{
    pthread_t thread;

    if(pthread_create(&thread, nullptr, threadFunc, nullptr) != 0) {
        std::cout << "Error" << std::endl;
        exit(1);
    }

    for(int i = 0; i < 5; ++i) {
        std::cout << "I'm main" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    return 0;
}