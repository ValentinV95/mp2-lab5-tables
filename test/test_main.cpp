#define _CRT_SECURE_NO_WARNIGNS
#pragma warning(disable : 4996)
#pragma warning(disable : 4002)

#include "../gtest/gtest.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
