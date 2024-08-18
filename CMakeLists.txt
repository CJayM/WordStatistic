cmake_minimum_required(VERSION 3.16)

project(word_statistics VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS QuickControls2)


qt_add_executable(appword_statistics
    main.cpp
)

qt_add_qml_module(appword_statistics
    URI word_statistics
    VERSION 1.0
    QML_FILES main.qml
    QML_FILES Histogram.qml
    SOURCES words_model.h words_model.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appword_statistics PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appword_statistics
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appword_statistics
    PRIVATE Qt6::Quick
)

target_link_libraries(appword_statistics PRIVATE Qt6::QuickControls2)

include(GNUInstallDirs)
install(TARGETS appword_statistics
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
