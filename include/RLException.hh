#include <exception>
#include <stdarg.h>
#include <stdio.h>
#define MAX_EXCEPTION_TEXT_LENGTH 1024

#ifndef RLException_hh
#define RLException_hh 1

using namespace std;

class RLException : public exception
{
  
private:
  char * msg; ///  The reason of the exception to be thrown.

public:
  RLException(const char* message = "Exception!", ...); ///Constructor. Variable arguments.

  ~RLException() throw(); /// Destructor.
  const char* what() const throw(); /// Retrieves the reason of the exception.
};

#endif
