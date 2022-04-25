#pragma once
#include "User.h"


#include <QWidget>
#include "ui_MasterKeyParentWidget.h"

namespace aether_key_master_core
{
	/**
	 * @brief Main GUI class for the Master Key related widget presentation (Master Key creation and enter)
	*/
	class MasterKeyParentWidget : public QWidget
	{
		Q_OBJECT

	public:
		MasterKeyParentWidget(QWidget* parent = Q_NULLPTR);
		~MasterKeyParentWidget() = default;

	private:
		Ui::MasterKeyParentWidget ui;

		/**
		 * @brief Initialize the default UI state
		*/
		void initializeUi();
		/**
		 * @brief Check the existence of the Keys file and that its content is unmodified externally
		 * 
		 * @return True if the Keys file exists and its integrity is preserved
		*/
		bool checkKeysFileIntegrity() const;

		/**
		 * @brief Show the Master Key creation widget in the content area
		*/
		void showCreateMasterKeyWidget();
		/**
		 * @brief Show the Master Key enter widget in the content area
		*/
		void showEnterMasterKeyWidget();

		/**
		 * @brief Slot to handle the creation of a new Master Key
		 * 
		 * @param masterKey The new Master Key
		*/
		void slot_masterKeyCreated(const QString& masterKey);
		/**
		 * @brief Slot to handle the reset Master Key request
		*/
		void slot_resetRequested();
		/**
		 * @brief Slot to handle the acceptance of the processed Master Key
		 * 
		 * @param user The which is create after accepting the Master Key
		*/
		void slot_masterKeyAccepted(QPointer<User> user);

	signals:
		/**
		 * @brief Signal which is emitted when the Master Key was either created or accepted
		*/
		void sig_authenticationDone(QPointer<User> user);
	};
}