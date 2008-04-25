INCLUDE(MacroAddFileDependencies)

FIND_PATH(CXXTEST_INCLUDE_DIR cxxtest
                              /usr/include/
                              /usr/local/include/
)

FIND_PROGRAM(CXXTEST_EXECUTABLE cxxtestgen.py
                                /usr/bin/
                                /usr/local/bin)
SET(CXXTEST_FOUND "NO")
IF(EXISTS ${CXXTEST_INCLUDE_DIR})
	SET(CXXTEST_FOUND "YES")
ENDIF(EXISTS ${CXXTEST_INCLUDE_DIR})

IF (CXXTEST_FOUND)
   IF (NOT CXXTEST_FIND_QUIETLY)
      MESSAGE(STATUS "Found cxxtest: ${CXXTEST_INCLUDE_DIR}")
   ENDIF (NOT CXXTEST_FIND_QUIETLY)
ELSE (CXXTEST_FOUND)
   IF (CXXTEST_FIND_REQUIRED)
      MESSAGE(FATAL_ERROR "Could not find cxxtest")
   ENDIF (CXXTEST_FIND_REQUIRED)
ENDIF (CXXTEST_FOUND)

MACRO (CXXTEST_GENERATE_RUNNER infile outfile )
  GET_FILENAME_COMPONENT(infullpath ${infile} ABSOLUTE)
  set(outfileFull ${CMAKE_CURRENT_BINARY_DIR}/${outfile})

  ADD_CUSTOM_COMMAND(OUTPUT ${outfileFull}
    COMMAND ${CXXTEST_EXECUTABLE}
    ARGS  --error-printer -o ${outfileFull} ${infullpath}
    DEPENDS ${infile})

  MACRO_ADD_FILE_DEPENDENCIES(${infullpath} ${outfileFull})
ENDMACRO (CXXTEST_GENERATE_RUNNER)
