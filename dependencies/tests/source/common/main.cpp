#include <Windows.h>
#include <gtest\gtest.h>
#include <iostream>

#include <url/tests.h>

int __cdecl main()
{
    testing::InitGoogleTest();
    auto result = RUN_ALL_TESTS();

    system("pause");
    return result;
}