project (liboops)

configure_file (${PROJECT_SOURCE_DIR}/hdr/oops-platform/compats.hhh
                ${PROJECT_BINARY_DIR}/hdr/oops-platform/compats.h)

add_library (oops oops-platform/misc.cxx)

set (oops_cxx_phdrs oops-cxx/Object.h oops-cxx/packstrc.h oops-cxx/endpack.h)
set (oops_plat_phdrs oops-platform/misc.h)
set (oops_object_phdrs oops-object/object.h)

prepend(oops_cxx_hdrs ${PROJECT_SOURCE_DIR}/hdr/ ${oops_cxx_pdhrs})
prepend(oops_plat_hdrs ${PROJECT_SOURCE_DIR}/hdr/ ${oops_plat_phdrs})
prepend(oops_object_hdrs ${PROJECT_SOURCE_DIR}/hdr/ ${oops_object_phdrs})

list(APPEND oops_plat_hdrs ${PROJECT_BINARY_DIR}/hdr/oops-platform/compats.h)

prepend(oops_cxx_hdrs_i ${CMAKE_INSTALL_INCLUDEDIR} ${oops_cxx_phdrs})
prepend(oops_plat_hdrs_i ${CMAKE_INSTALL_INCLUDEDIR} ${oops_plat_phdrs})
prepend(oops_object_hdrs_i ${CMAKE_INSTALL_INCLUDEDIR} ${oops_object_phdrs})

list(APPEND oops_plat_hdrs_i
     ${CMAKE_INSTALL_INCLUDEDIR}}/oops-platform/compats.h)

target_include_directories (oops PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/hdr>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/hdr>
    $<INSTALL_INTERFACE:include>)

target_sources (oops INTERFACE
    $<BUILD_INTERFACE:${oops_plat_hdrs} ${oops_object_hdrs}>
    $<INSTALL_INTERFACE:${oops_plat_hdrs_i} ${oops_object_hdrs_i}>)

install (TARGETS oops EXPORT LiboopsConfig
         ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
         LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
         RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install (EXPORT LiboopsConfig DESTINATION share/oopsilon/cmake)

install (FILES ${oops_cxx_hdrs}
         DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/oops-cxx)
install (FILES ${oops_plat_hdrs}
         DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/oops-platform)
install (FILES ${oops_object_hdrs}
         DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/oops-object)

export (TARGETS oops FILE LiboopsConfig.cmake)
