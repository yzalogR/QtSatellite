//
// Created by Isaac on 2020/2/21.
//

#include "Light.h"

Light::Light(Qt3DRender::QCamera *camera, Qt3DCore::QEntity *parent) : Qt3DCore::QEntity(parent) {
    light = new Qt3DRender::QPointLight(this);
    light->setColor("white");
    light->setIntensity(1.0f);
    light->setEnabled(true);

    transform = new Qt3DCore::QTransform(this);
    transform->setTranslation(camera->position());

    this->addComponent(light);
    this->addComponent(transform);
}
