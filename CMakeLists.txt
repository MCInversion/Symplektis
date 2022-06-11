cmake_minimum_required(VERSION 3.14)

# use a diferent name for GUI version
project(Symplektis_ConsoleApp VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set source directories
set(SYMPLEKTIS_SOURCE_DIR Symplekt_Source)

# set external source directories

set(EIGEN_SOURCE_DIR External/Eigen)
include_directories(${EIGEN_SOURCE_DIR})

set(GOOGLETEST_SOURCE_DIR External/GoogleTest)
include_directories(${GOOGLETEST_SOURCE_DIR})

enable_testing()

add_subdirectory(${SYMPLEKTIS_SOURCE_DIR}/Symplekt_UtilityGeneral)
add_subdirectory(${SYMPLEKTIS_SOURCE_DIR}/Symplekt_DataReps)
add_subdirectory(${SYMPLEKTIS_SOURCE_DIR}/Symplekt_IOService)
add_subdirectory(${SYMPLEKTIS_SOURCE_DIR}/Symplekt_GeometryBase)
add_subdirectory(${SYMPLEKTIS_SOURCE_DIR}/Symplekt_GeometryReps)
add_subdirectory(${SYMPLEKTIS_SOURCE_DIR}/Symplekt_Numerics)
add_subdirectory(${SYMPLEKTIS_SOURCE_DIR}/Symplekt_AnalysisKernel)
add_subdirectory(${SYMPLEKTIS_SOURCE_DIR}/Symplekt_ProcessingKernel)

add_executable(${PROJECT_NAME} ${SYMPLEKTIS_SOURCE_DIR}/SymplektMain.cpp)

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