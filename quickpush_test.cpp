#include <iostream>
#include "quickPush.hpp"


int intcompfunc(const int lhs, const int rhs)
{
    return lhs - rhs;
}

void TestNativeType()
{
    QuickPushDataStructure<int> ds(&intcompfunc);
    int arr[] = {3,6,7,2,4};
    ds.Push(arr[0]);
    ds.Push(arr[1]);
    ds.Push(arr[2]);
    ds.Push(arr[3]);
    ds.Push(arr[4]);

    std::cout << ds.Pop() <<std::endl;
    std::cout << ds.Pop() <<std::endl;
    std::cout << ds.Pop() <<std::endl;
    std::cout << ds.Pop() <<std::endl;
    std::cout << ds.Pop() <<std::endl;
}

int main(int argc, char const *argv[])
{
    TestNativeType();
    return 0;
}



