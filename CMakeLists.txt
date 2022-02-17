cmake_minimum_required(VERSION 3.2)
project(dht)

set(CMAKE_CXX_STANDARD 14)

add_library(dht "src/common_dht_read.c"  "src/common_dht_read.h"  "src/pi_2_dht_read.c"  "src/pi_2_dht_read.h"	"src/pi_2_mmio.c"  "src/pi_2_mmio.h")

add_executable(dht_test "src/main.cpp")
target_link_libraries(dht_test dht)
