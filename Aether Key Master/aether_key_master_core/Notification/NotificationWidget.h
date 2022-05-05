#pragma once
#include "Animation/FadeInAnimation.h"

#include <QWidget>
#include "ui_NotificationWidget.h"

namespace aether_key_master_core
{
	/**
	 * @brief GUI class to show notifications
	*/
	class NotificationWidget : public FadeInAnimation
	{
		Q_OBJECT

	public:
		NotificationWidget(const QString& message, QWidget* parent = Q_NULLPTR);

		virtual bool eventFilter(QObject* watched, QEvent* event) override;

	private:
		Ui::NotificationWidget ui;

		/**
		 * @brief The message which has to be displayed
		*/
		QString m_message;

		/**
		 * @brief Initialize the default UI state
		*/
		void initializeUI();
		/**
		 * @brief Initialize the default signal-slot connections
		*/
		void initializeConnections() const;

		/**
		 * @brief Move the notification widget to the bottom center of the parent widget
		*/
		void moveToPosition();

	private slots:
		/**
		 * @brief Slot to handle the widget behaviour after the animation is finished
		*/
		void slot_fadeInAnimationFinished();
	};
}