#include "FadeInAnimation.h"

#include <QtCore/QPropertyAnimation>
#include <QtCore/QPointer>

namespace aether_key_master_core
{
	FadeInAnimation::FadeInAnimation(QWidget* parent)
		: QWidget(parent)
	{
	}

	void FadeInAnimation::showEvent(QShowEvent* event)
	{
		initializeAnimation();

		QWidget::showEvent(event);
	}

	void FadeInAnimation::initializeAnimation()
	{
		//Create a property animation which changes the window opacity over time
		QPointer<QPropertyAnimation> fadeInAnimation = new QPropertyAnimation(this, "windowOpacity");
		fadeInAnimation->setDuration(m_animationDuration);
		fadeInAnimation->setStartValue(0);
		fadeInAnimation->setEndValue(1);

		fadeInAnimation->start();
	}
}