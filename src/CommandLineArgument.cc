#include "CommandLineArgument.hh"

CommandLineArgument::CommandLineArgument(string _flag, unsigned int _nArguments, bool _mandatory, string _description, list<string> _argumentDescription, list<string> _defaultArguments)
  :flag(_flag), nArguments(_nArguments), mandatory(_mandatory), description(_description), argumentDescription(_argumentDescription), defaultArguments(_defaultArguments)
{
  if(flag.size() < 1)
	{
	  throw CommandLineException("Invalid size of command flag: must have at least one character.");
	}
  if(flag[0] == '-')
	{
	  throw CommandLineException("You are using the command line arguments in the wrong way: do not supply initial '-' character.");
	}
  if(argumentDescription.size() > nArguments)
	{
	  throw CommandLineException("Invalid number of command line parameter descriptions supplied.");
	}
  if(defaultArguments.size() > nArguments)
	{
	  throw CommandLineException("Invalid number of default arguments supplied for command.");
	}
  if(defaultArguments.size() > 0 && mandatory )
	{
	  throw CommandLineException("Cannot have default arguments for a mandatory argument.");
	}
  if(defaultArguments.size() > 0 && defaultArguments.size() != nArguments)
	{
	  throw CommandLineException("Need to specify either all or none arguments with default value.");
	}
}

string CommandLineArgument::GetFlag() const
{
  return flag;
}

unsigned int CommandLineArgument::GetNArguments() const
{
  return nArguments;
}

string CommandLineArgument::GetDescription() const
{
  return description;
}

list<string> CommandLineArgument::GetArgumentDescription() const
{
  return argumentDescription;

}

bool CommandLineArgument::operator==(const CommandLineArgument &other) const
{
  return other.flag == flag;
}

bool CommandLineArgument::GetMandatory() const
{
  return mandatory;
}

list<string> CommandLineArgument::GetDefaultArguments() const
{
  return defaultArguments;
}
