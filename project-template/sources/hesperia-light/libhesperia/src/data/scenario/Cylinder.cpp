/*
 * Copyright (c) Christian Berger and Bernhard Rumpe, Rheinisch-Westfaelische Technische Hochschule Aachen, Germany.
 *
 * The Hesperia Framework.
 */

#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"
#include "hesperia/data/scenario/Cylinder.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace core::base;

            Cylinder::Cylinder() :
                    m_center(),
                    m_radius(0),
                    m_height(0),
                    m_color() {
                Shape::setType(Shape::CYLINDER);
            }

            Cylinder::Cylinder(const Cylinder &obj) :
                    Shape(obj),
                    m_center(obj.m_center),
                    m_radius(obj.m_radius),
                    m_height(obj.m_height),
                    m_color(obj.m_color) {}

            Cylinder::~Cylinder() {}

            Cylinder& Cylinder::operator=(const Cylinder &obj) {
                Shape::operator=(obj);
                setCenter(obj.getCenter());
                setRadius(obj.getRadius());
                setHeight(obj.getHeight());
                setColor(obj.getColor());
                return (*this);
            }

            void Cylinder::accept(ScenarioVisitor &visitor) {
                visitor.visit(*this);

                m_center.accept(visitor);
                m_color.accept(visitor);
            }

            const Vertex3& Cylinder::getCenter() const {
                return m_center;
            }

            void Cylinder::setCenter(const Vertex3 &c) {
                m_center = c;
            }

            double Cylinder::getRadius() const {
                return m_radius;
            }

            void Cylinder::setRadius(const double &r) {
                if (!(r > 0)) {
                    m_radius = 0.1;
                } else {
                    m_radius = r;
                }
            }

            double Cylinder::getHeight() const {
                return m_height;
            }

            void Cylinder::setHeight(const double &h) {
                m_height = h;
            }

            const Vertex3& Cylinder::getColor() const {
                return m_color;
            }

            void Cylinder::setColor(const Vertex3 &c) {
                m_color = c;
            }

            const string Cylinder::toString() const {
                stringstream s;
                s << Shape::toString() << ", Center: " << m_center.toString() << ", Radius: " << m_radius << ", Height: " << m_height << ", Color: " << m_color.toString();
                return s.str();
            }

            ostream& Cylinder::operator<<(ostream &out) const {
                // Serializer super class.
                Shape::operator<<(out);

                SerializationFactory sf;

                Serializer &s = sf.getSerializer(out);

                s.write(CRC32 < HESPERIA_CORE_STRINGLITERAL6('c', 'e', 'n', 't', 'e', 'r') >::RESULT,
                        m_center);

                s.write(CRC32 < HESPERIA_CORE_STRINGLITERAL6('r', 'a', 'd', 'i', 'u', 's') >::RESULT,
                        m_radius);

                s.write(CRC32 < HESPERIA_CORE_STRINGLITERAL6('h', 'e', 'i', 'g', 'h', 't') >::RESULT,
                        m_height);

                s.write(CRC32 < HESPERIA_CORE_STRINGLITERAL5('c', 'o', 'l', 'o', 'r') >::RESULT,
                        m_color);

                return out;
            }

            istream& Cylinder::operator>>(istream &in) {
                // Deserializer super class.
                Shape::operator>>(in);

                SerializationFactory sf;

                Deserializer &d = sf.getDeserializer(in);

                d.read(CRC32 < HESPERIA_CORE_STRINGLITERAL6('c', 'e', 'n', 't', 'e', 'r') >::RESULT,
                       m_center);

                d.read(CRC32 < HESPERIA_CORE_STRINGLITERAL6('r', 'a', 'd', 'i', 'u', 's') >::RESULT,
                       m_radius);

                d.read(CRC32 < HESPERIA_CORE_STRINGLITERAL6('h', 'e', 'i', 'g', 'h', 't') >::RESULT,
                       m_height);

                d.read(CRC32 < HESPERIA_CORE_STRINGLITERAL5('c', 'o', 'l', 'o', 'r') >::RESULT,
                       m_color);

                return in;
            }

        }
    }
} // core::data::scenario
