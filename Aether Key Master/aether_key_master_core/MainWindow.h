#pragma once
#include "User.h"
#include "Notification/NotificationWidget.h"

#include <QtCore/QPointer>
#include <QtWidgets/QWidget>

#include "ui_MainWindow.h"

namespace aether_key_master_core
{
	/**
	 * @brief The main GUI class which presents every other widget
	*/
	class MainWindow : public QWidget
	{
		Q_OBJECT

	public:
		MainWindow(QWidget* parent = Q_NULLPTR);
		~MainWindow() = default;

		/**
		 * @brief Show the notification widget which displays the given message
		 * 
		 * @param message The message which has to be displayed
		*/
		static void showNotification(const QString& message);

	private:
		Ui::MainWindow ui;

		/**
		 * @brief Instance of the MainWindow
		*/
		static MainWindow* s_instance;
		/**
		 * @brief Instance of the notification widget
		*/
		static QPointer<NotificationWidget> s_notificationWidget;

		/**
		 * @brief Show the MasterKeyWidget in the content area where the Master Key can be entered or created
		*/
		void showMasterKeyWidget();
		/**
		 * @brief Show the KeysContentWidget in the content area where the passwords can be stored and viewed
		 * 
		 * @param user The User object with the stored Keys data
		*/
		void showKeysContentWidget(QPointer<User> user);
	};
}