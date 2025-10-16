add_library(optics STATIC
    source/Scene.cpp
    source/Camera.cpp
    source/Light.cpp
    source/Sphere.cpp
    source/OpticObj.cpp
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

set_target_properties(optics PROPERTIES FOLDER "source")

target_include_directories(optics
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> # Для сборки проекта
        $<INSTALL_INTERFACE:include>                           # Для будущей установки
)

target_link_libraries(optics
    PRIVATE 
        sfml-graphics
        common
        hui
        global
)