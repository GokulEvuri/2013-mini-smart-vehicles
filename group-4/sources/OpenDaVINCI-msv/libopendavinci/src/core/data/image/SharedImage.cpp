/*
 * OpenDaVINCI.
 *
 * This software is open source. Please see COPYING and AUTHORS for further information.
 */

#include <sstream>

#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"
#include "core/data/SharedData.h"
#include "core/data/image/SharedImage.h"

namespace core {
    namespace data {
        namespace image {

            using namespace std;
            using namespace core::base;

            SharedImage::SharedImage() :
                    SharedData(),
                    m_width(0),
                    m_height(0),
                    m_bytesPerPixel(0) {}

            SharedImage::~SharedImage() {}

            SharedImage::SharedImage(const SharedImage &obj) :
                    SharedData(obj),
                    m_width(obj.getWidth()),
                    m_height(obj.getHeight()),
                    m_bytesPerPixel(obj.getBytesPerPixel()) {}

            SharedImage& SharedImage::operator=(const SharedImage &obj) {
                SharedData::operator=(obj);
                setWidth(obj.getWidth());
                setHeight(obj.getHeight());
                setBytesPerPixel(obj.getBytesPerPixel());

                return (*this);
            }

            uint32_t SharedImage::getWidth() const {
                return m_width;
            }

            void SharedImage::setWidth(const uint32_t &width) {
                m_width = width;
            }

            uint32_t SharedImage::getHeight() const {
                return m_height;
            }

            void SharedImage::setHeight(const uint32_t &height) {
                m_height = height;
            }

            uint32_t SharedImage::getBytesPerPixel() const {
                return m_bytesPerPixel;
            }

            void SharedImage::setBytesPerPixel(const uint32_t &bytesPerPixel) {
                m_bytesPerPixel = bytesPerPixel;
            }

            ostream& SharedImage::operator<<(ostream &out) const {
                // Serializer super class.
                SharedData::operator<<(out);

                // Serialize this class.
                SerializationFactory sf;

                Serializer &s = sf.getSerializer(out);

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('w', 'i', 'd', 't', 'h') >::RESULT,
                        getWidth());

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('h', 'e', 'i', 'g', 'h', 't') >::RESULT,
                        getHeight());

                s.write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('b', 'p', 'p') >::RESULT,
                        getBytesPerPixel());

                return out;
            }

            istream& SharedImage::operator>>(istream &in) {
                // Deserializer super class.
                SharedData::operator>>(in);

                // Deserialize this class.
                SerializationFactory sf;

                Deserializer &d = sf.getDeserializer(in);

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('w', 'i', 'd', 't', 'h') >::RESULT,
                       m_width);

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('h', 'e', 'i', 'g', 'h', 't') >::RESULT,
                       m_height);

                d.read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('b', 'p', 'p') >::RESULT,
                       m_bytesPerPixel);

                return in;
            }

            const string SharedImage::toString() const {
                stringstream sstr;
                sstr << SharedData::toString() << ", width = " << getWidth() << ", height = " << getHeight() << ", bytes per pixel = " << getBytesPerPixel();
                return sstr.str();
            }
        }
    }
} // core::data::image
