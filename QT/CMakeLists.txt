cmake_minimum_required(VERSION 3.21.1)

option(LINK_INSIGHT "Link Qt Insight Tracker library" ON)
option(BUILD_QDS_COMPONENTS "Build design studio components" ON)

project(QTApp LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Core Gui Qml Quick)

if (Qt6_VERSION VERSION_GREATER_EQUAL 6.3)
    qt_standard_project_setup()
endif()

qt_add_executable(QTApp
    src/main.cpp
    src/DBManager.cpp
    src/customer.cpp
    src/account.cpp
    src/transaction.cpp
    src/card.cpp
    src/atm.cpp
    headers/app_environment.h
    headers/import_qml_components_plugins.h
    headers/import_qml_plugins.h
)

qt_add_resources(QTApp "configuration"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf
)

include_directories(
    include
    headers
)

find_package(Qt6 REQUIRED COMPONENTS Sql)

target_link_libraries(QTApp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::Sql
)

if (BUILD_QDS_COMPONENTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/qmlcomponents)
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/qmlmodules)

if (LINK_INSIGHT)
    include(${CMAKE_CURRENT_SOURCE_DIR}/insight)
endif ()

include(GNUInstallDirs)
install(TARGETS QTApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Link SQLite3 library
find_package(SQLite3 REQUIRED)
