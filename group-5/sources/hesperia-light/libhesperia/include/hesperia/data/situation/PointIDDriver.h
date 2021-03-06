/*
 * Copyright (c) Christian Berger and Bernhard Rumpe, Rheinisch-Westfaelische Technische Hochschule Aachen, Germany.
 *
 * The Hesperia Framework.
 */

#ifndef HESPERIA_CORE_DATA_SITUATION_POINTIDDRIVER_H_
#define HESPERIA_CORE_DATA_SITUATION_POINTIDDRIVER_H_

#include <vector>

#include "hesperia/data/situation/Behavior.h"
#include "hesperia/data/situation/PointID.h"
#include "hesperia/data/situation/StartType.h"
#include "hesperia/data/situation/StopType.h"

namespace hesperia {
    namespace data {
        namespace situation {

            using namespace std;

            /**
             * This class represents a point ID driver.
             */
            class HESPERIA_API PointIDDriver : public Behavior {
                public:
                    PointIDDriver();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    PointIDDriver(const PointIDDriver &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    PointIDDriver& operator=(const PointIDDriver &obj);

                    virtual ~PointIDDriver();

                    virtual void accept(SituationVisitor &visitor);

                    /**
                     * This method returns the starttype of this point-ID-driver.
                     *
                     * @return Starttype of this point-ID-driver.
                     */
                    StartType* getStartType() const;

                    /**
                     * This method sets the point-ID-driver's starttype.
                     *
                     * @param st Starttype of this point-ID-driver.
                     */
                    void setStartType(StartType *st);

                    /**
                     * This method returns the stoptype of this point-ID-driver.
                     *
                     * @return Stoptype of this point-ID-driver.
                     */
                    StopType* getStopType() const;

                    /**
                     * This method sets the point-ID-driver's stoptype.
                     *
                     * @param st Stoptype of this point-ID-driver.
                     */
                    void setStopType(StopType *st);

                    /**
                     * This method returns the constant acceleration.
                     *
                     * @return Constant acceleration.
                     */
                    double getConstantAcceleration() const;

                    /**
                     * This method sets the constant acceleration.
                     *
                     * @param a Constant acceleration.
                     */
                    void setConstantAcceleration(const double &a);

                    /**
                     * This method returns the constant velocity.
                     *
                     * @return Constant velocity.
                     */
                    double getConstantVelocity() const;

                    /**
                     * This method sets the constant velocity.
                     *
                     * @param v Constant velocity.
                     */
                    void setConstantVelocity(const double &v);

                    /**
                     * This method adds a PointID.
                     *
                     * @param p PointID to add.
                     */
                    void addPointID(const PointID &p);

                    /**
                     * This method returns the list of PointIDs.
                     *
                     * @return List of PointIDs.
                     */
                    vector<PointID> getListOfPointIDs() const;

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    StartType *m_startType;
                    StopType *m_stopType;
                    double m_constantAcceleration;
                    double m_constantVelocity;
                    vector<PointID> m_listOfPointIDs;

                    /**
                     * This method creates a deep copy.
                     *
                     * @param obj Object of another instance of this class.
                     */
                    void deepCopy(const PointIDDriver &obj);

                    /**
                     * This method clean's up the data.
                     */
                    void cleanUp();
            };

        }
    }
} // core::data::situation

#endif /*HESPERIA_CORE_DATA_SITUATION_POINTIDDRIVER_H_*/
