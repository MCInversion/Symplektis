project(Symplekt_IOService)

file(GLOB Symplekt_IOService_Src "*.h" "*.cpp")

add_library(Symplekt_IOService ${Symplekt_IOService_Src})

# to make sure "Symplekt_" source directories can be included
target_include_directories(Symplekt_IOService PUBLIC ${SYMPLEKTIS_SOURCE_DIR})

add_subdirectory(UnitTests)