/*
 * Copyright (c) Christian Berger and Bernhard Rumpe, Rheinisch-Westfaelische Technische Hochschule Aachen, Germany.
 *
 * The Hesperia Framework.
 */

#ifndef HESPERIA_CORE_WRAPPER_BERKELEYDB_BERKELEYDBKEYVALUEDATABASEINMEMORY_H_
#define HESPERIA_CORE_WRAPPER_BERKELEYDB_BERKELEYDBKEYVALUEDATABASEINMEMORY_H_

#include <db.h>

#ifndef DB_LOG_INMEMORY
        #define DB_LOG_INMEMORY DB_LOG_IN_MEMORY
#endif

#include "core/wrapper/BerkeleyDB/BerkeleyDBKeyValueDatabase.h"

namespace core {
    namespace wrapper {
        namespace BerkeleyDB {

            // Forward declaration to prevent circular dependencies.
            class BerkeleyDBKeyValueDatabaseFactory;

            /**
             * This class implements a key/value database held only in memory
             * using the BerkeleyDB.
             *
             * @See KeyValueDatabaseFactory
             */
            class BerkeleyDBKeyValueDatabaseInMemory : public BerkeleyDBKeyValueDatabase {
                private:
                    friend class BerkeleyDBKeyValueDatabaseFactory;

                    BerkeleyDBKeyValueDatabaseInMemory();

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    BerkeleyDBKeyValueDatabaseInMemory(const BerkeleyDBKeyValueDatabaseInMemory &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    BerkeleyDBKeyValueDatabaseInMemory& operator=(const BerkeleyDBKeyValueDatabaseInMemory &);

                public:
                    virtual ~BerkeleyDBKeyValueDatabaseInMemory();

                private:
                    DB_ENV *m_databaseEnvironment;
                    DB *m_database;

                    virtual DB* getDatabase() const;

                    /**
                     * This method sets up the database environment.
                     */
                    void setupEnvironment();

                    /**
                     * This method sets up the database using the previously
                     * set up environment.
                     */
                    void setupDatabase();
            };

        }
    }
} // core::wrapper::BerkeleyDB

#endif /*HESPERIA_CORE_WRAPPER_BERKELEYDB_BERKELEYDBKEYVALUEDATABASEINMEMORY_H_*/
