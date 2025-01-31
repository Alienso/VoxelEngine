//
// Created by Alienson on 28.5.2023..
//

#ifndef INC_3DTEST_BUFFERDATA_H
#define INC_3DTEST_BUFFERDATA_H

#include <vector>
#include "VertexArray.h"

#include <memory>
#include <typeinfo>

class BufferData{
public:
    BufferData();
    ~BufferData();
    BufferData(float* vertices, std::size_t length);
    BufferData(float* vertices, std::size_t length, std::vector<int>& layout);
    static void genAtLocation(BufferData* dest, const float* vertices, size_t length);

    std::shared_ptr<VertexArray> va;
    std::shared_ptr<VertexBuffer> vb;
    std::shared_ptr<VertexBufferLayout> layout;
};

#endif //INC_3DTEST_BUFFERDATA_H