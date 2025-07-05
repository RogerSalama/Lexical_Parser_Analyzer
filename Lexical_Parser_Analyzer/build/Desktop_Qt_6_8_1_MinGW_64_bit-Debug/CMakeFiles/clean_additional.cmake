# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Lexical_Analyzer_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Lexical_Analyzer_autogen.dir\\ParseCache.txt"
  "Lexical_Analyzer_autogen"
  )
endif()
