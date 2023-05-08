#include <iostream>
#include <atomic>
#include <vector>
#include <thread>
#include "quickpop.hpp"
#include "tests.hpp"

//////////Primitive type/////////////

int IntCompFunc(const int lhs, const int rhs)
{
    return lhs - rhs;
}

void TestPrimitiveType()
{
    QuickPopDataStructure<int> ds(&IntCompFunc);
    int arr[] = {3,6,7,2,4};
    for (int i = 0; i < sizeof(arr) / sizeof(int); ++i)
    {
        ds.Push(arr[i]);
    }

    TEST("pop 7",ds.Pop(),7);
    TEST("pop 6",ds.Pop(),6);
    TEST("pop 4",ds.Pop(),4);
    TEST("pop 3",ds.Pop(),3);
    TEST("pop 2",ds.Pop(),2);
    
    PASS;
}

//////////Complex type/////////////

class Person
{
public:
    Person(int hight = 0);
    ~Person();
    int m_hight;
};

Person::Person(int hight):m_hight(hight)
{
}

Person::~Person()
{
}


int PersonCompFunc(const Person lhs, const Person rhs)
{
    return lhs.m_hight - rhs.m_hight;
}

void TestComplexType()
{
    QuickPopDataStructure<Person> ds(&PersonCompFunc);
    int arr[] = {3,6,7,2,4, 5, 8, 19, 20, 23, 40, 50};

    for (int i = 0; i < sizeof(arr) / sizeof(int); ++i)
    {
        ds.Push(arr[i]);
    }


    TEST("pop 50",ds.Pop().m_hight,50);
    TEST("pop 40",ds.Pop().m_hight,40);
    TEST("pop 23",ds.Pop().m_hight,23);
    TEST("pop 20",ds.Pop().m_hight,20);
    TEST("pop 19",ds.Pop().m_hight,19);
    TEST("pop 8",ds.Pop().m_hight,8);
    TEST("pop 7",ds.Pop().m_hight,7);
    TEST("pop 6",ds.Pop().m_hight,6);
    TEST("pop 5",ds.Pop().m_hight,5);
    TEST("pop 4",ds.Pop().m_hight,4);
    TEST("pop 3",ds.Pop().m_hight,3);
    TEST("pop 2",ds.Pop().m_hight,2);
    
    PASS;
}

//////////Thread Safe/////////////

void TestThreadSafe()
{
    QuickPopDataStructure<int> qps(IntCompFunc);
    std::atomic_int sum(0);

    // Spawn multiple threads to push and pop values from the data structure
    const int numThreads = 10;
    const int numValuesPerThread = 100;
    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([&qps, &sum]() {
            for (int j = 0; j < numValuesPerThread; ++j) {
                int val = rand() % 100;
                qps.Push(val);
                sum += val;
                int poppedVal = qps.Pop();
                sum -= poppedVal;
            }
        });
    }

    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }
}

int main(int argc, char const *argv[])
{
    //TestPrimitiveType();
    TestComplexType();
    TestThreadSafe();
    return 0;
}



