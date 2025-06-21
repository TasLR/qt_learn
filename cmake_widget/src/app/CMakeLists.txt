
set(RESOURCE_FILES
    ${CMAKE_SOURCE_DIR}/resources/example.qrc
)

qt_add_executable(cmake_widget
    mainwindow.ui
    mainwindow.cpp
    main.cpp
    ${RESOURCE_FILES}
)

# qt_add_binary_resources(resources example.qrc DESTINATION example.rcc)
# add_dependencies(cmake_widget resources)

target_link_libraries(cmake_widget PRIVATE
    businesslogic
    Qt6::Widgets
)

set_target_properties(cmake_widget PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
