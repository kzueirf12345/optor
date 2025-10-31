
add_library(dr4 STATIC
    source/math/Vector.cpp
    # source/Color.cpp
    # source/RectDouble.cpp
    
    # source/Drawable.cpp
    # source/Transformable.cpp

    # source/Shape.cpp
    # source/RectangleShape.cpp
    # source/Texture.cpp
    # source/Sprite.cpp
    # source/Textured.cpp

    # source/Font.cpp
    # source/Text.cpp
    
    # source/Event.cpp
    # source/Renderer.cpp
    # source/Window.cpp
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

set_target_properties(dr4 PROPERTIES FOLDER "source")

target_include_directories(dr4
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> # Для сборки проекта
        $<INSTALL_INTERFACE:include>                           # Для будущей установки
)

target_link_libraries(dr4
    PRIVATE 
        sfml-graphics
        common
        libs
)