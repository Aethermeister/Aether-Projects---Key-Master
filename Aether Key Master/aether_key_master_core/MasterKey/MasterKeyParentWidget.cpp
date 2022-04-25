#include "MasterKeyParentWidget.h"
#include "Utility/Utility.h"
#include "MasterKey/CreateMasterKeyWidget.h"
#include "MasterKey/EnterMasterKeyWidget.h"

#include <QtCore/QPointer>
#include <QtCore/QFile>

namespace aether_key_master_core
{
	MasterKeyParentWidget::MasterKeyParentWidget(QWidget* parent)
		: QWidget(parent)
	{
		ui.setupUi(this);

		initializeUi();
	}

	void MasterKeyParentWidget::initializeUi()
	{
		//Check the existence and integrity of the Keys file
		//and show the create or enter Master Key widget accordingly
		if (checkKeysFileIntegrity())
		{
			showEnterMasterKeyWidget();
		}
		else
		{
			showCreateMasterKeyWidget();
		}
	}

	bool MasterKeyParentWidget::checkKeysFileIntegrity() const
	{
		//Check the existence of the Keys file and the time lock key in the registry
		if (QFile::exists(appdataFolder() + KEYSFILE) &&
			!keysFileTimeLockKey().isEmpty())
		{
			//Get the content of the Keys file and the time lock key
			const auto& base64MergedKeysData = readKeysFile();
			const auto& timeLockKey = keysFileTimeLockKey();
			const auto& base64TimeLockKey = dataToBase64(timeLockKey);

			//Check whether the Keys file contains the time lock key
			return base64MergedKeysData.contains(base64TimeLockKey);
		}

		return false;
	}

	void MasterKeyParentWidget::showCreateMasterKeyWidget()
	{
		//Delete the previous widget from the content area
		deleteContentWidget<QWidget*>(ui.m_masterKeyContainer_frame, ui.m_masterKeyContainer_layout);

		//Create a CreateMasterKeyWidget object and show it in the content area
		QPointer<CreateMasterKeyWidget> createMasterKeyWidget = new CreateMasterKeyWidget(ui.m_masterKeyContainer_frame);
		ui.m_masterKeyContainer_layout->addWidget(createMasterKeyWidget);

		connect(createMasterKeyWidget, &CreateMasterKeyWidget::sig_masterKeyCreated, this, &MasterKeyParentWidget::slot_masterKeyCreated);
	}

	void MasterKeyParentWidget::showEnterMasterKeyWidget()
	{
		//Delete the previous widget from the content area
		deleteContentWidget<QWidget*>(ui.m_masterKeyContainer_frame, ui.m_masterKeyContainer_layout);

		//Create a EnterMasterKeyWidget object and show it in the content area
		QPointer<EnterMasterKeyWidget> enterMasterKeyWidget = new EnterMasterKeyWidget(ui.m_masterKeyContainer_frame);
		ui.m_masterKeyContainer_layout->addWidget(enterMasterKeyWidget);

		connect(enterMasterKeyWidget, &EnterMasterKeyWidget::sig_resetRequested, this, &MasterKeyParentWidget::slot_resetRequested);
		connect(enterMasterKeyWidget, &EnterMasterKeyWidget::sig_masterKeyAccepted, this, &MasterKeyParentWidget::slot_masterKeyAccepted);
	}

	void MasterKeyParentWidget::slot_masterKeyCreated(const QString& masterKey)
	{
		//Create a new User object and create an initial Keys file
		QPointer<User> user = new User(masterKey);
		user->saveKeys();

		//Send the authentication done signal with the User object as parameter so the GUI can be changed on higher level
		emit sig_authenticationDone(user);
	}

	void MasterKeyParentWidget::slot_resetRequested()
	{
		//Show the create Master Key widget 
		showCreateMasterKeyWidget();
	}

	void MasterKeyParentWidget::slot_masterKeyAccepted(QPointer<User> user)
	{
		//Send the authentication done signal with the User object as parameter so the GUI can be changed on higher level
		emit sig_authenticationDone(user);
	}
}