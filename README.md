# Vrekrer scpi parser
A simple [SCPI](https://en.wikipedia.org/wiki/Standard_Commands_for_Programmable_Instruments) parser for Arduino projects.

## Features
- Small memory footprint, implemented for reduced RAM usage.
- Minimal, clean code API.
- Can process `char*` strings or input from any [Stream](https://www.arduino.cc/reference/en/language/functions/communication/stream/) interface like [Serial](https://www.arduino.cc/reference/en/language/functions/communication/serial) or [Ethernet](https://www.arduino.cc/en/Reference/Ethernet).
- Flash strings ([F() macro](https://www.arduino.cc/reference/en/language/variables/utilities/progmem/#_the_f_macro)) support for lower RAM usage.
- Automatic `Stream` communication errors handling (timeout, buffer overflow)


## SCPI features:
- Commands defined using strings
  E.g. `"MEASure:VOLTage:DC?"`
- Short and long token forms, and upper and lower case commands
  E.g. `"MEASURE:VOLTAGE:DC?"`, `"meas:VoLt:DC?"`
- Numeric suffixes using the `#` character:
  E.g. definition : `"CHANnel#:SELect"`
  E.g. usage : `"CHAN0:SEL"`, `"chan5:sel"`, `"chan13:sel"`
- Comma separated parameters recognition.
- Parameters treated as text, processed by the user program.
- Option to process large raw data parameters.

## Installation
To use the Vrekrer SCPI parser in your Arduino project, first install it using the Library Manager in the Arduino IDE. Then, include the header file:

```cpp
#include "Vrekrer_scpi_parser.h"
```

## Configuration
You can customize the parser's behavior by defining the following macros *before* including the header file.

```cpp
/// Max number of valid tokens.
#define SCPI_MAX_TOKENS 15
/// Max number of registered commands.
#define SCPI_MAX_COMMANDS 20
/// Max number of registered special commands.
#define SCPI_MAX_SPECIAL_COMMANDS 0
/// Length of the message buffer.
#define SCPI_BUFFER_LENGTH 64
/// Max branch size of the command tree and max number of parameters.
#define SCPI_ARRAY_SYZE 6
/// Integer size used for hashes.
#define SCPI_HASH_TYPE uint8_t
```

You also have the option to define a custom error code enumeration. To do this, define the `SCPI_CUSTOM_ERROR_CODES` macro and then declare your custom `ErrorCode` enum *before* including the header file.

```cpp
/// Define custom error codes if necessary
#define SCPI_CUSTOM_ERROR_CODES

/// SCPI Error codes.
enum class ErrorCode
{
    /// No error
    NoError = 0,
    /// Unknown command received.
    UnknownCommand,
    /// Timeout before receiving the termination chars.
    Timeout,
    /// Message buffer overflow.
    BufferOverflow,
    /// Add your custom error codes here
    CustomError1,
    CustomError2
};

#include "Vrekrer_scpi_parser.h"
```

**Important:** When using custom definitions and/or a custom `ErrorCode` enumeration, ensure the following order in your Arduino sketch:

1. Define all custom macros (e.g., `SCPI_MAX_TOKENS`).
2. If using custom error codes, define the `SCPI_CUSTOM_ERROR_CODES` macro.
3. If using custom error codes, define your custom `ErrorCode` enumeration.
4. Include the `Vrekrer_scpi_parser.h` header file: `#include "Vrekrer_scpi_parser.h"`