#!/bin/bash
for i in $(grep "public GenericUnitTest" include/*.hh -B 1 | grep -v GenericUnitTest | awk '{print $2}')
do 
	echo ADDMACRO_BEFORE $i ADDMACRO_AFTER >> include/ExistingTests_TMP.cff
done
if cmp --silent "include/ExistingTests_TMP.cff" "include/ExistingTests.cff"
then
	rm include/ExistingTests_TMP.cff
else
	mv include/ExistingTests_TMP.cff include/ExistingTests.cff
fi
