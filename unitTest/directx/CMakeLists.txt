CXXTEST_GENERATE_RUNNER(MathTestSuite.h MathTestSuiteRunner.cpp)

include_directories($ENV{DXSDK_DIR}/Include)
link_directories($ENV{DXSDK_DIR}/Lib)

add_executable(testDirectX MathTestSuiteRunner.cpp)
target_link_libraries(testDirectX StarMath d3dx10)
