/*
 * OpenDaVINCI.
 *
 * This software is open source. Please see COPYING and AUTHORS for further information.
 */

#ifndef OPENDAVINCI_CORE_WRAPPER_TCPACCEPTORLISTENER_H_
#define OPENDAVINCI_CORE_WRAPPER_TCPACCEPTORLISTENER_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include "core/wrapper/TCPConnection.h"

namespace core {
    namespace wrapper {
        class OPENDAVINCI_API TCPAcceptorListener {
            public:
                virtual ~TCPAcceptorListener() {};
                virtual void onNewConnection(TCPConnection* connection) = 0;
        };
    }
}

#endif /* OPENDAVINCI_CORE_WRAPPER_TCPACCEPTORLISTENER_H_ */
