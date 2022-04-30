#pragma once
#include "User.h"

#include <QtCore/QPointer>
#include <QWidget>
#include "ui_EnterMasterKeyWidget.h"

namespace aether_key_master_core
{
	/**
	 * @brief GUI class which provides methods to enter or reset the Master Key
	*/
	class EnterMasterKeyWidget : public QWidget
	{
		Q_OBJECT

	public:
		EnterMasterKeyWidget(QWidget* parent = Q_NULLPTR);
		~EnterMasterKeyWidget() = default;

	private:
		Ui::EnterMasterKeyWidget ui;

		/**
		 * @brief Initialize the default UI state
		*/
		void initializeUi();
		/**
		 * @brief Initialize the default signal-slot connections
		*/
		void initializeConnections() const;

		/**
		 * @brief Slot to reset the previous Master Key and the corresponding Keys data
		*/
		void reset();
		/**
		 * @brief Overwrite and delete the Keys file in the AppData
		*/
		void deleteKeysFile() const;
		/**
		 * @brief Delete the time lock key and enter attempt counter entries from the registry
		*/
		void deleteRegistryEntries() const;
		/**
		 * @brief Show the appropriate error message
		*/
		void adjustErrorMessage();

		/**
		 * @brief Decrease the counter of the remaining enter attempts and store the new value in the registry
		 * 
		 * @return The decreased attempt counter value
		*/
		int decreaseRemainingEnterAttempts() const;

	private slots:
		/**
		 * @brief Slot to handle the program behaviour according to the user entered Master Key
		*/
		void slot_enterMasterKey();
		/**
		 * @brief Slot to reset the previous Master Key and the corresponding Keys data
		*/
		void slot_reset();

	signals:
		/**
		 * @brief Emitted when the Master Key is valid
		*/
		void sig_masterKeyAccepted(QPointer<User> user);
		/**
		 * @brief Emitted when the user requests the reset of the Master Key and Keys data
		*/
		void sig_resetRequested();
	};
}