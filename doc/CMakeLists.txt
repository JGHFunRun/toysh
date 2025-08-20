find_package(Doxygen)

# Converts from a CMake option() bool (ie ON/OFF) to a Doxygen bool (YES/NO)
macro(doxy_bool varname)
	if (${varname})
		set(${varname} YES)
	else()
		set(${varname} NO)
	endif()
endmacro(doxy_bool)

option(BUILD_DOCS "Create documentation using Doxygen" ${Doxygen_FOUND})

option(DOXY_WARN "Have doxygen emit warnings whilst generating docs" ON)

option(GEN_HTML     "Generate HTML documentation" ${BUILD_DOCS})
option(GEN_HTMLHELP "Generate HTML \"help\" files" OFF)
option(GEN_PDF      "Generate PDF (LaTeX) documentation" ${BUILD_DOCS})
option(GEN_RTF      "Generate RTF documentation" OFF)
option(GEN_MANINT   "Generate man files for internal documentation" OFF)
option(GEN_XML      "Generate XML structure with doxygen" OFF)
option(GEN_DOCBOOK  "Generate Docbook documentation with doxygen" OFF)
option(GEN_AUTOGEN  "Generate AutoGen Definitions with doxygen" OFF)
option(GEN_SQLITE3  "Generate Sqlite3 database with doxygen" OFF)

doxy_bool(DOXY_WARN)
doxy_bool(GEN_HTML)
doxy_bool(GEN_HTMLHELP)
doxy_bool(GEN_PDF)
doxy_bool(GEN_RTF)
doxy_bool(GEN_MANINT)
doxy_bool(GEN_XML)
doxy_bool(GEN_DOCBOOK)
doxy_bool(GEN_AUTOGEN)
doxy_bool(GEN_SQLITE3)

set(DOXY_LANG "English" CACHE STRING
	"Language to generate internal documentation in")

set(HTML_COLOR "AUTO_DARK" CACHE STRING
	"Doxygen color style to generate internal documentation with")

if(BUILD_DOCS)
	message(STATUS "BUILD_DOCS selected. Use target `doc` in generated build system.")

	if(NOT Doxygen_FOUND)
		message(FATAL_ERROR "Doxygen could not be found.")
	endif()

	set(DOXY_INPUT_DIRS "\"${PROJECT_SOURCE_DIR}/include/\" \\
		\"${PROJECT_SOURCE_DIR}/src/\" \\
		\"${CMAKE_CURRENT_SOURCE_DIR}/pages/\"")

	set(DOXY_OUTPUT_DIR "\"${CMAKE_CURRENT_BINARY_DIR}\"")

	configure_file(Doxyfile.in ${PROJECT_BINARY_DIR}/Doxyfile)

	add_custom_target(doc
		COMMAND "${DOXYGEN_EXECUTABLE}" "${PROJECT_BINARY_DIR}/Doxyfile"
		WORKING_DIRECTORY "${PROJECT_BINARY_DIR}"
		COMMENT "Generating internal API documentation with Doxygen"
		SOURCES Doxyfile.in)
endif(BUILD_DOCS)
