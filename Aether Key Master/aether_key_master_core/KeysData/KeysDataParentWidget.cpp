#include "KeysDataParentWidget.h"

#include <QtCore/QPointer>

namespace aether_key_master_core
{
	KeysDataParentWidget::KeysDataParentWidget(QPointer<User> user, QWidget* parent)
		: QWidget(parent)
	{
		ui.setupUi(this);

	}
}