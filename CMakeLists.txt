cmake_minimum_required(VERSION 3.10)
project(FastBoot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} SHARED
	include/mod/config.cpp

	src/main.cpp
	src/socialclub.cpp
	src/startmode.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	log
)

target_compile_options(${PROJECT_NAME} PRIVATE
	-O3
)

target_link_options(${PROJECT_NAME} PRIVATE
	-s
)
