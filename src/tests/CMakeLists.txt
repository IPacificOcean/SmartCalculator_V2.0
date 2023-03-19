# 'Google_test' is the subproject name
cmake_minimum_required(VERSION 3.21.1)

project(Google_tests)
set(CMAKE_CXX_STANDARD 17)
include(FetchContent)
FetchContent_Declare(
        googletest
        Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

#enable_testing()

set(HEADER_FILES
        ../model/executors/validator.h
        ../model/executors/parser.h
        ../model/executors/calculator_exec.h
        ../model/executors/plot.h
        ../model/executors/credit_exec.h
        ../model/executors/debit_exec.h
        ../model/fasad/model.h
        )

set(SOURCE_FILES
        ../model/executors/validator.cc
        ../model/executors/parser.cc
        ../model/executors/calculator_exec.cc
        ../model/executors/plot.cc
        ../model/executors/credit_exec.cc
        ../model/executors/debit_exec.cc
        ../model/fasad/model.cc
        )

add_library(smart_calc STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_executable(unit_tests tests.cc)

target_link_libraries(unit_tests
        smart_calc
        gtest
        gtest_main
        )

#add_test(test_all unit_tests)