find_package(Qt6Core REQUIRED)
find_package(Qt6Gui REQUIRED)
find_package(Qt6Widgets REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

CreateTarget(browser-selector EXECUTABLE "browser-selector" C++ 20)

target_compile_definitions(browser-selector PRIVATE -DQT_DEPRECATED_WARNINGS)
target_compile_definitions(browser-selector PRIVATE -DQT_DISABLE_DEPRECATED_BEFORE=0x060000)
target_compile_definitions(browser-selector PRIVATE -DQT_NO_FOREACH)

target_link_libraries(browser-selector
PUBLIC
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
PRIVATE
    yaml-cpp::yaml-cpp
)
