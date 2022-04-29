#pragma once
#include "User.h"

#include <QWidget>
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

	private:
		Ui::MainWindow ui;

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