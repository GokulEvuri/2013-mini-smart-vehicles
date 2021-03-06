/*
 * Copyright (c) Rheinisch-Westfaelische Technische Hochschule Aachen, Germany.
 *
 * The Hesperia Framework.
 */

#include <string>
#include <sstream>
#include <iostream>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include "core/wrapper/ConcurrencyFactory.h"
#include "core/wrapper/MutexFactory.h"
#include "core/wrapper/POSIX/POSIXTCPAcceptor.h"
#include "core/wrapper/POSIX/POSIXTCPConnection.h"

namespace core {
    namespace wrapper {
        namespace POSIX {

            using namespace std;

            POSIXTCPAcceptor::POSIXTCPAcceptor(const uint32_t& port)
                    : m_thread(NULL),
                    m_listenerMutex(NULL),
                    m_listener(NULL),
                    m_fileDescriptor(0),
                    m_port(port) {
                m_thread = ConcurrencyFactory::getInstance().createThread(*this);
                if (m_thread == NULL) {
                    throw std::string("[PosixTCPAcceptor] Error creating thread");
                }

                m_listenerMutex = MutexFactory::getInstance().createMutex();
                if (m_listenerMutex == NULL) {
                    throw std::string("[PosixTCPAcceptor] Error creating mutex");
                }

                // Socket erstellen.
                m_fileDescriptor = socket(PF_INET, SOCK_STREAM, 0);
                if (m_fileDescriptor < 0) {
                    stringstream s;
                    s << "Error while creating file descriptor at " << __FILE__ << ": " << __LINE__;
                    throw s.str();
                }

                // Allow reusing of ports by multiple sockets.
                int32_t yes = 1;
                int32_t retval = setsockopt (m_fileDescriptor,
                                         SOL_SOCKET,
                                         SO_REUSEADDR,
                                         &yes,
                                         sizeof(yes));
                if (retval < 0) {
                    stringstream s;
                    s << "Error while setting socket options at " << __FILE__ << ": " << __LINE__;
                    throw s.str();
                }

                // Setup address and port.
                sockaddr_in address;
                memset(&address, 0, sizeof(address));
                address.sin_family = AF_INET;
                address.sin_addr.s_addr = htonl(INADDR_ANY);
                address.sin_port = htons(port);


                // An den handle binden.
                if (bind(m_fileDescriptor, (struct sockaddr *) &address, sizeof(address)) == -1) {
                    stringstream s;
                    s << "Error while binding socket at " << __FILE__ << ": " << __LINE__;
                    throw s.str();
                }

                if (listen(m_fileDescriptor, POSIXTCPAcceptor::BACKLOG) == -1) {
                    stringstream s;
                    s << "Listen failed at " << __FILE__ << ": " << __LINE__;
                    throw s.str();
                }
            }

            POSIXTCPAcceptor::~POSIXTCPAcceptor() {
                setAcceptorListener(NULL);
                close(m_fileDescriptor);

                if (m_thread != NULL) {
                    delete m_thread;
                    m_thread = NULL;
                }

                if (m_listenerMutex != NULL) {
                    delete m_listenerMutex;
                    m_listenerMutex = NULL;
                }

            }
            void POSIXTCPAcceptor::setAcceptorListener(TCPAcceptorListener* listener) {
                m_listenerMutex->lock();
                m_listener = listener;
                m_listenerMutex->unlock();
            }

            void POSIXTCPAcceptor::invokeAcceptorListener(TCPConnection* connection) {
                m_listenerMutex->lock();
                if (m_listener != NULL) {
                    m_listener->onNewConnection(connection);
                } else {
                    // Kein Listener vorhanden, akzeptierte Connection wieder löschen
                    // damit kein Speicherleck enststeht
                    delete connection;
                    connection = NULL;
                }
                m_listenerMutex->unlock();
            }

            void POSIXTCPAcceptor::start() {
                m_thread->start();
            }

            void POSIXTCPAcceptor::stop() {
                m_thread->stop();
            }

            bool POSIXTCPAcceptor::isRunning() {
                return m_thread->isRunning();
            }

            void POSIXTCPAcceptor::run() {
                fd_set rfds;
                struct timeval timeout;

                while (isRunning() ) {
                    timeout.tv_sec = 1;
                    timeout.tv_usec = 0;

                    FD_ZERO(&rfds);
                    FD_SET(m_fileDescriptor, &rfds);

                    select(m_fileDescriptor + 1, &rfds, NULL, NULL, &timeout);

                    if (FD_ISSET(m_fileDescriptor, &rfds)) {
                        sockaddr clientsock;
                        socklen_t csize = sizeof(clientsock);

                        int32_t client = accept(m_fileDescriptor, &clientsock, &csize);

                        if (client >= 0) {
                            invokeAcceptorListener(new POSIXTCPConnection(client));
                        } else {
                            stringstream s;
                            s << "unable to accept tcp connection at " << __FILE__ << ": " << __LINE__;
                            throw s.str();
                        }
                    }
                }
                close(m_fileDescriptor);
            }
        }
    }
}
