#pragma once
#include <QtCore/QString>

namespace aether_key_master_core
{
	/**
	 * @brief Class which wraps the Key related data
	*/
	class KeyData
	{
	public:
		explicit KeyData(const QString& title, const QString& username, const QString& password);

		KeyData(const KeyData&) = default;
		KeyData& operator=(const KeyData&) = default;

		KeyData(KeyData&&) = default;
		KeyData& operator=(KeyData&&) = default;

		bool operator==(const KeyData& keyData) const;

		/**
		 * @brief Getter of the title variable
		 * 
		 * @return The title of the Key
		*/
		const QString& title() const;
		/**
		 * @brief Getter of the username variable
		 * 
		 * @return The username used for this Key
		*/
		const QString& username() const;
		/**
		 * @brief Setter of the username variable
		 * 
		 * @param username The new username
		*/
		void setUsername(const QString& username);
		/**
		 * @brief Getter of the password variable
		 * 
		 * @return The password used for this Key
		*/
		const QString& password() const;
		/**
		 * @brief Setter of the password variable
		 * 
		 * @param password The new password
		*/
		void setPassword(const QString& password);

	private:
		/**
		 * @brief The title of the Key
		*/
		QString m_title;
		/**
		 * @brief The username used for this Key
		*/
		QString m_username;
		/**
		 * @brief The password used for this Key
		*/
		QString m_password;
	};
}