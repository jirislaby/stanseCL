project(clang-cmake)
cmake_minimum_required(VERSION 3.0)

find_package(LLVM REQUIRED CONFIG)

add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})

find_package(Clang REQUIRED)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

add_library(parser Parser.cpp)

if (TARGET LLVMSupport)
	llvm_map_components_to_libnames(llvm_libs support core)
else()
	set(llvm_libs LLVM)
endif()
message(STATUS "Mapped LLVM libs: ${llvm_libs}")

target_link_libraries(parser libclang clang-cpp ${llvm_libs})

add_executable(stanseCL main.cpp)
target_link_libraries(stanseCL parser)
