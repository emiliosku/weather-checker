cmake_minimum_required(VERSION 3.19)
project(weather-checker LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS
    Core
    Widgets
    Network
    LinguistTools
    Positioning
    Sql)

qt_standard_project_setup()

# Obtain all the GIT information to log
execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND git rev-parse --abbrev-ref HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
    COMMAND git describe --tags --exact-match
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_TAG
    ERROR_QUIET  # Evita errors si no hi ha tag
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if("${GIT_TAG}" STREQUAL "")
    set(GIT_TAG "no-tag")
endif()

# Add GIT information to the application
add_compile_definitions(
    BUILD_COMMIT="${GIT_COMMIT}"
    BUILD_BRANCH="${GIT_BRANCH}"
    BUILD_TAG="${GIT_TAG}"
)

qt_add_executable(weather-checker
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.h mainwindow.cpp
    mainwindow.ui
    weathermanager.h weathermanager.cpp
    apirequestresponse.h apirequestresponse.cpp
    locationsmanager.h locationsmanager.cpp
    locations.h locations.cpp
    locationsdb.h locationsdb.cpp
)

qt_add_translations(
    TARGETS weather-checker
    TS_FILES weather-checker_ca_ES.ts
)

target_link_libraries(weather-checker
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::Network
        Qt6::Positioning
        Qt6::Sql
)

include(GNUInstallDirs)

install(TARGETS weather-checker
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET weather-checker
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
