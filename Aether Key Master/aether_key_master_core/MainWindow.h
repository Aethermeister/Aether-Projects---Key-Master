#pragma once
#include <QtWidgets/QMainWindow>

namespace aether_key_master_core
{
    class MainWindow : public QMainWindow
    {
    public:
        MainWindow(QWidget* parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    };
}