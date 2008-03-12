set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)

IF(NOT WIN32)
add_subdirectory(ogre)
ADD_TEST(MathTestSuite ${EXECUTABLE_OUTPUT_PATH}/testOgre)
ADD_TEST(MathTestQuaternion ${EXECUTABLE_OUTPUT_PATH}/testQuaternionOgre)
ADD_TEST(MathTestPlane ${EXECUTABLE_OUTPUT_PATH}/testPlaneOgre)
endif(NOT WIN32)

IF(WIN32)
add_subdirectory(directx)
ADD_TEST(MathTestSuite ${EXECUTABLE_OUTPUT_PATH}/testDirectX)
endif(WIN32)


