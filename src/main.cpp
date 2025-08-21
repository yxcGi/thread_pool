#include <iostream>
#include "threadpool.hpp"
#include <future>

// 计算累计和
using ullong = unsigned long long;
ullong add(ullong a, ullong b)
{
    ullong sum = 0;
    for (ullong i = a; i <= b; ++i)
    {
        sum += i;
    }
    return sum;
}


int main()
{
    ThreadPool* pool = &ThreadPool::getInstance();
    pool->start(5);
    std::cout << "start()" << std::endl;
    auto first_time1 = std::chrono::high_resolution_clock::now();
    std::future<ullong> res1 = pool->submitTask(add, 1, 10000000000);
    std::future<ullong> res2 = pool->submitTask(add, 10000000001, 20000000000);
    std::future<ullong> res3 = pool->submitTask(add, 20000000001, 30000000000);
    std::future<ullong> res4 = pool->submitTask(add, 30000000001, 40000000000);
    std::future<ullong> res5 = pool->submitTask(add, 40000000001, 50000000000);
    std::cout << res1.get() + res2.get() + res3.get() + res4.get() << '\n';
    auto end_time1 = std::chrono::high_resolution_clock::now();

    auto first_time2 = std::chrono::high_resolution_clock::now();
    ullong sum2 = 0;
    for (ullong i = 1; i <= 50000000000; ++i)
    {
        sum2 += i;
    }
    std::cout << sum2 << std::endl;
    auto end_time2 = std::chrono::high_resolution_clock::now();

    std::cout << "多线程耗时: "
        << std::chrono::duration_cast<std::chrono::milliseconds>(end_time1 - first_time1).count()
        << " ms" << std::endl;
    std::cout << "单线程耗时: "
        << std::chrono::duration_cast<std::chrono::milliseconds>(end_time2 - first_time2).count()
        << " ms" << std::endl;

    getchar();

    return 0;
}