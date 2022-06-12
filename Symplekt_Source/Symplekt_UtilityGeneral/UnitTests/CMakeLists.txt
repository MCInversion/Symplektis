cmake_minimum_required(VERSION 3.14)

project(Symplekt_UtilityGeneral_Tests VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB Symplekt_UtilityGeneral_Tests_Src "*.h" "*.cpp")

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(${PROJECT_NAME} ${Symplekt_UtilityGeneral_Tests_Src})

# to make sure "Symplekt_" source directories can be included
target_include_directories(${PROJECT_NAME} PUBLIC ${SYMPLEKTIS_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}
	gtest_main			       # gtest lib
	Symplekt_UtilityGeneral    # tested lib
)

add_test(NAME UtilityGeneral_TestSuite COMMAND ${PROJECT_NAME})

# post build command
#add_custom_command(
#     TARGET ${PROJECT_NAME}
#     COMMENT "Run tests"
#     POST_BUILD 
#     COMMAND ${PROJECT_NAME}
#)