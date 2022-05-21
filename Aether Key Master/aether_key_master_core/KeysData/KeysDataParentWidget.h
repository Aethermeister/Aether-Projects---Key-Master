#pragma once
#include "MasterKey/MasterKeyResetHandler.h"
#include "User.h"

#include <QWidget>
#include <QtCore/QPointer>

#include "ui_KeysDataParentWidget.h"

namespace aether_key_master_core
{
	/**
	 * @brief Main GUI class for the Key Data related widget presentation
	*/
	class KeysDataParentWidget : public MasterKeyResetHandler
	{
		Q_OBJECT

	public:
		KeysDataParentWidget(QPointer<User> user, QWidget* parent = Q_NULLPTR);
		virtual ~KeysDataParentWidget() = default;

	private:
		Ui::KeysDataParentWidget ui;

		/**
		 * @brief The currently active user
		*/
		QPointer<User> m_user;
		/**
		 * @brief The title of the last cklicked KeyData list item
		*/
		QString m_lastSelectedKey;

		/**
		 * @brief Initialize the default UI state
		*/
		void initializeUI();
		/**
		 * @brief Initialize the default signal-slot connections
		*/
		void initializeConnections() const;
		/**
		 * @brief List each stored KeyData element
		*/
		void listKeys();
		/**
		 * @brief Show the KeyData widget with the data of the selected KeyData
		 * or hide it if the given KeyData is deselected
		*/
		void showKeyDataWidget();

	private slots:
		/**
		 * @brief Slot to show modal dialog to add new KeyData to the user
		*/
		void slot_showAddKeyDataWidget();
		/**
		 * @brief Slot to show modal dialog to change the user's Master Key
		*/
		void slot_showChangeMasterKeyWidget();
		/**
		 * @brief Slot to handle when the user click on one of the listed KeyData list element
		*/
		void slot_keyItemSelected(const QListWidgetItem* item);
		/**
		 * @brief Slot to update the UI when a KeyData is deleted
		*/
		void slot_keyDataDeleted();
	};
}