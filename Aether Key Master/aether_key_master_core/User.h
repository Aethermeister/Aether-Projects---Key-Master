#pragma once
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QMap>

namespace aether_key_master_core
{
	/**
	 * @brief Class to manage the Master Key, Keys and Keys file
	*/
	class User : public QObject
	{
		Q_OBJECT

	public:
		/**
		 * @brief Create a User object with the Master Key only
		 * 
		 * @param masterKey The Master Key thi User object is created with
		 * @param parent Parent of this object
		*/
		explicit User(const QString& masterKey, QObject* parent = Q_NULLPTR);
		/**
		 * @brief Create a User object with the Master Key and Keys data
		 * 
		 * @param masterKey The Master Key thi User object is created with
		 * @param rawKeysData The Keys data in JSON format
		 * @param parent Parent of this object
		*/
		explicit User(const QString& masterKey, const QString& rawKeysData, QObject* parent = Q_NULLPTR);

		/**
		 * @brief Check whether the given Master Key is valid 
		 * 
		 * @param masterKey The user given Master Key
		 * 
		 * @return The User pointer which contains the Master Key and Keys data if the given Master Key is valid
		*/
		static QPointer<User> verifyMasterKeyForEnter(const QString& masterKey);

		/**
		 * @brief Saves the Keys data to the KEys file in the AppData
		*/
		void saveKeys() const;

	private:
		/**
		 * @brief The Master Key (master password) which secures the other Keys (passwords)
		*/
		QString m_masterKey;
		/**
		 * @brief The Keys map which contains the names and passwords the user stores
		*/
		QMap<QString, QString> m_storedKeys;

		/**
		 * @brief Convert the stored Keys map into JSON format
		 * 
		 * @return The converted Keys data in JSON format
		*/
		QString generateKeysData() const;
		/**
		 * @brief Generates a SALT from the current time which is used to lock the Keys file and secure its integrity
		 * 
		 * @return The SALT created from the current time
		*/
		QString generateKeysFileTimeLockKey() const;

		/**
		 * @brief Creates a merged string from the parameter given data
		 * 
		 * @param base64KeysFileTimeLockKey The base64 data of the time lock SALT
		 * @param base64MasterKey The base64 data of the Master Key SALT
		 * @param base64KeysData The actual keys data in base64
		 * 
		 * @return The merged base64 data
		*/
		QString generateMergedKeysData(const QString& base64KeysFileTimeLockKey, const QString& base64MasterKey, const QString& base64KeysData) const;
	};
}