//
// Created by Isaac on 2020/2/4.
//

#include "StarFinderModel.h"

StarFinderModel::StarFinderModel(Qt3DCore::QEntity *parent) : Qt3DCore::QEntity(parent), radius(6.0f) {
    loader = new Qt3DRender::QSceneLoader(this);
    loader->setSource(QUrl("qrc:/shaders/starFinder.obj"));

    transform = new Qt3DCore::QTransform(this);
    transform->setTranslation(QVector3D(0.0f, radius, 0.0f));

    this->addComponent(loader);
    this->addComponent(transform);

    longitude = 0;
    latitude = 90;
    angle = 0;
}

QPointF StarFinderModel::getCurrentPosition() {
    return QPointF(longitude,latitude);
}

void StarFinderModel::setCurrentPosition(float newLon, float newLat)
{
    this->longitude = newLon;
    this->latitude = newLat;
}

void StarFinderModel::updatePosition()
{
    float newLon = 3.14f / 180.0f * (this->longitude - 90); // Φ
    float newLat = 3.14f / 180.0f * (90 - this->latitude); // θ
    auto z = radius * sin(newLat) * cos(newLon);
    auto x = radius * sin(newLat) * sin(newLon);
    auto y = radius * cos(newLat);
    QVector3D currentPosition;
    currentPosition.setX(x);
    currentPosition.setY(y);
    currentPosition.setZ(z);
    transform->setTranslation(currentPosition);
}


void StarFinderModel::updateAngle()
{
    float newAngleX = 90+180*(-this->latitude/180);
    float newAngleY = -90+180*this->longitude/180;
    this->transform->setRotationX(newAngleX);
    this->transform->setRotationY(newAngleY);
}


void StarFinderModel::update()
{
    this->updateAngle();
    this->updatePosition();
}
