#include <pthread.h>
#include <iostream>

constexpr int N_THREAD = 1000;
constexpr int MAX_PRIME_NUMBERS = 100000;

int primeNumber[MAX_PRIME_NUMBERS];
int nPrimeNumber;
pthread_mutex_t usingPrimeNumber;

int isPrimeNumber(int m)
{
    for(int i = 0; i < nPrimeNumber; ++i) {
        if(m % primeNumber[i] == 0)
        {
            return 0;
        }
    }
    return 1;
}

int countPrimeNumbers(int n)
{
    pthread_mutex_lock(&usingPrimeNumber);
    nPrimeNumber = 0;
    int i;
    for(i = 2; i <= n; ++i) {
        if (isPrimeNumber(i)) {
            if(nPrimeNumber >= MAX_PRIME_NUMBERS) {
                exit(1);
            }
            primeNumber[nPrimeNumber] = i;
            nPrimeNumber++;
        }
    }
    i = nPrimeNumber;
    pthread_mutex_unlock(&usingPrimeNumber);
    return i;
}

void *threadFunc(void *arg)
{
    int n = *((int*)arg);
    int x = countPrimeNumbers(n);

    if(x != 25) {
        std::cout << n << ":" << x << std::endl;
    }

    return nullptr;
}

int main()
{
    pthread_t threads[N_THREAD];
    pthread_mutex_init(&usingPrimeNumber, nullptr);

    int n = 100;
    for(int i = 0; i < N_THREAD; ++i) 
    {
        if(pthread_create(&threads[i], nullptr, threadFunc, (void*)&n ) != 0) {
            exit(1);
        }
    }

    for(int i = 0; i < N_THREAD; ++i) {
        pthread_join(threads[i], nullptr);
    }

    pthread_mutex_destroy(&usingPrimeNumber);

    return 0;
}
