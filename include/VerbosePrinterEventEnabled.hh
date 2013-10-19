/**\file VerbosePrinterEventEnabled.hh
   \author Rikard Lundmark
   \brief Header file for the VerbosePrinterEventEnabled class.
*/
/**\file VerbosePrinterEventEnabled.cc
   \author Rikard Lundmark
   \brief Source file for the VerbosePrinterEventEnabled class.
*/




#ifndef VerbosePrinterEventEnabled_hh
#define VerbosePrinterEventEnabled_hh 1

#include <list>
#include <stdarg.h>

#include "VerbosePrinter.hh"

/**Classes using VerbosePrinter usually wants to implement this class.
   \author Rikard Lundmark
 */
class VerbosePrinterEventEnabled
{
 public:
  VerbosePrinterEventEnabled(); //!<Constructs the object.
  ~VerbosePrinterEventEnabled(); //!<Destroys the object.
  void RegisterListener(VerbosePrinter * Listener //!<The listener to register.
			);//!<Registers the VerbosePrinter listener with this object.
  void RemoveListener();  //!<Unregisters the listener.
 protected:
  VerbosePrinter * myPrinter; //!<Pointer to the registered VerbosePrinter, if any.
  bool vPrint(int verbosityLevel, //!<The verbosity level of this message. Used by the VerbosePrinter to determine if it should be printed or not.
	      const char* message, //!<The message to print.
	      ... //!<Any arguments to this message (like printf...).
	      ) const; //!<Called to print 
  void RegisterChild(VerbosePrinterEventEnabled * child //!<The child to add.
		     ); //!<Registers a child. If a VerbosePrinter is added, all children will also add it.
 private:
  list<VerbosePrinterEventEnabled *> children; //!<The registered children.

};
#endif
