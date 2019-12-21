# Oopsilon
# c-oopsC: C++-hosted Oopsilon Static Compiler
#
#      Copyright Notice
#
# Copyright (c) 2017 D. Mackay. All rights reserved.
#
# This file and its contents are supplied under the terms of the Peer
# Production Licence as found in the Oopsilon project's source repository,
# and David Mackay is the sole copyright holder.
#
#      End Copyright Notice
#
 
project(c-oopsC)

FlexComp(front/scan.l)
LemonComp(front/gram.y)

set (c-oopsC_srcs
    ${PROJECT_BINARY_DIR}/gram.tab.cxx ${PROJECT_BINARY_DIR}/scan.yy.cxx
	front/ast/symbol.cxx front/ast/visitor.cxx front/ast/astPrinter.cxx
    front/ast/ast.cxx front/ast/field.cxx
    front/state.cxx front/msgUnpacking.cxx
	OopsC.cxx)

add_executable (c-oopsC "")

target_sources(c-oopsC
    PRIVATE ${c-oopsC_srcs}
    INTERFACE front/scan.l front/gram.y)

# For our Flex and Lemon files:
target_include_directories(c-oopsC PRIVATE
    ${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR})

target_link_libraries(c-oopsC oopsRt)

INSTALL(TARGETS c-oopsC DESTINATION ${CMAKE_INSTALL_BINDIR})
