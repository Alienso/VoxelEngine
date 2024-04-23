//
// Created by Alienson on 20.4.2024..
//

#include "BufferData.h"

#include "VertexBufferLayout.h"

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "../../../Global.h"

using namespace std;

BufferData::BufferData() {
    vb = new VertexBuffer(&(Global::cubeVertices[0]), sizeof(Global::cubeVertices));
    layout = new VertexBufferLayout();
    layout->push<float>(3);
    layout->push<float>(3);
    layout->push<float>(2);
    va = new VertexArray();
    va->addBuffer(*vb, *layout);
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

BufferData::~BufferData() {
    delete va;
    delete vb;
    delete layout;
}
