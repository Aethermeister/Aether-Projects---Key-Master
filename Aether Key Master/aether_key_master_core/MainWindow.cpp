#include "MainWindow.h"
#include "MasterKey/MasterKeyParentWidget.h"
#include "Utility/Utility.h"

#include <QPointer>

namespace aether_key_master_core
{
	MainWindow::MainWindow(QWidget* parent)
		: QWidget(parent)
	{
		ui.setupUi(this);

		//Always show the MasterKeyWidget first
		showMasterKeyWidget();
	}

	void MainWindow::showMasterKeyWidget()
	{
		//Delete the previous widget in the content area
		deleteContentWidget<QWidget*>(this, ui.m_mainWindow_layout);

		//Create the MasterKeyWidget and add it ti the content area
		QPointer<MasterKeyParentWidget> masterKeyWidget = new MasterKeyParentWidget(this);
		ui.m_mainWindow_layout->addWidget(masterKeyWidget);

		connect(masterKeyWidget, &MasterKeyParentWidget::sig_authenticationDone, this, &MainWindow::showKeysContentWidget);
	}
	void MainWindow::showKeysContentWidget()
	{
		//Delete the previous widget in the content area
		deleteContentWidget<QWidget*>(this, ui.m_mainWindow_layout);
	}
}
