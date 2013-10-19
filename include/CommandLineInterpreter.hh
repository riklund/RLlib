/**\file CommandLineInterpreter.hh
   \brief Header file for the CommandLineInterpreter class.
   \author Rikard Lundmark
*/
/**\file CommandLineInterpreter.cc
   \brief Source file for the CommandLineInterpreter class.
   \author Rikard Lundmark
*/

#ifndef CommandLineInterpreter_hh
#define CommandLineInterpreter_hh 1 //!<Inclusion guard.

#include <string>
#include <vector>
#include <map>
#include <list>
#include <stdio.h>

#include "CommandLineArgument.hh"
#include "CommandLineException.hh"

using namespace std;


/**Interprets command line arguments according to a list of CommandLineArguments (acceptable flags), and throws an exception if unknown flags are encountered.

   \author Rikard Lundmark
 */
class CommandLineInterpreter
{
 public:
  CommandLineInterpreter(int argc, //!<The number of command line arguments.
			 char *argv[], //!<The actual arguments.
			 list<CommandLineArgument> myAcceptableFlags //!<The flags which should be accepted by this interpreter.
			 );
  //!< Constructor. \exception CommandLineException if the CommandLineArguments does not match argv and argc (if there are unknown flags).

  vector<string> ReadFlaggedCommand(string flag //!<The flag to read
				    );//!<Returns a vector<string> containing all arguments for a specific flag. Returns an empty vector if there are no arguments for this flag.
  
  vector<string> ReadFlaglessCommands(); //!<Returns all arguments without flags.
 private:
  map<string, vector<string> > myFlaggedCommands; //!<The current flagged commands.
  vector<string> myFlaglessCommands; //!<The current flagless commands.
};
#endif
