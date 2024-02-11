find_package(Catch2 3 CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/*.cc)
list(FILTER SOURCES EXCLUDE REGEX main\.cc$)

add_executable(tests ${SOURCES})
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/src ${CMAKE_CURRENT_BINARY_DIR} ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/include)
target_link_directories(tests PRIVATE ${VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/lib)
target_link_libraries(tests PRIVATE ${PJSIP_STATIC_LIBRARIES} Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(tests)
