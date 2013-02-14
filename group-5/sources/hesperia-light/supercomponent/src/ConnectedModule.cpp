/*
 * Copyright (c) Christian Berger and Bernhard Rumpe, Rheinisch-Westfaelische Technische Hochschule Aachen, Germany.
 *
 * The Hesperia Framework.
 */

#include "ConnectedModule.h"

namespace supercomponent {

    using namespace std;
    using namespace core::base;
    using namespace hesperia::dmcp::connection;

    ConnectedModule::ConnectedModule(ModuleConnection* connection, const ModuleState::MODULE_STATE& state) :
        m_state(state),
        m_connection(connection),
        m_hasExitCode(false)
    {}

    ConnectedModule::~ConnectedModule()
    {
        delete m_connection;
    }

    ModuleState::MODULE_STATE ConnectedModule::getState() const
    {
        return m_state;
    }

    void ConnectedModule::setExitCode()
    {
        m_hasExitCode = true;
    }

    bool ConnectedModule::hasExitCode() const
    {
        return m_hasExitCode;
    }

    ModuleConnection& ConnectedModule::getConnection()
    {
        return *m_connection;
    }

    void ConnectedModule::setState(const ModuleState::MODULE_STATE& state) {
        m_state = state;
    }
}
