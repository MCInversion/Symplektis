project(Symplekt_DataReps)

file(GLOB Symplekt_DataReps_Src "*.h" "*.cpp")
add_library(Symplekt_DataReps ${Symplekt_DataReps_Src})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER ${SYMPLEKT_BASIS_FOLDER})

# to make sure "Symplekt_" source directories can be included
target_include_directories(Symplekt_DataReps PUBLIC ${SYMPLEKTIS_SOURCE_DIR})

add_subdirectory(UnitTests)