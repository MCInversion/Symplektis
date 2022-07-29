project(Symplekt_Algorithms)

file(GLOB Symplekt_Algorithms_Src CONFIGURE_DEPENDS "*.h" "*.cpp")

add_library(Symplekt_Algorithms ${Symplekt_Algorithms_Src})

# to make sure "Symplekt_" source directories can be included
target_include_directories(Symplekt_Algorithms PUBLIC ${SYMPLEKTIS_SOURCE_DIR})

add_subdirectory(UnitTests)