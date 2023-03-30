set(target polinoms_test)

#file(GLOB hdrs "*.h*" "../include/*.h" "../gtest/*.h" "../polinom/include/*.h")
file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp" "../src/*.cpp" "../polinom/src/*.cpp")

add_executable(${target} ${srcs} ${hdrs})
target_link_libraries(${target} gtest)
