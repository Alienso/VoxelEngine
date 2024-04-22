//
// Created by Alienson on 28.5.2023..
//

#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"

#ifndef INC_3DTEST_BUFFERDATA_H
#define INC_3DTEST_BUFFERDATA_H

class BufferData{
public:
    explicit BufferData();
    BufferData(float* vertices, std::size_t length);

    ~BufferData(){
        delete va;
        delete vb;
        delete layout;
    }

    VertexArray* va;
    VertexBuffer* vb;
    VertexBufferLayout* layout;

private:
};

#endif //INC_3DTEST_BUFFERDATA_H