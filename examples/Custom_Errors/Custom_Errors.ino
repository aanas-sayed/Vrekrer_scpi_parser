/*
Vrekrer_scpi_parser library.
SCPI Custom Errors  example.

Demonstrate how to add custom error codes.
These include :
  Adding a custom error code enumeration with custom error codes.

Hardware required: None

Commands:
  *IDN?
    Gets the instrument's identification string

  SYSTem:ERRor?
    Reads the last error occurred and then delete it.

  ENABle
    Sets the parameter to "ON", "1", "OFF", or "0".
    If the parameter is something else, the custom error is triggered.
*/

#include "Arduino.h"

/// To add a custom error enumeration, define SCPI_CUSTOM_ERROR_CODES
/// followed by the custom ErrorCode enumeration.
/// 1. SCPI_CUSTOM_ERROR_CODES must be defined.
/// 2. The custom ErrorCode enumeration must be defined.
/// 3. #include "Vrekrer_scpi_parser.h" after both the SCPI_CUSTOM_ERROR_CODES
///    definition and the custom ErrorCode enumeration.
#define SCPI_CUSTOM_ERROR_CODES

/// Custom SCPI Error codes.
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
  /// Invalid parameter.
  InvalidParameter
};

#include "Vrekrer_scpi_parser.h"

SCPI_Parser my_instrument;

void setup()
{
  my_instrument.RegisterCommand(F("*IDN?"), &Identify);
  my_instrument.RegisterCommand(F("SYSTem:ERRor?"), &GetLastEror);
  // This command accepts the parameters "ON", "1", "OFF", or "0".
  // Set to something else to trigger the custom error.
  my_instrument.RegisterCommand(F("ENABle"), &SetParameter);
  // Check out Error_Handling example for details about error handlers.

  Serial.begin(9600);

  /*
  Timeout time can be changed even during program execution
  */
  my_instrument.timeout = 10; // value in miliseconds. Default value = 10
}

void loop()
{
  my_instrument.ProcessInput(Serial, "\n");
}

void Identify(SCPI_C commands, SCPI_P parameters, Stream &interface)
{
  interface.println(
      F("Vrekrer,Error Handling Example,#00," VREKRER_SCPI_VERSION));
}

void SetParameter(SCPI_C commands, SCPI_P parameters, Stream &interface)
{
  String first_parameter = String(parameters.First());
  first_parameter.toUpperCase();
  if ((first_parameter == "ON") || (first_parameter == "1"))
  {
    return;
  }
  else if ((first_parameter == "OFF") || (first_parameter == "0"))
  {
    return;
  }
  my_instrument.last_error = ErrorCode::InvalidParameter;
}

void GetLastEror(SCPI_C commands, SCPI_P parameters, Stream &interface)
{
  switch (my_instrument.last_error)
  {
  case ErrorCode::BufferOverflow:
    interface.println(F("Buffer overflow error"));
    break;
  case ErrorCode::Timeout:
    interface.println(F("Communication timeout error"));
    break;
  case ErrorCode::UnknownCommand:
    interface.println(F("Unknown command received"));
    break;
  case ErrorCode::NoError:
    interface.println(F("No Error"));
    break;
  case ErrorCode::InvalidParameter:
    interface.println(F("Invalid parameter"));
    break;
  }
  my_instrument.last_error = ErrorCode::NoError;
}
