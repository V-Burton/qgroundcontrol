/****************************************************************************
 *
 * (c) 2009-2024 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/

#include "VehiclePressureFactGroup.h"
#include "Vehicle.h"

VehiclePressureFactGroup::VehiclePressureFactGroup(QObject* parent)
    : FactGroup(1000, ":/json/Vehicle/PressureFact.json", parent)
    , _timestampFactName("timestamp")
    , _pressureInFactName("pressureIn")
    , _pressureOutFactName("pressureOut")
    , _meanInFactName("meanIn")
    , _meanOutFactName("meanOut")
    , _differentialFactName("differential")
    , _timestampFact(0, "timestamp", FactMetaData::valueTypeDouble)
    , _pressureInFact(0, "pressureIn", FactMetaData::valueTypeDouble)
    , _pressureOutFact(0, "pressureOut", FactMetaData::valueTypeDouble)
    , _meanInFact(0, "meanIn", FactMetaData::valueTypeDouble)
    , _meanOutFact(0, "meanOut", FactMetaData::valueTypeDouble)
    , _differentialFact(0, "differential", FactMetaData::valueTypeDouble)
{
    _addFact(&_timestampFact, _timestampFactName);
    _addFact(&_pressureInFact, _pressureInFactName);
    _addFact(&_pressureOutFact, _pressureOutFactName);
    _addFact(&_meanInFact, _meanInFactName);
    _addFact(&_meanOutFact, _meanOutFactName);
    _addFact(&_differentialFact, _differentialFactName);

    _timestampFact.setRawValue(qQNaN());
    _pressureInFact.setRawValue(qQNaN());
    _pressureOutFact.setRawValue(qQNaN());
    _meanInFact.setRawValue(qQNaN());
    _meanOutFact.setRawValue(qQNaN());
    _differentialFact.setRawValue(qQNaN());
}

void VehiclePressureFactGroup::handleMessage(Vehicle* vehicle, mavlink_message_t& message)
{
    switch (message.msgid) {
    case MAVLINK_MSG_ID_RIGID_DATA: {
        _handleRigidData(message);
        break;
    }
    default:
        break;
    }
}

void VehiclePressureFactGroup::_handleRigidData(mavlink_message_t& message)
{
    mavlink_rigid_data_t rigidData;
    mavlink_msg_rigid_data_decode(&message, &rigidData);

    _timestampFact.setRawValue(rigidData.timestamp);
    _pressureInFact.setRawValue(rigidData.pressure_in[0]);
    _pressureOutFact.setRawValue(rigidData.pressure_out[0]);
    _meanInFact.setRawValue(rigidData.mean_in);
    _meanOutFact.setRawValue(rigidData.mean_out);
    _differentialFact.setRawValue(rigidData.differential);

    _setTelemetryAvailable(true);
}