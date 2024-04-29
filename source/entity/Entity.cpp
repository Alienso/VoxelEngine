//
// Created by Alienson on 28.5.2023..
//

#include "Entity.h"

Entity::Entity(Material &material) : material(material) {}

Entity::Entity(Material &material, float* vertices, size_t length) : material(material), bufferData(BufferData(vertices, length)) {}

Entity::Entity(Material &material, float *vertices, size_t length, std::vector<int> layout) :
    material(material), bufferData(BufferData(vertices, length, layout)) {}


Entity::~Entity() = default;

void Entity::onUpdate(float deltaTime) {}

void Entity::render() {}
