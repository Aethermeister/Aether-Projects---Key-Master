#pragma once

#include <QtCore/QString>

#include <QtWidgets/QWidget>
#include <QtWidgets/QStyle>
#include <QtWidgets/QLayout>

/**
 * @brief Name of the Keys file stored in the APPDATA
*/
constexpr const char* KEYSFILE = "ksf.akm";
/**
 * @brief Name of the time lock key registry entry
*/
constexpr const char* TIMELOCKENTRYNAME = "kftlk";
/**
 * @brief Name of the remaining enter attempts registry entry
*/
constexpr const char* REMAININGENTERATTEMPTSENTRYNAME = "rea";
/**
 * @brief Maximum number of invalid enter attempts
*/
constexpr int MAXENTERATTEMPTS = 5;
/**
 * @brief zlib compression level used before file writing
*/
constexpr int COMPRESSIONLEVEL = 3;

/**
 * @brief Removes the given object type the the parent widget and parent layout and deletes the removed object
 * 
 * @tparam T The object type which has to be removed
 * @param parentWidget The parent widget which has the T object as a child
 * @param parentLayout The layout of the parent widget which aligns the T object
*/
template<typename T>
void deleteContentWidget(QWidget* parentWidget, QLayout* parentLayout);
/**
 * @brief Changes the severityType dynamic property of of the given QWidget to the given new severity value
 * 
 * @param widget The widget which dynamic property has to change
 * @param severityValue The new severtity property value
*/
void changeWidgetSeverityStyle(QWidget* widget, const QString& severityValue);

/**
 * @brief Sets the RetainSizeWhenHidden of the given widget
 * 
 * @param widget The QWidget which RetainSizeWhenHidden property has to be set
 * @param retainSize The flag to set the RetainSizeWhenHidden property
*/
void setWidgetSizeRetain(QWidget* widget, const bool retainSize);
/**
 * @brief Get the application specific APPDATA folder path and create it if it does not exist
 * 
 * @return The path to the application specific APPDATA folder
*/
QString appdataFolder();
/**
 * @brief Read the Keys file and return its base64 content
 * 
 * @return The base64 content of the Keys file
*/
QString readKeysFile();
/**
 * @brief Write the given Keys data to the Keys file
 * 
 * @param keysData The Keys data which has to be written to the Keys file
*/
void writeKeysFile(const QString& keysData);

/**
 * @brief Get the time lock key stored in the registry
 * 
 * @return The time lock key
*/
QString keysFileTimeLockKey();
/**
 * @brief Get the time lock key stored in the registry
 *
 * @return The time lock key
*/
void storeKeysFileTimeLockKey(const QString& timeLockKey);

/**
 * @brief Reset the enter attempt counter in the registry
*/
void restartEnterAttemptCounter();
/**
 * @brief Get the remaining enter attempt counter stored in the registry
 * 
 * @return The remaining enter attempt counter
*/
int remainingEnterAttempts();

/**
 * @brief Converts the given data QString to base64
 * 
 * @param data The data which has to be converted to base64
 * 
 * @return The base64 version of the original data
*/
QString dataToBase64(const QString& data);
/**
 * @brief Converts the given base64 data QString to UTF8
 * 
 * @param data The data which has to be converted from base64
 * 
 * @return The UTF8 version of the base64 data
*/
QString dataFromBase64(const QString& base64Data);
/**
 * @brief Compress the given data with zlib
 *
 * @param data The data which has to be compressed
 *
 * @return The compressed data
*/
QByteArray compressData(const QByteArray& data);
/**
 * @brief Uncompress the given data with zlib
 *
 * @param data The data which has to be uncompressed
 *
 * @return The uncompressed data
*/
QByteArray uncompressData(const QByteArray& data);


template<typename T>
void deleteContentWidget(QWidget* parentWidget, QLayout* parentLayout)
{
	//Get the T object of the parent widget and convert it to QWidget
	auto* widgetToDelete = dynamic_cast<QWidget*>(parentWidget->findChild<T>());

	//If the T object was found remove it from the parent widget and layout and delete the object
	if (widgetToDelete)
	{
		parentLayout->removeWidget(widgetToDelete);
		widgetToDelete->setParent(nullptr);
		widgetToDelete->deleteLater();
	}
}