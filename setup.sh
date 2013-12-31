#!/bin/bash
function Main()
{
	CheckRequirements
	if [ -f "makefile" ]
	then
		chmod a+w makefile
	fi

	cp makefile.in makefile
	#To prevent accidental modification of makefile instead of makefile.in
	chmod a-w makefile 

	echo "Setup complete."
}


function CheckRequirements()
{
	#Check if we have a makefile in the current directory. If not, we are obviously not in the project directory.
	if [ ! -f "makefile.in" ]
	then
		echo "Fatal error: makefile.in not found."
		RETURNCODE=1
		exit $RETURNCODE
	fi
}

Main