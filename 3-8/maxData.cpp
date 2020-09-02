#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <random>

constexpr int DATASIZE = 1000;
constexpr int THREADS = 10;

int data[DATASIZE];

// グローバル配列に乱数を入れる。
void setRandomeData()
{
    std::random_device rng;
    for(int i = 0; i < DATASIZE; i++) {
        data[i] = rng();
    }
}

// 一定範囲内の最大値を求める
int getMax(size_t startIndex, size_t endIndex)
{
    int max = data[startIndex];
    for(size_t index = startIndex + 1; index <= endIndex; index++) {
        if(max < data[index]) {
            max = data[index];
        }
    }
    return max;
}

void* threadFunc(void* arg)
{
    int n = *((int*)arg);
    size_t startIndex = (DATASIZE/THREADS) * n;
    size_t endIndex = startIndex + (DATASIZE / THREADS) - 1;
    int max = getMax(startIndex, endIndex);
    return (void*)max;
}

int main()
{
    pthread_t thread[THREADS];
    int res[THREADS];
    
    setRandomeData();
    int max;

    for(int i = 0; i < THREADS; i++) {
        if(pthread_create(&(thread[i]),nullptr, threadFunc, (void*)&i) != 0) 
        {
            std::cout << "erorr\n";
            exit(1);
        }
    }

    for(int i = 0; i < THREADS; i++) {
        if(pthread_join(thread[i], (void**)&(res[i]))!= 0) {
            exit(1);
        }
    }

    max = res[0];
    for(int i = 1; i < THREADS; ++i) {
        if(max < res[i]) {
            max = res[i];
        }
    }

    std::cout << max << std::endl;
    return 0;
}