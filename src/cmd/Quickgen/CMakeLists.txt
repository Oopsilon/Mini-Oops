# Oopsilon
# Class generator
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
 
project(Quickgen)

FlexComp(scan.l)
LemonComp(gram.y)

set (Cg_srcs
    ${PROJECT_BINARY_DIR}/gram.tab.cxx ${PROJECT_BINARY_DIR}/scan.yy.cxx
    AST.cxx Quickgen.cxx)

add_executable (Quickgen "")

target_sources(Quickgen
    PRIVATE ${Cg_srcs}
    INTERFACE scan.l gram.y)

# For our Flex and Lemon files:
target_include_directories(Quickgen PRIVATE
    ${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR})

target_link_libraries(Quickgen oops)

# Define a command for using it.

function (GenerateVM path)
GET_FILENAME_COMPONENT (file ${path} NAME_WE)
add_custom_command(
OUTPUT ${PROJECT_BINARY_DIR}/Oops/${file}Desc.cxx
    ${PROJECT_BINARY_DIR}/Oops/${file}Desc.h
    ${PROJECT_BINARY_DIR}/Oops/Klass/${file}Klass.cxx
    ${PROJECT_BINARY_DIR}/Oops/Klass/${file}Klass.h
COMMAND $<TARGET_FILE:Quickgen>
ARGS ${CMAKE_CURRENT_SOURCE_DIR}/${path} ${PROJECT_BINARY_DIR}
DEPENDS $<TARGET_FILE:Quickgen>
MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${path}
WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)
endfunction (GenerateVM)