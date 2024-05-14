//
// Created by vladimira on 07/05/2024.
//

#include "CullMesher.h"


void getBlockOffsets(size_t side, int vertexIndex, glm::ivec3* offsets[3]){
    switch (side) {
        case 0:
            switch (vertexIndex) {
                case 0:
                    (*offsets)[0] = {};
                    (*offsets)[1] = {};
                    (*offsets)[2] = {};
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
            }
            break;
    }
}

float CullMesher::getAOValue(int vertexIndex, size_t sideId, float* vertexPos, ChunkProvider& chunkProvider){
    return 1;
}