#pragma once

#include <QtWidgets/QWidget>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QPointer>

namespace aether_key_master_core
{
	/**
	 * @brief Base class to handle fade in animation of widgets
	*/
	class FadeInAnimation : public QWidget
	{
		Q_OBJECT

	public:
		FadeInAnimation(QWidget* parent = Q_NULLPTR);

	protected:
		virtual void showEvent(QShowEvent* event) override;

		/**
		 * @brief Member variable which handles the animation
		 * It is initialized in the header so the derived classes can use it during construction
		*/
		QPointer<QPropertyAnimation> m_fadeInAnimation = new QPropertyAnimation();

	private:
		/**
		 * @brief The duration of the fade in animation in ms
		*/
		int m_animationDuration = 250;

		/**
		 * @brief Initialize the fade in animation
		*/
		void initializeAnimation();
	};
}