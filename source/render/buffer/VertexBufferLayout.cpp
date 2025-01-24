//
// Created by Alienso on 19.9.2022..
//

#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout() : stride(0) {}

const std::vector<VertexBufferElement> &VertexBufferLayout::getElements() const {
    return elements;
}

unsigned int VertexBufferLayout::getStride() const {
    return stride;
}

unsigned int VertexBufferElement::getSizeOfType(unsigned int type){
    switch (type) {
        case GL_FLOAT:          return sizeof(float);
        case GL_UNSIGNED_INT:   return sizeof(unsigned int);
        case GL_UNSIGNED_BYTE:  return 1;
        default: return 0;
    }
}
