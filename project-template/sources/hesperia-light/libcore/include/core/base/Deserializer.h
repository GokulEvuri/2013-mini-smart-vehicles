/*
 * Copyright (c) Christian Berger and Bernhard Rumpe, Rheinisch-Westfaelische Technische Hochschule Aachen, Germany.
 *
 * The Hesperia Framework.
 */

#ifndef HESPERIA_CORE_BASE_DESERIALIZER_H_
#define HESPERIA_CORE_BASE_DESERIALIZER_H_

#include <string>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"

namespace core {
    namespace base {

        using namespace std;

        class Serializable;

        /**
         * This class is the interface for any deserializer.
         *
         * @See Serializable
         */
        class HESPERIA_API Deserializer {
            public:
                Deserializer();

                virtual ~Deserializer();

                /**
                 * This method deserializes a Serializable.
                 *
                 * @param id Identifier for the s to be deserialized.
                 * @param s Serializable to be deserialized.
                 */
                virtual void read(const uint32_t id, Serializable &s) = 0;

                /**
                 * This method deserializes a bool.
                 *
                 * @param id Identifier for the b to be deserialized.
                 * @param b Bool to be deserialized.
                 */
                virtual void read(const uint32_t id, bool &b) = 0;

                /**
                 * This method deserializes a char.
                 *
                 * @param id Identifier for the c to be deserialized.
                 * @param c Char to be deserialized.
                 */
                virtual void read(const uint32_t id, char &c) = 0;

                /**
                 * This method deserializes an unsigned char.
                 *
                 * @param id Identifier for the uc to be deserialized.
                 * @param uc Unsigned char to be deserialized.
                 */
                virtual void read(const uint32_t id, unsigned char &uc) = 0;

                /**
                 * This method deserializes an int.
                 *
                 * @param id Identifier for the i to be deserialized.
                 * @param i Int to be deserialized.
                 */
                virtual void read(const uint32_t id, int32_t &i) = 0;

                /**
                 * This method deserializes an uint32_t.
                 *
                 * @param id Identifier for the ui to be deserialized.
                 * @param ui Unsigned int32_t to be deserialized.
                 */
                virtual void read(const uint32_t id, uint32_t &ui) = 0;

                /**
                 * This method deserializes a float.
                 *
                 * @param id Identifier for the f to be deserialized.
                 * @param f Float to be deserialized.
                 */
                virtual void read(const uint32_t id, float &f) = 0;

                /**
                 * This method deserializes a double.
                 *
                 * @param id Identifier for the d to be deserialized.
                 * @param d Double to be deserialized.
                 */
                virtual void read(const uint32_t id, double &d) = 0;

                /**
                 * This method deserializes a string.
                 *
                 * @param id Identifier for the s to be deserialized.
                 * @param s String to be deserialized.
                 */
                virtual void read(const uint32_t id, string &s) = 0;

                /**
                 * This method deserializes undefined data of length size.
                 *
                 * @param id Identifier for the data to be deserialized.
                 * @param data Data to be deserialized.
                 * @param size Length of the data to be deserialized.
                 */
                virtual void read(const uint32_t id, void *data, uint32_t size) = 0;

            public:
                /**
                 * This method converts a float from
                 * network byte order to host byte order.
                 *
                 * @param f float to be converted.
                 * @return f in HBO.
                 */
                static float ntohf(float f);

                /**
                 * This method converts a double from
                 * network byte order to host byte order.
                 *
                 * @param d double to be converted.
                 * @return d in HBO.
                 */
                static double ntohd(double d);
        };

    }
} // core::base

#endif /*HESPERIA_CORE_BASE_DESERIALIZER_H_*/
