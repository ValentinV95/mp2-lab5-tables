cmake_minimum_required(VERSION 2.8)

include_directories(include gtest polinom/include)

# BUILD
add_subdirectory(samples)
add_subdirectory(test)
add_subdirectory(gtest)