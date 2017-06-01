# Oopsilon
# Mini-Oops VM
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
 
project(VMkernel)

FlexComp(Bcom/scan.l)
LemonComp(Bcom/gram.y)

file (MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/Oops)
file (MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/Oops/Klass)
file (MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/VM)

GenerateClass(Oops/Context.cls)
GenerateClass(Oops/Method.cls)

GenerateVM(VM/QuickSilver.qvm ${PROJECT_BINARY_DIR}/VM)

set (oopsc_srcs
    ${PROJECT_BINARY_DIR}/gram.tab.cxx ${PROJECT_BINARY_DIR}/scan.yy.cxx
    Bcom/State.cxx Bcom/MsgSyntax.cxx Bcom/Compiler/Code.cxx
    Bcom/AST.cxx Bcom/Symbol.cxx Bcom/Compiler/Context.cxx
    Bytecode/Bytecode.cxx
    Oops/Klass/ClassKlass.cxx Oops/Klass/SymbolKlass.cxx Oops/Klass/Klass.cxx
    Oops/Klass/ByteVecKlass.cxx Oops/Desc.cxx Oops/ClassDesc.cxx
    Oops/Symbol.cxx Oops/Klass/MethodKlass.cxx Oops/Klass/ContextKlass.cxx
    ${PROJECT_BINARY_DIR}/Oops/ContextDesc.cxx ${PROJECT_BINARY_DIR}/Oops/MethodDesc.cxx
    ${PROJECT_BINARY_DIR}/Oops/Klass/ContextKlass.cxx
    ${PROJECT_BINARY_DIR}/Oops/Klass/MethodKlass.cxx
    ${PROJECT_BINARY_DIR}/VM/QuickSilverDisasm.cxx
    ObjectMemory/ObjectMemory.cxx ObjectMemory/ObjectFactory.cxx
    VM/VM.cxx VM/Interpreter/Interpreter.cxx
	VMkernel.cxx)

add_executable (VMkernel "")

target_sources(VMkernel
    PRIVATE ${oopsc_srcs}
    INTERFACE Bcom/scan.l Bcom/gram.y)

# For our Flex and Lemon files:
target_include_directories(VMkernel PRIVATE
    ${PROJECT_SOURCE_DIR} ${PROJECT_BINARY_DIR})

target_link_libraries(VMkernel oops)

install (TARGETS VMkernel EXPORT OopscConfig
         RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})