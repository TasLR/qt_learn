cmake_minimum_required(VERSION 3.19)
project(producer_consumer LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(producer_consumer
    main.cpp
)

target_link_libraries(producer_consumer
    PRIVATE
        Qt::Core
)

include(GNUInstallDirs)

install(TARGETS producer_consumer
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
