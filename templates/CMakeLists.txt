cmake_minimum_required(VERSION 3.3)
project(templates)

add_executable(algo algo.cpp)
add_executable(algo_tree algo_tree.cpp)
add_executable(bit bit.cpp)
# add_executable(cps cps.cpp)
# target_compile_features(cps PRIVATE cxx_std_17)
add_executable(fft fft.cpp)
add_executable(gcd gcd.cpp)
add_executable(interpreter interpreter.cpp)
add_executable(sort sort.cpp)
add_executable(suffix_array suffix_array.cpp)
add_executable(stack stack.cpp)
