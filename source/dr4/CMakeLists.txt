
add_library(dr4 SHARED

    source/math/rect.cpp
    source/math/vec2.cpp

    source/Texture.cpp
    source/Window.cpp 
    source/Backend.cpp
    source/Image.cpp
    source/Font.cpp
    source/text.cpp
    
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