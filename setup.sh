
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
	if [[ "$(echo "`gsl-config --version`>1.14" | bc)" -lt "1" ]]
	then 
		echo "Fatal error: This program required GSL >= 1.15 to run."
		RETURNCODE=2
		exit $RETURNCODE
	fi
}

Main