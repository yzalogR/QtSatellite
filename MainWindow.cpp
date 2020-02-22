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
    satelliteLat = new QLineEdit();
    satelliteLat->setValidator(validator);
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
    groundLat = new QLineEdit();
    groundLat->setValidator(validator);
    groundSubmit = new QPushButton();
    groundSubmit->setText(QStringLiteral("Submit"));
    groundReset = new QPushButton();
    groundReset->setText(QStringLiteral("Reset"));

    vLayout->addWidget(groundAngleText);
    vLayout->addWidget(groundLon);
    vLayout->addWidget(groundLat);
    vLayout->addWidget(groundSubmit);
    vLayout->addWidget(groundReset);

    connect(satelliteSubmit,&QPushButton::clicked,this,&MainWindow::setSatellitePosion);
}

void MainWindow::setSatellitePosion()
{
    float longitude = satelliteLon->text().toFloat();
    float latitude = satelliteLat->text().toFloat();
    view->setSatellitePosion(longitude,latitude);
}
