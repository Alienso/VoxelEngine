//
// Created by Alienson on 28.5.2023..
//

#ifndef INC_3DTEST_BUFFERDATA_H
#define INC_3DTEST_BUFFERDATA_H

#include "VertexArray.h"

#include "typeinfo"

class BufferData{
public:
    explicit BufferData();
    BufferData(float* vertices, std::size_t length);

    ~BufferData();

    VertexArray* va;
    VertexBuffer* vb;
    VertexBufferLayout* layout;

private:
};

#endif //INC_3DTEST_BUFFERDATA_H