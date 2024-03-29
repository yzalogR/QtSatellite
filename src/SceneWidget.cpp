//
// Created by Isaac on 2020/2/15.
//

#include "SceneWidget.h"
#include "CustomCameraController.h"

SceneWidget::SceneWidget(QScreen *screen) : Qt3DExtras::Qt3DWindow(screen) {
    this->defaultFrameGraph()->setClearColor(QColor(0x4D4D4F));

    createScene();
    this->setRootEntity(rootEntity);
    auto *m_camera = this->camera();
    m_camera->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
    m_camera->setPosition(QVector3D(0.0f, 0.0f, 20.0f));
    m_camera->setUpVector(QVector3D(0.0f, 0.1f, 0.0f));
    m_camera->setViewCenter(QVector3D(0.0f, 0.0f, 0.0f));

    auto *manipulator = new CustomCameraController(rootEntity);
    manipulator->setRotationSpeed(2.0f);
    manipulator->setWindowSize(QSize(this->width(), this->height()));
    manipulator->setCamera(m_camera);

    light = new Light(m_camera, rootEntity);

    auto *forwardRenderer = new Qt3DExtras::QForwardRenderer(rootEntity);
    forwardRenderer->setCamera(m_camera);
    forwardRenderer->setClearColor(QColor("transparent"));

    moveSatelliteTimer = new QTimer;
    connect(moveSatelliteTimer, &QTimer::timeout, this, &SceneWidget::runSatelliteMoveTimer);
}

Qt3DCore::QEntity *SceneWidget::createScene() {
    rootEntity = new Qt3DCore::QEntity();

    earthModel = new EarthModel(rootEntity);
    satelliteModel = new SatelliteModel(rootEntity);
    starFinderModel = new StarFinderModel(rootEntity);
    torusModel = new TorusModel(rootEntity);
    coneSignalModel = new ConeSignalModel(rootEntity,satelliteModel);

    return rootEntity;
}

void SceneWidget::setSatellitePosion(float longitude, float latitude) {
    this->satelliteModel->setCurrentPosition(longitude, latitude);
    this->satelliteModel->update();
}

void SceneWidget::setGroundPosion(float longitude, float latitude) {
    this->starFinderModel->setCurrentPosition(longitude, latitude);
    this->starFinderModel->update();
}

void SceneWidget::moveSatellite(float longitude, float latitude) {
    QPointF prePos = satelliteModel->getCurrentPosition();
    this->moveSatelliteOffset.setX(prePos.x() - longitude);
    this->moveSatelliteOffset.setY(prePos.y() - latitude);
    this->moveSatelliteTimer->start(100);
}

void SceneWidget::stopSatellite() {
    if (this->moveSatelliteTimer->isActive()) {
        this->moveSatelliteOffset.setX(0);
        this->moveSatelliteOffset.setY(0);
        this->moveSatelliteTimer->stop();
    }
}

void SceneWidget::runSatelliteMoveTimer() {
    QPointF currentPosition = satelliteModel->getCurrentPosition();
    //QPointF groundPosition = starFinderModel->getCurrentPosition();
    float nextLon = currentPosition.x();
    float nextLat = currentPosition.y();
    if (this->moveSatelliteOffset.x() > 0) {
        nextLon--;
        this->moveSatelliteOffset.rx()--;
    } else if (this->moveSatelliteOffset.x() < 0) {
        nextLon++;
        this->moveSatelliteOffset.rx()++;
    }
    if (this->moveSatelliteOffset.y() > 0) {
        nextLat--;
        this->moveSatelliteOffset.ry()--;
    } else if (this->moveSatelliteOffset.y() < 0) {
        nextLat++;
        this->moveSatelliteOffset.ry()++;
    }
    satelliteModel->setCurrentPosition(nextLon, nextLat);
    satelliteModel->update();

    //if satellite scaned ground
    QVector3D satellite3DPosition = satelliteModel->getVector3DPosition();
    QVector3D starFinder3DPosition = starFinderModel->getVector3DPosition();
    float distanceDiff = satellite3DPosition.distanceToPoint(starFinder3DPosition);
    if (distanceDiff < 2.15)
        this->coneSignalModel->updateColor(true);
    else
        this->coneSignalModel->updateColor(false);

    if (this->moveSatelliteOffset.x() == 0 && this->moveSatelliteOffset.y() == 0)
        this->moveSatelliteTimer->stop();

}

void SceneWidget::updateTorusAngle(float angleX,float angleY)
{
    torusModel->setAngleX(angleX);
    torusModel->setAngleY(angleY);
    torusModel->updateAngle();
}
