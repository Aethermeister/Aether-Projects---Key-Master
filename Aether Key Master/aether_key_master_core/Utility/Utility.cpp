#include "Utility.h"

#include <QtCore/QSettings>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QStandardPaths>

void changeWidgetSeverityStyle(QWidget* widget, const QString& severityValue)
{
	widget->setProperty("severityType", severityValue);

	widget->style()->unpolish(widget);
	widget->style()->polish(widget);
}

void setWidgetSizeRetain(QWidget* widget, const bool retainSize)
{
	auto widgetSizePolicy = widget->sizePolicy();
	widgetSizePolicy.setRetainSizeWhenHidden(retainSize);
	widget->setSizePolicy(widgetSizePolicy);
}

QString appdataFolder()
{
	const auto& appdataFolderPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/";

	if (const QDir appdataDir(appdataFolderPath); !appdataDir.exists())
	{
		appdataDir.mkpath(appdataFolderPath);
	}

	return appdataFolderPath;
}

QString readKeysFile()
{
	QFile keysFile(appdataFolder() + KEYSFILE);
	keysFile.open(QIODevice::ReadOnly);

	const auto& compressedKeysData = keysFile.readAll();
	const auto& keysData = uncompressData(compressedKeysData);

	return keysData;
}

void writeKeysFile(const QString& keysData)
{
	QFile keysFile(appdataFolder() + KEYSFILE);
	keysFile.open(QIODevice::WriteOnly);

	const auto& compressedKeysData = compressData(keysData.toUtf8());
	keysFile.write(compressedKeysData);

	keysFile.close();
}

QString keysFileTimeLockKey()
{
	const QSettings settings;
	return settings.value(TIMELOCKENTRYNAME).toString();
}

void storeKeysFileTimeLockKey(const QString& timeLockKey)
{
	QSettings settings;
	settings.setValue(TIMELOCKENTRYNAME, timeLockKey);
}

void restartEnterAttemptCounter()
{
	QSettings settings;
	settings.setValue(REMAININGENTERATTEMPTSENTRYNAME, MAXENTERATTEMPTS);
}

int remainingEnterAttempts()
{
	QSettings settings;
	return settings.value(REMAININGENTERATTEMPTSENTRYNAME, 0).toInt();
}

QString dataToBase64(const QString& data)
{
	return data.toUtf8().toBase64();
}

QString dataFromBase64(const QString& base64Data)
{
	return QByteArray::fromBase64(base64Data.toUtf8());
}

QByteArray compressData(const QByteArray& data)
{
	return qCompress(data, COMPRESSIONLEVEL);
}

QByteArray uncompressData(const QByteArray& data)
{
	return qUncompress(data);
}