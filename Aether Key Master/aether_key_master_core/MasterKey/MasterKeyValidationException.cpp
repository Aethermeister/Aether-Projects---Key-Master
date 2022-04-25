#include "MasterKeyValidationException.h"

namespace aether_key_master_core
{
	MasterKeyValidationException::MasterKeyValidationException(const char* message) : std::exception(message)
	{
	}

	MasterKeyValidationException::MasterKeyValidationException(const QString& message) : std::exception(message.toStdString().c_str())
	{
	}
}