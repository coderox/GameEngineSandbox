#include <gtest\gtest.h>

// Tests included here
#include <url/tests.hpp>

#if UWP
int __cdecl main()
#elif WIN32
int main(int argc, char* const argv[])
#endif
{
    testing::InitGoogleTest();
    auto result = RUN_ALL_TESTS();

    system("pause");
    return result;
}