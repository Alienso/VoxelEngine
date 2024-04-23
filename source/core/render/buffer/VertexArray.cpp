//
// Created by Alienso on 19.9.2022..
//

#include "VertexArray.h"
#include "VertexBufferLayout.h"

using namespace std;

VertexArray::VertexArray() {
    glGenVertexArrays(1,&renderedID);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1,&renderedID);
}

void VertexArray::addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) {
    this->bind();
    vb.bind();

    const std::vector<VertexBufferElement>& elements = layout.getElements();
    size_t offset = 0;

    for (size_t i=0; i<elements.size(); i++){
        const auto& element = elements[i];
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
        glEnableVertexAttribArray(i);
        offset+=element.count * VertexBufferElement::getSizeOfType(element.type);
    }

}

void VertexArray::bind() const {
    glBindVertexArray(renderedID);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}
