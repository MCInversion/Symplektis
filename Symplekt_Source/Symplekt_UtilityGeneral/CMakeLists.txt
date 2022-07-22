project(Symplekt_UtilityGeneral)

file(GLOB Symplekt_UtilityGeneral_Src "*.h" "*.cpp")
add_library(Symplekt_UtilityGeneral ${Symplekt_UtilityGeneral_Src})

# to make sure "Symplekt_" source directories can be included
target_include_directories(Symplekt_UtilityGeneral PUBLIC ${SYMPLEKTIS_SOURCE_DIR})

add_subdirectory(UnitTests)