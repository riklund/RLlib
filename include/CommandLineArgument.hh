/** \file CommandLineArgument.hh
    \brief Header file for the CommandLineArgument class.
    \author Rikard Lundmark
*/
/** \file CommandLineArgument.cc
    \brief Source file for the CommandLineArgument class.
    \author Rikard Lundmark
*/

using namespace std;

#ifndef STRING
#define STRING //!<Inclusion guard
#include <string>
#endif

#ifndef CommandLineArgument_hh
#define CommandLineArgument_hh 1 //!<Inclusion guard.
/** Represents an argument the program expects on the command line.
    Sent to the CommandLineInterpreter, this class will throw a
    CommandLineException if it encounters a flag it does not recognize.
    
    \author Rikard Lundmark
 */
class CommandLineArgument
{
 public:
  string flag; //!< The flag (without the - or --) which should be expected.
  int numberOfArguments; //!<The number of arguments to be expected.
  CommandLineArgument(); //!<Constructor, sets the members to default values.
  CommandLineArgument(
		      string mFlag, //!< flag = mFlag
		      int mNumberOfArguments //!< numberOfArguments = mNumberOfArguments
		      ); //!<Constructor, sets the members to the values sent.
};
#endif
