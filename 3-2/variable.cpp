#include <iostream>
#include <pthread.h>
#include <thread>
#include <chrono>

int varA;

void* threadFunc(void *arg)
{
    int n = *((int*)arg);
    int varB;

    varB = 4 * n;
    std::cout << "threadFunc - 1 " << n << "," << varA << "," << varB << std::endl;
    varA = 5 * n;
    std::cout << "threadFunc - 2 " << n << "," << varA << "," << varB << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    std::cout << "threadFunc - 3 " << n << "," << varA << "," << varB << std::endl;
    varB = 6*n;
    std::cout << "threadFunc - 4 " << n << "," << varA << "," << varB << std::endl;
    return nullptr;
}

int main()
{
    pthread_t thread1, thread2;
    int varB;

    varA = 1; varB = 2;
    int a = 1;
    int b= 2;
    std::cout << "main - 1 " << varA << "," << varB << std::endl;
    pthread_create(&thread1, nullptr, threadFunc, (void*)&a);
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    varB = 3;
    std::cout << "main - 2 " << varA << "," << varB << std::endl;
    pthread_create(&thread2,nullptr, threadFunc, (void*)&b);
    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);
    std::cout << "main - 3 " << varA << "," << varB << std::endl;
    return 0;
}