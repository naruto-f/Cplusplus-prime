cmake_minimum_required(VERSION 3.16)
project(fund_info)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_compile_options(-l sqlite3)
add_executable(fund_info main.cpp init_sqlite3_db.cpp init_sqlite3_db.h sourcepage_Get.cpp sourcepage_Get.h Date_handle.cpp Date_handle.h)
target_link_libraries(fund_info LINK_PUBLIC sqlite3)