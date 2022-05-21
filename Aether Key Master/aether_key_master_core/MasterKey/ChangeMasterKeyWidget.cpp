#include "ChangeMasterKeyWidget.h"
#include "Aether CPP Logger/include/Logger.h"
#include "MasterKeyValidationException.h"
#include "Utility/Utility.h"
#include "MainWindow.h"

namespace aether_key_master_core
{
	ChangeMasterKeyWidget::ChangeMasterKeyWidget(QPointer<User> user, QWidget* parent)
		: FadeInAnimation(parent), m_user(user)
	{
		ui.setupUi(this);

		initializeUI();
		initializeConnections();
	}

	void ChangeMasterKeyWidget::initializeUI()
	{
		//Set the properties of the widget
		setWindowModality(Qt::WindowModality::ApplicationModal);
		setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
		setAttribute(Qt::WA_DeleteOnClose);
		setAutoFillBackground(true);

		//Change the size policy of the information label and hide it
		setWidgetSizeRetain(ui.m_errorInformation_lbl, true);
		ui.m_errorInformation_lbl->setVisible(false);
	}
	void ChangeMasterKeyWidget::initializeConnections() const
	{
		connect(ui.m_change_btn, &QPushButton::clicked, this, &ChangeMasterKeyWidget::slot_changeMasterKey);
		connect(ui.m_cancel_btn, &QPushButton::clicked, this, &ChangeMasterKeyWidget::close);
	}
	void ChangeMasterKeyWidget::slot_changeMasterKey()
	{
		AETHER_LOG_INFO("Changing Master Key");

		//Reset the style of the QLineEdits
		changeWidgetSeverityStyle(ui.m_oldMasterKey_lineEdit, "");
		changeWidgetSeverityStyle(ui.m_newMasterKey_lineEdit, "");
		changeWidgetSeverityStyle(ui.m_verifyNewMasterKey_lineEdit, "");

		try
		{
			//Validate the Master Keys
			//If the given Master Key is invalid an exception is thrown
			validateMasterKeyRequirements(m_user, ui.m_oldMasterKey_lineEdit, ui.m_newMasterKey_lineEdit, ui.m_verifyNewMasterKey_lineEdit);

			//If the old and new Master Keys are valid change it in the User object and save the Keys file
			const auto masterKey = ui.m_newMasterKey_lineEdit->text();
			m_user->setMasterKey(masterKey);
			m_user->saveKeys();

			MainWindow::showNotification("Master Key changed");
			AETHER_LOG_INFO("Master Key changed");

			close();
		}
		catch (const MasterKeyValidationException& mkve)
		{
			//Show the error QLabel
			ui.m_errorInformation_lbl->setVisible(true);
			ui.m_errorInformation_lbl->setText(mkve.what());

			AETHER_LOG_ERROR(mkve.what());
		}
	}
}