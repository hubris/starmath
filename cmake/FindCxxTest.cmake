INCLUDE(MacroAddFileDependencies)

set(CXXTEST_EXECUTABLE cxxtestgen.py)
MACRO (CXXTEST_GENERATE_RUNNER infile outfile )
  GET_FILENAME_COMPONENT(infullpath ${infile} ABSOLUTE)
  set(outfileFull ${CMAKE_CURRENT_BINARY_DIR}/${outfile})

  ADD_CUSTOM_COMMAND(OUTPUT ${outfileFull}
    COMMAND ${CXXTEST_EXECUTABLE}
    ARGS  --error-printer -o ${outfileFull} ${infullpath}
    DEPENDS ${infile})

  MACRO_ADD_FILE_DEPENDENCIES(${infullpath} ${outfileFull})
ENDMACRO (CXXTEST_GENERATE_RUNNER)
