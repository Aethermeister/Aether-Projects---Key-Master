#pragma once

#include <QtWidgets/QWidget>

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