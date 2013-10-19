
/**\file VerbosePrinter.hh
   \author Rikard Lundmark
   \brief Header file for the VerbosePrinter class.
*/
/**\file VerbosePrinter.cc
   \author Rikard Lundmark
   \brief Source file for the VerbosePrinter class.
*/

#ifndef VerbosePrinter_hh
#define VerbosePrinter_hh 1 //! Inclusion guard


using namespace std;

#include <stdio.h>
#include <string>
#include <stdarg.h>
#include <list>
#include <algorithm>


class VerbosePrinterEventEnabled;
/**A class used to print messages to the user, which prints all messages it receives with a verbosity level lower than a set level.
   Classes wanting to use this should extend VerbosePrinterEventEnabled. They can call the print(int, char*, ...) or va_print(int, char, va_list, ...) functions to print messages.

   \author Rikard Lundmark
 */
class VerbosePrinter 
{
 public:
  VerbosePrinter(int verbosityLevel //!<The verbosity level.
		 ); //!<Creates a VerbosePrinter with the stated verbosityLevel.

  VerbosePrinter(int verbosityLevel, //!<The verbosity level.
		 string fileName //!<The filename to redirect the output to.
		 ); //!<Creates a VerbosePrinter with the stated verbosityLevel and redirects output to the file fileName.

  ~VerbosePrinter(); //!<Destroys the printer.

  bool Print(int verbosityLevel, //!< The verbosity level to print with.
	     const char* , //!<The string to print
	     ... //!<Other arguments to send to vprintf.
	     ); //!<Print message to user or file. \returns True if the message was printed, false if it was not. \note No messages with a too high verbosity level are printed.

  bool va_print(int verbosityLevel, //!<The verbosity level to print with.
		const char*, //!<The string to print.
		va_list args //!<Other arguments to send to vprintf.
		); //!<Print message to user or file. \returns True if the message was printed, false if it was not. \note No messages with a too high verbosity level are printed.
  
  list<VerbosePrinterEventEnabled *> GetConnectedEventClasses(); //!<VerbosePrinterEventEnabled automatically registers with the VerbosePrinter object, and the VerbosePrinterEventEnabled object is added to this list. \returns all the connected VerbosePrinterEventEnabled classes.

  bool RegisterConnectedEventClass(VerbosePrinterEventEnabled * myEvent //!<The VerbosePrinterEventEnabled to register.
				   ); //!<Registers a connected event class (of type VerbosePrinterEventEnabled).
  bool UnRegisterConnectedEventClass(VerbosePrinterEventEnabled * myEvent //!<Registers a connected event class. \note This registered class is not currently being used for anything. \returns True if the class was registered.
				     ); //!<Unregisters a connected event class. \note This registered class is not currently being used for anything. \returns True if the class was removed.

  int GetVerbosityLevel() const; //!<Returns the verbosity level of this VerbosePrinter. \returns The verbosity level.

 private:
  list<VerbosePrinterEventEnabled *> myConnectedEventClasses; //!<The connected event classes.
  int myVerbosityLevel; //!<The verbosity level of the printer.
  FILE * myFile; //!<The file to print to, if any.
};
#endif
