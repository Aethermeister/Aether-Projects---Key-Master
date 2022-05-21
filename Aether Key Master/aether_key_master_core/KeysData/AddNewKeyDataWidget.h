#pragma once
#include "Animation/FadeInAnimation.h"
#include "User.h"

#include <QtCore/QPointer>

#include "ui_AddNewKeyDataWidget.h"

namespace aether_key_master_core
{
	/**
	 * @brief A modal GUI to add new KeyData to the user
	*/
	class AddNewKeyDataWidget : public FadeInAnimation
	{
		Q_OBJECT

	public:
		AddNewKeyDataWidget(QPointer<User> user, QWidget* parent = Q_NULLPTR);

	private:
		Ui::AddNewKeyDataWidget ui;

		/**
		 * @brief The currently active user
		*/
		QPointer<User> m_user;

		/**
		 * @brief Initialize the default UI state
		*/
		void initializeUI();
		/**
		 * @brief Initialize the default signal-slot connections
		*/
		void initializeConnections() const;

		/**
		 * @brief Check the given title for duplication. The base title is automatically modified if a duplication exists
		 * 
		 * @param baseTitle The title which was given by the user
		 * @param index The duplication count of the title
		 * 
		 * @return The non-duplicated title
		*/
		QString checkTitleDuplication(const QString& baseTitle, int index = 1);

	private slots:
		/**
		 * @brief Slot to add the new KeyData to the User
		*/
		void slot_add();
		/**
		 * @brief Slot to handle the user invoked cancel
		*/
		void slot_canceled();

	signals:
		/**
		 * @brief Emitted when a new KeyData is added
		*/
		void sig_newKeyDataAdded();
	};
}