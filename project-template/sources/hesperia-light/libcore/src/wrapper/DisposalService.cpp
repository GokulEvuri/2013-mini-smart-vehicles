/*
 * Copyright (c) Christian Berger and Bernhard Rumpe, Rheinisch-Westfaelische Technische Hochschule Aachen, Germany.
 *
 * The Hesperia Framework.
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include "core/macros.h"
#include "core/wrapper/ConcurrencyFactory.h"
#include "core/wrapper/ConditionFactory.h"
#include "core/wrapper/DisposalService.h"
#include "core/wrapper/MutexFactory.h"
#include "core/wrapper/TimeFactory.h"

namespace core {
    namespace wrapper {

        // Initialization of the singleton instance.
        Mutex* DisposalService::m_singletonMutex = MutexFactory::getInstance().createMutex();
        DisposalService* DisposalService::m_singleton = NULL;

        DisposalService::DisposalService() :
            m_queueCondition(NULL),
            m_finalRemovalMutex(NULL),
            m_queueMutex(NULL),
            m_queueForRegularRemoval(),
            m_queueForFinalRemoval(),
            m_thread(NULL),
            m_queueCleaner(NULL) {

            m_queueCondition = ConditionFactory::getInstance().createCondition();
            if (m_queueCondition == NULL) {
                stringstream s;
                s << "Error while creating condition at " << __FILE__ << ": " << __LINE__;
                throw s.str();
            }

            m_finalRemovalMutex = MutexFactory::getInstance().createMutex();
            if (m_finalRemovalMutex == NULL) {
                stringstream s;
                s << "Error while creating mutex at " << __FILE__ << ": " << __LINE__;
                throw s.str();
            }

            m_queueMutex = MutexFactory::getInstance().createMutex();
            if (m_queueMutex == NULL) {
                stringstream s;
                s << "Error while creating mutex at " << __FILE__ << ": " << __LINE__;
                throw s.str();
            }

            m_queueCleaner = new DisposalService::QueueCleaner(*m_queueCondition, *m_finalRemovalMutex, *m_queueMutex, m_queueForRegularRemoval);
            if (m_queueCleaner == NULL) {
                stringstream s;
                s << "Error while creating queue cleaner at " << __FILE__ << ": " << __LINE__;
                throw s.str();
            }

            m_queueCleaner->setRunning(true);

            // Create thread for encapsulating string distribution.
            m_thread = ConcurrencyFactory::getInstance().createThread(*m_queueCleaner);
            if (m_thread == NULL) {
                stringstream s;
                s << "Error while creating thread at " << __FILE__ << ": " << __LINE__;
                throw s.str();
            }

            // Start thread.
            m_thread->start();
        }

        DisposalService::~DisposalService() {
            // Stop runnable.
            m_queueCleaner->setRunning(false);

            // Wake awaiting threads before destructing.
            m_queueCondition->wakeAll();

            // Stop thread.
            m_thread->stop();

            // Clean up finally.
            cleanUpFinally();

            // Destroy distributor.
            if (m_queueCleaner != NULL) {
                delete m_queueCleaner;
            }
            m_queueCleaner = NULL;

            // Destroy mutex.
            if (m_finalRemovalMutex != NULL) {
                delete m_finalRemovalMutex;
            }
            m_finalRemovalMutex = NULL;

            // Destroy mutex.
            if (m_queueMutex != NULL) {
                delete m_queueMutex;
            }
            m_queueMutex = NULL;

            // Destroy condition.
            if (m_queueCondition != NULL) {
                delete m_queueCondition;
            }
            m_queueCondition = NULL;

            // Destroy thread.
            if (m_thread != NULL) {
                delete m_thread;
            }
            m_thread = NULL;

            DisposalService::m_singleton = NULL;
        }

        DisposalService& DisposalService::getInstance() {
            DisposalService::m_singletonMutex->lock();
            {
                if (DisposalService::m_singleton == NULL) {
                    DisposalService::m_singleton = new DisposalService();

                    // ConditionFactory, ConcurrencyFactory and MutexFactory need special handling.
                    DisposalService::m_singleton->addDisposableForFinalRemoval(&ConditionFactory::getInstance());
                    DisposalService::m_singleton->addDisposableForFinalRemoval(&ConcurrencyFactory::getInstance());
                    DisposalService::m_singleton->addDisposableForFinalRemoval(&MutexFactory::getInstance());
                }
            }
            DisposalService::m_singletonMutex->unlock();

            return *m_singleton;
        }

        void DisposalService::cleanUpImmediately() {
            m_queueCondition->lock();
            {
                // Wake awaiting threads.
                m_queueCondition->wakeAll();
            }
            m_queueCondition->unlock();
        }

        void DisposalService::cleanUpFinally() {
            m_finalRemovalMutex->lock();
            {
                deque<Disposable*>::iterator it;

                clog << "Cleaning up regular removal queue... ";
                // Clean up regular removal queue.
                it = m_queueForRegularRemoval.begin();
                while (it != m_queueForRegularRemoval.end()) {
                    Disposable *disposable = (*it++);
                    clog << disposable << " ";
                    HESPERIA_CORE_FREE_POINTER(disposable);
                }
                m_queueForRegularRemoval.clear();
                clog << "done." << endl;

                clog << "Cleaning up final removal queue... ";
                // Clean up regular removal queue.
                it = m_queueForFinalRemoval.begin();
                while (it != m_queueForFinalRemoval.end()) {
                    Disposable *disposable = (*it++);
                    clog << disposable << " ";
                    HESPERIA_CORE_FREE_POINTER(disposable);
                }
                m_queueForFinalRemoval.clear();
                clog << "done." << endl;
            }
            m_finalRemovalMutex->unlock();
        }

        void DisposalService::addDisposableForRegularRemoval(Disposable *d) {
            if (d != NULL) {
                m_queueCondition->lock();
                {
                    // Enter new data.
                    m_queueMutex->lock();
                    m_queueForRegularRemoval.push_back(d);
                    m_queueMutex->unlock();

                    // Wake awaiting threads.
                    m_queueCondition->wakeAll();
                }
                m_queueCondition->unlock();
            }
        }

        void DisposalService::addDisposableForFinalRemoval(Disposable *d) {
            if (d != NULL) {
                // Enter new data.
                m_queueForFinalRemoval.push_back(d);
            }
        }

        DisposalService::QueueCleaner::QueueCleaner(Condition &condition, Mutex &finalRemovalMutex, Mutex &mutex, deque<Disposable*> &queue) :
                m_queueCondition(condition),
                m_finalRemovalMutex(finalRemovalMutex),
                m_queueMutex(mutex),
                m_queue(queue),
                m_threadStateMutex(NULL),
                m_threadState(false) {
            m_threadStateMutex = MutexFactory::getInstance().createMutex();
            if (m_threadStateMutex == NULL) {
                stringstream s;
                s << "Error while creating mutex at " << __FILE__ << ": " << __LINE__;
                throw s.str();
            }
        }

        DisposalService::QueueCleaner::~QueueCleaner() {
            if (m_threadStateMutex != NULL) {
                delete m_threadStateMutex;
                m_threadStateMutex = NULL;
            }
        }

        void DisposalService::QueueCleaner::run() {
            while (isRunning()) {
                m_queueCondition.lock();
                m_queueCondition.waitOnSignal();
                m_queueCondition.unlock();

                // Delay removal.
                ConcurrencyFactory::getInstance().usleep(1000);

                if (isRunning()) {
                    uint32_t numberOfEntries = 0;

                    // Determine the amount of current entries.
                    m_queueMutex.lock();
                    {
                        numberOfEntries = static_cast<uint32_t>(m_queue.size());
                    }
                    m_queueMutex.unlock();

                    if (numberOfEntries > 0) {
                        // Lock final removal method.
                        m_finalRemovalMutex.lock();

                        // Read all entries and clean up.
                        Disposable *disposable = NULL;
                        for (uint32_t i = 0; i < numberOfEntries; i++) {
                            // Acquire next entry.
                            m_queueMutex.lock();
                            {
                                disposable = m_queue.front();
                            }
                            m_queueMutex.unlock();

                            // Remove entry.
//                            clog << "(DisposalService) Removing: " << disposable << endl;
                            HESPERIA_CORE_DELETE_POINTER(disposable);

                            // Delay removal.
                            ConcurrencyFactory::getInstance().usleep(5);

                            // Remove processed entry.
                            m_queueMutex.lock();
                            {
                                m_queue.pop_front();
                            }
                            m_queueMutex.unlock();
                        }

                        m_finalRemovalMutex.unlock();
                    }
                }
            }
        }

        void DisposalService::QueueCleaner::setRunning(const bool &b) {
            m_threadStateMutex->lock();
            {
                m_threadState = b;
            }
            m_threadStateMutex->unlock();
        }

        bool DisposalService::QueueCleaner::isRunning() {
            bool retVal = false;
            m_threadStateMutex->lock();
            {
                retVal = m_threadState;
            }
            m_threadStateMutex->unlock();

            return retVal;
        }

    }
} // core::wrapper
