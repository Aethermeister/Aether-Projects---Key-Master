#pragma once
#include "User.h"
#include "KeysData/KeyData.h"

#include <QWidget>
#include <QtCore/QPointer>
#include "ui_KeyDataWidget.h"

namespace aether_key_master_core
{
	/**
	 * @brief UI class which allows the user to manage one KeyData at a time
	*/
	class KeyDataWidget : public QWidget
	{
		Q_OBJECT

	public:
		KeyDataWidget(QWidget* parent = Q_NULLPTR);
		~KeyDataWidget() = default;

		/**
		 * @brief Setter of the User object
		 * 
		 * @param user The new User
		*/
		void setUser(QPointer<User> user);
		/**
		 * @brief Initialize the UI according to the given KeyData
		 * 
		 * @param keyData The KeyData which is used to (re)-initialize the UI
		*/
		void initializeKeyData(KeyData* keyData);
		/**
		 * @brief Resets the UI so there no sensitive information remains on the UI
		*/
		void resetKeyData();

	private:
		Ui::KeyDataWidget ui;

		/**
		 * @brief The User object whose KeyData is managed
		*/
		QPointer<User> m_user;
		/**
		 * @brief The currently managed KeyData
		*/
		KeyData* m_currentKeyData;

		/**
		 * @brief Initialize the default UI state
		*/
		void initializeUi();
		/**
		 * @brief Initialize the default signal-slot connections
		*/
		void initializeConnections() const;
		/**
		 * @brief Sets the UI according to the given editing flag
		 * 
		 * @param isEditing The editing flag which decides how the UI should be modified
		 * True: The username and password QLineEdits can be edited
		 * False: The username and password QLineEdits cannot be edited
		*/
		void adjustUiForEditing(const bool isEditing);

		/**
		 * @brief Copies the given text to the clipboard
		 * 
		 * @param text The text which has to be copied to the clipboard
		*/
		void copyTextToClipboard(const QString& text) const;

	private slots:
		/**
		 * @brief Slot which handles the user requested username copy to clipboard
		*/
		void slot_copyUsernameToClipboard() const;
		/**
		 * @brief Slot which handles the user requested password copy to clipboard
		*/
		void slot_copyPasswordToClipboard() const;
		/**
		 * @brief Slot which handles the deletion of the current KeyData
		*/
		void slot_deleteKeyData();
		/**
		 * @brief Slot which adjusts the UI for username and password editing
		*/
		void slot_startEditing();
		/**
		 * @brief Slot to save the modified username and password and stop editing
		*/
		void slot_saveEditing();
		/**
		 * @brief Slot to restore the changed username and password and stop editing
		*/
		void slot_cancelEditing();

	signals:
		/**
		 * @brief Emitted when the current KeyData is deleted
		*/
		void sig_keyDataDeleted();
	};
}