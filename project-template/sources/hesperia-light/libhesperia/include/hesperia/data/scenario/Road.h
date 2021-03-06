/*
 * Copyright (c) Christian Berger and Bernhard Rumpe, Rheinisch-Westfaelische Technische Hochschule Aachen, Germany.
 *
 * The Hesperia Framework.
 */

#ifndef HESPERIA_CORE_DATA_SCENARIO_ROAD_H_
#define HESPERIA_CORE_DATA_SCENARIO_ROAD_H_

#include <string>
#include <vector>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"

#include "core/data/SerializableData.h"
#include "hesperia/data/scenario/Lane.h"
#include "hesperia/data/scenario/ScenarioNode.h"
#include "hesperia/data/scenario/ScenarioVisitor.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;

            /** Prevent circular dependencies. */
            class Layer;

            /**
             * This class represents a road.
             */
            class HESPERIA_API Road : public core::data::SerializableData, public ScenarioNode {
                public:
                    Road();

                    virtual ~Road();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    Road(const Road &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    Road& operator=(const Road &obj);

                    virtual void accept(scenario::ScenarioVisitor &visitor);

                    /**
                     * This method returns the ID.
                     *
                     * @return ID.
                     */
                    uint32_t getID() const;

                    /**
                     * This method sets the ID.
                     *
                     * @param id ID to be set.
                     */
                    void setID(const uint32_t &id);

                    /**
                     * This method returns the road's name.
                     *
                     * @return Road's name.
                     */
                    const string getName() const;

                    /**
                     * This method set the road's name.
                     *
                     * @param name The road's name.
                     */
                    void setName(const string &name);

                    /**
                     * This method returns the list of lanes.
                     *
                     * @return List of lanes.
                     */
                    const vector<Lane>& getListOfLanes() const;

                    /**
                     * This method adds a lane.
                     *
                     * @param l Lane to be added.
                     */
                    void addLane(const Lane &l);

                    /**
                     * This method sets the layer to which this road belongs to.
                     *
                     * @param l Layer.
                     */
                    void setLayer(const Layer *l);

                    /**
                     * This method returns the layer to which this road belongs to.
                     *
                     * @return Layer.
                     */
                    const Layer* getLayer() const;

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    uint32_t m_id;
                    string m_name;
                    const Layer *m_layer;
                    vector<Lane> m_listOfLanes;

                    /**
                     * This method creates a deep copy.
                     *
                     * @param obj Object of another instance of this class.
                     */
                    void deepCopy(const Road &obj);
            };

        }
    }
} // hesperia::data::scenario

#endif /*HESPERIA_CORE_DATA_SCENARIO_ROAD_H_*/
