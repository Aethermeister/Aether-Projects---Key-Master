#include "KeysDataParentWidget.h"
#include "AddNewKeyDataWidget.h"
#include "MasterKey/ChangeMasterKeyWidget.h"
#include "Aether CPP Logger/include/Logger.h"

namespace aether_key_master_core
{
	KeysDataParentWidget::KeysDataParentWidget(QPointer<User> user, QWidget* parent)
		: MasterKeyResetHandler(parent), m_user(user)
	{
		ui.setupUi(this);

		initializeConnections();
	}

	void KeysDataParentWidget::initializeConnections() const
	{
		connect(ui.m_addNew_btn, &QPushButton::clicked, this, &KeysDataParentWidget::slot_showAddKeyDataWidget);
		connect(ui.m_changeMasterKey_btn, &QPushButton::clicked, this, &KeysDataParentWidget::slot_showChangeMasterKeyWidget);
		connect(ui.m_reset_btn, &QPushButton::clicked, this, &KeysDataParentWidget::slot_reset);
	}

	void KeysDataParentWidget::slot_showAddKeyDataWidget()
	{
		//Show the AddNewKeyDataWidget so a new KeyData can be added
		QPointer<AddNewKeyDataWidget> addKeyDataWidget = new AddNewKeyDataWidget(m_user, this);
		addKeyDataWidget->show();
	}

	void KeysDataParentWidget::slot_showChangeMasterKeyWidget()
	{
		//Show the ChangeMasterKeyWidget so the user can change the Master Key
		QPointer<ChangeMasterKeyWidget> changeMasterKeyWidget = new ChangeMasterKeyWidget(m_user, this);
		changeMasterKeyWidget->show();
	}
}