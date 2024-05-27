cmake_minimum_required(VERSION 3.16)
project(Voxel)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wno-unused-parameter -g -O0")
endif(WIN32)
if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wno-unused-parameter -g -O0 -fsanitize=address")
endif(UNIX)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

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

        source/render/Shader.cpp source/render/Shader.h
        source/render/buffer/VertexBuffer.cpp source/render/buffer/VertexBuffer.h
        source/render/buffer/IndexBuffer.cpp source/render/buffer/IndexBuffer.h
        source/render/buffer/VertexArray.cpp source/render/buffer/VertexArray.h
        source/render/buffer/VertexBufferLayout.cpp source/render/buffer/VertexBufferLayout.h
        source/render/Texture.cpp source/render/Texture.h
        source/Configuration.cpp source/Configuration.h
        source/render/Camera.cpp source/render/Camera.h
        source/render/buffer/UniformBuffer.cpp source/render/buffer/UniformBuffer.h
        source/render/buffer/FrameBuffer.cpp source/render/buffer/FrameBuffer.h
        source/render/buffer/ShaderStorageBuffer.cpp source/render/buffer/ShaderStorageBuffer.h
        source/util/Profiler.cpp source/util/Profiler.h
        source/entity/Entity.cpp source/entity/Entity.h
        source/util/AxisAlignedBB.cpp source/util/AxisAlignedBB.h
        source/render/EntityRenderer.cpp source/render/EntityRenderer.h
        source/render/Material.cpp source/render/Material.h
        source/render/buffer/BufferData.h
        source/Global.cpp source/Global.h
        source/AppName.cpp source/AppName.h
        source/render/AssetManager.h
        source/Asset.h source/Asset.cpp
        source/render/buffer/BufferData.cpp
        source/world/World.cpp source/world/World.h
        source/world/Chunk.cpp source/world/Chunk.h
        source/world/Block.cpp source/world/Block.h
        source/world/Blocks.h source/world/Blocks.cpp
        source/entity/SunEntity.cpp source/entity/SunEntity.h
        source/InputHandler.cpp source/InputHandler.h
        source/render/Mesh.cpp source/render/Mesh.h
        source/world/gen/TerrainGen.cpp source/world/gen/TerrainGen.h
        source/render/CullMesher.cpp source/render/CullMesher.h
        source/world/gen/PerlinNoise.cpp source/world/gen/PerlinNoise.h
        source/util/Util.cpp source/util/Util.h
        source/entity/Skybox.cpp source/entity/Skybox.h
        source/world/ChunkProvider.cpp source/world/ChunkProvider.h
        source/EnumFacing.h source/EnumFacing.cpp
        source/render/WorldRenderer.cpp source/render/WorldRenderer.h
        source/CubeVerticesTypes.h source/CubeVerticesTypes.cpp source/world/biome/Biome.cpp source/world/biome/Biome.h source/world/gen/PlantGenerator.cpp source/world/gen/PlantGenerator.h source/world/gen/TreeGenerator.cpp source/world/gen/TreeGenerator.h source/world/biome/BiomeDecorator.cpp source/world/biome/BiomeDecorator.h source/world/biome/Biomes.cpp source/world/biome/Biomes.h source/world/biome/BiomeProvider.cpp source/world/biome/BiomeProvider.h source/util/RayTrace.cpp source/util/RayTrace.h
        source/world/gen/ao.cpp
        source/util/ts_queue.h
        source/world/gen/WaterGen.cpp source/world/gen/WaterGen.h source/entity/PlayerEntity.cpp source/entity/PlayerEntity.h)

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

