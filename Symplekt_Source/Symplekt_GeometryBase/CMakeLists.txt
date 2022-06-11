project(Symplekt_GeometryBase)

file(GLOB Symplekt_GeometryBase_Src "*.h" "*.cpp")

add_library(Symplekt_GeometryBase ${Symplekt_GeometryBase_Src})

add_subdirectory(UnitTests)