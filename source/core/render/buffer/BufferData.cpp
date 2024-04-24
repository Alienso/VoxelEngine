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

BufferData::BufferData(float *vertices, size_t length) {
    vb = new VertexBuffer(vertices, length * sizeof(float));
    layout = new VertexBufferLayout();
    layout->push<float>(3);
    layout->push<float>(3);
    layout->push<float>(2);
    va = new VertexArray();
    va->addBuffer(*vb, *layout);
}

BufferData::BufferData(float *vertices, std::size_t length, std::vector<int>& layoutFormat) {
    vb = new VertexBuffer(vertices, length * sizeof(float));
    layout = new VertexBufferLayout();

    for (int i : layoutFormat){
        layout->push<float>(i);
    }

    va = new VertexArray();
    va->addBuffer(*vb, *layout);
}

BufferData::~BufferData() {
    if (!va) delete va;
    if (!vb) delete vb;
    if (!layout) delete layout;
}
