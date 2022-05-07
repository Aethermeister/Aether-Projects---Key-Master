#pragma once
#include <QtWidgets/QWidget>

namespace aether_key_master_core
{
	/**
	 * @brief Base class to handle Master Key reset and reset confirmation
	*/
	class MasterKeyResetHandler : public QWidget
	{
		Q_OBJECT

	public:
		MasterKeyResetHandler(QWidget* parent = Q_NULLPTR);
		virtual ~MasterKeyResetHandler() = default;

	protected:
		/**
		 * @brief Reset the previous Master Key and the corresponding Keys data
		*/
		void reset();

	protected slots:
		/**
		* @brief Slot to reset the previous Master Key and the corresponding Keys data
		*/
		void slot_reset();

	private:
		/**
		 * @brief Overwrite and delete the Keys file in the AppData
		*/
		void deleteKeysFile() const;
		/**
		 * @brief Delete the time lock key and enter attempt counter entries from the registry
		*/
		void deleteRegistryEntries() const;

	signals:
		/**
		 * @brief Emitted when the user requests the reset of the Master Key and Keys data
		*/
		void sig_resetRequested();
	};
}