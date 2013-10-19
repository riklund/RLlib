#include "VerbosePrinterEventEnabled.hh"

VerbosePrinterEventEnabled::VerbosePrinterEventEnabled()
{
  myPrinter = NULL;
}

VerbosePrinterEventEnabled::~VerbosePrinterEventEnabled()
{
  RemoveListener();
}

void VerbosePrinterEventEnabled::RegisterListener(VerbosePrinter * Listener)
{
  myPrinter = Listener;
  if(myPrinter!=NULL)
    {
      myPrinter->RegisterConnectedEventClass(this);
    }
  for(list<VerbosePrinterEventEnabled *>::iterator it = children.begin(); it!=children.end(); it++)
    {
      if((*it)!=NULL)
	(*it)->RegisterListener(Listener);
    }
}

void VerbosePrinterEventEnabled::RemoveListener()
{
  if(myPrinter!=NULL)
    {
      myPrinter->UnRegisterConnectedEventClass(this);
    }
  myPrinter = NULL;
}

void VerbosePrinterEventEnabled::RegisterChild(VerbosePrinterEventEnabled * child)
{
  children.push_back(child);
}

bool VerbosePrinterEventEnabled::vPrint(int verbosityLevel, const char* message, ...) const
{
  if(myPrinter!=NULL)
    {
      va_list args;
      va_start(args, message);
      myPrinter->va_print(verbosityLevel, message, args);
      va_end(args);
      return true;
    }
  return false;
}
