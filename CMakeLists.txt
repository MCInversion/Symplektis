cmake_policy(SET CMP0074 NEW)
cmake_policy(SET CMP0077 NEW)
cmake_policy(SET CMP0048 NEW)
cmake_policy(SET CMP0090 NEW)
cmake_minimum_required(VERSION 3.14)

# use a diferent name for GUI version
project(Symplektis_ShrinkWrapper VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CONFIGURATION_TYPES Debug Release)

# set source directories
set(SYMPLEKTIS_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SYMPLEKTIS_SOURCE_DIR ${SYMPLEKTIS_ROOT_DIR}/Symplekt_Source)

# Set Symplektis_ShrinkWrapper the startup project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

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
set(repo_googletest https://github.com/google/googletest.git)

# set base directory for FetchContent
set(FETCHCONTENT_BASE_DIR ${GOOGLETEST_SOURCE_DIR})

FetchContent_Declare(googletest
	GIT_REPOSITORY                     ${repo_googletest}
	GIT_TAG                            release-1.11.0
	GIT_PROGRESS                       TRUE
	FETCHCONTENT_TRY_FIND_PACKAGE_MODE ON 
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(${GOOGLETEST_SOURCE_DIR}/googletest-src/googletest/include)

# -----------------------------------------------------------------------
# ......................... Set Up Eigen ................................
# -----------------------------------------------------------------------

set(EIGEN_SOURCE_DIR ${EXTERNAL_DIR}/Eigen)
set(repo_eigen https://gitlab.com/libeigen/eigen.git)

# set base directory for FetchContent
set(FETCHCONTENT_BASE_DIR ${EIGEN_SOURCE_DIR})

FetchContent_Declare(Eigen
	GIT_REPOSITORY                     ${repo_eigen}
	GIT_TAG                            3.4.0
	GIT_PROGRESS                       TRUE
	FETCHCONTENT_TRY_FIND_PACKAGE_MODE ON 
)
set(EIGEN_BUILD_DOC FALSE)
set(BUILD_TESTING FALSE)
set(EIGEN_BUILD_PKGCONFIG FALSE)
FetchContent_MakeAvailable(Eigen)
find_package(Eigen3 3.4 REQUIRED NO_MODULE)

include_directories(${EIGEN_SOURCE_DIR}/eigen-src)

# -----------------------------------------------------------------------
# .............. Set Up Symplektis Components ...........................
# -----------------------------------------------------------------------

# block folder definitions

set(SYMPLEKT_APPS_FOLDER "Symplekt_Apps")
set(SYMPLEKT_KERNEL_FOLDER "Kernel")
set(SYMPLEKT_BASIS_FOLDER "Basis")
set(SYMPLEKT_EXTERNAL_FOLDER "External")

# add component directories

# -- Basis --
add_subdirectory(${SYMPLEKTIS_SOURCE_DIR}/Symplekt_UtilityGeneral)
add_subdirectory(${SYMPLEKTIS_SOURCE_DIR}/Symplekt_DataReps)
add_subdirectory(${SYMPLEKTIS_SOURCE_DIR}/Symplekt_Numerics)

# -- Kernel --
add_subdirectory(${SYMPLEKTIS_SOURCE_DIR}/Symplekt_IOService)
add_subdirectory(${SYMPLEKTIS_SOURCE_DIR}/Symplekt_GeometryKernel)
add_subdirectory(${SYMPLEKTIS_SOURCE_DIR}/Symplekt_Algorithms)

# executable
add_executable(${PROJECT_NAME} ${SYMPLEKTIS_SOURCE_DIR}/ShrinkWrapper.cpp)

# Autogen folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY AUTOGEN_TARGETS_FOLDER Autogen)

# VS solution filters for targets
set_target_properties(

	${PROJECT_NAME}
	# ${PROJECT2_NAME}
	# ${PROJECT3_NAME}
	
	PROPERTIES FOLDER ${SYMPLEKT_APPS_FOLDER}
)
set_target_properties(
	
	# googletest
	gmock
	gmock_main
	gtest
	gtest_main
	uninstall
	
	PROPERTIES FOLDER ${SYMPLEKT_EXTERNAL_FOLDER}
)

set_target_properties(

	Symplekt_IOService
	Symplekt_IOService_Tests
	Symplekt_DataReps
	Symplekt_DataReps_Tests
	Symplekt_Numerics
	# Symplekt_Numerics_Tests
	
	PROPERTIES FOLDER ${SYMPLEKT_BASIS_FOLDER}
)

set_target_properties(

	Symplekt_UtilityGeneral
	Symplekt_UtilityGeneral_Tests
	Symplekt_GeometryKernel
	Symplekt_GeometryKernel_Tests
	Symplekt_Algorithms
	# Symplekt_Algorithms_Tests
	
	PROPERTIES FOLDER ${SYMPLEKT_KERNEL_FOLDER}
)


# to make sure "Symplekt_" source directories can be included
target_include_directories(${PROJECT_NAME} PUBLIC ${SYMPLEKTIS_SOURCE_DIR})

# link components to main project
target_link_libraries(${PROJECT_NAME}

	Symplekt_UtilityGeneral
	Symplekt_DataReps
	Symplekt_Numerics
	
	Symplekt_IOService
	Symplekt_GeometryKernel
	Symplekt_Algorithms
	
	Eigen3::Eigen
)

# -----------------------------------------------------------------------