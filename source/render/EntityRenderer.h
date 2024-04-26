//
// Created by Alienson on 28.5.2023..
//

#ifndef INC_3DTEST_ENTITYRENDERER_H
#define INC_3DTEST_ENTITYRENDERER_H

class Entity;

class EntityRenderer {
public:
    EntityRenderer() = default;
    static void render(const Entity& entity);
};


#endif //INC_3DTEST_ENTITYRENDERER_H
