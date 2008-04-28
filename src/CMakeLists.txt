
set(HEADERS 
        ../include/StarMath/StarVec2.h
        ../include/StarMath/StarVec3.h
        ../include/StarMath/StarVec4.h
        ../include/StarMath/StarMatrix.h
        ../include/StarMath/StarQuaternion.h
        ../include/StarMath/StarPlane.h
        ../include/StarMath/StarUtils.h
        ../include/StarMath/StarBox.h
)

source_group(Headers\\StarMath FILES ${HEADERS})
source_group(Headers FILES ../include/StarMath.h)

add_library(StarMath StarMath.cpp ${HEADERS} ../include/StarMath.h)

install(TARGETS StarMath
        RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)
