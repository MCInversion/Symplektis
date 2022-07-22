project(Symplekt_Algorithms)

file(GLOB Symplekt_Algorithms_Src "*.h" "*.cpp")

add_library(Symplekt_Algorithms ${Symplekt_Algorithms_Src})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER ${SYMPLEKT_KERNEL_FOLDER})

# to make sure "Symplekt_" source directories can be included
target_include_directories(Symplekt_Algorithms PUBLIC ${SYMPLEKTIS_SOURCE_DIR})