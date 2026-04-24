cmake_minimum_required(VERSION 3.16)

project(opengl_2 LANGUAGES C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/app/app.cpp
        src/graphics/vao.cpp
        src/graphics/vbo.cpp
        src/graphics/ebo.cpp
        src/meshes/circle/circle.cpp
        src/meshes/circle/circle_mesh.cpp
        src/meshes/cube/cube.cpp
        src/meshes/cube/cube_mesh.cpp
        src/meshes/square/square_mesh.cpp
        src/gameObjects/player/player.cpp
        src/editorUi/debug_ui.cpp
        src/editorUi/panels/objects/object_panel.cpp
        src/editorUi/panels/inspector/inspector_panel.cpp

        lib/stb/stb_image.cpp
        lib/gui/imgui.cpp
        lib/gui/imgui_demo.cpp
        lib/gui/imgui_draw.cpp
        lib/gui/imgui_tables.cpp
        lib/gui/imgui_widgets.cpp
        lib/gui/imgui_impl_glfw.cpp
        lib/gui/imgui_impl_opengl3.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_compile_definitions(${PROJECT_NAME}
        PRIVATE
        SHADER_DIR_PATH="${PROJECT_SOURCE_DIR}/assets/shaders"
)

# GLM: usa a copia versionada no repositorio para evitar diferencas entre sistemas.

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/lib/glm)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/lib/stb)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/lib/gui)


# GLFW: abordagem hibrida.
# - Windows: tenta pacote CMake, depois copia local versionada no repo, depois FetchContent.
# - Linux/Fedora: usa pkg-config com pacote do sistema.
set(GLFW_TARGET "")

if (WIN32)
    find_package(glfw3 CONFIG QUIET)

    if (TARGET glfw)
        set(GLFW_TARGET glfw)
    elseif (TARGET glfw3::glfw)
        set(GLFW_TARGET glfw3::glfw)
    elseif (MSVC AND
            EXISTS "${PROJECT_SOURCE_DIR}/lib/glfw/include/GLFW/glfw3.h" AND
            EXISTS "${PROJECT_SOURCE_DIR}/lib/glfw/lib/glfw3.lib")
        add_library(glfw_from_repo UNKNOWN IMPORTED)
        set_target_properties(glfw_from_repo PROPERTIES
                IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/lib/glfw/lib/glfw3.lib"
                INTERFACE_INCLUDE_DIRECTORIES "${PROJECT_SOURCE_DIR}/lib/glfw/include"
                INTERFACE_LINK_LIBRARIES "gdi32;user32;shell32"
        )
        set(GLFW_TARGET glfw_from_repo)
    else ()
        if (MINGW AND EXISTS "${PROJECT_SOURCE_DIR}/lib/glfw/lib/glfw3.lib")
            message(STATUS
                    "Ignorando lib/glfw/lib/glfw3.lib porque ela foi gerada para MSVC. "
                    "Com MinGW, GLFW sera obtida por FetchContent.")
        endif ()
        include(FetchContent)
        FetchContent_Declare(
                glfw
                GIT_REPOSITORY https://github.com/glfw/glfw.git
                GIT_TAG 3.4
        )
        set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
        set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
        set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(glfw)
        set(GLFW_TARGET glfw)
    endif ()
else ()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLFW REQUIRED IMPORTED_TARGET glfw3)
    set(GLFW_TARGET PkgConfig::GLFW)
endif ()

if (NOT GLFW_TARGET)
    message(FATAL_ERROR "GLFW nao encontrado. Instale glfw3 (Fedora: glfw-devel) ou configure um pacote CMake no Windows.")
endif ()

# GLAD: usa pacote se existir; se nao, compila a copia local do projeto.
set(GLAD_TARGET "")
find_package(glad CONFIG QUIET)
if (TARGET glad::glad)
    set(GLAD_TARGET glad::glad)
elseif (TARGET glad)
    set(GLAD_TARGET glad)
else ()
    target_sources(${PROJECT_NAME} PRIVATE src/glad.c)
    target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/lib/glad/include)
endif ()

find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        OpenGL::GL
        ${GLFW_TARGET}
)

if (GLAD_TARGET)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${GLAD_TARGET})
endif ()

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
else ()
    target_compile_options(${PROJECT_NAME}
            PRIVATE
            $<$<COMPILE_LANGUAGE:CXX>:-Wall -Wextra -Wpedantic>
            $<$<COMPILE_LANGUAGE:C>:-Wall -Wextra>
    )
endif ()
