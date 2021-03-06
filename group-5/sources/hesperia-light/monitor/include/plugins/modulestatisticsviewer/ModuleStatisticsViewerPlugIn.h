/*
 * Copyright (c) Christian Berger and Bernhard Rumpe, Rheinisch-Westfaelische Technische Hochschule Aachen, Germany.
 *
 * The Hesperia Framework.
 */

#ifndef MONITOR_PLUGINS_MODULESTATISTICSVIEWER_MODULESTATISTICSVIEWERPLUGIN_H_
#define MONITOR_PLUGINS_MODULESTATISTICSVIEWER_MODULESTATISTICSVIEWERPLUGIN_H_

#include "core/base/KeyValueConfiguration.h"

#include "plugins/PlugIn.h"
#include "plugins/modulestatisticsviewer/ModuleStatisticsViewerWidget.h"

namespace plugins {
    namespace modulestatisticsviewer {

        using namespace std;

        class ModuleStatisticsViewerPlugIn : public PlugIn {

            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                ModuleStatisticsViewerPlugIn(const ModuleStatisticsViewerPlugIn &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                ModuleStatisticsViewerPlugIn& operator=(const ModuleStatisticsViewerPlugIn &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param name Name of this plugin.
                 * @param kvc KeyValueConfiguration for this widget.
                 * @param prnt Pointer to the container super window.
                 */
                ModuleStatisticsViewerPlugIn(const string &name, const core::base::KeyValueConfiguration &kvc, QWidget *prnt);

                virtual ~ModuleStatisticsViewerPlugIn();

                virtual QWidget* getQWidget() const;

                virtual void setupPlugin();

                virtual void stopPlugin();

            private:
                ModuleStatisticsViewerWidget *m_modulestatisticsViewerWidget;
        };

    }
} // plugins::modulestatisticsviewer

#endif /*MONITOR_PLUGINS_MODULESTATISTICSVIEWER_MODULESTATISTICSVIEWERPLUGIN_H_*/
