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
    BufferData(float* vertices, std::size_t length);
    BufferData(float* vertices, std::size_t length, std::vector<int>& layout);

    BufferData(BufferData& other);
    BufferData& operator=(const BufferData&);

    std::shared_ptr<VertexArray> va;
    std::shared_ptr<VertexBuffer> vb;
    std::shared_ptr<VertexBufferLayout> layout;

private:
};

#endif //INC_3DTEST_BUFFERDATA_H