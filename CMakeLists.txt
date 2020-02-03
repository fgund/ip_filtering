cmake_minimum_required(VERSION 3.2)

if(NOT DEFINED ENV{TRAVIS_BUILD_NUMBER})
  message("TRAVIS_BUILD_NUMBER not defined. Setting its value to 1.")
  set(ENV{TRAVIS_BUILD_NUMBER} 1)
endif(NOT DEFINED ENV{TRAVIS_BUILD_NUMBER})

project(Otus_CPP_02 VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake) 
conan_basic_setup(TARGETS)

add_executable(ip_filter ip_filter.cpp)
add_library(ip_filter_lib ip4.cpp ip4.h filter.h)
add_executable(gtest_ip gtest_ip.cpp)

set_target_properties(
	ip_filter
	ip_filter_lib
	gtest_ip
PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(ip_filter PRIVATE
    ip_filter_lib
)

target_link_libraries(gtest_ip
    ip_filter_lib
    CONAN_PKG::gtest
)


if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4 /MD
    )
    target_compile_options(ip_filter_lib PRIVATE
        /W4 /MD
    )
    target_compile_options(gtest_ip PRIVATE
        /W4 /MD
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(ip_filter_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(gtest_ip PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

if (MSVC)
  set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/)
endif()
install(TARGETS ip_filter RUNTIME DESTINATION bin)

if (MSVC)
    set(CPACK_GENERATOR NSIS)
else ()
    set(CPACK_GENERATOR DEB)
endif()

set(CPACK_PACKAGE_NAME "IP_Filter")

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/LICENSE)
set(CPACK_RESOURCE_FILE_README ${CMAKE_SOURCE_DIR}/README.md)

include(CPack)

enable_testing()

add_test(gtest_ip "bin/gtest_ip")