#include "NetState.h"

void NetState::setState(State state)
{
    if (m_state != state) {
        m_state = state;
        emit stateChanged();
    }
}

NetState::State NetState::getState() const
{
    return m_state;
}
