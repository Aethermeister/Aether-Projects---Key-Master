#include "aether_key_master_core_main.h"
#include "MainWindow.h"

#include <QtWidgets/QApplication>

namespace aether_key_master_core
{
    int AETHER_KEY_MASTER_CORE_EXPORT aether_key_master_core_main(int argc, char** argv)
    {
        QApplication app(argc, argv);

        MainWindow mainWindow;
        mainWindow.show();

        return QApplication::exec();
    }
}