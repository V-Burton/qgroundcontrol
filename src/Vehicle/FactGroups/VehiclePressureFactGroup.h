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

class Vehicle;

class VehiclePressureFactGroup : public FactGroup
{
    Q_OBJECT

public:
    VehiclePressureFactGroup(QObject* parent = nullptr);

    Q_PROPERTY(Fact* timestamp          READ timestamp          CONSTANT)
    Q_PROPERTY(Fact* pressureIn         READ pressureIn         CONSTANT)
    Q_PROPERTY(Fact* pressureOut        READ pressureOut        CONSTANT)
    Q_PROPERTY(Fact* meanIn             READ meanIn             CONSTANT)
    Q_PROPERTY(Fact* meanOut            READ meanOut            CONSTANT)
    Q_PROPERTY(Fact* differential        READ differential        CONSTANT)

    Fact* timestamp         () { return &_timestampFact; }
    Fact* pressureIn       () { return &_pressureInFact; }
    Fact* pressureOut      () { return &_pressureOutFact; }
    Fact* meanIn           () { return &_meanInFact; }
    Fact* meanOut          () { return &_meanOutFact; }
    Fact* differential      () { return &_differentialFact; }

    void handleMessage(Vehicle* vehicle, mavlink_message_t& message) override;

private:
    void _handleRigidData(mavlink_message_t& message);

    Fact _timestampFact;
    Fact _pressureInFact;
    Fact _pressureOutFact;
    Fact _meanInFact;
    Fact _meanOutFact;
    Fact _differentialFact;

    const QString _timestampFactName = QStringLiteral("timestamp");
    const QString _pressureInFactName = QStringLiteral("pressureIn");
    const QString _pressureOutFactName = QStringLiteral("pressureOut");
    const QString _meanInFactName = QStringLiteral("meanIn");
    const QString _meanOutFactName = QStringLiteral("meanOut");
    const QString _differentialFactName = QStringLiteral("differential");
};