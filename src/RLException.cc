#include "RLException.hh"

RLException::RLException(const char* message, ...)
{
  va_list args;
  va_start(args, message);
  msg = new char[MAX_EXCEPTION_TEXT_LENGTH];
  vsprintf( msg, message, args);
  va_end(args);
}

RLException::~RLException() throw()
{
  delete msg;
  msg = NULL;
}

const char* RLException::what() const throw()
{
  return msg;
}
