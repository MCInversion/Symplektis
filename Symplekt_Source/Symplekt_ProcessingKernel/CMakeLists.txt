project(Symplekt_ProcessingKernel)

file(GLOB Symplekt_ProcessingKernel_Src "*.h" "*.cpp")

add_library(Symplekt_ProcessingKernel ${Symplekt_ProcessingKernel_Src})

# to make sure "Symplekt_" source directories can be included
target_include_directories(Symplekt_ProcessingKernel PUBLIC ${SYMPLEKTIS_SOURCE_DIR})