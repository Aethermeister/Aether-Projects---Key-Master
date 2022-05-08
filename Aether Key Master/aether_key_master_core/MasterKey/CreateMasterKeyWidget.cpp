#include "CreateMasterKeyWidget.h"
#include "Aether CPP Logger/include/Logger.h"
#include "MasterKeyValidationException.h"
#include "Utility/Utility.h"
#include "User.h"

namespace aether_key_master_core
{
	CreateMasterKeyWidget::CreateMasterKeyWidget(QWidget* parent)
		: QWidget(parent)
	{
		ui.setupUi(this);

		initializeUi();
		initializeConnections();
	}

	void CreateMasterKeyWidget::initializeUi()
	{
		//Set the properties of the error QLabel
		//The error QLabel takes its place even if it is hidden
		auto errorInformationLabelSizePolicy = ui.m_errorInformation_lbl->sizePolicy();
		errorInformationLabelSizePolicy.setRetainSizeWhenHidden(true);
		ui.m_errorInformation_lbl->setSizePolicy(errorInformationLabelSizePolicy);
		ui.m_errorInformation_lbl->setVisible(false);
	}

	void CreateMasterKeyWidget::initializeConnections() const
	{
		connect(ui.m_createMasterKey_btn, &QPushButton::clicked, this, &CreateMasterKeyWidget::slot_createMasterKey);
	}

	void CreateMasterKeyWidget::slot_createMasterKey()
	{
		AETHER_LOG_INFO("Creating Master Key");

		//Reset the style of the QLineEdits
		changeWidgetSeverityStyle(ui.m_masterKey_lineEdit, "");
		changeWidgetSeverityStyle(ui.m_verifyMasterKey_lineEdit, "");

		try
		{
			//Validate the Master Keys
			//If the given Master Key is invalid an exception is thrown
			validateMasterKeyRequirements(ui.m_masterKey_lineEdit, ui.m_verifyMasterKey_lineEdit);

			//Reset the remaining enter attempts counter upon Master Key creation
			//and send a signal with the new Master Key to the parent
			restartEnterAttemptCounter();

			const auto masterKey = ui.m_masterKey_lineEdit->text();
			emit sig_masterKeyCreated(masterKey);
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