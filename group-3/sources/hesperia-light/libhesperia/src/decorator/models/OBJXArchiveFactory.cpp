/*
 * Copyright (c) Christian Berger and Bernhard Rumpe, Rheinisch-Westfaelische Technische Hochschule Aachen, Germany.
 *
 * The Hesperia Framework.
 */

#include <vector>

#include "core/macros.h"
#include "core/base/Lock.h"
#include "core/exceptions/Exceptions.h"
#include "core/wrapper/CompressionFactory.h"
#include "core/wrapper/DecompressedData.h"
#include "core/wrapper/Image.h"
#include "core/wrapper/ImageFactory.h"

#include "hesperia/data/Constants.h"
#include "hesperia/decorator/models/OBJXArchiveFactory.h"

namespace hesperia {
    namespace decorator {
        namespace models {

            using namespace std;
            using namespace core::base;
            using namespace core::data;
            using namespace core::exceptions;

            // Initialize singleton instance.
            Mutex OBJXArchiveFactory::m_singletonMutex;
            OBJXArchiveFactory* OBJXArchiveFactory::m_singleton = NULL;

            OBJXArchiveFactory::OBJXArchiveFactory() {}

            OBJXArchiveFactory::~OBJXArchiveFactory() {}

            OBJXArchiveFactory& OBJXArchiveFactory::getInstance() {
                {
                    Lock l(OBJXArchiveFactory::m_singletonMutex);
                    if (OBJXArchiveFactory::m_singleton == NULL) {
                        OBJXArchiveFactory::m_singleton = new OBJXArchiveFactory();
                    }
                }

                return (*OBJXArchiveFactory::m_singleton);
            }

            OBJXArchive* OBJXArchiveFactory::getOBJXArchiveFromPlainOBJFile(istream &in) throw (InvalidArgumentException) {
                if (!(in.good())) {
                    // Try to rewind the stream.
                    clog << "Trying to rewind the stream." << endl;
                    in.clear();
                    in.seekg(ios::beg);

                    if (!(in.good())) {
                        HESPERIA_CORE_THROW_EXCEPTION(InvalidArgumentException, "Given inputstream is invalid.");
                    }
                }

                OBJXArchive *objxArchive = new OBJXArchive();

                char c;
                stringstream s;
                while (in.good()) {
                    in.get(c);
                    s << c;
                }
                objxArchive->setContentsOfObjFile(s.str());

                return objxArchive;
            }

            OBJXArchive* OBJXArchiveFactory::getOBJXArchive(istream &in) throw (InvalidArgumentException) {
                if (!(in.good())) {
                    // Try to rewind the stream.
                    clog << "Trying to rewind the stream." << endl;
                    in.clear();
                    in.seekg(ios::beg);

                    if (!(in.good())) {
                        HESPERIA_CORE_THROW_EXCEPTION(InvalidArgumentException, "Given inputstream is invalid.");
                    }
                }

                OBJXArchive *objxArchive = NULL;

                // Use CompressionFactory to read the contents of the OBJXArchive.
                core::wrapper::DecompressedData *data = core::wrapper::CompressionFactory::getInstance().getContents(in);

                if (data != NULL) {
                    // Create OBJXArchive.
                    objxArchive = new OBJXArchive();

                    vector<string> listOfEntries = data->getListOfEntries();
                    vector<string>::iterator it = listOfEntries.begin();

                    while (it != listOfEntries.end()) {
                        string entry = (*it++);

                        if (entry.find(".obj") != string::npos) {
                            // Set object file.
                            istream *stream = data->getInputStreamFor(entry);

                            char c;
                            stringstream s;
                            while (stream->good()) {
                                stream->get(c);
                                s << c;
                            }
                            objxArchive->setContentsOfObjFile(s.str());
                        } else if (entry.find(".mtl") != string::npos) {
                            // Set material file.
                            istream *stream = data->getInputStreamFor(entry);

                            char c;
                            stringstream s;
                            while (stream->good()) {
                                stream->get(c);
                                s << c;
                            }
                            objxArchive->setContentsOfMtlFile(s.str());
                        } else {
                            // Try to load an image.
                            istream *stream = data->getInputStreamFor(entry);

                            if (stream != NULL) {
                                core::wrapper::Image *image = core::wrapper::ImageFactory::getInstance().getImage(*stream);

                                if (image != NULL) {
                                    // TODO: Check where origin lies.
                                    image->rotate(static_cast<float>(data::Constants::PI));

                                    // Remove any directory prefixes from the entry.
                                    string name = entry;
                                    if (name.rfind('/') != string::npos) {
                                        name = name.substr(name.rfind('/') + 1);
                                    }

                                    objxArchive->addImage(name, image);
                                }
                            }
                        }

                    }
                }

                return objxArchive;
            }

        }
    }
} // hesperia::decorator::models
