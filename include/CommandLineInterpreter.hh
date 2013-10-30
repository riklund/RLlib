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
#include <sstream>
#include <iostream>
#include <iomanip>

#include "CommandLineArgument.hh"
#include "CommandLineException.hh"

using namespace std;


/**Interprets command line arguments according to a list of CommandLineArguments (acceptable flags), and throws an exception if unknown flags are encountered.

   \author Rikard Lundmark
 */
class CommandLineInterpreter
{
 public:
  void Initialize(unsigned int argc, ///The number of command line arguments. Take it directly from main.
				  char * argv[] ///The actual arguments. Take it directly form main.
				  ); ///Initialize to a specific command line.

  CommandLineInterpreter(list<CommandLineArgument> _myAcceptableFlags  = list<CommandLineArgument>(),///The flags that should be accepted by this interpreter. Default: empty list.
						 string _description = ""
						 ); ///Constructor, sets the default stuff.

  void SetDescription(string _description = "" ///Change the description to this. Default is empty.
					  ); ///Change the description

  void AddCommandLineArgument(CommandLineArgument toAdd ///Add this commmand line argument.
							  ); ///Add a command line argument.

  vector<string> ReadFlaggedCommand(string flag //!<The flag to read
				    );//!<Returns a vector<string> containing all arguments for a specific flag. Returns an empty vector if there are no arguments for this flag.
  
  vector<string> ReadFlaglessCommands(); //!<Returns all arguments without flags.

  void PrintHelp(); ///Prints help message to stderr.

 private:
  string programName; ///The name of the program.
  bool initialized; ///Set to true when the program is initialized.
  list<CommandLineArgument> myAcceptableArguments; ///The arguments accepted by the program.
  string description; ///Description of the program. Used to print help.
  map<string, vector<string> > myFlaggedCommands; //!<The current flagged commands.
  vector<string> myFlaglessCommands; //!<The current flagless commands.
};
#endif
