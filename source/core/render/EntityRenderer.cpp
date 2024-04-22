//
// Created by Alienson on 28.5.2023..
//

#include "EntityRenderer.h"
#include "../entity/Entity.h"
#include "../../Global.h"

void EntityRenderer::render(const Entity& entity) {
    entity.material.texture.bind();
    entity.material.shader.use();
    entity.bufferData.va->bind();

    entity.material.shader.setMat4("projection", Global::currentFrame.projection);
    entity.material.shader.setMat4("view", Global::currentFrame.view);
    entity.material.shader.setMat4("model", Global::currentFrame.model);

    //TODO textureUniformBind?

    glDrawArrays(GL_TRIANGLES, 0, 36);
    //glDrawArrays(GL_TRIANGLES, 0, (int)entity.mesh.triangles.size());
    //glDrawElements(GL_TRIANGLES, (int)entity.mesh.indices.size(), GL_UNSIGNED_INT, nullptr); //TODO
    //glDrawElements(GL_TRIANGLES, (int)entity.mesh.triangles.size(), GL_UNSIGNED_INT, &(entity.mesh.indices[0]));
}