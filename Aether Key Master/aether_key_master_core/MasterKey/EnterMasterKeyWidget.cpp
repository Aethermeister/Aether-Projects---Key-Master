#include "EnterMasterKeyWidget.h"
#include "Utility/Utility.h"

#include <QtCore/QFile>
#include <QtCore/QSettings>

namespace aether_key_master_core
{
	static constexpr const char* OVERWRITEPATTERN = "00000000000000000000000000000000000000000000000000";

	EnterMasterKeyWidget::EnterMasterKeyWidget(QWidget* parent)
		: QWidget(parent)
	{
		ui.setupUi(this);

		initializeUi();
		initializeConnections();
	}

	void EnterMasterKeyWidget::initializeUi()
	{
		//Set the properties of the error QLabel
		//The error QLabel takes its place even if it is hidden
		auto errorInformationLabelSizePolicy = ui.m_errorInformation_lbl->sizePolicy();
		errorInformationLabelSizePolicy.setRetainSizeWhenHidden(true);
		ui.m_errorInformation_lbl->setSizePolicy(errorInformationLabelSizePolicy);
		ui.m_errorInformation_lbl->setVisible(false);

		//Show the appripriate error message on initialization
		adjustErrorMessage();
	}
	void EnterMasterKeyWidget::initializeConnections() const
	{
		connect(ui.m_enter_btn, &QPushButton::clicked, this, &EnterMasterKeyWidget::slot_enterMasterKey);
		connect(ui.m_reset_btn, &QPushButton::clicked, this, &EnterMasterKeyWidget::slot_reset);
	}

	void EnterMasterKeyWidget::deleteKeysFile() const
	{
		//Overwrite the Keys file with dummy data and delete the file
		writeKeysFile(OVERWRITEPATTERN);
		QFile::remove(appdataFolder() + KEYSFILE);
	}

	void EnterMasterKeyWidget::deleteRegistryEntries() const
	{
		//Remove the time lock key and remaining attempts counter registry entries
		QSettings settings;
		settings.remove(TIMELOCKENTRYNAME);
		settings.remove(REMAININGENTERATTEMPTSENTRYNAME);
	}

	void EnterMasterKeyWidget::adjustErrorMessage()
	{
		//Get the remaining attempts counter and check whether the error QLabel should be shown
		const auto attempts = remainingEnterAttempts();
		const auto shouldShowError = attempts < MAXENTERATTEMPTS;
		if (shouldShowError)
		{
			//Update the error QLabel text with the current counter value
			ui.m_errorInformation_lbl->setText(QString("%0 attempt(s) remaining until automatic reset").arg(attempts));
		}

		ui.m_errorInformation_lbl->setVisible(shouldShowError);
	}

	int EnterMasterKeyWidget::decreaseRemainingEnterAttempts() const
	{
		//Get the remaining attempts counter value and decrease it
		//and save the new value in the registry
		auto attempts = remainingEnterAttempts();

		QSettings settings;
		settings.setValue(REMAININGENTERATTEMPTSENTRYNAME, --attempts);

		return attempts;
	}

	void EnterMasterKeyWidget::slot_enterMasterKey()
	{
		//Get the Master Key from the UI and validate it
		const auto masterKey = ui.m_masterKey_lineEdit->text();

		//If the user is not nullptr after the verification the Master Key is valid
		if (auto user = User::verifyMasterKeyForEnter(masterKey); user)
		{
			//Reset the enter attempts counter and send signal to the parent so the GUI can be changed
			restartEnterAttemptCounter();
			emit sig_masterKeyAccepted(user);
		}
		else
		{
			//Change the severityType dynamic property of the QLineEdit so it indicates error
			changeWidgetSeverityStyle(ui.m_masterKey_lineEdit, "error");

			//Decrease the remaining attempts
			const auto remainingAttempts = decreaseRemainingEnterAttempts();
			//If the remaining attempts counter value reaches 0 initiate the Master Key and Keys data reset
			if(remainingAttempts <= 0)
			{
				restartEnterAttemptCounter();
				slot_reset();
			}
		}

		adjustErrorMessage();
	}

	void EnterMasterKeyWidget::slot_reset()
	{
		//Delete the Keys file and the registry entries
		deleteKeysFile();
		deleteRegistryEntries();

		//send signal to the parent so the GUI can be changed
		emit sig_resetRequested();
	}
}