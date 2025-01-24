//
// Created by Alienson on 30.4.2024..
//

#ifndef VOXEL_WORLDRENDERER_H
#define VOXEL_WORLDRENDERER_H


#include "render/buffer/FrameBuffer.h"
#include "Shader.h"
#include "Mesh.h"
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

    std::unordered_map<uint16_t, Mesh*>& getTerrainMeshesWriteMap();
    std::unordered_map<uint16_t, Mesh*>& getTerrainMeshesReadMap();
    void swapMaps();

private:
    void renderBlockMesh(Block &block, Mesh *mesh);
    void renderFog();
    void applyBloom();
    void applyToneMapping();
    void applyColorCorrection();
    void applyGammaCorrection();

    FrameBuffer depthBuffer{FRAME_BUFFER_SHADOW};
    FrameBuffer renderBuffer;
    FrameBuffer bloomBuffer;
    FrameBuffer toneMapperBuffer;
    Shader* shadowShader;

    FrameBuffer mipLevels[8];
    FrameBuffer scaledImages[8];

    std::unordered_map<uint16_t, Mesh*> terrainMeshes1;
    std::unordered_map<uint16_t, Mesh*> terrainMeshes2;
    std::unordered_map<uint16_t, Mesh*>* terrainMeshesWriteMap = &terrainMeshes1;
    std::unordered_map<uint16_t, Mesh*>* terrainMeshesReadMap = &terrainMeshes2;
    std::mutex swapMutex;

};


#endif //VOXEL_WORLDRENDERER_H
