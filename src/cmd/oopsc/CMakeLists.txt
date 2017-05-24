# Mini-Oops
# Oops VM
# Copyright (c) 2017 D. Mackay. All rights reserved. */
 
project(oopsc)

FlexComp(ANSYN/scan.l)
LemonComp(ANSYN/gram.y)

set (oopsc_srcs
    ${PROJECT_BINARY_DIR}/gram.tab.cxx ${PROJECT_BINARY_DIR}/scan.yy.cxx
    ANSYN/State.cxx ANSYN/MsgSyntax.cxx
    AST/AST.cxx AST/Symbol.cxx
    Oops/Klass/ClassKlass.cxx Oops/Klass/SymbolKlass.cxx Oops/Klass/Klass.cxx
    Oops/Klass/ByteVecKlass.cxx Oops/Desc.cxx
    Oops/Symbol.cxx
    ObjectMemory/ObjectMemory.cxx
    VM/VM.cxx
	oopsc.cxx)

add_executable (oopsc "")

target_sources(oopsc
    PRIVATE ${oopsc_srcs}
    INTERFACE ANSYN/scan.l ANSYN/gram.y)

# For our Flex and Lemon files:
target_include_directories(oopsc PRIVATE
    ${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR})

target_link_libraries(oopsc oops)

install (TARGETS oopsc EXPORT OopscConfig
         RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})