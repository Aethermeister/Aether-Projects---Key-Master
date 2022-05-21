#include "KeysDataParentWidget.h"
#include "AddNewKeyDataWidget.h"
#include "MasterKey/ChangeMasterKeyWidget.h"
#include "Aether CPP Logger/include/Logger.h"

#include <QtCore/QDebug>

namespace aether_key_master_core
{
	KeysDataParentWidget::KeysDataParentWidget(QPointer<User> user, QWidget* parent)
		: MasterKeyResetHandler(parent), m_user(user)
	{
		ui.setupUi(this);

		initializeUI();
		initializeConnections();
	}

	void KeysDataParentWidget::initializeUI()
	{
		ui.m_keyData_widget->setUser(m_user);
		ui.m_keyData_widget->setVisible(false);
		listKeys();
	}

	void KeysDataParentWidget::initializeConnections() const
	{
		connect(ui.m_addNew_btn, &QPushButton::clicked, this, &KeysDataParentWidget::slot_showAddKeyDataWidget);
		connect(ui.m_changeMasterKey_btn, &QPushButton::clicked, this, &KeysDataParentWidget::slot_showChangeMasterKeyWidget);
		connect(ui.m_reset_btn, &QPushButton::clicked, this, &KeysDataParentWidget::slot_reset);

		connect(ui.m_keys_listWidget, &QListWidget::itemClicked, this, &KeysDataParentWidget::slot_keyItemSelected);
		connect(ui.m_keyData_widget, &KeyDataWidget::sig_keyDataDeleted, this, &KeysDataParentWidget::slot_keyDataDeleted);
	}

	void KeysDataParentWidget::listKeys()
	{
		//Cleat the QListWidget because it will be repopulated
		ui.m_keys_listWidget->clear();

		//Get the user's stored KeyData list and create a list item for each
		const auto& storedKeysData = m_user->storedKeys();
		for (const auto& keyData : storedKeysData)
		{
			ui.m_keys_listWidget->addItem(keyData.title());
		}

		//Check whether a list item should be selected (e.g.: adding a new KeyData while an other KeyData item is already selected)
		for (int i = 0; i < ui.m_keys_listWidget->count(); ++i)
		{
			const auto listItem = ui.m_keys_listWidget->item(i);
			if (listItem->text() == m_lastSelectedKey)
			{
				listItem->setSelected(true);
				break;
			}
		}
	}

	void KeysDataParentWidget::showKeyDataWidget()
	{
		//Check whether the KeyData widget should be visible or hidden
		if (m_lastSelectedKey.isEmpty())
		{
			//If there is no valid last used KeyData hide the KeyData widget and reset its content
			ui.m_keyData_widget->setVisible(false);
			ui.m_keyData_widget->resetKeyData();
		}
		else
		{
			//If there is a valid last used KeyData show the KeyData widget and initialize it with the selected KeyData
			ui.m_keyData_widget->setVisible(true);
			
			for (auto& keyData : m_user->storedKeys())
			{
				if (keyData.title() == m_lastSelectedKey)
				{
					ui.m_keyData_widget->initializeKeyData(&keyData);
					break;
				}
			}
		}
	}

	void KeysDataParentWidget::slot_showAddKeyDataWidget()
	{
		//Show the AddNewKeyDataWidget so a new KeyData can be added
		QPointer<AddNewKeyDataWidget> addKeyDataWidget = new AddNewKeyDataWidget(m_user, this);
		addKeyDataWidget->show();

		connect(addKeyDataWidget, &AddNewKeyDataWidget::sig_newKeyDataAdded, this, &KeysDataParentWidget::listKeys);
	}

	void KeysDataParentWidget::slot_showChangeMasterKeyWidget()
	{
		//Show the ChangeMasterKeyWidget so the user can change the Master Key
		QPointer<ChangeMasterKeyWidget> changeMasterKeyWidget = new ChangeMasterKeyWidget(m_user, this);
		changeMasterKeyWidget->show();
	}

	void KeysDataParentWidget::slot_keyDataDeleted()
	{
		//Reset the last used KeyData and the UI
		m_lastSelectedKey = "";
		showKeyDataWidget();

		ui.m_keys_listWidget->clearSelection();
		listKeys();
	}

	void KeysDataParentWidget::slot_keyItemSelected(const QListWidgetItem* item)
	{
		//Check whether this is a new selection or an already selected item is deselected
		//and modify the UI according to the new selection/deselection
		if (const auto selectedKey = item->text(); m_lastSelectedKey == selectedKey)
		{
			ui.m_keys_listWidget->clearSelection();
			m_lastSelectedKey = "";
		}
		else
		{
			m_lastSelectedKey = selectedKey;
		}

		showKeyDataWidget();
	}
}