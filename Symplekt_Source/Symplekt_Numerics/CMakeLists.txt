project(Symplekt_Numerics)

file(GLOB Symplekt_Numerics_Src "*.h" "*.cpp")
add_library(Symplekt_Numerics ${Symplekt_Numerics_Src})

# to make sure "Symplekt_" source directories can be included
target_include_directories(Symplekt_Numerics PUBLIC ${SYMPLEKTIS_SOURCE_DIR})