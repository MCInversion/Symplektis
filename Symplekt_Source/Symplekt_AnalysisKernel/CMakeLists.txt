project(Symplekt_AnalysisKernel)

file(GLOB Symplekt_AnalysisKernel_Src "*.h" "*.cpp")

add_library(Symplekt_AnalysisKernel ${Symplekt_AnalysisKernel_Src})

# to make sure "Symplekt_" source directories can be included
target_include_directories(Symplekt_AnalysisKernel PUBLIC ${SYMPLEKTIS_SOURCE_DIR})