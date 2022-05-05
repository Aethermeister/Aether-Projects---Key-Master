#include "FadeInAnimation.h"

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
		m_fadeInAnimation->setParent(this);

		m_fadeInAnimation->setTargetObject(this);
		m_fadeInAnimation->setPropertyName("windowOpacity");

		m_fadeInAnimation->setDuration(m_animationDuration);
		m_fadeInAnimation->setStartValue(0);
		m_fadeInAnimation->setEndValue(1);

		m_fadeInAnimation->start();
	}
}