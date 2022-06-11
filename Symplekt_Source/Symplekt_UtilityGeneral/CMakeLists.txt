project(Symplekt_UtilityGeneral)

file(GLOB Symplekt_UtilityGeneral_Src "*.h" "*.cpp")
add_library(Symplekt_UtilityGeneral ${Symplekt_UtilityGeneral_Src})

add_subdirectory(UnitTests)