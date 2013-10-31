#include "CommandLineInterpreter.hh"

void CommandLineInterpreter::SetDescription(string _description)
{
  description = _description;
}

void CommandLineInterpreter::AddCommandLineArgument(CommandLineArgument toAdd)
{
  myAcceptableArguments.push_back(toAdd);
}

void CommandLineInterpreter::Initialize(unsigned int argc, char * argv[])
{
  if(initialized)
	{
	  throw CommandLineException("Tried to reinitialize the command line interpreter.");
	}
  initialized=true;
  if(argc < 1)
	{
	  throw CommandLineException("Too few arguments provided. This cannot be the input to the program.");
	}
  programName = argv[0];

  for(unsigned int i = 1; i<argc; i++)
    {
      string temp(argv[i]);
      if(temp[0]=='-') //we have a flag...
		{
		  while(temp[0]=='-' && temp.size() > 0)
			temp = temp.substr(1,temp.size());
		  if(temp.size() == 0)
			throw CommandLineException("Invalid flag: length was zero.");
		  
		  bool found = false;
		  for(list<CommandLineArgument>::iterator it = myAcceptableArguments.begin(); it!=myAcceptableArguments.end(); it++)
			{
			  if(temp.compare(it->GetFlag())==0)
				{
				  if(i+it->GetNArguments()>=argc)
					throw CommandLineException("Insufficient number of arguments for flag.\n");
				  vector<string> myList;
				  for(unsigned int k = i+1; k<=i+it->GetNArguments(); k++)
					{
					  string tmp(argv[k]);
					  if(tmp[0]=='-')
						{
						  char buffer[300];
						  sprintf(buffer, "Insufficient number of parameters for flag %s.",temp.c_str());
						  throw CommandLineException(buffer);
						}
					  myList.push_back(tmp);
					}
				  myFlaggedCommands[temp] = myList;
				  i+=it->GetNArguments();
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
  for(list<CommandLineArgument>::const_iterator it = myAcceptableArguments.begin(); it!=myAcceptableArguments.end(); ++it)
	{
	  if(myFlaggedCommands.find(it->GetFlag()) == myFlaggedCommands.end())
		{
		  if(it->GetMandatory())
			{
			  char buffer[300];
			  sprintf(buffer, "A mandatory argument (%s) was omitted.",it->GetFlag().c_str());
			  throw CommandLineException(buffer);
			}
		  else
			{
			  if(!it->GetDefaultArguments().empty()) ///Fill in default arguments.
				{
				  list<string> defaultArgs = it->GetDefaultArguments();
				  myFlaggedCommands[it->GetFlag()] = vector<string>();
				  for(list<string>::const_iterator iq = defaultArgs.begin(); iq != defaultArgs.end(); ++iq)
					{
					  myFlaggedCommands[it->GetFlag()].push_back(*iq);
					}
				}
			}
		}
  
	}
}


CommandLineInterpreter::CommandLineInterpreter(list<CommandLineArgument> _myAcceptableArguments, string _description)
  :myAcceptableArguments(_myAcceptableArguments), description(_description)
{
  initialized=false;
}

vector<string> CommandLineInterpreter::ReadFlaggedCommandStrict(string flag)
{
  if(myFlaggedCommands.find(flag)!=myFlaggedCommands.end())
    {
      if(myFlaggedCommands[flag].empty())
		myFlaggedCommands[flag].push_back("");
      return myFlaggedCommands[flag];
    }
  else
    {
	  char buffer[300];
	  sprintf(buffer, "Strict lookup of command flag '%s' failed.", flag.c_str());
      throw CommandLineException(buffer);
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


void CommandLineInterpreter::PrintHelp()
{
  cerr << endl;
  cerr << programName.substr(2,programName.size()) << ": " << description << endl;

  bool hasMandatory = false;
  bool hasNonMandatory = false;
  for(list<CommandLineArgument>::const_iterator it = myAcceptableArguments.begin(); it!=myAcceptableArguments.end(); ++it)
	{
	  if(it->GetMandatory())
		hasMandatory = true;
	  else
		hasNonMandatory = true;
	}

  cerr << "Synopsis: " << programName;
  if(hasMandatory)
	cerr << " mandatory_args";
  if(hasNonMandatory)
	cerr << " [optional_args]";
  cerr << endl;
  cerr << setiosflags(ios::left);
  cerr << endl;
  cerr << setw(40) << "Command description:" << endl;
  cerr << endl;
  for(int m = 1; m>=0; --m)
	{
	  if( (m==1 && hasMandatory) || (m==0 && hasNonMandatory) )
		{
		  stringstream sts;
		  sts << "The following arguments are " << ((m>0)?"MANDATORY":"OPTIONAL") << ":" ;
		  cerr << setw(40) << sts.str() << endl;
		  for(list<CommandLineArgument>::const_iterator it = myAcceptableArguments.begin(); it!=myAcceptableArguments.end(); ++it)
			{
			  if((m == 1 && it->GetMandatory()) || (m == 0 && !it->GetMandatory()))
				{
				  stringstream ss;
				  ss << "--" << it->GetFlag();
				  list<string> argumentDescription = it->GetArgumentDescription();
				  for(list<string>::const_iterator ip = argumentDescription.begin(); ip!=argumentDescription.end(); ++ip)
					{
					  ss << " <" << (*ip) << ">";
					}
				  list<string> defaultArguments = it->GetDefaultArguments(); 
				  stringstream pp;
				  if(!defaultArguments.empty())
					{
					  pp << "[Default:";
					  for(list<string>::const_iterator ip = defaultArguments.begin(); ip!=defaultArguments.end(); ++ip)
						{
						  pp << " " << (*ip);
						}
					  pp << "]";
					}
				  cerr << setw(5) << " " << setw(40) << ss.str() << " " << it->GetDescription() << setw(20) << pp.str() << endl;
				}
			}
		  cerr << endl;
		}
	}
  cerr << endl;
  return;
}
