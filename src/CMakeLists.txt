project(certexp_src)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)


set(SOURCE_FILES
    main.cpp
    config.cpp
    net.cpp
    cert.cpp
    utils.cpp
    )

add_executable(certexp ${SOURCE_FILES})

include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(certexp ${CURL_LIBRARIES})

install(TARGETS certexp DESTINATION ${CERTEXP_INSTALL_BIN_DIR})
