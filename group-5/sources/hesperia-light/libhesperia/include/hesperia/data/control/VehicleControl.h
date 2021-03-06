/*
 * Copyright (c) Christian Berger.
 *
 * The Hesperia Framework.
 */

#ifndef HESPERIA_DATA_CONTROL_VEHICLECONTROL_H_
#define HESPERIA_DATA_CONTROL_VEHICLECONTROL_H_

#include <string>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"

#include "core/data/SerializableData.h"

namespace hesperia {
    namespace data {
        namespace control {

            /**
             * This class represents commands to control the car.
             */
            class HESPERIA_API VehicleControl : public core::data::SerializableData {
                public:
                    VehicleControl();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    VehicleControl(const VehicleControl &obj);

                    virtual ~VehicleControl();

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    VehicleControl& operator=(const VehicleControl &obj);

                    /**
                     * This method returns the speed.
                     *
                     * @return Speed.
                     */
                    double getSpeed() const;

                    /**
                     * This method sets the speed.
                     *
                     * @param s Speed.
                     */
                    void setSpeed(const double &s);

                    /**
                     * This method returns the acceleration.
                     *
                     * @return Acceleration.
                     */
                    double getAcceleration() const;

                    /**
                     * This method sets the acceleration.
                     *
                     * @param a Acceleration.
                     */
                    void setAcceleration(const double &a);

                    /**
                     * This method returns the steering wheel angle in RAD.
                     *
                     * @return Steering wheel angle.
                     */
                    double getSteeringWheelAngle() const;

                    /**
                     * This method sets the steering force.
                     *
                     * @param a Steering wheel angle.
                     */
                    void setSteeringWheelAngle(const double &f);

                    /**
                     * This method returns the status of the brake lights.
                     *
                     * @return true if the brake lights are on.
                     */
                    bool getBrakeLights() const;

                    /**
                     * This method turns the brake lights on/off.
                     *
                     * @param on Set to true to turn on the brake lights.
                     */
                    void setBrakeLights(const bool &on);

                    /**
                     * This method returns the status of the left flashing lights.
                     *
                     * @return true if the left flashing lights are on.
                     */
                    bool getLeftFlashingLights() const;

                    /**
                     * This method turns the left flashing lights on/off.
                     *
                     * @param on Set to true to turn on the left flashing lights.
                     */
                    void setLeftFlashingLights(const bool &on);

                    /**
                     * This method returns the status of the right flashing lights.
                     *
                     * @return true if the right flashing lights are on.
                     */
                    bool getRightFlashingLights() const;

                    /**
                     * This method turns the right flashing lights on/off.
                     *
                     * @param on Set to true to turn on the right flashing lights.
                     */
                    void setRightFlashingLights(const bool &on);

                    virtual std::ostream& operator<<(std::ostream &out) const;
                    virtual std::istream& operator>>(std::istream &in);

                    virtual const std::string toString() const;

                private:
                    double m_speed;
                    double m_acceleration;
                    double m_steeringWheelAngle;
                    bool m_brakeLights;
                    bool m_flashingLightsLeft;
                    bool m_flashingLightsRight;
            };
        }
    }
} // hesperia::data::control

#endif /*HESPERIA_DATA_CONTROL_VEHICLECONTROL_H_*/
