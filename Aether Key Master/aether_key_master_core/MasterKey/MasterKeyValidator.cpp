#include "MasterKeyValidator.h"
#include "Utility/Utility.h"
#include "MasterKeyValidationException.h"

#include <QtCore/QRegularExpression>

namespace aether_key_master_core
{
	static constexpr const char* ERROR_SEVERITY_TYPE = "error";

	void MasterKeyValidator::validateMasterKeyRequirements(QPointer<User> user, QLineEdit* oldMasterKeyLineEdit, QLineEdit* masterKeyLineEdit, QLineEdit* verifyMasterKeyLineEdit) const
	{
		//Check whether the given old/current Master Key is the one which is currently used
		if (!user->verifyMasterKeyForChange(oldMasterKeyLineEdit->text()))
		{
			changeWidgetSeverityStyle(oldMasterKeyLineEdit, ERROR_SEVERITY_TYPE);
			throw MasterKeyValidationException("Incorrect old Master Key");
		}

		//Run the general validation
		validateMasterKeyRequirements(masterKeyLineEdit, verifyMasterKeyLineEdit);
	}

	void MasterKeyValidator::validateMasterKeyRequirements(QLineEdit* masterKeyLineEdit, QLineEdit* verifyMasterKeyLineEdit) const
	{
		const auto masterKey = masterKeyLineEdit->text();
		const auto verifyMasterKey = verifyMasterKeyLineEdit->text();

		//Check that the given Master Key has the minimum character count
		if (const int minMasterKeySize = 3; masterKey.size() < minMasterKeySize)
		{
			changeWidgetSeverityStyle(masterKeyLineEdit, ERROR_SEVERITY_TYPE);
			throw MasterKeyValidationException(QString("The Master Key must contain at least %0 characters").arg(minMasterKeySize));
		}

		//Check that the given Master Key does not contain eny spaces
		if (masterKey.trimmed().size() != masterKey.size())
		{
			changeWidgetSeverityStyle(masterKeyLineEdit, ERROR_SEVERITY_TYPE);
			throw MasterKeyValidationException("The Master Key must not contain spaces");
		}

		//Check that the Master Key contains lower case letters
		if (!validateMasterKeyWithRegex(masterKey, "[a-z]"))
		{
			changeWidgetSeverityStyle(masterKeyLineEdit, ERROR_SEVERITY_TYPE);
			throw MasterKeyValidationException("The Master Key must contain at least one lower case letter");
		}

		//Check that the Master Key contains upper case letters
		if (!validateMasterKeyWithRegex(masterKey, "[A-Z]"))
		{
			changeWidgetSeverityStyle(masterKeyLineEdit, ERROR_SEVERITY_TYPE);
			throw MasterKeyValidationException("The Master Key must contain at least one upper case letter");
		}

		//Check that the Master Key contains digits
		if (!validateMasterKeyWithRegex(masterKey, "[0-9]"))
		{
			changeWidgetSeverityStyle(masterKeyLineEdit, ERROR_SEVERITY_TYPE);
			throw MasterKeyValidationException("The Master Key must contain at least one digit");
		}

		//Check that the Master Key contains special symbols
		if (!validateMasterKeyWithRegex(masterKey, "[^A-Za-z0-9]"))
		{
			changeWidgetSeverityStyle(masterKeyLineEdit, ERROR_SEVERITY_TYPE);
			throw MasterKeyValidationException("The Master Key must contain at least one special character (e.g.: #, &, @ or $)");
		}

		//Check that the Master Key matches the verified Master Key
		if (masterKey != verifyMasterKey)
		{
			changeWidgetSeverityStyle(masterKeyLineEdit, ERROR_SEVERITY_TYPE);
			changeWidgetSeverityStyle(verifyMasterKeyLineEdit, ERROR_SEVERITY_TYPE);

			throw MasterKeyValidationException("The given Master Keys do not match");
		}
	}
	bool MasterKeyValidator::validateMasterKeyWithRegex(const QString& masterKey, const QString& regexPattern) const
	{
		//Create a regex with the given pattern and return the match result
		const QRegularExpression regex(regexPattern);
		const auto& match = regex.match(masterKey);
		return match.hasMatch();
	}
}