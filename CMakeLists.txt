cmake_minimum_required(VERSION 3.21)

project("SkyrimScripting MessageBox" VERSION 0.0.1)

find_package(SkyrimScripting.CMake CONFIG REQUIRED)
find_package(SkyrimScripting.Plugin CONFIG REQUIRED)

set(LIBRARY SkyrimScriptingMessageBox)
set(PLUGIN SkyrimScripting.MessageBox)

# Header-only SKSE library for creating messageboxes
add_library(${LIBRARY} INTERFACE)
target_include_directories(
    ${LIBRARY}
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(${LIBRARY} INTERFACE CommonLibSSE::CommonLibSSE)

# Installation (for vcpkg)
include(GNUInstallDirs)
install(DIRECTORY include DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/..")
install(
    TARGETS ${LIBRARY}
    EXPORT ${LIBRARY}-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} # static and import libs?
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} # .so?
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} # .dll
)
install(
    EXPORT ${LIBRARY}-targets
    FILE ${LIBRARY}-targets.cmake
    NAMESPACE "${LIBRARY}::"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake"
)
configure_file(cmake/Config.cmake.in ${LIBRARY}Config.cmake @ONLY)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY}Config.cmake" DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake")

# SKSE Plugin providing a Papyrus interface for these dynamic MessageBoxes
add_skse_plugin(${PLUGIN} SOURCES plugin.cpp)
target_link_libraries(${PLUGIN} PRIVATE SkyrimScriptingPlugin::SkyrimScripting.Plugin)
target_link_libraries(${PLUGIN} PRIVATE ${LIBRARY})
