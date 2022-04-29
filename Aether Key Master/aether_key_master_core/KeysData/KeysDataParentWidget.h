#pragma once
#include "User.h"

#include <QWidget>
#include "ui_KeysDataParentWidget.h"

namespace aether_key_master_core
{
	/**
	 * @brief Main GUI class for the Key Data related widget presentation
	*/
	class KeysDataParentWidget : public QWidget
	{
		Q_OBJECT

	public:
		KeysDataParentWidget(QPointer<User> user, QWidget* parent = Q_NULLPTR);
		~KeysDataParentWidget() = default;

	private:
		Ui::KeysDataParentWidget ui;
	};
}