#include "MainWindow.h"
#include "MasterKey/MasterKeyParentWidget.h"
#include "KeysData/KeysDataParentWidget.h"
#include "Utility/Utility.h"

namespace aether_key_master_core
{
	MainWindow* MainWindow::s_instance = nullptr;
	QPointer<NotificationWidget> MainWindow::s_notificationWidget = nullptr;

	MainWindow::MainWindow(QWidget* parent)
		: QWidget(parent)
	{
		ui.setupUi(this);

		s_instance = this;

		//Always show the MasterKeyWidget first
		showMasterKeyWidget();
	}

	void MainWindow::showNotification(const QString& message)
	{
		//Check whether there is a notification already shown
		//and delete it if it exists
		if (s_notificationWidget)
		{
			s_notificationWidget->deleteLater();
		}

		//Create and show the notification widget
		s_notificationWidget = new NotificationWidget(message, s_instance);
		s_notificationWidget->show();
	}

	void MainWindow::showMasterKeyWidget()
	{
		//Delete the previous widget in the content area
		deleteContentWidget<QWidget*>(this, ui.m_mainWindow_layout);

		//Create the MasterKeyParentWidget and add it to the content area
		QPointer<MasterKeyParentWidget> masterKeyWidget = new MasterKeyParentWidget(this);
		ui.m_mainWindow_layout->addWidget(masterKeyWidget);

		connect(masterKeyWidget, &MasterKeyParentWidget::sig_authenticationDone, this, &MainWindow::showKeysContentWidget);
	}
	void MainWindow::showKeysContentWidget(QPointer<User> user)
	{
		//Delete the previous widget in the content area
		deleteContentWidget<QWidget*>(this, ui.m_mainWindow_layout);

		//Create the KeysDataParentWidget and add it to the content area
		QPointer<KeysDataParentWidget> keysDataWidget = new KeysDataParentWidget(user, this);
		ui.m_mainWindow_layout->addWidget(keysDataWidget);
	}
}
