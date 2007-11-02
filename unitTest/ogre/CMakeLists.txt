CXXTEST_GENERATE_RUNNER(MathTestSuite.h MathTestSuiteRunner.cpp)

add_executable(testOgre MathTestSuiteRunner.cpp)
target_link_libraries(testOgre StarMath OgreMain)
