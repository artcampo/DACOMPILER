include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../include")


set(files
    Node.cpp
    ASTVisitor.cpp
    ASTVisitorPrettyPrinter.cpp
    ASTVisitorCodeGenerator.cpp
)

#Set intermediate library
add_definitions( -std=c++11 -g)
add_library(COMPILER STATIC ${files})

#Set Flex/bison output
set(TMP_DIR "${PROJECT_BINARY_DIR}/generated")
file(MAKE_DIRECTORY ${TMP_DIR})

find_package(BISON REQUIRED)
set(BisonOutput ${TMP_DIR}/parser.cpp ${TMP_DIR}/parser.hpp)
set(BisonSpecFile parser.y)
if(BISON_FOUND)
    add_custom_command(
    OUTPUT ${BisonOutput}
    COMMAND ${BISON_EXECUTABLE}
        -d --output=${TMP_DIR}/parser.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/${BisonSpecFile}
    DEPENDS ${BisonSpecFile}
    COMMENT "Generating ${BisonOutput} - with: ${BISON_EXECUTABLE}
        --defines=${CMAKE_SOURCE_DIR}/parser.h
            --output=${TMP_DIR}/parser.cpp
            ${BisonSpecFile} in DIR: ${CMAKE_CURRENT_SOURCE_DIR}"
    VERBATIM
    )
endif()

find_package(FLEX REQUIRED)
set(FlexOutput ${TMP_DIR}/lexer.cpp)
set(FlexSpecFile tokens.l)
if(FLEX_FOUND)
    add_custom_command(
        OUTPUT ${FlexOutput}
        COMMAND ${FLEX_EXECUTABLE}
              --outfile=${FlexOutput}
        ${CMAKE_CURRENT_SOURCE_DIR}/${FlexSpecFile}
    DEPENDS ${FlexSpecFile} ${BisonOutput}
    COMMENT "Generating ${FlexOutput}"
    VERBATIM
    )
endif()

#Set final compiler
add_executable(dacomp main.cpp ${BisonOutput} ${FlexOutput})
target_link_libraries(dacomp COMPILER)

INSTALL(FILES ${PROJECT_BINARY_DIR}/src/lib/dacomp DESTINATION tests)