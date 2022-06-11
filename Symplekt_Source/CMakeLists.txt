cmake_minimum_required(VERSION 3.14)

# use a diferent name for GUI version
project(Symplektis_ConsoleApp VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(Symplekt_UtilityGeneral)
add_subdirectory(Symplekt_DataReps)
add_subdirectory(Symplekt_IOService)
add_subdirectory(Symplekt_GeometryBase)
add_subdirectory(Symplekt_GeometryReps)
add_subdirectory(Symplekt_Numerics)
add_subdirectory(Symplekt_AnalysisKernel)
add_subdirectory(Symplekt_ProcessingKernel)

add_executable(${PROJECT_NAME} SymplektMain.cpp)

target_link_libraries(${PROJECT_NAME}
	Symplekt_UtilityGeneral
	Symplekt_DataReps
	Symplekt_IOService
    Symplekt_GeometryReps
	Symplekt_GeometryBase
	Symplekt_Numerics
	Symplekt_ProcessingKernel
	Symplekt_AnalysisKernel
)

enable_testing()

include(FetchContent)
if (NOT googletest)
	FetchContent_Declare(
		googletest
		# Specify the commit you depend on and update it regularly.
		URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
	)
	# For Windows: Prevent overriding the parent project's compiler/linker settings
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	FetchContent_MakeAvailable(googletest)
endif()

