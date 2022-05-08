#pragma once
#include "Animation/FadeInAnimation.h"
#include "MasterKeyValidator.h"
#include "User.h"

#include <QtWidgets/QWidget>
#include <QtCore/QPointer>
#include "ui_ChangeMasterKeyWidget.h"

namespace aether_key_master_core
{
	/**
	 * @brief A modal GUI to change the user's Master Key
	*/
	class ChangeMasterKeyWidget : public FadeInAnimation, public MasterKeyValidator
	{
		Q_OBJECT

	public:
		ChangeMasterKeyWidget(QPointer<User> user, QWidget* parent = Q_NULLPTR);
		virtual ~ChangeMasterKeyWidget() = default;

	private:
		Ui::ChangeMasterKeyWidget ui;

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

	private slots:
		/**
		 * @brief Slot to process the user given new Master Key
		*/
		void slot_changeMasterKey();
	};
}