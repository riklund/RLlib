#!/bin/bash
for i in $(ls include | grep .hh | grep -v '~' | grep -v RunTests.hh | grep -v GenericUnitTest.hh)
do 
	echo "#include \""$i\" >> include/AllHeaders_TMP.cff
done

if cmp --silent "include/AllHeaders_TMP.cff" "include/AllHeaders.cff"
then
	rm include/AllHeaders_TMP.cff
else
	mv include/AllHeaders_TMP.cff include/AllHeaders.cff
fi
