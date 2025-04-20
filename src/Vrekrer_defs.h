#ifndef VREKRER_SCPI_DEFS_H_
#define VREKRER_SCPI_DEFS_H_

/// Library version
#define VREKRER_SCPI_VERSION "v0.6.0"

/// Max number of valid tokens.
#ifndef SCPI_MAX_TOKENS
#define SCPI_MAX_TOKENS 15
#endif

/// Max number of registered commands.
#ifndef SCPI_MAX_COMMANDS
#define SCPI_MAX_COMMANDS 20
#endif

/// Max number of registered special commands.
#ifndef SCPI_MAX_SPECIAL_COMMANDS
#define SCPI_MAX_SPECIAL_COMMANDS 0
#endif

/// Length of the message buffer.
#ifndef SCPI_BUFFER_LENGTH
#define SCPI_BUFFER_LENGTH 64
#endif

/// Max branch size of the command tree and max number of parameters.
#ifndef SCPI_ARRAY_SYZE
#define SCPI_ARRAY_SYZE 6
#endif

/// Integer size used for hashes.
#ifndef SCPI_HASH_TYPE
#define SCPI_HASH_TYPE uint8_t
#endif

#endif