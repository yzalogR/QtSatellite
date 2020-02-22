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
    m_camera->setUpVector(QVector3D(0.0f, 0.0f, 0.0f));
    m_camera->setViewCenter(QVector3D(0.0f, 0.0f, 0.0f));

    auto *manipulator = new CustomCameraController(rootEntity);
    manipulator->setRotationSpeed(2.0f);
    manipulator->setWindowSize(QSize(this->width(), this->height()));
    manipulator->setCamera(m_camera);

    light = new Light(m_camera, rootEntity);

    auto *forwardRenderer = new Qt3DExtras::QForwardRenderer(rootEntity);
    forwardRenderer->setCamera(m_camera);
    forwardRenderer->setClearColor(QColor("transparent"));
}

Qt3DCore::QEntity *SceneWidget::createScene() {
    rootEntity = new Qt3DCore::QEntity();

    earthModel = new EarthModel(rootEntity);
    satelliteModel = new SatelliteModel(rootEntity);
    starFinderModel = new StarFinderModel(rootEntity);

    return rootEntity;
}

void SceneWidget::setSatellitePosion(float longitude , float latitude)
{
    this->satelliteModel->setCurrentPosition(longitude,latitude);
    this->satelliteModel->update();
}

void SceneWidget::setGroundPosion(float longitude , float latitude)
{
    this->starFinderModel->setCurrentPosition(longitude,latitude);
    this->starFinderModel->update();
}
