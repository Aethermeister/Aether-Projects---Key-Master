#include "CreateMasterKeyWidget.h"
#include "Aether CPP Logger/include/Logger.h"
#include "MasterKeyValidationException.h"
#include "Utility/Utility.h"
#include "User.h"

#include <QtCore/QDebug>
#include <QtCore/QRegularExpression>

namespace aether_key_master_core
{
	static constexpr const char* ERRORSEVERITYTYPE = "error";

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

	void CreateMasterKeyWidget::validateMasterKeyRequirements(const QString& masterKey, const QString& verifyMasterKey) const
	{
		//Check that the given Master Key has the minimum character count
		if (const int minMasterKeySize = 3; masterKey.size() < minMasterKeySize)
		{
			changeWidgetSeverityStyle(ui.m_masterKey_lineEdit, ERRORSEVERITYTYPE);
			throw MasterKeyValidationException(QString("The Master Key must contain at least %0 characters").arg(minMasterKeySize));
		}

		//Check that the given Master Key does not contain eny spaces
		if (masterKey.trimmed().size() != masterKey.size())
		{
			changeWidgetSeverityStyle(ui.m_masterKey_lineEdit, ERRORSEVERITYTYPE);
			throw MasterKeyValidationException("The Master Key must not contain spaces");
		}

		//Check that the Master Key contains lower case letters
		if (!validateMasterKeyWithRegex(masterKey, "[a-z]"))
		{
			changeWidgetSeverityStyle(ui.m_masterKey_lineEdit, ERRORSEVERITYTYPE);
			throw MasterKeyValidationException("The Master Key must contain at least one lower case letter");
		}

		//Check that the Master Key contains upper case letters
		if (!validateMasterKeyWithRegex(masterKey, "[A-Z]"))
		{
			changeWidgetSeverityStyle(ui.m_masterKey_lineEdit, ERRORSEVERITYTYPE);
			throw MasterKeyValidationException("The Master Key must contain at least one upper case letter");
		}

		//Check that the Master Key contains digits
		if (!validateMasterKeyWithRegex(masterKey, "[0-9]"))
		{
			changeWidgetSeverityStyle(ui.m_masterKey_lineEdit, ERRORSEVERITYTYPE);
			throw MasterKeyValidationException("The Master Key must contain at least one digit");
		}

		//Check that the Master Key contains special symbols
		if (!validateMasterKeyWithRegex(masterKey, "[^A-Za-z0-9]"))
		{
			changeWidgetSeverityStyle(ui.m_masterKey_lineEdit, ERRORSEVERITYTYPE);
			throw MasterKeyValidationException("The Master Key must contain at least one special character (e.g.: #, &, @ or $)");
		}

		//Check that the Master Key matches the verified Master Key
		if (masterKey != verifyMasterKey)
		{
			changeWidgetSeverityStyle(ui.m_masterKey_lineEdit, ERRORSEVERITYTYPE);
			changeWidgetSeverityStyle(ui.m_verifyMasterKey_lineEdit, ERRORSEVERITYTYPE);

			throw MasterKeyValidationException("The given Master Keys do not match");
		}
	}

	bool CreateMasterKeyWidget::validateMasterKeyWithRegex(const QString& masterKey, const QString& regexPattern) const
	{
		//Create a regex with the given pattern and return the match result
		const QRegularExpression regex(regexPattern);
		const auto& match = regex.match(masterKey);
		return match.hasMatch();
	}

	void CreateMasterKeyWidget::slot_createMasterKey()
	{
		AETHER_LOG_INFO("Creating Master Key");

		//Reset the style of the QLineEdits
		changeWidgetSeverityStyle(ui.m_masterKey_lineEdit, "");
		changeWidgetSeverityStyle(ui.m_verifyMasterKey_lineEdit, "");

		//Get the given Master Keys
		const auto& masterKey = ui.m_masterKey_lineEdit->text();
		const auto& verifyMasterKey = ui.m_verifyMasterKey_lineEdit->text();

		try
		{
			//Validate the Master Keys
			//If the given Master Key is invalid an exception is thrown
			validateMasterKeyRequirements(masterKey, verifyMasterKey);

			//Reset the remaining enter attempts counter upon Master Key creation
			//and send a signal with the new Master Key to the parent
			restartEnterAttemptCounter();
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