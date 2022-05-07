#include "MasterKeyResetHandler.h"
#include "Notification/VerificationWidget.h"
#include "Aether CPP Logger/include/Logger.h"
#include "Utility/Utility.h"

#include <QtCore/QFile>
#include <QtCore/QSettings>

namespace aether_key_master_core
{
	/**
	 * @brief The Keys file is overwritten with this value before the deletion of the file
	*/
	static constexpr const char* OVERWRITE_PATTERN = "00000000000000000000000000000000000000000000000000";

	MasterKeyResetHandler::MasterKeyResetHandler(QWidget* parent) : QWidget(parent)
	{

	}
	
	void MasterKeyResetHandler::slot_reset()
	{
		//Show the verification widget to confirm the reset of the Master Key
		QPointer<VerificationWidget> verificationWidget = new VerificationWidget("By resetting the Master Key you will lose all previously saved data\n\n"
			"Do you confirm?", this);
		verificationWidget->show();

		//If the user confirms the reset of the Master Key reset it
		QObject::connect(verificationWidget, &VerificationWidget::sig_verificationConfirmed, [this]
			{
				AETHER_LOG_INFO("Resetting Master Key by user request");
				reset();
			});
	}
	void MasterKeyResetHandler::reset()
	{
		//Delete the Keys file and the registry entries
		deleteKeysFile();
		deleteRegistryEntries();

		//send signal to the parent so the GUI can be changed
		emit sig_resetRequested();
	}
	void MasterKeyResetHandler::deleteKeysFile() const
	{
		//Overwrite the Keys file with dummy data and delete the file
		writeKeysFile(OVERWRITE_PATTERN);
		QFile::remove(appdataFolder() + KEYSFILE);
	}
	void MasterKeyResetHandler::deleteRegistryEntries() const
	{
		//Remove the time lock key and remaining attempts counter registry entries
		QSettings settings;
		settings.remove(TIMELOCKENTRYNAME);
		settings.remove(REMAININGENTERATTEMPTSENTRYNAME);
	}
}