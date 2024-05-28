//
// Created by Alienson on 30.4.2024..
//

#ifndef VOXEL_WORLDRENDERER_H
#define VOXEL_WORLDRENDERER_H


#include "render/buffer/FrameBuffer.h"
#include "Shader.h"
#include "Mesh.h"
#include "CullMesher.h"
#include <unordered_map>
#include <mutex>

class Block;

class WorldRenderer {
public:
    WorldRenderer();
    ~WorldRenderer();

    void renderScene();
    void renderTerrain();
    void renderShadows();

    void updateMeshes(std::vector<Chunk *>& chunksToRemove, ChunkProvider& chunkProvider);

    terrainMeshMap& getTerrainMeshesWriteMap();
    terrainMeshMap& getTerrainMeshesReadMap();
    void swapMaps();

private:
    void setupParamsForBlockMesh(Block &block);
    void renderFog();
    void applyBloom();
    void applyToneMapping();
    void applyColorCorrection();
    void applyGammaCorrection();

    CullMesher cullMesher;

    FrameBuffer depthBuffer{FRAME_BUFFER_SHADOW};
    FrameBuffer renderBuffer;
    FrameBuffer bloomBuffer;
    FrameBuffer toneMapperBuffer;
    Shader* shadowShader;

    //bloom downscale buffers
    FrameBuffer mipLevels[8];
    FrameBuffer scaledImages[8];

    terrainMeshMap terrainMeshes1;
    terrainMeshMap terrainMeshes2;
    terrainMeshMap* terrainMeshesWriteMap = &terrainMeshes1;
    terrainMeshMap* terrainMeshesReadMap = &terrainMeshes2;
    std::mutex swapMutex;

};


#endif //VOXEL_WORLDRENDERER_H
