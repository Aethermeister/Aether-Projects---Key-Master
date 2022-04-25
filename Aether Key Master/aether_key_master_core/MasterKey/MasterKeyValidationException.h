#pragma once
#include <QtCore/QString>
#include <exception>

namespace aether_key_master_core
{
	/**
	 * @brief Unique exception based class for the Master Key validation
	*/
	class MasterKeyValidationException : public std::exception
	{
	public:
		explicit MasterKeyValidationException(const char* message);
		explicit MasterKeyValidationException(const QString& message);
		~MasterKeyValidationException() override = default;
	};
}