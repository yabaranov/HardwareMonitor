#pragma once

#include <QObject>

class NetState : public QObject
{
    Q_OBJECT
    Q_PROPERTY(State currentState READ getState WRITE setState
                   NOTIFY stateChanged)
public:
    enum State {
        Disconnected = 0,
        Connecting = 1,
        Connected = 2,
    };
    Q_ENUM(State)

    Q_INVOKABLE void setState(State state);
    State getState() const;

Q_SIGNALS:
    void stateChanged();

private:
    State m_state;
};
