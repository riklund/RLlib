#!/bin/bash
rm -f ExistingTests.cff
rm ExistingTests.cff -f
for i in $(grep "public GenericUnitTest" include/*.hh | awk '{print $2}')
do 
	echo ADDMACRO_BEFORE $i ADDMACRO_AFTER >> include/ExistingTests.cff
done
