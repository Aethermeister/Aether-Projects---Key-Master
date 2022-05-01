#include "User.h"
#include "Utility/Utility.h"

#include <QtCore/QPointer>

#include <QtCore/QRandomGenerator>
#include <QtCore/QDateTime>

#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>

namespace aether_key_master_core
{
	User::User(const QString& masterKey, QObject* parent) : QObject(parent), m_masterKey(masterKey)
	{
	}

	User::User(const QString& masterKey, const QString& rawKeysData, QObject* parent) : QObject(parent), m_masterKey(masterKey)
	{
		//Convert the raw Keys data to JSON object
		const auto keysJsonDocument = QJsonDocument::fromJson(rawKeysData.toUtf8());
		const auto keysJsonArray = keysJsonDocument.array();

		//Iterate over the Keys JSON array and extract teh Key Data from it
		for (const auto& arrayValue : keysJsonArray)
		{
			const auto keyObject = arrayValue.toObject();

			m_storedKeys.append(
				KeyData(
					keyObject["title"].toString(),
					keyObject["username"].toString(),
					keyObject["password"].toString()
				)
			);
		}
	}

	QPointer<User> User::verifyMasterKeyForEnter(const QString& masterKey)
	{
		//Get the content of the Keys file
		auto base64MergedKeysData = readKeysFile();

		//Get the time lock key from the registry and its base64 data
		const auto timeLockKey = keysFileTimeLockKey();
		const auto base64TimeLockKey = dataToBase64(timeLockKey);

		//Remove the time lock key from the data read from the Keys file
		base64MergedKeysData = base64MergedKeysData.remove(base64TimeLockKey);
		
		//Convert the user given Master Key to base64 and check if the remaining Keys data (with the Master Key) contains the given Master Key
		if (const auto& base64MasterKey = dataToBase64(masterKey); 
			!masterKey.isEmpty() && base64MergedKeysData.contains(base64MasterKey))
		{
			//If the Keys data contains the given Master Key than remove it from the string and get the JSON formatted Keys data
			base64MergedKeysData = base64MergedKeysData.remove(base64MasterKey);
			const auto& keysData = dataFromBase64(base64MergedKeysData);

			//Create and return a User object which contains the extracted Keys data
			return new User(masterKey, keysData);
		}

		return nullptr;
	}

	void User::saveKeys() const
	{
		//Get the base64 Keys data and Master Key
		const auto base64KeysData = generateKeysData();
		const auto base64MasterKey = dataToBase64(m_masterKey);

		//Get the time lock key and its base64 data
		const auto keysFileTimeLockKey = generateKeysFileTimeLockKey();
		const auto base64KeysFileTimeLockKey = dataToBase64(keysFileTimeLockKey);
		//Save the current time lock key to the registry
		storeKeysFileTimeLockKey(keysFileTimeLockKey);

		//Merge the individual data into one QString and write it into the Keys file
		const auto mergedData = generateMergedKeysData(base64KeysFileTimeLockKey, base64MasterKey, base64KeysData);
		writeKeysFile(mergedData);
	}

	const QVector<KeyData>& User::storedKeys() const
	{
		return m_storedKeys;
	}

	void User::addKeyData(const KeyData& keyData)
	{
		m_storedKeys.append(keyData);
	}

	QString User::generateKeysData() const
	{
		//Convert hte Key Data to JSON format
		QJsonArray keysArray;
		for (const auto& keyData : m_storedKeys)
		{
			QJsonObject keyObject;
			keyObject["title"] = keyData.title();
			keyObject["username"] = keyData.username();
			keyObject["password"] = keyData.password();
			keysArray.append(keyObject);
		}

		//Return the JSON formatted Keys data as a QString
		const auto keysDoc = QJsonDocument(keysArray);
		return dataToBase64(keysDoc.toJson());
	}

	QString User::generateKeysFileTimeLockKey() const
	{
		//Get the elapsed seconds since 1970 and return it as a QString
		const auto currentDateTime = QDateTime::currentDateTime();
		const auto secsSinceEpoch = QString::number(currentDateTime.toSecsSinceEpoch());

		return secsSinceEpoch;
	}
	QString User::generateMergedKeysData(const QString& base64KeysFileTimeLockKey, const QString& base64MasterKey, const QString& base64KeysData) const
	{
		QString mergedData = base64KeysData;
		const int randomOffsetModifier = 2;

		//Calculate the random position where the Master Key SALT has to be placed and insert it into the original Keys data
		const int masterKeyInsertPosition = QRandomGenerator::global()->bounded(mergedData.size() - randomOffsetModifier);
		mergedData.insert(masterKeyInsertPosition, base64MasterKey);

		//Calculate the random position where the time lock key SALT has to be placed and insert it into the original Keys data modified with the Master Key
		const int timeLockKeyInsertPosition = QRandomGenerator::global()->bounded(mergedData.size() - randomOffsetModifier);
		mergedData.insert(timeLockKeyInsertPosition, base64KeysFileTimeLockKey);

		return mergedData;
	}
}