#include "NotificationWidget.h"

#include <QtCore/QTimer>
#include <QtCore/QDebug>

namespace aether_key_master_core
{
	NotificationWidget::NotificationWidget(const QString& message, QWidget* parent)
		: FadeInAnimation(parent), m_message(message)
	{
		ui.setupUi(this);

		initializeUI();
		initializeConnections();
		//Install the parent's event filter so the notification widget can be moved
		parent->installEventFilter(this);
	}

	bool NotificationWidget::eventFilter(QObject* watched, QEvent* event)
	{
		//If the parent widget is the sender and 
		//the event is resize or move move the notification to its new position
		if (watched == parentWidget() &&
			(event->type() == QEvent::Resize || event->type() == QEvent::Move))
		{
			moveToPosition();
		}

		return FadeInAnimation::eventFilter(watched, event);
	}

	void NotificationWidget::initializeUI()
	{
		//Set the properties of the widget
		setAttribute(Qt::WA_DeleteOnClose);
		setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

		setMaximumWidth(parentWidget()->width() / 2);
		ui.m_message_lbl->setText(m_message);

		moveToPosition();

		//Start timer to close the notification widget after 5 sec
		QTimer::singleShot(5000, this, [this]
			{
				close();
			});
	}

	void NotificationWidget::initializeConnections() const
	{
		connect(m_fadeInAnimation, &QPropertyAnimation::finished, this, &NotificationWidget::slot_fadeInAnimationFinished);
	}

	void NotificationWidget::moveToPosition()
	{
		//Move the notification widget to the center of the parent widget and
		//than move it to the bottom of the parent widget
		auto notificationPosition = parentWidget()->geometry().center() - geometry().center();
		notificationPosition.setY(notificationPosition.y() + parentWidget()->geometry().height() / 2 - height() - 10);
		move(mapToGlobal(notificationPosition));
	}

	void NotificationWidget::slot_fadeInAnimationFinished()
	{
		setWindowOpacity(0.85);
	}
}