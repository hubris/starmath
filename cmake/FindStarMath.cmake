FIND_PATH(STARMATH_INCLUDE_DIR StarMath.h
			       ${PROJECT_SOURCE_DIR}/include
                               $ENV{STARMATH_DIR}/include
			       /usr/include/SDL
    			       /usr/local/include/SDL
)

set(STARMATH_INCLUDE_FOUND "NO")
if(EXISTS ${STARMATH_INCLUDE_DIR})
	set(STARMATH_INCLUDE_FOUND "YES")
endif(EXISTS ${STARMATH_INCLUDE_DIR})

FIND_LIBRARY(STARMATH_LIBRARY StarMath
                              ${CMAKE_BINARY_DIR}/lib
                              $ENV{STARMATH_DIR}/lib
			      /usr/lib
    			      /usr/local/lib
)

set(STARMATH_LIB_FOUND "NO")
if(STARMATH_LIB)
	set(STARMATH_LIB_FOUND "YES")
endif(STARMATH_LIB)
