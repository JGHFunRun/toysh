find_package(LATEX)

option(BUILD_PDFMAN "Build PDF of manual" ${LATEX_PDFLATEX_FOUND})

set(MAN_LANG "en" CACHE STRING
	"Language to generate manual in")

if(BUILD_PDFMAN)
	add_custom_target(pdfman
		COMMAND "${PDFLATEX_COMPILER}" "${CMAKE_CURRENT_SOURCE_DIR}/${MAN_LANG}/toysh.tex"
		WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
		BYPRODUCTS "${CMAKE_CURRENT_BINARY_DIR}/toysh.pdf")
endif()
