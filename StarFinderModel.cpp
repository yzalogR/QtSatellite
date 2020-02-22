//
// Created by Isaac on 2020/2/4.
//

#include "StarFinderModel.h"

StarFinderModel::StarFinderModel(Qt3DCore::QEntity *parent) : Qt3DCore::QEntity(parent), radius(5.8f) {
    loader = new Qt3DRender::QSceneLoader(this);
    loader->setSource(QUrl("qrc:/shaders/starFinder.fbx"));

    transform = new Qt3DCore::QTransform(this);
    transform->setTranslation(QVector3D(0.0f, radius, 0.0f));

    this->addComponent(loader);
    this->addComponent(transform);
}
