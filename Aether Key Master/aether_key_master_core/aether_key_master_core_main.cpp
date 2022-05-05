#include "aether_key_master_core_main.h"
#include "MainWindow.h"
#include "Aether CPP Logger/include/Logger.h"

#include <QtWidgets/QApplication>
#include <QtCore/QFile>

namespace aether_key_master_core
{
    int AETHER_KEY_MASTER_CORE_EXPORT aether_key_master_core_main(int argc, char** argv)
    {
        QApplication app(argc, argv);

        //Set the application specific core information
        QApplication::setApplicationName("Key Master");
        QApplication::setOrganizationName("Aether Projects");
        QApplication::setOrganizationDomain("Aether Projects");
        QApplication::setApplicationVersion("1.0");

        //Initialize the Aether CPP Logger so it logs to the AppData folder
        AETHER_LOG_INIT_2(QApplication::applicationName().toStdString(), QApplication::organizationDomain().toStdString());
        AETHER_LOG_INFO(QString("Starting the application - V%0").arg(QApplication::applicationVersion()).toStdString());

        //Set the application level stylesheet
        QFile styleSheetFile(":/Style/style.qss");
        styleSheetFile.open(QFile::ReadOnly);
        app.setStyleSheet(styleSheetFile.readAll());

        MainWindow mainWindow;
        mainWindow.show();

        return QApplication::exec();
    }
}