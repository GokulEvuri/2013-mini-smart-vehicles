/*
 * Copyright (c) Christian Berger.
 *
 * The Hesperia Framework.
 */

#include <cmath>
#include <iomanip>

#include "hesperia/data/Constants.h"

#include "LinearBicycleModel.h"

namespace vehicle {

    using namespace core::base;
    using namespace core::data;
    using namespace hesperia::data::environment;

    LinearBicycleModel::LinearBicycleModel(const KeyValueConfiguration &kvc) :
        m_minimumTurningRadius(0),
        m_vehicleMass(0),
        m_adherenceCoefficient(0),
        m_idleForce(0),
        m_Ksteering(0),
        m_maximumSteeringRate(0),
        m_Kthrottle(0),
        m_tauBrake(0),
        m_KstaticBrake(0),
        m_KdynamicBrake(0),
        m_steeringRate(0.0),
        m_motorForce(0.0),
        m_brakeForce(0.0),
        m_adherenceForce(0.0),
        m_turningCurvature(0.0),
        m_deltaHeading(0.0),
        m_vehicleDesiredRotationalEffort(0.0),
        m_vehicleDesiredLinearEffortX(0.0),
        m_vehicleDesiredResistiveEffortX(0),
        m_vehicleRotationalEffort(0.0),
        m_vehicleLinearEffortX(0.0),
        m_vehicleResistiveEffortX(0),
        m_speed(0),
        m_speedOld(0),
        m_heading(0),
        m_direction(+1), //driving direction: +1: forwards, -1: backwards
        m_previousTime(),
        m_oldPosition(),
        m_orientation(1,0,0),
        m_oldAcceleration(0,0,0),
        m_vehicleData()
    {
        m_minimumTurningRadius = kvc.getValue<double>("Vehicle.LinearBicycleModel.minimumTurningRadius");
        m_vehicleMass = kvc.getValue<double>("Vehicle.LinearBicycleModel.vehicleMass");
        m_adherenceCoefficient = kvc.getValue<double>("Vehicle.LinearBicycleModel.adherenceCoefficient");
        m_idleForce = kvc.getValue<double>("Vehicle.LinearBicycleModel.idleForce");
        m_Ksteering = kvc.getValue<double>("Vehicle.LinearBicycleModel.Ksteering");
        m_maximumSteeringRate = kvc.getValue<double>("Vehicle.LinearBicycleModel.maximumSteeringRate");
        m_Kthrottle = kvc.getValue<double>("Vehicle.LinearBicycleModel.Kthrottle");
        m_tauBrake = kvc.getValue<double>("Vehicle.LinearBicycleModel.tauBrake");
        m_KstaticBrake = kvc.getValue<double>("Vehicle.LinearBicycleModel.KstaticBrake");
        m_KdynamicBrake = kvc.getValue<double>("Vehicle.LinearBicycleModel.KdynamicBrake");

        // Stop the vehicle.
        m_vehicleDesiredResistiveEffortX = (m_idleForce/(m_KstaticBrake * m_tauBrake)) + 0.1;

        // Setup initial position.
        m_oldPosition = Point3(kvc.getValue<double>("Vehicle.posX"), kvc.getValue<double>("Vehicle.posY"), 0);
        m_heading = hesperia::data::Constants::DEG2RAD * kvc.getValue<double>("Vehicle.headingDEG");
    }

    LinearBicycleModel::~LinearBicycleModel() {}

    void LinearBicycleModel::accelerate(const double& value)
    {
        m_vehicleDesiredLinearEffortX = value;
    }

    void LinearBicycleModel::brake(const double& value)
    {
        m_vehicleDesiredResistiveEffortX = value;
    }

    void LinearBicycleModel::steer(const double &value)
    {
        m_vehicleDesiredRotationalEffort = value;
    }

    VehicleData LinearBicycleModel::getVehicleData() const {
        return m_vehicleData;
    }

    EgoState LinearBicycleModel::computeEgoState() {
        TimeStamp currentTime;
        double timeStep = (currentTime.toMicroseconds() - m_previousTime.toMicroseconds()) / (1000.0 * 1000.0);

        // Decide driving direction: +1: forwards, -1: backwards
        // Change only direction if m_speed is nearly zero.
        int32_t signLinearEffortX = (m_vehicleDesiredLinearEffortX < 0) ? -1 : +1;
        if (m_speed < 5e-3) {
            m_direction = signLinearEffortX;
        }
        cout << "Driving direction: " << ( (m_direction < 0) ? "backwards" : "forwards") << endl;

        // Steering.
        m_steeringRate = m_Ksteering * (m_vehicleDesiredRotationalEffort - m_vehicleRotationalEffort);
        if (m_steeringRate > m_maximumSteeringRate) {
            m_steeringRate = m_maximumSteeringRate;
        }
        else if (m_steeringRate < (-1 * m_maximumSteeringRate)) {
            m_steeringRate = -1 * m_maximumSteeringRate;
        }
        m_vehicleRotationalEffort += m_steeringRate * timeStep;
        m_turningCurvature = -1 * m_vehicleRotationalEffort / 100.0 / m_minimumTurningRadius;

        // Acceleration.
        m_vehicleLinearEffortX = fabs(m_vehicleDesiredLinearEffortX);
        m_motorForce = m_Kthrottle * m_vehicleLinearEffortX + m_idleForce;

        // Brake.
        if (m_vehicleDesiredResistiveEffortX > 6) {
            m_vehicleDesiredResistiveEffortX = 6.0;
        }
        else if (m_vehicleDesiredResistiveEffortX < -6) {
            m_vehicleDesiredResistiveEffortX = -6.0;
        }
        m_vehicleResistiveEffortX += m_tauBrake * (fabs(m_vehicleDesiredResistiveEffortX) - m_vehicleResistiveEffortX);
        
        // Calculate movement speed.
        if (m_speed < 5e-3) {
            m_brakeForce = m_KstaticBrake * m_vehicleResistiveEffortX;

            if (m_brakeForce > m_motorForce) {
                m_brakeForce = m_motorForce + 1.0;
            }
        }
        else {
            m_brakeForce = m_KdynamicBrake * m_vehicleResistiveEffortX;
        }
        m_adherenceForce = m_adherenceCoefficient * m_speed * m_speed;
        m_speed += (m_motorForce - m_brakeForce - m_adherenceForce) / m_vehicleMass * timeStep;

        // Stop car if speed is small enough.
        if (fabs(m_speed) < 5e-3) {
            m_speed = 0;
        }

        m_deltaHeading = m_turningCurvature * m_speed * timeStep * m_direction;

        m_orientation = Point3(1, 0, 0);
        m_orientation.rotateZ(m_heading + m_deltaHeading/2.0);
        m_orientation.normalize();

        double x = cos(m_heading + m_deltaHeading/2.0) * m_speed * timeStep * m_direction;
        double y = sin(m_heading + m_deltaHeading/2.0) * m_speed * timeStep * m_direction;

        m_heading += m_deltaHeading;
        m_heading = fmod(m_heading, 2 * hesperia::data::Constants::PI);

        Point3 position(m_oldPosition.getX() + x, m_oldPosition.getY() + y, 0);
        double relDrivenPath = (position - m_oldPosition).lengthXY();
        m_oldPosition = position;

        // Set velocity.
        Point3 velocity(cos(m_heading + m_deltaHeading/2.0) * m_speed * m_direction,
                        sin(m_heading + m_deltaHeading/2.0) * m_speed * m_direction,
                        0);

        Point3 acceleration;

        // Update internal data.
        m_vehicleData.setPosition(position);
        m_vehicleData.setVelocity(velocity);
        m_vehicleData.setSpeed(m_speed * m_direction);
        m_vehicleData.setV_log(0);
        m_vehicleData.setV_batt(0);
        // For fake :-)
        m_vehicleData.setTemp(19.5 + cos(m_heading + m_deltaHeading/2.0));
        m_vehicleData.setRelTraveledPath(relDrivenPath);
        m_vehicleData.setAbsTraveledPath(m_vehicleData.getAbsTraveledPath() + relDrivenPath);

        m_previousTime = currentTime;
        return EgoState(position, m_orientation, velocity, acceleration);
    }
}
