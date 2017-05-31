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
 
project(Classgen)

FlexComp(scan.l)
LemonComp(gram.y)

set (Cg_srcs
    ${PROJECT_BINARY_DIR}/gram.tab.cxx ${PROJECT_BINARY_DIR}/scan.yy.cxx
    AST.cxx Classgen.cxx)

add_executable (Classgen "")

target_sources(Classgen
    PRIVATE ${Cg_srcs}
    INTERFACE scan.l gram.y)

# For our Flex and Lemon files:
target_include_directories(Classgen PRIVATE
    ${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR})

target_link_libraries(Classgen oops)

# Define a command for using it.

function (GenerateClass path)
GET_FILENAME_COMPONENT (file ${path} NAME_WE)
add_custom_command(
OUTPUT ${PROJECT_BINARY_DIR}/${file}_desc.cxx
COMMAND $<TARGET_FILE:Classgen>
ARGS ${CMAKE_CURRENT_SOURCE_DIR}/${path} fake.out
DEPENDS $<TARGET_FILE:Classgen>
MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${path}
WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)
endfunction (GenerateClass)