project(Symplekt_GeometryReps)

file(GLOB Symplekt_GeometryReps_Src "*.h" "*.cpp")

add_library(Symplekt_GeometryReps ${Symplekt_GeometryReps_Src})

add_subdirectory(UnitTests)