#pragma once
#include "Animation/FadeInAnimation.h"

#include "ui_VerificationWidget.h"

namespace aether_key_master_core
{
	/**
	 * @brief GUI class to handle verifications
	*/
	class VerificationWidget : public FadeInAnimation
	{
		Q_OBJECT

	public:
		VerificationWidget(const QString& message, QWidget* parent = Q_NULLPTR);

	private:
		Ui::VerificationWidget ui;

		/**
		 * @brief The message which has to be shown in the verification widget
		*/
		QString m_message;

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
		 * @brief Slot to handle the user invoked confirmation
		*/
		void slot_confirmed();
		/**
		 * @brief Slot to handle the user invoked cancel
		*/
		void slot_canceled();

	signals:
		/**
		 * @brief Emitted when the user click on the Confirm button
		*/
		void sig_verificationConfirmed();
	};
}