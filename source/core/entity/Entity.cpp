//
// Created by Alienson on 28.5.2023..
//

#include "Entity.h"

Entity::Entity(Material &material) : material(material), bufferData(BufferData()) {}

Entity::~Entity() = default;

void Entity::onUpdate(float deltaTime) {}

void Entity::render() {}
