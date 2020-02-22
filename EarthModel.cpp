#include "EarthModel.h"

EarthModel::EarthModel(Qt3DCore::QEntity *parent) : Qt3DCore::QEntity(parent), radius(5.5f) {
    mesh = new Qt3DExtras::QSphereMesh(this);
    material = new Qt3DExtras::QTextureMaterial(this);
    transform = new Qt3DCore::QTransform(this);

    auto *loader = new Qt3DRender::QTextureLoader(this);
    loader->setSource(QUrl("qrc:/shaders/earth_4k.jpg"));
    material->setTexture(loader);
    transform->setScale(radius);

    this->addComponent(mesh);
    this->addComponent(material);
    this->addComponent(transform);
}
