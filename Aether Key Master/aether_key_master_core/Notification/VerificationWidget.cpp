#include "VerificationWidget.h"

#include <QtWidgets/QGraphicsDropShadowEffect>

namespace aether_key_master_core
{
	VerificationWidget::VerificationWidget(const QString& message, QWidget* parent)
		: FadeInAnimation(parent), m_message(message)
	{
		ui.setupUi(this);

		initializeUI();
		initializeConnections();
	}

	void VerificationWidget::initializeUI()
	{
		//Set the properties of the widget and show the verification message
		setWindowModality(Qt::WindowModality::ApplicationModal);
		setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
		setAttribute(Qt::WA_DeleteOnClose);
		setAutoFillBackground(true);

		ui.m_message_lbl->setText(m_message);
	}

	void VerificationWidget::initializeConnections() const
	{
		connect(ui.m_cancel_btn, &QPushButton::clicked, this, &VerificationWidget::slot_canceled);
		connect(ui.m_confirm_btn, &QPushButton::clicked, this, &VerificationWidget::slot_confirmed);
	}

	void VerificationWidget::slot_canceled()
	{
		close();
	}

	void VerificationWidget::slot_confirmed()
	{
		//If the user click on the Confirm button send a signal indicating the confirmation
		emit sig_verificationConfirmed();
		close();
	}
}