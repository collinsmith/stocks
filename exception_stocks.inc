/**
 * Contains stocks related to logging runtime errors, referred to as
 * "exceptions". While not treated as a runtime exception in another language,
 * this provides a simplified API to log common errors, such as when an illegal
 * argument is detected.
 */

#if defined _exception_stocks_included
  #endinput
#endif
#define _exception_stocks_included

#include <amxmodx>
#include <logger>

#if !defined AMX_ERR_ASSERT
  #define AMX_ERR_ASSERT 2
#endif

#tryinclude "include/stocks/simple_logger_stocks.inc"
#if !defined _simple_logger_stocks_included
  #include <simple_logger_stocks>
#endif

enum Exception {
  AssertionException,
  IllegalArgumentException,
  IllegalStateException,
  IOException,
  SocketException,
  UnsupportedOperationException,
};

stock const Exceptions[Exception][] = {
  "AssertionException",
  "IllegalArgumentException",
  "IllegalStateException",
  "IOException",
  "SocketException",
  "UnsupportedOperationException",
};

/*******************************************************************************
 * STOCKS
 ******************************************************************************/

#define message_length 1023
static stock tmpErr[message_length + 1];

stock ThrowAssertionException(const msg[] = "", any: ...) {
  vformat(tmpErr, message_length, msg, 2);
  Throw(AMX_ERR_ASSERT, Exceptions[AssertionException], tmpErr);
}

stock ThrowIllegalArgumentException(const msg[] = "", any: ...) {
  vformat(tmpErr, message_length, msg, 2);
  Throw(AMX_ERR_PARAMS, Exceptions[IllegalArgumentException], tmpErr);
}

stock ThrowIllegalStateException(const msg[] = "", any: ...) {
  vformat(tmpErr, message_length, msg, 2);
  Throw(AMX_ERR_GENERAL, Exceptions[IllegalStateException], tmpErr);
}

stock ThrowIOException(const msg[] = "", any: ...) {
  vformat(tmpErr, message_length, msg, 2);
  Throw(AMX_ERR_GENERAL, Exceptions[IOException], tmpErr);
}

stock ThrowSocketException(const msg[] = "", any: ...) {
  vformat(tmpErr, message_length, msg, 2);
  Throw(AMX_ERR_GENERAL, Exceptions[SocketException], tmpErr);
}

stock ThrowUnsupportedOperationException(const msg[] = "", any: ...) {
  vformat(tmpErr, message_length, msg, 2);
  Throw(AMX_ERR_GENERAL, Exceptions[UnsupportedOperationException], tmpErr);
}

stock Throw(error = AMX_ERR_GENERAL, const exception[], const msg[] = "", any: ...) {
  static message[message_length + 1];
  new len = copy(message, message_length, exception);
  len += copy(message[len], message_length - len, ": ");
  len += vformat(message[len], message_length - len, msg, 4);  
  loge(message);
  log_error(error, message);
}