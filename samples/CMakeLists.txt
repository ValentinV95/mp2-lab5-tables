file(GLOB hdrs "*.h*" "../include/*.h" "../polinom/include/*.h")
file(GLOB srcs "*.cpp" "../src/*.cpp" "../polinom/src/*.cpp")

add_executable(tables ${srcs} ${hdrs})
