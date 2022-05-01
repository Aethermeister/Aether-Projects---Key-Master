#pragma once
#include "User.h"

#include <QWidget>
#include <QtCore/QPointer>

#include "ui_KeysDataParentWidget.h"

namespace aether_key_master_core
{
	/**
	 * @brief Main GUI class for the Key Data related widget presentation
	*/
	class KeysDataParentWidget : public QWidget
	{
		Q_OBJECT

	public:
		KeysDataParentWidget(QPointer<User> user, QWidget* parent = Q_NULLPTR);
		~KeysDataParentWidget() = default;

	private:
		Ui::KeysDataParentWidget ui;

		/**
		 * @brief The currently active user
		*/
		QPointer<User> m_user;

		/**
		 * @brief Initialize the default signal-slot connections
		*/
		void initializeConnections() const;

	private slots:
		/**
		 * @brief Slot to show modal dialog to add new KeyData to the user
		*/
		void slot_showAddKeyDataWidget() const;
	};
}