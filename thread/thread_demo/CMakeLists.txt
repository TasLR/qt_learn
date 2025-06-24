cmake_minimum_required(VERSION 3.19)
project(thread_demo LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(thread_demo
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    mywork.h mywork.cpp
)

target_link_libraries(thread_demo
    PRIVATE
        Qt::Core
        Qt::Widgets
)
target_link_libraries(thread_demo PRIVATE Qt6::Core)

include(GNUInstallDirs)

install(TARGETS thread_demo
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET thread_demo
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
