/*
 * OpenDaVINCI.
 *
 * This software is open source. Please see COPYING and AUTHORS for further information.
 */

#ifndef OPENDAVINCI_DATA_DMCP_MODULEDESCRIPTORCOMPARATOR_H_
#define OPENDAVINCI_DATA_DMCP_MODULEDESCRIPTORCOMPARATOR_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include "core/data/dmcp/ModuleDescriptor.h"

namespace core {
    namespace data {
        namespace dmcp {

            using namespace std;

            /**
             * This class compares ModuleDescriptors for sorting.
             */
            class OPENDAVINCI_API ModuleDescriptorComparator {
                public:
                    ModuleDescriptorComparator();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    ModuleDescriptorComparator(const ModuleDescriptorComparator &/*obj*/) {};

                    virtual ~ModuleDescriptorComparator();

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    ModuleDescriptorComparator& operator=(const ModuleDescriptorComparator &/*obj*/) {
                        return (*this);
                    };

                    /**
                     * This method returns s1 < s2.
                     *
                     * @return s1 < s2.
                     */
                    bool operator()(const ModuleDescriptor &m1, const ModuleDescriptor &m2) const;
            };

        }
    }
} // core::data::dmcp

#endif /*OPENDAVINCI_DATA_DMCP_MODULEDESCRIPTORCOMPARATOR_H_*/
