project(Symplekt_GeometryBase)

file(GLOB Symplekt_GeometryBase_Src "*.h" "*.cpp")

add_library(Symplekt_GeometryBase ${Symplekt_GeometryBase_Src})

# to make sure "Symplekt_" source directories can be included
target_include_directories(Symplekt_GeometryBase PUBLIC ${SYMPLEKTIS_SOURCE_DIR})

add_subdirectory(UnitTests)