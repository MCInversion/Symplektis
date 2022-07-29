cmake_minimum_required(VERSION 3.14)

project(Symplekt_Algorithms_Tests VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB Symplekt_Algorithms_Tests_Src CONFIGURE_DEPENDS "*.h" "*.cpp")

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(${PROJECT_NAME} ${Symplekt_Algorithms_Tests_Src})

# ----- make sure SYMPLEKTIS_ROOT_DIR is readable in source ---------
#
# VS Test Explorer automatically sets working directory as CMAKE_CURRENT_BINARY_DIR,
# so we use DSYMPLEKTIS_ROOT_DIR in source files instead of std::filesystem::::current_path()
#
target_compile_definitions(${PROJECT_NAME} PUBLIC DSYMPLEKTIS_ROOT_DIR=\"${SYMPLEKTIS_ROOT_DIR}\")

# to make sure "Symplekt_" source directories can be included
target_include_directories(${PROJECT_NAME} PUBLIC ${SYMPLEKTIS_SOURCE_DIR})
# include_directories(${SYMPLEKTIS_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}
	gtest_main			    # gtest lib
	Symplekt_Algorithms     # tested lib
	Symplekt_GeometryKernel # geom dependencies
	Symplekt_UtilityGeneral # util dependencies
)

add_test(NAME Symplekt_Algorithms_TestSuite COMMAND ${PROJECT_NAME})

# post build command
#add_custom_command(
#     TARGET ${PROJECT_NAME}
#     COMMENT "Run tests"
#     POST_BUILD 
#     COMMAND ${PROJECT_NAME}
#)