#pragma once
#include "MasterKeyValidator.h"

#include <QWidget>
#include "ui_CreateMasterKeyWidget.h"

namespace aether_key_master_core
{
	/**
	 * @brief GUI class which provides methods to create a new Master Key
	*/
	class CreateMasterKeyWidget : public QWidget, public MasterKeyValidator
	{
		Q_OBJECT

	public:
		CreateMasterKeyWidget(QWidget* parent = Q_NULLPTR);
		virtual ~CreateMasterKeyWidget() = default;

	private:
		Ui::CreateMasterKeyWidget ui;

		/**
		 * @brief Initialize the default UI state
		*/
		void initializeUi();
		/**
		 * @brief Initialize the default signal-slot connections
		*/
		void initializeConnections() const;

	private slots:
		/**
		 * @brief Slot to handle the user invoked Master Key creation
		*/
		void slot_createMasterKey();

	signals:
		/**
		 * @brief Emitted when the new Master Key meets the minimum requirements
		*/
		void sig_masterKeyCreated(const QString& masterKey);
	};
}