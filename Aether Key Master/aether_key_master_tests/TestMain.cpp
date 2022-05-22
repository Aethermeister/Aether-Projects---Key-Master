#include <QtCore/QCoreApplication>
#include <QtTest/QTest>

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);

    //Set the application specific core information
    QApplication::setApplicationName("Key Master Test");
    QApplication::setOrganizationName("Aether Projects");
    QApplication::setOrganizationDomain("Aether Projects");
    QApplication::setApplicationVersion("1.0");

    return a.exec();
}
