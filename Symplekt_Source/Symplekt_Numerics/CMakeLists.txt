project(Symplekt_Numerics)

file(GLOB Symplekt_Numerics_Src "*.h" "*.cpp")
add_library(Symplekt_Numerics ${Symplekt_Numerics_Src})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER ${SYMPLEKT_BASIS_FOLDER})

# to make sure "Symplekt_" source directories can be included
target_include_directories(Symplekt_Numerics PUBLIC ${SYMPLEKTIS_SOURCE_DIR})