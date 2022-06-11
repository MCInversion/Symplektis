cmake_minimum_required(VERSION 3.14)

project(Symplekt_DataReps_Tests VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB Symplekt_DataReps_Tests_Src "*.h" "*.cpp")

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(${PROJECT_NAME} ${Symplekt_DataReps_Tests_Src})
target_link_libraries(${PROJECT_NAME}
	gtest_main			                # gtest lib
	Symplekt_DataReps                   # tested lib
    Symplekt_UtilityGeneral             # dependent utils
)

add_test(NAME DataReps_TestSuite COMMAND ${PROJECT_NAME})

# post build command
#add_custom_command(
#     TARGET ${PROJECT_NAME}
#     COMMENT "Run tests"
#     POST_BUILD 
#     COMMAND ${PROJECT_NAME}
#)