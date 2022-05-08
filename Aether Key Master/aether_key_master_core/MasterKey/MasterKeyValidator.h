#pragma once
#include "User.h"

#include <QtCore/QPointer>
#include <QtWidgets/QLineEdit>

namespace aether_key_master_core
{
	/**
	 * @brief This class holds the essentials to handle the validation of the user's Master Key
	*/
	class MasterKeyValidator
	{
	public:
		MasterKeyValidator() = default;
		virtual	~MasterKeyValidator() = default;

	protected:
		/**
		 * @brief Check the currently used Master Key and validate the given new Master Key whether it meets the minimum requirements
		 * 
		 * @param user The user whose Master Key has to be changed
		 * @param oldMasterKeyLineEdit The QLineEdit object for the old/current Master Key
		 * @param masterKeyLineEdit The QLineEdit object for the new Master Key
		 * @param verifyMasterKeyLineEdit The QLineEdit object for the verification of the new Master Key
		*/
		void validateMasterKeyRequirements(QPointer<User> user, QLineEdit* oldMasterKeyLineEdit, QLineEdit* masterKeyLineEdit, QLineEdit* verifyMasterKeyLineEdit) const;
		/**
		 * @brief Validate the given Master Key whether it meets the minimum requirements
		 *
		 * @param masterKeyLineEdit The QLineEdit object for the new Master Key
		 * @param verifyMasterKeyLineEdit The QLineEdit object for the verification of the new Master Key
		*/
		void validateMasterKeyRequirements(QLineEdit* masterKeyLineEdit, QLineEdit* verifyMasterKeyLineEdit) const;

	private:
		/**
		 * @brief Check the given Master Key with a regex
		 *
		 * @param masterKey The Master Key which has to be checked
		 * @param regexPattern The pattern of the regex matched on the Master Key
		 *
		 * @return The matching result of the regex
		*/
		bool validateMasterKeyWithRegex(const QString& masterKey, const QString& regexPattern) const;
	};
}