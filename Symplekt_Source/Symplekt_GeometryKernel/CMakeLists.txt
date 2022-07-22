project(Symplekt_GeometryKernel)

file(GLOB Symplekt_GeometryKernel_Src "*.h" "*.cpp")

add_library(Symplekt_GeometryKernel ${Symplekt_GeometryKernel_Src})

# to make sure "Symplekt_" source directories can be included
target_include_directories(Symplekt_GeometryKernel PUBLIC ${SYMPLEKTIS_SOURCE_DIR})

add_subdirectory(UnitTests)