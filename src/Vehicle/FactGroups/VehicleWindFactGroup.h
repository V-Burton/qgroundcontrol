/****************************************************************************
 *
 * (c) 2009-2024 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#pragma once

#include "FactGroup.h"
#include "QGCMAVLink.h"
// TODO: Removed if not needed anymore
#ifdef MAVLINK_MSG_ID_WIND_SENSOR
#pragma message "WIND_SENSOR is defined"
#else
#pragma message "WIND_SENSOR is NOT defined"
#endif

class VehicleWindFactGroup : public FactGroup
{
    Q_OBJECT

public:
    VehicleWindFactGroup(QObject* parent = nullptr);

    Q_PROPERTY(Fact* direction      READ direction      CONSTANT)
    Q_PROPERTY(Fact* speed          READ speed          CONSTANT)
    Q_PROPERTY(Fact* verticalSpeed  READ verticalSpeed  CONSTANT)
    Q_PROPERTY(Fact* speed3D        READ speed3D       CONSTANT)
    Q_PROPERTY(Fact* speed2D        READ speed2D       CONSTANT)
    Q_PROPERTY(Fact* horizontalDirection READ horizontalDirection CONSTANT)
    Q_PROPERTY(Fact* verticalDirection   READ verticalDirection   CONSTANT)
    Q_PROPERTY(Fact* temperature     READ temperature    CONSTANT)
    Q_PROPERTY(Fact* speedSound      READ speedSound     CONSTANT)
    Q_PROPERTY(Fact* humidity        READ humidity       CONSTANT)
    Q_PROPERTY(Fact* dewPoint        READ dewPoint       CONSTANT)
    Q_PROPERTY(Fact* pressure        READ pressure       CONSTANT)
    Q_PROPERTY(Fact* airDensity      READ airDensity     CONSTANT)

    Fact* direction     () { return &_directionFact; }
    Fact* speed         () { return &_speedFact; }
    Fact* verticalSpeed () { return &_verticalSpeedFact; }
    Fact* speed3D       () { return &_speed3DFact; }
    Fact* speed2D       () { return &_speed2DFact; }
    Fact* horizontalDirection() { return &_horizontalDirectionFact; }
    Fact* verticalDirection  () { return &_verticalDirectionFact; }
    Fact* temperature    () { return &_temperatureFact; }
    Fact* speedSound     () { return &_speedSoundFact; }
    Fact* humidity       () { return &_humidityFact; }
    Fact* dewPoint       () { return &_dewPointFact; }
    Fact* pressure       () { return &_pressureFact; }
    Fact* airDensity     () { return &_airDensityFact; }

    // Overrides from FactGroup
    void handleMessage(Vehicle* vehicle, mavlink_message_t& message) override;

private:
    void _handleHighLatency (mavlink_message_t& message);
    void _handleHighLatency2(mavlink_message_t& message);
    void _handleWindCov     (mavlink_message_t& message);
#if !defined(NO_ARDUPILOT_DIALECT)
    void _handleWind        (mavlink_message_t& message);
#endif
    void _handleWindSensor(mavlink_message_t& message);

    const QString _directionFactName =      QStringLiteral("direction");
    const QString _speedFactName =          QStringLiteral("speed");
    const QString _verticalSpeedFactName =  QStringLiteral("verticalSpeed");
    const QString _speed3DFactName =          QStringLiteral("speed3D");
    const QString _speed2DFactName =          QStringLiteral("speed2D");
    const QString _horizontalDirectionFactName = QStringLiteral("horizontalDirection");
    const QString _verticalDirectionFactName =   QStringLiteral("verticalDirection");
    const QString _temperatureFactName =       QStringLiteral("temperature");
    const QString _speedSoundFactName =        QStringLiteral("speedSound");
    const QString _humidityFactName =          QStringLiteral("humidity");
    const QString _dewPointFactName =          QStringLiteral("dewPoint");
    const QString _pressureFactName =          QStringLiteral("pressure");
    const QString _airDensityFactName =        QStringLiteral("airDensity");

    Fact        _directionFact;
    Fact        _speedFact;
    Fact        _verticalSpeedFact;
    Fact _speed3DFact;
    Fact _speed2DFact;
    Fact _horizontalDirectionFact;
    Fact _verticalDirectionFact;
    Fact _temperatureFact;
    Fact _speedSoundFact;
    Fact _humidityFact;
    Fact _dewPointFact;
    Fact _pressureFact;
    Fact _airDensityFact;
};
