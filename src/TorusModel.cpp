#include "TorusModel.h"

TorusModel::TorusModel(Qt3DCore::QEntity *parent):
                                Qt3DCore::QEntity(parent),
                                radius(7.0f),
                                angleX(90),
                                angleY(0)
{
    material = new Qt3DExtras::QPhongMaterial(parent);
    torusEntity = new Qt3DCore::QEntity(parent);
    torusMesh = new Qt3DExtras::QTorusMesh;
    torusMesh->setRadius(radius);
    torusMesh->setMinorRadius(0.01);
    torusMesh->setRings(100);
    torusMesh->setSlices(20);
    transform = new Qt3DCore::QTransform(this);
    transform->setScale3D(QVector3D(1, 1, 1));
    transform->setRotationX(angleX);

    torusEntity->addComponent(torusMesh);
    torusEntity->addComponent(transform);
    torusEntity->addComponent(material);
}

void TorusModel::setAngleX(float angleX)
{
    this->angleX = 90-angleX;
}

void TorusModel::setAngleY(float angleY)
{
    this->angleY = angleY;
}

void TorusModel::updateAngle()
{
    transform->setRotationX(angleX);
    transform->setRotationY(angleY);
}
