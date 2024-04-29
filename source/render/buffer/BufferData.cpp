//
// Created by Alienson on 20.4.2024..
//

#include "BufferData.h"

#include "VertexBufferLayout.h"

#include "VertexBuffer.h"
#include "VertexArray.h"

using namespace std;

BufferData::BufferData() {
    vb = nullptr;
    layout = nullptr;
    va = nullptr;
}

BufferData::BufferData(BufferData &other) {
    va = other.va;
    vb = other.vb;
    layout = other.layout;
}

BufferData::BufferData(float *vertices, size_t length) {
    vb = make_shared<VertexBuffer>(vertices, length * sizeof(float));
    layout = make_shared<VertexBufferLayout>();
    layout->push<float>(3);
    layout->push<float>(3);
    layout->push<float>(2);
    va = make_shared<VertexArray>();
    va->addBuffer(*vb, *layout);
}

BufferData::BufferData(float *vertices, std::size_t length, std::vector<int>& layoutFormat) {
    vb = make_shared<VertexBuffer>(vertices, length * sizeof(float));
    layout = make_shared<VertexBufferLayout>();

    for (int i : layoutFormat){
        layout->push<float>(i);
    }

    va = make_shared<VertexArray>();
    va->addBuffer(*vb, *layout);
}

BufferData& BufferData::operator=(const BufferData& other) = default;
