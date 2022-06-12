project(Symplekt_GeometryReps)

file(GLOB Symplekt_GeometryReps_Src "*.h" "*.cpp")

add_library(Symplekt_GeometryReps ${Symplekt_GeometryReps_Src})

# to make sure "Symplekt_" source directories can be included
target_include_directories(Symplekt_GeometryReps PUBLIC ${SYMPLEKTIS_SOURCE_DIR})

add_subdirectory(UnitTests)