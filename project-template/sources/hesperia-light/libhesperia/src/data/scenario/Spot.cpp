/*
 * Copyright (c) Christian Berger and Bernhard Rumpe, Rheinisch-Westfaelische Technische Hochschule Aachen, Germany.
 *
 * The Hesperia Framework.
 */

#include <sstream>

#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"
#include "hesperia/data/scenario/Spot.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace core::base;

            Spot::Spot() :
                    m_id(0),
                    m_firstVertex(),
                    m_secondVertex() {
            }

            Spot::Spot(const Spot &obj) :
                    SerializableData(),
                    m_id(obj.getID()),
                    m_firstVertex(obj.getFirstVertex()),
                    m_secondVertex(obj.getSecondVertex()) {}

            Spot::~Spot() {}

            Spot& Spot::operator=(const Spot &obj) {
                setID(obj.getID());
                setFirstVertex(obj.getFirstVertex());
                setSecondVertex(obj.getSecondVertex());
                return (*this);
            }

            void Spot::accept(ScenarioVisitor &visitor) {
                visitor.visit(*this);

                m_firstVertex.accept(visitor);
                m_secondVertex.accept(visitor);
            }

            uint32_t Spot::getID() const {
                return m_id;
            }

            void Spot::setID(const uint32_t &id) {
                m_id = id;
            }

            const Vertex3& Spot::getFirstVertex() const {
                return m_firstVertex;
            }

            void Spot::setFirstVertex(const Vertex3 &v) {
                m_firstVertex = v;
            }

            const Vertex3& Spot::getSecondVertex() const {
                return m_secondVertex;
            }

            void Spot::setSecondVertex(const Vertex3 &v) {
                m_secondVertex = v;
            }

            const string Spot::toString() const {
                stringstream s;
                s << "ID: " << getID() << " @ " << m_firstVertex.toString() << "/" << m_secondVertex.toString();
                return s.str();
            }

            ostream& Spot::operator<<(ostream &out) const {
                SerializationFactory sf;

                Serializer &s = sf.getSerializer(out);

                s.write(CRC32 < HESPERIA_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                        getID());

                s.write(CRC32 < HESPERIA_CORE_STRINGLITERAL5('f', 'i', 'r', 's', 't') >::RESULT,
                        getFirstVertex());

                s.write(CRC32 < HESPERIA_CORE_STRINGLITERAL6('s', 'e', 'c', 'o', 'n', 'd') >::RESULT,
                        getSecondVertex());

                return out;
            }

            istream& Spot::operator>>(istream &in) {
                SerializationFactory sf;

                Deserializer &d = sf.getDeserializer(in);

                d.read(CRC32 < HESPERIA_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                       m_id);

                d.read(CRC32 < HESPERIA_CORE_STRINGLITERAL5('f', 'i', 'r', 's', 't') >::RESULT,
                       m_firstVertex);

                d.read(CRC32 < HESPERIA_CORE_STRINGLITERAL6('s', 'e', 'c', 'o', 'n', 'd') >::RESULT,
                       m_secondVertex);

                return in;
            }

        }
    }
} // hesperia::data::scenario
