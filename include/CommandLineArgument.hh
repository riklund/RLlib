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
#include "CommandLineException.hh"
#include <list>


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
					  unsigned int _nArguments = 0, ///Number of arguments to accept. Default: 0
					  bool _mandatory = false, ///Signals if the argument is mandatory.
					  string _description = "", ///Help for the command. Default: empty
					  list<string> _argumentDescription = list<string>() ///Help for the arguments. Default: no description
					  ); ///Constructor, sets the members.

  string GetFlag() const; ///Return the flag.
  unsigned int GetNArguments() const; ///Return the number of arguments.
  string GetDescription() const; ///Returns the command description.
  list<string> GetArgumentDescription() const; ///Returns description of the arguments. Guaranteed to contain at most GetNArguments() elements, but may contain fewer.
  bool GetMandatory() const;

  bool operator==(const CommandLineArgument &other ///To compare with.
				  ) const; ///Equals operator. Compares the flag only.

private:
  string flag; ///The flag of the command. 
  unsigned int nArguments; ///The arguments of the command.
  bool mandatory; ///Signals if the argument is mandatory.
  string description; ///The description of the command.
  list<string> argumentDescription; ///The description of the arguments of the command.
};
#endif
