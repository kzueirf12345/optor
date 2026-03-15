add_library(widgets STATIC
    source/Widget.cpp
    source/WidgetChildable.cpp
    source/WidgetManager.cpp
    source/SceneWidget.cpp
    source/WidgetButton.cpp
    source/Textable.cpp
    source/WidgetButtonCamera.cpp
    source/WidgetHeader.cpp
    source/ScrollBar.cpp
    source/WidgetList.cpp
    source/WidgetScrolledList.cpp
    source/HideButton.cpp
    source/WidgetText.cpp
    source/TopBar.cpp
    source/WidgetCheckbox.cpp
    source/HideCheckbox.cpp
    source/OpticObjShort.cpp
    source/OpticObjDesc.cpp
    source/WidgetButtonMoveOpticObj.cpp
    source/WidgetPiska.cpp
    source/PiskaToolButton.cpp
    source/DeleteObjButton.cpp
    source/ColorPicker.cpp
    source/TextBox.cpp
    source/ColorRect.cpp
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(
        -g
        -O0
        -fsanitize=address
        -fsanitize=undefined
        -fno-omit-frame-pointer
    )
    add_link_options(
        -fsanitize=address
        -fsanitize=undefined
    )
else()
    add_compile_options(-O2)
endif()

set_target_properties(widgets PROPERTIES FOLDER "source")

target_include_directories(widgets
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> # Для сборки проекта
        $<INSTALL_INTERFACE:include>                           # Для будущей установки
)

target_link_libraries(widgets
    PRIVATE 
        # SDL3_ttf
        # SDL3
        common
        cum
        dr4
        pp
        global
        optics
        dr4Plugin
)

# add_subdirectory(external/SDL_ttf)
# target_link_libraries(твоя_цель PRIVATE SDL3_ttf)
