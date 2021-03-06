/*
 * OpenDaVINCI.
 *
 * This software is open source. Please see COPYING and AUTHORS for further information.
 */

#ifndef OPENDAVINCI_CORE_BASE_KEYVALUECONFIGURATION_H_
#define OPENDAVINCI_CORE_BASE_KEYVALUECONFIGURATION_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include "core/exceptions/Exceptions.h"
#include "core/wrapper/StringComparator.h"

namespace core {
    namespace base {

        using namespace std;

        /**
         * This class is the key/value-based configuration.
         * It reads configuration data using istream:
         *
         * @code
         * KeyValueConfiguration kvc;
         * istream i = ...;
         * i >> kvc;
         *
         * @endcode
         *
         * Format for the configuration data:
         * # Comment
         * key=value
         * #key=value Disabled key.
         * anotherKey=anotherValue # Commented key-value-pair.
         */
        class OPENDAVINCI_API KeyValueConfiguration {
            public:
                KeyValueConfiguration();

                /**
                 * Copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                KeyValueConfiguration(const KeyValueConfiguration &obj);

                virtual ~KeyValueConfiguration();

                /**
                 * Assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                KeyValueConfiguration& operator=(const KeyValueConfiguration &obj);

                /**
                 * This method is used to write configuration data using iostreams.
                 * It is necessary to allow human readable data on disks.
                 *
                 * @param out Stream to which the configuration data will be written.
                 * @return Stream.
                 */
                ostream& operator<<(ostream &out) const;

                /**
                 * This method is used to read configuration data using iostreams.
                 * It is necessary to allow human readable data on disks.
                 *
                 * @param in Stream from which the configuration data will be read.
                 * @return Stream.
                 */
                istream& operator>>(istream &in);

                /**
                 * This method returns a configuration value
                 *
                 * @code
                 * KeyValueConfiguration kvc;
                 * ...
                 * T t = kvc.getValue<T>();
                 * @endcode
                 *
                 * @param key Key for retrieving the value.
                 * @return Value.
                 * @throws ValueForKeyNotFoundException is the value for the given key does not exist.
                 */
                template<class T>
                inline T getValue(string key) const throw (exceptions::ValueForKeyNotFoundException) {
                    string stringValue(getValueFor(key));
                    if (stringValue == "") {
                        stringstream s;
                        s << "Value for key '" << key << "' not found.";
                        errno = 0;
                        OPENDAVINCI_CORE_THROW_EXCEPTION(ValueForKeyNotFoundException, s.str());
                    }
                    stringstream s(stringValue);
                    T value;
                    s >> value;
                    return value;
                };

                /**
                 * This method returns a subset of this key/value-configuration, i.e.
                 * all key/value-pairs starting with "section".
                 *
                 * @param section Build subset key/value-configuration for this section.
                 * @return (Empty) subset key/value-configuration.
                 */
                KeyValueConfiguration getSubsetForSection(const string &section) const;

                /**
                 * This method returns a vector of keys.
                 *
                 * @return Vector of contained keys.
                 */
                const vector<string> getListOfKeys() const;

            private:
                map<string, string, wrapper::StringComparator> m_keyValueConfiguration;

                /**
                 * This method returns the string for given key or ""
                 * if the key does not exist.
                 *
                 * @param key Key for which the value is queried for.
                 * @return value for the key or "".
                 */
                string getValueFor(string key) const;
        };

    }
} // core::base

namespace std {
    // The following methods are declarations for convenient usage.
    OPENDAVINCI_API ostream& operator<<(ostream& out, const core::base::KeyValueConfiguration &configuration);
    OPENDAVINCI_API istream& operator>>(istream& in, core::base::KeyValueConfiguration &configuration);
}

#endif /*OPENDAVINCI_CORE_BASE_KEYVALUECONFIGURATION_H_*/
