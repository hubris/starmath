add_library(StarMath StarMath.cpp)

install(TARGETS StarMath
        RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)
