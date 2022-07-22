cmake_policy(SET CMP0074 NEW)
cmake_policy(SET CMP0077 NEW)
cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0090 NEW)
cmake_minimum_required(VERSION 3.14)

# use a diferent name for GUI version
project(Symplektis_ConsoleApp VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CONFIGURATION_TYPES Debug Release)

# set source directories
set(SYMPLEKTIS_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SYMPLEKTIS_SOURCE_DIR ${SYMPLEKTIS_ROOT_DIR}/Symplekt_Source)

# Autogen folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY AUTOGEN_TARGETS_FOLDER Autogen)

# -------------------------------------------------------------------------
# ---------------------------- External Libs ------------------------------
# -------------------------------------------------------------------------

include(FetchContent)
set(FETCHCONTENT_QUIET off)
set(EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/External)

# -------------------------------------------------------------------------
#  ........................ Set Up Google Test ............................
# -------------------------------------------------------------------------

enable_testing()

set(GOOGLETEST_SOURCE_DIR ${EXTERNAL_DIR}/GoogleTest)

message("Searching for Google Test repo in ${GOOGLETEST_SOURCE_DIR}")

if(EXISTS ${GOOGLETEST_SOURCE_DIR}/googletest-src)

	message("\${GOOGLETEST_SOURCE_DIR}/googletest-src exists in ${GOOGLETEST_SOURCE_DIR}")
    set(repo_googletest ${GOOGLETEST_SOURCE_DIR}/googletest-src)	

	# set base directory for FetchContent
	set(FETCHCONTENT_BASE_DIR ${repo_googletest})
	set(FETCHCONTENT_SOURCE_DIR ${repo_googletest})
	
else()

	message("\${GOOGLETEST_SOURCE_DIR}/googletest-src does not exist, cloning from https://github.com/google/googletest.git")
    set(repo_googletest https://github.com/google/googletest.git)
	
	# set base directory for FetchContent
	set(FETCHCONTENT_BASE_DIR ${GOOGLETEST_SOURCE_DIR})
	
endif()

FetchContent_Declare(googletest
	GIT_REPOSITORY                     ${repo_googletest}
	GIT_TAG                            release-1.11.0
	GIT_PROGRESS                       TRUE
	FETCHCONTENT_TRY_FIND_PACKAGE_MODE ON 
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include_directories(${GOOGLETEST_SOURCE_DIR}/googletest-src)

# -----------------------------------------------------------------------
# ......................... Set Up Eigen ................................
# -----------------------------------------------------------------------

set(EIGEN_SOURCE_DIR ${EXTERNAL_DIR}/Eigen)
message("Searching for Eigen repo in ${EIGEN_SOURCE_DIR}")

if (EXISTS ${EIGEN_SOURCE_DIR}/eigen-src)

	message("\${EIGEN_SOURCE_DIR}/eigen-src exists in ${EIGEN_SOURCE_DIR}")
	set(repo_eigen ${EIGEN_SOURCE_DIR}/eigen-src)
	
	find_package(Eigen3 3.4 REQUIRED NO_MODULE)
	
else()

	message("\${EIGEN_SOURCE_DIR}/eigen-src does not exist, cloning from https://gitlab.com/libeigen/eigen.git")
	set(repo_eigen https://gitlab.com/libeigen/eigen.git)
	
	# set base directory for FetchContent
	set(FETCHCONTENT_BASE_DIR ${EIGEN_SOURCE_DIR})
	
	FetchContent_Declare(Eigen
		GIT_REPOSITORY ${repo_eigen}
		GIT_TAG        3.4.0
		GIT_PROGRESS   TRUE
		GIT_SHALLOW    TRUE
	)
	set(EIGEN_BUILD_DOC FALSE)
	set(BUILD_TESTING FALSE)
	set(EIGEN_BUILD_PKGCONFIG FALSE)
	FetchContent_MakeAvailable(Eigen)
	
endif()

include_directories(${EIGEN_SOURCE_DIR}/eigen-src)

# -----------------------------------------------------------------------
# .............. Set Up Symplektis Components ...........................
# -----------------------------------------------------------------------

# add component directories
add_subdirectory(${SYMPLEKTIS_SOURCE_DIR}/Symplekt_UtilityGeneral)
add_subdirectory(${SYMPLEKTIS_SOURCE_DIR}/Symplekt_DataReps)
add_subdirectory(${SYMPLEKTIS_SOURCE_DIR}/Symplekt_IOService)
add_subdirectory(${SYMPLEKTIS_SOURCE_DIR}/Symplekt_GeometryBase)
add_subdirectory(${SYMPLEKTIS_SOURCE_DIR}/Symplekt_GeometryReps)
add_subdirectory(${SYMPLEKTIS_SOURCE_DIR}/Symplekt_Numerics)
add_subdirectory(${SYMPLEKTIS_SOURCE_DIR}/Symplekt_AnalysisKernel)
add_subdirectory(${SYMPLEKTIS_SOURCE_DIR}/Symplekt_ProcessingKernel)

# executable
add_executable(${PROJECT_NAME} ${SYMPLEKTIS_SOURCE_DIR}/SymplektMain.cpp)

# to make sure "Symplekt_" source directories can be included
target_include_directories(${PROJECT_NAME} PUBLIC ${SYMPLEKTIS_SOURCE_DIR})

# link components to main project
target_link_libraries(${PROJECT_NAME}
	Symplekt_UtilityGeneral
	Symplekt_DataReps
	Symplekt_IOService
    Symplekt_GeometryReps
	Symplekt_GeometryBase
	Symplekt_Numerics
	Symplekt_ProcessingKernel
	Symplekt_AnalysisKernel
	Eigen3::Eigen
)

# -----------------------------------------------------------------------