#include "KeysDataParentWidget.h"
#include "AddNewKeyDataWidget.h"

namespace aether_key_master_core
{
	KeysDataParentWidget::KeysDataParentWidget(QPointer<User> user, QWidget* parent)
		: QWidget(parent), m_user(user)
	{
		ui.setupUi(this);

		initializeConnections();
	}

	void KeysDataParentWidget::initializeConnections() const
	{
		connect(ui.m_addNew_btn, &QPushButton::clicked, this, &KeysDataParentWidget::slot_showAddKeyDataWidget);
	}

	void KeysDataParentWidget::slot_showAddKeyDataWidget() const
	{
		//Show the AddNewKeyDataWidget so a new KeyData can be added
		QPointer<AddNewKeyDataWidget> addKeyDataWidget = new AddNewKeyDataWidget(m_user);
		addKeyDataWidget->show();
	}
}