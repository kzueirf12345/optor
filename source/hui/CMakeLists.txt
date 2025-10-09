add_library(hui STATIC
    source/Vector.cpp
    source/Color.cpp

    source/Drawable.cpp
    source/Shape.cpp
    source/RectangleShape.cpp

    source/Event.cpp
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

set_target_properties(hui PROPERTIES FOLDER "source")

target_include_directories(hui
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> # Для сборки проекта
        $<INSTALL_INTERFACE:include>                           # Для будущей установки
)

target_link_libraries(hui
    PRIVATE 
        sfml-graphics
        common
)