cmake_minimum_required(VERSION 3.16)
project(Voxel)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wno-unused-parameter -g -O0")

include_directories(${PROJECT_SOURCE_DIR}/source)
include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

if (WIN32)
    link_directories(${PROJECT_SOURCE_DIR}/lib/GLFW/lib-mingw-w64)
endif(WIN32)

add_executable(Voxel main.cpp
        include/imgui/imgui.cpp include/imgui/imgui.h
        include/imgui/imgui_draw.cpp
        include/imgui/imgui_tables.cpp include/imgui/imgui_widgets.cpp
        include/imgui/imgui_impl_glfw.h include/imgui/imgui_impl_glfw.cpp
        include/imgui/imgui_impl_opengl3.h include/imgui/imgui_impl_opengl3.cpp

        include/stb_image.cpp include/stb_image.h
        include/glad.c include/glad.h

        source/core/render/Shader.cpp source/core/render/Shader.h
        source/core/render/buffer/VertexBuffer.cpp source/core/render/buffer/VertexBuffer.h
        source/core/render/buffer/IndexBuffer.cpp source/core/render/buffer/IndexBuffer.h
        source/core/render/buffer/VertexArray.cpp source/core/render/buffer/VertexArray.h
        source/core/render/buffer/VertexBufferLayout.cpp source/core/render/buffer/VertexBufferLayout.h
        source/core/render/Texture.cpp source/core/render/Texture.h
        source/Configuration.cpp source/Configuration.h
        source/core/render/Camera.cpp source/core/render/Camera.h
        source/core/render/buffer/UniformBuffer.cpp source/core/render/buffer/UniformBuffer.h
        source/core/render/buffer/FrameBuffer.cpp source/core/render/buffer/FrameBuffer.h
        source/core/render/buffer/ShaderStorageBuffer.cpp source/core/render/buffer/ShaderStorageBuffer.h
        source/util/Profiler.cpp source/util/Profiler.h
        source/core/entity/Entity.cpp source/core/entity/Entity.h
        source/util/AxisAlignedBB.cpp source/util/AxisAlignedBB.h
        source/core/render/EntityRenderer.cpp source/core/render/EntityRenderer.h
        source/core/render/Material.cpp source/core/render/Material.h
        source/core/render/buffer/BufferData.h
        source/Global.cpp source/Global.h
        source/AppName.cpp source/AppName.h
        source/core/render/AssetManager.h
        source/Asset.h source/Asset.cpp
        source/core/render/buffer/BufferData.cpp
        source/core/world/World.cpp source/core/world/World.h
        source/core/world/Chunk.cpp source/core/world/Chunk.h
        source/core/world/Block.cpp source/core/world/Block.h
        source/core/world/Blocks.h source/core/world/Blocks.cpp
        source/core/entity/LightSource.cpp source/core/entity/LightSource.h
        source/InputHandler.cpp source/InputHandler.h
        source/core/render/Mesh.cpp source/core/render/Mesh.h
        source/core/world/gen/WorldGen.cpp source/core/world/gen/WorldGen.h
        source/core/world/gen/CullMesher.cpp source/core/world/gen/CullMesher.h
        source/core/world/gen/PerlinNoise.cpp source/core/world/gen/PerlinNoise.h
        source/util/Util.cpp source/core/entity/Skybox.cpp source/core/entity/Skybox.h)

if (WIN32)
    target_link_libraries(Voxel glfw3 gdi32 opengl32)
endif(WIN32)
if (UNIX)
    target_link_libraries(Voxel glfw3 GL X11)
endif(UNIX)

add_custom_command(TARGET Voxel PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:Voxel>)

add_custom_command(TARGET Voxel PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/resource $<TARGET_FILE_DIR:Voxel>)

