/*
 * Copyright (c) Christian Berger and Bernhard Rumpe, Rheinisch-Westfaelische Technische Hochschule Aachen, Germany.
 *
 * The Hesperia Framework.
 */

#ifndef HESPERIA_CORE_IO_CONTAINERCONFERENCE_H_
#define HESPERIA_CORE_IO_CONTAINERCONFERENCE_H_

// native.h must be included right before boost/asio.hpp because of the definition of _WIN32_WINNT.
#include "core/native.h"

#include "core/base/Mutex.h"
#include "core/data/Container.h"
#include "core/io/ContainerObserver.h"

namespace core {
    namespace io {

        using namespace std;

        class ContainerConferenceFactory;

        /**
         * This class provides an interface for a ContainerConference.
         * A ContainerConference is either a UDPMultiCastContainerConference
         * of a pure virtual conference as needed by simulation.
         */
        class HESPERIA_API ContainerConference : public ContainerObserver {
            private:
                friend class ContainerConferenceFactory;

            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                ContainerConference(const ContainerConference &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                ContainerConference& operator=(const ContainerConference &);

            protected:
                ContainerConference();

            public:
                virtual ~ContainerConference();

                virtual void setContainerListener(ContainerListener *cl);

                /**
                 * This methods sends a container to this conference.
                 *
                 * @param container Container to be sent.
                 */
                virtual void send(core::data::Container &container) const = 0;

            protected:
                /**
                 * This method can be called from any subclass to distribute
                 * a newly received container.
                 *
                 * @param c Container to be distributed.
                 */
                void receive(core::data::Container &c);

                /**
                 * This method returns true if a ContainerListener is registered.
                 *
                 * @return true, iff a ContainerListener is registered.
                 */
                bool hasContainerListener() const;

            private:
                mutable base::Mutex m_containerListenerMutex;
                ContainerListener *m_containerListener;
        };

    }
} // core::io

#endif /*HESPERIA_CORE_IO_CONTAINERCONFERENCE_H_*/
