/*
 * Copyright (c) Christian Berger.
 *
 * The Hesperia Framework.
 */

#include <sstream>

#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"
#include "hesperia/data/control/VehicleControl.h"

namespace hesperia {
    namespace data {
        namespace control {

            using namespace std;

            using namespace core::base;

            VehicleControl::VehicleControl() :
                    m_speed(0),
                    m_acceleration(0),
                    m_steeringWheelAngle(0),
                    m_brakeLights(false),
                    m_flashingLightsLeft(false),
                    m_flashingLightsRight(false)
            {}

            VehicleControl::VehicleControl(const VehicleControl &obj) :
                    m_speed(obj.getSpeed()),
                    m_acceleration(obj.getAcceleration()),
                    m_steeringWheelAngle(obj.getSteeringWheelAngle()),
                    m_brakeLights(obj.getBrakeLights()),
                    m_flashingLightsLeft(obj.getLeftFlashingLights()),
                    m_flashingLightsRight(obj.getRightFlashingLights())
            {}

            VehicleControl::~VehicleControl() {}

            VehicleControl& VehicleControl::operator=(const VehicleControl &obj) {
                setSpeed(obj.getSpeed());
                setAcceleration(obj.getAcceleration());
                setSteeringWheelAngle(obj.getSteeringWheelAngle());
                setBrakeLights(obj.getBrakeLights());
                setLeftFlashingLights(obj.getLeftFlashingLights());
                setRightFlashingLights(obj.getRightFlashingLights());

                return (*this);
            }

            double VehicleControl::getSpeed() const {
                return m_speed;
            }

            void VehicleControl::setSpeed(const double &s) {
                m_speed = s;
            }

            double VehicleControl::getAcceleration() const {
                return m_acceleration;
            }

            void VehicleControl::setAcceleration(const double &s) {
                m_acceleration = s;
            }

            double VehicleControl::getSteeringWheelAngle() const {
                return m_steeringWheelAngle;
            }

            void VehicleControl::setSteeringWheelAngle(const double &a) {
                m_steeringWheelAngle = a;
            }

            bool VehicleControl::getBrakeLights() const {
                return m_brakeLights;            
            } 

            void VehicleControl::setBrakeLights(const bool &on) {
                m_brakeLights = on;
            }

            bool VehicleControl::getLeftFlashingLights() const {
                return m_flashingLightsLeft;
            }

            void VehicleControl::setLeftFlashingLights(const bool &on) {
                m_flashingLightsLeft = on;
            }

            bool VehicleControl::getRightFlashingLights() const {
                return m_flashingLightsRight;
            }

            void VehicleControl::setRightFlashingLights(const bool &on) {
                m_flashingLightsRight = on;
            }

            const string VehicleControl::toString() const {
                stringstream sstr;
                sstr << "Speed: " << getSpeed() << ", acceleration: " << getAcceleration() << ", steering wheel angle: " << getSteeringWheelAngle() << ", brake lights: " << getBrakeLights() << ", flashingLightsLeft: " << getLeftFlashingLights() << ", flashingLightsRight: " << getRightFlashingLights();
                return sstr.str();
            }

            ostream& VehicleControl::operator<<(ostream &out) const {
                SerializationFactory sf;

                Serializer &s = sf.getSerializer(out);

                s.write(CRC32 < HESPERIA_CORE_STRINGLITERAL5('s', 'p', 'e', 'e', 'd') >::RESULT,
                        m_speed);

                s.write(CRC32 < HESPERIA_CORE_STRINGLITERAL5('a', 'c', 'c', 'e', 'l') >::RESULT,
                        m_acceleration);

                s.write(CRC32 < HESPERIA_CORE_STRINGLITERAL5('s', 't', 'e', 'e', 'r') >::RESULT,
                        m_steeringWheelAngle);

                s.write(CRC32 < HESPERIA_CORE_STRINGLITERAL5('b', 'r', 'l', 'i', 't') >::RESULT,
                        m_brakeLights);

                s.write(CRC32 < HESPERIA_CORE_STRINGLITERAL4('l', 'e', 'f', 't') >::RESULT,
                        m_flashingLightsLeft);

                s.write(CRC32 < HESPERIA_CORE_STRINGLITERAL5('r', 'i', 'g', 'h', 't') >::RESULT,
                        m_flashingLightsRight);

                return out;
            }

            istream& VehicleControl::operator>>(istream &in) {
                SerializationFactory sf;

                Deserializer &d = sf.getDeserializer(in);

                d.read(CRC32 < HESPERIA_CORE_STRINGLITERAL5('s', 'p', 'e', 'e', 'd') >::RESULT,
                       m_speed);

                d.read(CRC32 < HESPERIA_CORE_STRINGLITERAL5('a', 'c', 'c', 'e', 'l') >::RESULT,
                       m_acceleration);

                d.read(CRC32 < HESPERIA_CORE_STRINGLITERAL5('s', 't', 'e', 'e', 'r') >::RESULT,
                       m_steeringWheelAngle);

                d.read(CRC32 < HESPERIA_CORE_STRINGLITERAL5('b', 'r', 'l', 'i', 't') >::RESULT,
                        m_brakeLights);

                d.read(CRC32 < HESPERIA_CORE_STRINGLITERAL4('l', 'e', 'f', 't') >::RESULT,
                        m_flashingLightsLeft);

                d.read(CRC32 < HESPERIA_CORE_STRINGLITERAL5('r', 'i', 'g', 'h', 't') >::RESULT,
                        m_flashingLightsRight);

                return in;
            }

        }
    }
} // core::data::control
