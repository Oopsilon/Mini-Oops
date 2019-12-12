project (liboopsRt)

configure_file (${CMAKE_SOURCE_DIR}/hdr/oops-platform/compats.hhh
                ${CMAKE_BINARY_DIR}/hdr/oops-platform/compats.h)

add_library (oopsRt oops-platform/misc.cxx)

set (oopsRt_cxx_phdrs oops-cxx/Object.h oops-cxx/packstrc.h oops-cxx/endpack.h)
set (oopsRt_plat_phdrs oops-platform/misc.h)
set (oopsRt_object_phdrs oops-object/object.h)

prepend(oopsRt_cxx_hdrs ${CMAKE_SOURCE_DIR}/hdr/ ${oopsRt_cxx_pdhrs})
prepend(oopsRt_plat_hdrs ${CMAKE_SOURCE_DIR}/hdr/ ${oopsRt_plat_phdrs})
prepend(oopsRt_object_hdrs ${CMAKE_SOURCE_DIR}/hdr/ ${oopsRt_object_phdrs})

list(APPEND oopsRt_plat_hdrs ${CMAKE_BINARY_DIR}/hdr/oops-platform/compats.h)

prepend(oopsRt_cxx_hdrs_i ${CMAKE_INSTALL_INCLUDEDIR} ${oopsRt_cxx_phdrs})
prepend(oopsRt_plat_hdrs_i ${CMAKE_INSTALL_INCLUDEDIR} ${oopsRt_plat_phdrs})
prepend(oopsRt_object_hdrs_i ${CMAKE_INSTALL_INCLUDEDIR} ${oopsRt_object_phdrs})

list(APPEND oopsRt_plat_hdrs_i
     ${CMAKE_INSTALL_INCLUDEDIR}}/oops-platform/compats.h)

target_include_directories (oopsRt PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/hdr>
    $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/hdr>
    $<INSTALL_INTERFACE:include>)

target_sources (oopsRt INTERFACE
    $<BUILD_INTERFACE:${oopsRt_plat_hdrs} ${oopsRt_object_hdrs}>
    $<INSTALL_INTERFACE:${oopsRt_plat_hdrs_i} ${oopsRt_object_hdrs_i}>)

install (TARGETS oopsRt EXPORT LiboopsRtConfig
         ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
         LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
         RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install (EXPORT LiboopsRtConfig DESTINATION share/oopsilon/cmake)

install (FILES ${oopsRt_cxx_hdrs}
         DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/oops-cxx)
install (FILES ${oopsRt_plat_hdrs}
         DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/oops-platform)
install (FILES ${oopsRt_object_hdrs}
         DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/oops-object)

export (TARGETS oopsRt FILE LiboopsConfig.cmake)
