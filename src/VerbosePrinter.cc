#include "VerbosePrinter.hh"

VerbosePrinter::VerbosePrinter(int verbosityLevel)
{
  myFile = NULL;
  myVerbosityLevel = verbosityLevel;
}

VerbosePrinter::VerbosePrinter(int verbosityLevel, string fileName)
{
  myVerbosityLevel = verbosityLevel;
  myFile = fopen(fileName.c_str(), "w");
}

VerbosePrinter::~VerbosePrinter()
{
  if( myFile != NULL )
    fclose(myFile);
}

bool VerbosePrinter::Print(int verbosityLevel, const char* message, ...)
{
  va_list args;
  va_start(args, message);
  bool retval = va_print(verbosityLevel, message, args);
  va_end(args);
  return retval;
}

bool VerbosePrinter::va_print(int verbosityLevel, const char* message, va_list args)
{
  if(verbosityLevel<=myVerbosityLevel)
    {
      if(myFile!=NULL)
	{
	  vfprintf( myFile, message, args );
	}
      else
	{
	  vprintf( message, args );
	  fflush(stdout);
	}
      return true;
    }
  else
    {
      return false;
    }
}

list<VerbosePrinterEventEnabled *> VerbosePrinter::GetConnectedEventClasses()
{
  return myConnectedEventClasses;
}

bool VerbosePrinter::RegisterConnectedEventClass(VerbosePrinterEventEnabled * myEvent)
{
  if(find(myConnectedEventClasses.begin(), myConnectedEventClasses.end(), 
	  myEvent)==myConnectedEventClasses.end())
    {
      myConnectedEventClasses.push_back(myEvent);
      return true;
    }
  else
    return false;
}

bool VerbosePrinter::UnRegisterConnectedEventClass(VerbosePrinterEventEnabled * myEvent)
{
  myConnectedEventClasses.remove(myEvent);
  return true;
}

int VerbosePrinter::GetVerbosityLevel() const
{
  return myVerbosityLevel;
}
