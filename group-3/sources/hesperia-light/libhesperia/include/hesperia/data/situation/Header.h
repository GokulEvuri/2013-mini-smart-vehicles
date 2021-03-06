/*
 * Copyright (c) Christian Berger and Bernhard Rumpe, Rheinisch-Westfaelische Technische Hochschule Aachen, Germany.
 *
 * The Hesperia Framework.
 */

#ifndef HESPERIA_CORE_DATA_SITUATION_HEADER_H_
#define HESPERIA_CORE_DATA_SITUATION_HEADER_H_

#include <string>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"
#include "core/data/SerializableData.h"

#include "hesperia/data/situation/SituationNode.h"
#include "hesperia/data/situation/SituationVisitor.h"

namespace hesperia {
    namespace data {
        namespace situation {

            using namespace std;

            /**
             * This class represents the header of a scenario.
             */
            class HESPERIA_API Header : public core::data::SerializableData, public SituationNode {
                public:
                    Header();

                    virtual ~Header();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    Header(const Header &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    Header& operator=(const Header &obj);

                    virtual void accept(situation::SituationVisitor &visitor);

                    /**
                     * This method returns the situation's name.
                     *
                     * @return Situation's name.
                     */
                    const string getName() const;

                    /**
                     * This method sets the situation's name.
                     *
                     * @param name Situation's name.
                     */
                    void setName(const string &name);

                    /**
                     * This method returns the situation's version.
                     *
                     * @return Situation's version.
                     */
                    const string getVersion() const;

                    /**
                     * This method sets the situation's version.
                     *
                     * @param v Situation's version.
                     */
                    void setVersion(const string &v);

                    /**
                     * This method returns the situation's date.
                     *
                     * @return Situation's date.
                     */
                    const string getDate() const;

                    /**
                     * This method sets the situation's date.
                     *
                     * @param d Situation's date.
                     */
                    void setDate(const string &d);

                    /**
                     * This method returns the situation's scenario.
                     *
                     * @return Situation's scenario.
                     */
                    const string getScenario() const;

                    /**
                     * This method sets the situation's scenario.
                     *
                     * @param s Situation's scenario.
                     */
                    void setScenario(const string &s);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    string m_name;
                    string m_version;
                    string m_date;
                    string m_scenario;
            };

        }
    }
} // hesperia::data::situation

#endif /*HESPERIA_CORE_DATA_SITUATION_HEADER_H_*/
