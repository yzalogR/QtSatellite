//
// Created by Isaac on 2020/1/22.
//

#include "SatelliteModel.h"

SatelliteModel::SatelliteModel(Qt3DCore::QEntity *parent) : Qt3DCore::QEntity(parent), radius(6.0f) {
    loader = new Qt3DRender::QSceneLoader(this);
    loader->setSource(QUrl("qrc:/shaders/satellite.fbx"));

    transform = new Qt3DCore::QTransform(this);
    transform->setTranslation(QVector3D(0.0f, radius, 0.0f));

    this->addComponent(loader);
    this->addComponent(transform);
}
