#include "KeyData.h"

namespace aether_key_master_core
{
	KeyData::KeyData(const QString& title, const QString& username, const QString& password) :
		m_title(title), m_username(username), m_password(password)
	{
	}
	bool KeyData::operator==(const KeyData& keyData) const
	{
		return m_title == keyData.title();
	}
	const QString& KeyData::title() const
	{
		return m_title;
	}
	const QString& KeyData::username() const
	{
		return m_username;
	}
	void KeyData::setUsername(const QString& username)
	{
		m_username = username;
	}
	const QString& KeyData::password() const
	{
		return m_password;
	}
	void KeyData::setPassword(const QString& password)
	{
		m_password = password;
	}
}