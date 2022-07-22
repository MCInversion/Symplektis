cmake_minimum_required(VERSION 3.14)

project(Symplekt_GeometryKernel_Tests VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB GeometryKernel_Tests_Src "*.h" "*.cpp")

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(${PROJECT_NAME} ${GeometryKernel_Tests_Src})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER ${SYMPLEKT_KERNEL_FOLDER})

# to make sure "Symplekt_" source directories can be included
target_include_directories(${PROJECT_NAME} PUBLIC ${SYMPLEKTIS_SOURCE_DIR})
# include_directories(${SYMPLEKTIS_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}
	gtest_main			    # gtest lib
	Symplekt_GeometryKernel # tested lib
	Symplekt_UtilityGeneral # util dependencies
)

add_test(NAME GeometryKernel_TestSuite COMMAND ${PROJECT_NAME})

# post build command
#add_custom_command(
#     TARGET ${PROJECT_NAME}
#     COMMENT "Run tests"
#     POST_BUILD 
#     COMMAND ${PROJECT_NAME}
#)
