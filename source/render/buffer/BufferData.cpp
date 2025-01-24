//
// Created by Alienson on 20.4.2024..
//

#include "BufferData.h"

#include "VertexBufferLayout.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "util/Util.h"

using namespace std;

BufferData::BufferData() {
    vb = nullptr;
    layout = nullptr;
    va = nullptr;
}

BufferData::~BufferData() {

}


BufferData::BufferData(float *vertices, size_t length) {
    vb = make_shared<VertexBuffer>(vertices, length * sizeof(float));
    layout = make_shared<VertexBufferLayout>();
    layout->push<float>(3);
    layout->push<float>(3);
    layout->push<float>(2);
    layout->push<float>(1);
    va = make_shared<VertexArray>();
    va->addBuffer(*vb, *layout);
}

void BufferData::genAtLocation(BufferData* dest, const float* vertices, size_t length){
    //Timer timer("Create Buffer Data");
    dest->vb = make_shared<VertexBuffer>(vertices, length * sizeof(float));
    dest->layout = make_shared<VertexBufferLayout>();
    dest->layout->push<float>(3);
    dest->layout->push<float>(3);
    dest->layout->push<float>(2);
    dest->layout->push<float>(1);
    dest->va = make_shared<VertexArray>();
    dest->va->addBuffer(*(dest->vb), *(dest->layout));
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
