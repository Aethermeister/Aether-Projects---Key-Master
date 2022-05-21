#include "KeyDataWidget.h"
#include "MainWindow.h"
#include "Notification/VerificationWidget.h"
#include "Aether CPP Logger/include/Logger.h"
#include "Utility/Utility.h"

#include <QtGui/QClipboard>

namespace aether_key_master_core
{
	KeyDataWidget::KeyDataWidget(QWidget* parent)
		: QWidget(parent)
	{
		ui.setupUi(this);

		initializeUi();
		initializeConnections();
	}

	void KeyDataWidget::setUser(QPointer<User> user)
	{
		m_user = user;
	}

	void KeyDataWidget::initializeKeyData(KeyData* keyData)
	{
		//Set the currently used KeyData and change the UI according its data
		m_currentKeyData = keyData;

		ui.m_title_lbl->setText(m_currentKeyData->title());

		ui.m_username_lineEdit->setText(m_currentKeyData->username());
		ui.m_password_lineEdit->setText(m_currentKeyData->password());
	}
	void KeyDataWidget::resetKeyData()
	{
		//Null the currently used KeyData and reset the UI
		m_currentKeyData = nullptr;
		ui.m_title_lbl->setText("");

		ui.m_username_lineEdit->setText("");
		ui.m_password_lineEdit->setText("");
	}
	void KeyDataWidget::initializeUi()
	{
		setWidgetSizeRetain(ui.m_edit_btn, true);
		setWidgetSizeRetain(ui.m_save_btn, true);
		setWidgetSizeRetain(ui.m_cancel_btn, true);

		ui.m_save_btn->setVisible(false);
		ui.m_cancel_btn->setVisible(false);

		ui.m_username_lineEdit->setEnabled(false);
		ui.m_password_lineEdit->setEnabled(false);
	}
	void KeyDataWidget::initializeConnections() const
	{
		connect(ui.m_copyUsername_btn, &QPushButton::clicked, this, &KeyDataWidget::slot_copyUsernameToClipboard);
		connect(ui.m_copyPassword_btn, &QPushButton::clicked, this, &KeyDataWidget::slot_copyPasswordToClipboard);

		connect(ui.m_delete_btn, &QPushButton::clicked, this, &KeyDataWidget::slot_deleteKeyData);

		connect(ui.m_edit_btn, &QPushButton::clicked, this, &KeyDataWidget::slot_startEditing);
		connect(ui.m_save_btn, &QPushButton::clicked, this, &KeyDataWidget::slot_saveEditing);
		connect(ui.m_cancel_btn, &QPushButton::clicked, this, &KeyDataWidget::slot_cancelEditing);
	}
	void KeyDataWidget::adjustUiForEditing(const bool isEditing)
	{
		//According to the given parameter set the UI for editing or disabled editing
		ui.m_edit_btn->setVisible(!isEditing);
		ui.m_save_btn->setVisible(isEditing);
		ui.m_cancel_btn->setVisible(isEditing);

		ui.m_username_lineEdit->setEnabled(isEditing);
		ui.m_password_lineEdit->setEnabled(isEditing);
	}
	void KeyDataWidget::copyTextToClipboard(const QString& text) const
	{
		auto clipboard = QApplication::clipboard();
		clipboard->setText(text);
	}
	void KeyDataWidget::slot_copyUsernameToClipboard() const
	{
		const auto& username = m_currentKeyData->username();
		copyTextToClipboard(username);

		MainWindow::showNotification(QString("Username copied - %0").arg(m_currentKeyData->title()));
	}
	void KeyDataWidget::slot_copyPasswordToClipboard() const
	{
		const auto& password = m_currentKeyData->password();
		copyTextToClipboard(password);

		MainWindow::showNotification(QString("Password copied - %0").arg(m_currentKeyData->title()));
	}
	void KeyDataWidget::slot_deleteKeyData()
	{
		//Show the verification widget to confirm the KeyData deletion
		QPointer<VerificationWidget> verificationWidget = new VerificationWidget("Key Data deletion is permanent\n\n"
			"Do you confirm?", this);
		verificationWidget->show();

		//If the user confirms the deletion remove the current KeyData from the User and adjust the UI state
		QObject::connect(verificationWidget, &VerificationWidget::sig_verificationConfirmed, [this]
			{
				AETHER_LOG_INFO("Deleting KeyData");
				
				m_user->removeKeyData(*m_currentKeyData);
				m_user->saveKeys();
				MainWindow::showNotification(QString("Key data deleted - %0").arg(m_currentKeyData->title()));

				resetKeyData();
				emit sig_keyDataDeleted();

			});
	}

	void KeyDataWidget::slot_startEditing()
	{
		adjustUiForEditing(true);
	}
	void KeyDataWidget::slot_saveEditing()
	{
		//Save the edited KeyData and stop editing
		m_currentKeyData->setUsername(ui.m_username_lineEdit->text());
		m_currentKeyData->setPassword(ui.m_password_lineEdit->text());

		adjustUiForEditing(false);

		MainWindow::showNotification(QString("Key data edited - %0").arg(m_currentKeyData->title()));
	}
	void KeyDataWidget::slot_cancelEditing()
	{
		//Restore the edited UI and stop editing
		ui.m_username_lineEdit->setText(m_currentKeyData->username());
		ui.m_password_lineEdit->setText(m_currentKeyData->password());

		adjustUiForEditing(false);
	}
}