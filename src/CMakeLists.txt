add_executable(Satellite
        main.cpp
        MainWindow.cpp
        SceneWidget.cpp
        SatelliteModel.cpp
        StarFinderModel.cpp
        EarthModel.cpp
        CustomCameraController.cpp
        TorusModel.cpp
        ConeModel.cpp
        resources.qrc
        Light.cpp Light.h
        )

target_link_libraries(Satellite PRIVATE
        Qt5::Core
        Qt5::Widgets
        Qt5::3DCore
        Qt5::3DExtras
        Qt5::3DRender
        )
