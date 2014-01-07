/** \file CommandLineArgument.hh
    \brief Header file for the CommandLineArgument class.
    \author Rikard Lundmark
*/
/** \file CommandLineArgument.cc
    \brief Source file for the CommandLineArgument class.
    \author Rikard Lundmark
*/


#ifndef CommandLineArgument_hh
#define CommandLineArgument_hh 1 ///Inclusion guard.

using namespace std;

#include <string>
#include <list>
#include "CommandLineException.hh"
#include "RLMacros.hpp"

/** Represents an argument the program expects on the command line.
    Sent to the CommandLineInterpreter, this class will throw a
    CommandLineException if it encounters a flag it does not recognize,or if something else strange occurs.
	Typically, these exceptions should be caught by the caller of Initialize(), and thereafter PrintHelp() should be invoked, whereafter the program should terminate itself.
    
    \author Rikard Lundmark
 */
class CommandLineArgument
{
 public:

  CommandLineArgument(string _flag, ///Flag. Mandatory. Do not include the dashes (--)
					  uint _nArguments = 0, ///Number of arguments to accept. Default: 0
					  bool _mandatory = false, ///Signals if the argument is mandatory.
					  string _description = "", ///Help for the command. Default: empty
					  list<string> _argumentDescription = list<string>(), ///Help for the arguments. Default: no description
					  list<string> _defaultArguments = list<string>() ///Default arguments, may only be used if mandatory is not specified. 
					  ); ///Constructor, sets the members.

  string GetFlag() const; ///Return the flag.
  uint GetNArguments() const; ///Return the number of arguments.
  string GetDescription() const; ///Returns the command description.
  list<string> GetArgumentDescription() const; ///Returns description of the arguments. Guaranteed to contain at most GetNArguments() elements, but may contain fewer.
  list<string> GetDefaultArguments() const; ///Returns the default arguments.
  bool GetMandatory() const;

  bool operator==(const CommandLineArgument &other ///To compare with.
				  ) const; ///Equals operator. Compares the flag only.

private:
  string flag; ///The flag of the command. 
  uint nArguments; ///The arguments of the command.
  bool mandatory; ///Signals if the argument is mandatory.
  string description; ///The description of the command.
  list<string> argumentDescription; ///The description of the arguments of the command.
  list<string> defaultArguments; ///Default arguments, if arguments are not specified.
};
#endif
