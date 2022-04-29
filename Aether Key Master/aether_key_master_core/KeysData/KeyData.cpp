#include "KeyData.h"

namespace aether_key_master_core
{
	KeyData::KeyData(const QString& title, const QString& username, const QString& password) :
		m_title(title), m_username(username), m_password(password)
	{
	}
	const QString& KeyData::title() const
	{
		return m_title;
	}
	const QString& KeyData::username() const
	{
		return m_username;
	}
	const QString& KeyData::password() const
	{
		return m_password;
	}
}