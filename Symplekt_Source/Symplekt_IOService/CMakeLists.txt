project(Symplekt_IOService)

file(GLOB Symplekt_IOService_Src "*.h" "*.cpp")
add_library(Symplekt_IOService ${Symplekt_IOService_Src})

add_subdirectory(UnitTests)