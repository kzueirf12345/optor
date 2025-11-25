
add_library(dr4Plugin SHARED

    source/Backend.cpp
    source/Circle.cpp
    source/Font.cpp
    source/Image.cpp
    source/Line.cpp
    source/Rectangle.cpp
    source/Text.cpp
    source/Texture.cpp
    source/Window.cpp 
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

set_target_properties(dr4Plugin PROPERTIES FOLDER "source")

target_include_directories(dr4Plugin
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> # Для сборки проекта
        $<INSTALL_INTERFACE:include>                           # Для будущей установки
)

target_link_libraries(dr4Plugin
    PRIVATE 
        sfml-graphics
        common
        cum
        dr4
        pp
)