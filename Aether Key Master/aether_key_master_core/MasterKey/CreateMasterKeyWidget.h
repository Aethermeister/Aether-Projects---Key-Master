#pragma once

#include <QWidget>
#include "ui_CreateMasterKeyWidget.h"

namespace aether_key_master_core
{
	/**
	 * @brief GUI class which provides methods to create a new Master Key
	*/
	class CreateMasterKeyWidget : public QWidget
	{
		Q_OBJECT

	public:
		CreateMasterKeyWidget(QWidget* parent = Q_NULLPTR);
		~CreateMasterKeyWidget() = default;

	private:
		Ui::CreateMasterKeyWidget ui;

		/**
		 * @brief Initialize the default UI state
		*/
		void initializeUi();
		/**
		 * @brief Initialize the default signal-slot connections
		*/
		void initializeConnections() const;

		/**
		 * @brief Validate the given Master Key whether it meets the minimum requirements
		 * 
		 * @param masterKey The Master Key which has to be checked
		 * @param verifyMasterKey The verified Master Key
		*/
		void validateMasterKeyRequirements(const QString& masterKey, const QString& verifyMasterKey) const;
		/**
		 * @brief Check the given Master Key with a regex
		 * 
		 * @param masterKey The Master Key which has to be checked
		 * @param regexPattern The pattern of the regex matched on the Master Key
		 * 
		 * @return The matching result of the regex
		*/
		bool validateMasterKeyWithRegex(const QString& masterKey, const QString& regexPattern) const;

	private slots:
		/**
		 * @brief Slot to handle the user invoked Master Key creation
		*/
		void slot_createMasterKey();

	signals:
		/**
		 * @brief Emitted when the new Master Key meets the minimum requirements
		*/
		void sig_masterKeyCreated(const QString& masterKey);
	};
}