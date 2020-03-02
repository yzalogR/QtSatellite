//
// Created by Isaac on 2020/2/14.
//

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    view = new SceneWidget();
    auto *container = QWidget::createWindowContainer(view);
    auto screenSize = view->screen()->size();
    container->setMinimumSize(1280, 720);
    container->setMaximumSize(screenSize);

    hLayout = new QHBoxLayout(this);
    vLayout = new QVBoxLayout();
    vLayout->setAlignment(Qt::AlignTop);
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);
    this->setWindowTitle(QStringLiteral("Satellite"));

    satelliteAngleText = new QLabel();
    satelliteAngleText->setText(QStringLiteral("Satellite"));
    auto *validator = new QDoubleValidator(-180, 180, 2);
    satelliteLon = new QLineEdit();
    satelliteLon->setValidator(validator);
    satelliteLon->setPlaceholderText("Longitude");
    satelliteLat = new QLineEdit();
    satelliteLat->setValidator(validator);
    satelliteLat->setPlaceholderText("Latitude");
    satelliteSubmit = new QPushButton();
    satelliteSubmit->setText(QStringLiteral("Submit"));
    satelliteReset = new QPushButton();
    satelliteReset->setText(QStringLiteral("Reset"));

    vLayout->addWidget(satelliteAngleText);
    vLayout->addWidget(satelliteLon);
    vLayout->addWidget(satelliteLat);
    vLayout->addWidget(satelliteSubmit);
    vLayout->addWidget(satelliteReset);

    groundAngleText = new QLabel();
    groundAngleText->setText(QStringLiteral("Ground"));
    groundLon = new QLineEdit();
    groundLon->setValidator(validator);
    groundLon->setPlaceholderText("Longitude");
    groundLat = new QLineEdit();
    groundLat->setValidator(validator);
    groundLat->setPlaceholderText("Latitude");
    groundSubmit = new QPushButton();
    groundSubmit->setText(QStringLiteral("Submit"));
    groundReset = new QPushButton();
    groundReset->setText(QStringLiteral("Reset"));

    vLayout->addWidget(groundAngleText);
    vLayout->addWidget(groundLon);
    vLayout->addWidget(groundLat);
    vLayout->addWidget(groundSubmit);
    vLayout->addWidget(groundReset);


    satelliteMoveText = new QLabel(QStringLiteral("Move satellite"));
    satelliteMoveLon = new QLineEdit();
    satelliteMoveLon->setValidator(validator);
    satelliteMoveLon->setPlaceholderText("Move to longitude");
    satelliteMoveLat = new QLineEdit();
    satelliteMoveLat->setValidator(validator);
    satelliteMoveLat->setPlaceholderText("Move to latitude");
    satelliteMoveSubmit = new QPushButton(QStringLiteral("Submit"));
    satelliteMoveStop = new QPushButton(QStringLiteral("Stop"));

    vLayout->addWidget(satelliteMoveText);
    vLayout->addWidget(satelliteMoveLon);
    vLayout->addWidget(satelliteMoveLat);
    vLayout->addWidget(satelliteMoveSubmit);
    vLayout->addWidget(satelliteMoveStop);

    torusText = new QLabel(QStringLiteral("Change torus"));
    torusAngleX = new QLineEdit();
    torusAngleX->setPlaceholderText("X rotation");
    torusAngleX->setValidator(validator);
    torusAngleY = new QLineEdit();
    torusAngleY->setValidator(validator);
    torusAngleY->setPlaceholderText("Y rotation");
    torusChangeSubmit = new QPushButton(QStringLiteral("Submit"));

    vLayout->addWidget(torusText);
    vLayout->addWidget(torusAngleX);
    vLayout->addWidget(torusAngleY);
    vLayout->addWidget(torusChangeSubmit);

    connect(satelliteSubmit,&QPushButton::clicked,this,&MainWindow::setSatellitePosion);
    connect(groundSubmit,&QPushButton::clicked,this,&MainWindow::setGroundPosion);
    connect(satelliteMoveSubmit,&QPushButton::clicked,this,&MainWindow::moveSatellite);
    connect(satelliteMoveStop,&QPushButton::clicked,this,&MainWindow::stopSatellite);
    connect(torusChangeSubmit,&QPushButton::clicked,this,&MainWindow::updateTorusAngle);
}

void MainWindow::setSatellitePosion()
{
    float longitude = satelliteLon->text().toFloat();
    float latitude = satelliteLat->text().toFloat();
    view->setSatellitePosion(longitude,latitude);
}

void MainWindow::setGroundPosion()
{
    float longitude = groundLon->text().toFloat();
    float latitude = groundLat->text().toFloat();
    view->setGroundPosion(longitude,latitude);
}

void MainWindow::moveSatellite()
{
    float longitude = satelliteMoveLon->text().toFloat();
    float latitude = satelliteMoveLat->text().toFloat();
    view->moveSatellite(longitude,latitude);
}

void MainWindow::stopSatellite()
{
    view->stopSatellite();
}

void MainWindow::updateTorusAngle()
{
    float angleX = torusAngleX->text().toFloat();
    float angleY = torusAngleY->text().toFloat();
    view->updateTorusAngle(angleX,angleY);
}
