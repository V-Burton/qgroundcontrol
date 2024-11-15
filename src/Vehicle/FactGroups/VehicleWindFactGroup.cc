/****************************************************************************
 *
 * (c) 2009-2024 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "VehicleWindFactGroup.h"
#include "Vehicle.h"

#include <QtMath>

VehicleWindFactGroup::VehicleWindFactGroup(QObject* parent)
    : FactGroup(1000, ":/json/Vehicle/WindFact.json", parent)
    , _directionFact    (0, _directionFactName,     FactMetaData::valueTypeDouble)
    , _speedFact        (0, _speedFactName,         FactMetaData::valueTypeDouble)
    , _verticalSpeedFact(0, _verticalSpeedFactName, FactMetaData::valueTypeDouble)
    , _speed3DFact      (0, _speed3DFactName,       FactMetaData::valueTypeDouble)
    , _speed2DFact      (0, _speed2DFactName,       FactMetaData::valueTypeDouble)
    , _horizontalDirectionFact(0, _horizontalDirectionFactName, FactMetaData::valueTypeDouble)
    , _verticalDirectionFact  (0, _verticalDirectionFactName,   FactMetaData::valueTypeDouble)
    , _temperatureFact   (0, _temperatureFactName,    FactMetaData::valueTypeDouble)
    , _speedSoundFact    (0, _speedSoundFactName,     FactMetaData::valueTypeDouble)
    , _humidityFact      (0, _humidityFactName,       FactMetaData::valueTypeDouble)
    , _dewPointFact      (0, _dewPointFactName,       FactMetaData::valueTypeDouble)
    , _pressureFact      (0, _pressureFactName,       FactMetaData::valueTypeDouble)
    , _airDensityFact    (0, _airDensityFactName,     FactMetaData::valueTypeDouble)
{
    _addFact(&_directionFact,       _directionFactName);
    _addFact(&_speedFact,           _speedFactName);
    _addFact(&_verticalSpeedFact,   _verticalSpeedFactName);
    _addFact(&_speed3DFact,       _speed3DFactName);
    _addFact(&_speed2DFact,       _speed2DFactName);
    _addFact(&_horizontalDirectionFact, _horizontalDirectionFactName);
    _addFact(&_verticalDirectionFact,   _verticalDirectionFactName);
    _addFact(&_temperatureFact,    _temperatureFactName);
    _addFact(&_speedSoundFact,     _speedSoundFactName);
    _addFact(&_humidityFact,       _humidityFactName);
    _addFact(&_dewPointFact,       _dewPointFactName);
    _addFact(&_pressureFact,       _pressureFactName);
    _addFact(&_airDensityFact,     _airDensityFactName);

    // Start out as not available "--.--"
    _directionFact.setRawValue      (qQNaN());
    _speedFact.setRawValue          (qQNaN());
    _verticalSpeedFact.setRawValue  (qQNaN());
    _speed3DFact.setRawValue(qQNaN());
    _speed2DFact.setRawValue(qQNaN());
    _horizontalDirectionFact.setRawValue(qQNaN());
    _verticalDirectionFact.setRawValue(qQNaN());
    _temperatureFact.setRawValue(qQNaN());
    _speedSoundFact.setRawValue(qQNaN());
    _humidityFact.setRawValue(qQNaN());
    _dewPointFact.setRawValue(qQNaN());
    _pressureFact.setRawValue(qQNaN());
    _airDensityFact.setRawValue(qQNaN());
}

void VehicleWindFactGroup::handleMessage(Vehicle* /* vehicle */, mavlink_message_t& message)
{
    switch (message.msgid) {
#ifdef MAVLINK_HYLIGHT_DIALECT
    case MAVLINK_MSG_ID_WIND_SENSOR: {
        _handleWindSensor(message);
        break;
    }
#endif
    case MAVLINK_MSG_ID_WIND_COV:
        _handleWindCov(message);
        break;
#if !defined(NO_ARDUPILOT_DIALECT)
    case MAVLINK_MSG_ID_WIND:
        _handleWind(message);
        break;
#endif
    case MAVLINK_MSG_ID_HIGH_LATENCY:
        _handleHighLatency(message);
        break;
    case MAVLINK_MSG_ID_HIGH_LATENCY2:
        _handleHighLatency2(message);
        break;
    default:
        break;
    }
}

void VehicleWindFactGroup::_handleHighLatency(mavlink_message_t& message)
{
    mavlink_high_latency_t highLatency;
    mavlink_msg_high_latency_decode(&message, &highLatency);
    speed()->setRawValue((double)highLatency.airspeed / 5.0);
    _setTelemetryAvailable(true);
}

void VehicleWindFactGroup::_handleHighLatency2(mavlink_message_t& message)
{
    mavlink_high_latency2_t highLatency2;
    mavlink_msg_high_latency2_decode(&message, &highLatency2);
    direction()->setRawValue((double)highLatency2.wind_heading * 2.0);
    speed()->setRawValue((double)highLatency2.windspeed / 5.0);
    _setTelemetryAvailable(true);
}

void VehicleWindFactGroup::_handleWindCov(mavlink_message_t& message)
{
    mavlink_wind_cov_t wind;
    mavlink_msg_wind_cov_decode(&message, &wind);

    float direction = qRadiansToDegrees(qAtan2(wind.wind_y, wind.wind_x));
    float speed = qSqrt(qPow(wind.wind_x, 2) + qPow(wind.wind_y, 2));

    if (direction < 0) {
        direction += 360;
    }

    this->direction()->setRawValue(direction);
    this->speed()->setRawValue(speed);
    verticalSpeed()->setRawValue(0);
    _setTelemetryAvailable(true);
}

void VehicleWindFactGroup::_handleWindSensor(mavlink_message_t& message)
{
    mavlink_wind_sensor_t wind;
    mavlink_msg_wind_sensor_decode(&message, &wind);
    
    _speed3DFact.setRawValue(wind.wind_speed_3d);
    _speed2DFact.setRawValue(wind.wind_speed_2d);
    _horizontalDirectionFact.setRawValue(wind.horizontal_wind_direction);
    _verticalDirectionFact.setRawValue(wind.vertical_wind_direction);
    _temperatureFact.setRawValue(wind.sonic_temperature);
    _speedSoundFact.setRawValue(wind.speed_of_sound);
    _humidityFact.setRawValue(wind.humidity);
    _dewPointFact.setRawValue(wind.drew_point);
    _pressureFact.setRawValue(wind.pressure);
    _airDensityFact.setRawValue(wind.air_density);
    
    _setTelemetryAvailable(true);
}

#if !defined(NO_ARDUPILOT_DIALECT)
void VehicleWindFactGroup::_handleWind(mavlink_message_t& message)
{
    mavlink_wind_t wind;
    mavlink_msg_wind_decode(&message, &wind);

    // We don't want negative wind angles
    float direction = wind.direction;
    if (direction < 0) {
        direction += 360;
    }
    this->direction()->setRawValue(direction);
    speed()->setRawValue(wind.speed);
    verticalSpeed()->setRawValue(wind.speed_z);
    _setTelemetryAvailable(true);
}
#endif
