#pragma once

#include <QObject>

class NetState : public QObject
{
    Q_OBJECT

public:
    enum State {
        Disconnected = 0,
        Connecting = 1,
        Connected = 2,
    };
    Q_ENUM(State)
};
