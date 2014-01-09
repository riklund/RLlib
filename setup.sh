#!/bin/bash
function Main()
{
	CheckRequirements
	if [ -f "makefile" ]
	then
		chmod a+w "makefile"
	fi

	if [ -f "test/makefile" ]
	then
		chmod a+w "test/makefile"
	fi

	cp "makefile.in" "makefile"
	cp "test/makefile.in" "test/makefile"
	#To prevent accidental modification of makefile instead of makefile.in


	GCCVER=`g++ -v 2>&1 |  grep 'gcc version' | awk '{print $3}'`
	REQVER="4.7.0"
	vercomp $GCCVER $REQVER
	if [[ "$?" -gt "1" ]]
	then
		echo "Warning: gcc version too old for c++11 support, falling back to c++03"
		OldCPPFallback
	fi

	chmod a-w "makefile"
	chmod a-w "test/makefile"

	echo "Setup complete."
}

function OldCPPFallback()
{
	for arg in "makefile" "test/makefile"
	do
		sed -i -e "s, -std=c++11,,g" $arg
	done

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

#Credit to Dennis Williamson for this
function vercomp () 
{
    if [[ $1 == $2 ]]
    then
        return 0
    fi
    local IFS=.
    local i ver1=($1) ver2=($2)
    # fill empty fields in ver1 with zeros
    for ((i=${#ver1[@]}; i<${#ver2[@]}; i++))
    do
        ver1[i]=0
    done
    for ((i=0; i<${#ver1[@]}; i++))
    do
        if [[ -z ${ver2[i]} ]]
        then
            # fill empty fields in ver2 with zeros
            ver2[i]=0
        fi
        if ((10#${ver1[i]} > 10#${ver2[i]}))
        then
            return 1
        fi
        if ((10#${ver1[i]} < 10#${ver2[i]}))
        then
            return 2
        fi
    done
    return 0
}

Main