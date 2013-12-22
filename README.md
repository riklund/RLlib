[![Build Status](https://travis-ci.org/riklund/rllib.png)](https://travis-ci.org/riklund/rllib)


#RLlib

A library with some useful classes that often tend to be useful in different projects. Can be included (after proper modification of the makefile, of course) in an existing C++ project without further prerequisities.

##Installation
Clone the repository, and then issue

	  cd RLlib
	  ./setup.sh
	  make


##Linking
RLlib needs to be linked with your project in order to work. You need to use the include option

	  -I/path/to/RLlib/include

and the library option

	-L/path/to/RLlib -lRLlib

of your compiler.

##Usage
Use an include directive to include the desired class. For example

	#include "RLException.hh"

gives the possibility to throw vararg-exceptions with printf-like syntax:

	  throw RLException("The answer is %d", 42);
