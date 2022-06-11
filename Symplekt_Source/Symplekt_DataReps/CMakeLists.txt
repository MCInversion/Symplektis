project(Symplekt_DataReps)

file(GLOB Symplekt_DataReps_Src "*.h" "*.cpp")
add_library(Symplekt_DataReps ${Symplekt_DataReps_Src})

add_subdirectory(UnitTests)