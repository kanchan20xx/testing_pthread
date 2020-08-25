#include <iostream>
#include <pthread.h>
#include <thread>
#include <chrono>

// スレッド実行関数戻り値を返す。
void *threadFunc(void* arg)
{
    int n = *((int*)arg);
    int i;

    for(int i = 0; i < n; ++i) {
        std::cout << "I'm threadFunc." << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    return (void*)n;
}

int main(int argc, char *argv[])
{
    pthread_t thread;
    int n = 2;
    if(pthread_create(&thread, nullptr, threadFunc, (void*)&n) != 0) {
        std::cout << "error" << std::endl;
        exit(1);
    }

    for(int i = 0; i < 5; ++i) {
        std::cout << "I'm Main." << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    int ret = 0;
    if(pthread_join(thread, (void**)&ret) != 0) {
        exit(1);
    }
    std::cout << "return value:" << ret << std::endl;
    return 0;
}