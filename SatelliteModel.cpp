//
// Created by Isaac on 2020/1/22.
//

#include "SatelliteModel.h"

SatelliteModel::SatelliteModel(Qt3DCore::QEntity *parent) :
        Qt3DCore::QEntity(parent),
        radius(7.0f),
        longitude(0),
        latitude(90),
        angle(0) {
    loader = new Qt3DRender::QSceneLoader(this);
    loader->setSource(QUrl("qrc:/shaders/satellite.obj"));

    transform = new Qt3DCore::QTransform(this);
    transform->setTranslation(QVector3D(0.0f, radius, 0.0f));

    this->addComponent(loader);
    this->addComponent(transform);
}

QPointF SatelliteModel::getCurrentPosition() {
    return QPointF(longitude, latitude);
}

void SatelliteModel::setCurrentPosition(float newLon, float newLat) {
    longitude = newLon;
    latitude = newLat;
    emit emitLonLat(newLon,newLat);
}

void SatelliteModel::updatePosition() {
    float newLon, newLat;
    newLon = M_PI / 180.0f * (this->longitude - 90); // Φ
    newLat = M_PI / 180.0f * (90 - this->latitude); // θ
    auto z = radius * sin(newLat) * cos(newLon);
    auto x = radius * sin(newLat) * sin(newLon);
    auto y = radius * cos(newLat);
    QVector3D currentPosition;
    currentPosition.setX(x);
    currentPosition.setY(y);
    currentPosition.setZ(z);
    this->transform->setTranslation(currentPosition);
}

void SatelliteModel::updateAngle() {
    float newAngle = 90 + 180 * (this->longitude / 180);
    this->transform->setRotationY(newAngle);
}

void SatelliteModel::update() {
    this->updatePosition();
    this->updateAngle();
}
