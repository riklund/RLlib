#include "CommandLineInterpreter.hh"

CommandLineInterpreter::CommandLineInterpreter(int argc, char *argv[], list<CommandLineArgument> myAcceptableFlags)
{
  for(int i = 0; i<argc; i++)
    {
      string temp(argv[i]);
      if(temp[0]=='-') //we have a flag...
	{
	  while(temp[0]=='-' && temp.size() > 0)
	    temp = temp.substr(1,temp.size());
	  if(temp.size() == 0)
	    throw CommandLineException("Invalid flag: length was zero.");

	  bool found = false;
	  for(list<CommandLineArgument>::iterator it = myAcceptableFlags.begin(); it!=myAcceptableFlags.end(); it++)
	    {
	      if(temp.compare(it->flag)==0)
		{
		  if(i+it->numberOfArguments>argc)
		    throw CommandLineException("Insufficient arguments for flag.\n");
		  vector<string> myList;
		  for(int k = i+1; k<=i+it->numberOfArguments; k++)
		    {
		      string tmp(argv[k]);
		      myList.push_back(tmp);
		    }
		  myFlaggedCommands[temp] = myList;
		  i+=it->numberOfArguments;
		  found=true;
		}
	    }
	  if(!found)
	    {
	      char buffer[300];
	      sprintf(buffer,"Command flag not recognized: '%s'.", temp.c_str());
	      throw CommandLineException(buffer);	  
	    }
	}
      else
	{
	  myFlaglessCommands.push_back(argv[i]);
	}
    }
}

vector<string> CommandLineInterpreter::ReadFlaggedCommand(string flag)
{
  if(myFlaggedCommands.find(flag)!=myFlaggedCommands.end())
    {
      if(myFlaggedCommands[flag].empty())
	myFlaggedCommands[flag].push_back("");
      return myFlaggedCommands[flag];
    }
  else
    {
      return vector<string>();
    }
}

vector<string> CommandLineInterpreter::ReadFlaglessCommands()
{
  return myFlaglessCommands;
}
