#include "ConeModel.h"

ConeSignalModel::ConeSignalModel(Qt3DCore::QEntity *parent,SatelliteModel* satellite):
                                Qt3DCore::QEntity(parent),
                                mSatellite(satellite),
                                radius(6.0f),
                                longitude(0),
                                latitude(90)
{
    material = new Qt3DExtras::QPhongAlphaMaterial(parent);
    material->setProperty("ambient",QVariant(QColor(144,238,144)));
    material->setProperty("alpha",QVariant(float(0.5)));
    signalEntity = new Qt3DCore::QEntity(parent);
    signalMesh = new Qt3DExtras::QConeMesh;
    signalMesh->setTopRadius(0.01);
    signalMesh->setBottomRadius(2);
    signalMesh->setLength(2);
    signalMesh->setRings(5);
    signalMesh->setSlices(100);

    transform = new Qt3DCore::QTransform(this);
    transform->setTranslation(QVector3D(0.0f, radius, 0.0));

    signalEntity->addComponent(signalMesh);
    signalEntity->addComponent(transform);
    signalEntity->addComponent(material);


    connect(mSatellite,&SatelliteModel::emitLonLat,this,&ConeSignalModel::recvSatelliteLonLat);
}

void ConeSignalModel::recvSatelliteLonLat(float newLon, float newLat)
{
    this->longitude = newLon;
    this->latitude = newLat;
    update();
}

void ConeSignalModel::updatePosition()
{
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

void ConeSignalModel::updateAngle()
{
    float newAngleX = 90 + 180 * (-this->latitude / 180);
    float newAngleY = -90 + 180 * this->longitude / 180;
    this->transform->setRotationX(newAngleX);
    this->transform->setRotationY(newAngleY);
}

void ConeSignalModel::update()
{
    this->updatePosition();
    this->updateAngle();
}

void ConeSignalModel::updateColor(bool found)
{
    if (found)
        material->setProperty("ambient",QVariant(QColor(137,207,240)));
    else
        material->setProperty("ambient",QVariant(QColor(144,238,144)));
}
