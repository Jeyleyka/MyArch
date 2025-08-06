cmake_minimum_required(VERSION 3.16)

project(Archiver VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Найти Qt
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets LinguistTools)

# 🧱 Сборка главного приложения
qt_add_executable(Archiver
    MANUAL_FINALIZATION

    main.cpp

    UI/MainWindow.cpp UI/MainWindow.h
    UI/Header/Header.cpp UI/Header/Header.h
    UI/ButtonGroup/ButtonGroup.cpp UI/ButtonGroup/ButtonGroup.h
    UI/ArchiveContent/ArchiveContent.cpp UI/ArchiveContent/ArchiveContent.h
    UI/ArchiveInfo/ArchiveInfo.cpp UI/ArchiveInfo/ArchiveInfo.h


    Resources.qrc
    Core/ArchiveWorker.h Core/ArchiveWorker.cpp
    UI/SizeItem/SizeItem.h UI/SizeItem/SizeItem.cpp
)

# 🔗 Линкуем библиотеки
target_link_libraries(Archiver PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

# Бандл и установка
set_target_properties(Archiver PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Archiver
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(Archiver)
