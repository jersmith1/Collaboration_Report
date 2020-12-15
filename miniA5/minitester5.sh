#!/bin/bash

check_for_source()
{
    if [[ ! -f "$1" ]]
    then
        echo "Source file '$1' not found. Please make sure to upload the mini tester script into the same folder as your source files."
        exit 1;
    fi
}

print_and_run()
{
    echo "\$ $1"
    bash -c "$1"
    echo -e "exit code: $?"
}


check_for_source "report.c"

# BEGIN SETUP
sourcedir=$PWD
tmpdir=/tmp/__tmp_comp206_${LOGNAME}
mkdir -p "$tmpdir"
cp scalc.c "$tmpdir"
cd "$tmpdir"

echo "*******************************  report.c tests *******************************"

echo
echo "[[[[ test case 0: compiling report.c ]]]]"
echo "********************************************************************************"
print_and_run "gcc -o report report.c"
echo "********************************************************************************"
echo
echo "[[[[ test case 1: EXPECTED TO FAIL - missing parameter ]]]]"
echo "********************************************************************************"
print_and_run "./report data.csv rpt.txt"
echo "********************************************************************************"
echo
echo "[[[[ test case 2: EXPECTED TO FAIL - file doesnt exist ]]]]"
echo "********************************************************************************"
print_and_run "./report noinfo.csv \"Devon Estrada\" rpt.txt"
echo '********************************************************************************'
echo
echo "[[[[ test case 3: EXPECTED TO FAIL - name not in file ]]]]"
echo '********************************************************************************'
print_and_run "./report \"Marquise Goodwin\" rpt.txt"
echo '********************************************************************************'
echo
echo "[[[[ test case 4: EXPECTED TO WORK ]]]]"
echo '********************************************************************************'
print_and_run "./report data.csv \"Devon Estrada\" rpt.txt"
echo
echo "[[[[ test case 5: EXPECTED TO WORK ]]]]"
echo '********************************************************************************'
print_and_run "./report data.csv \"Aminah North\" rpt.txt"
echo
echo "[[[[ test case 6: EXPECTED TO WORK ]]]]"
echo '********************************************************************************'
print_and_run "./report data.csv \"Tayah Dougherty\" rpt.txt"
echo
echo "[[[[ test case 7: EXPECTED TO WORK ]]]]"
echo '********************************************************************************'
print_and_run "./report data.csv \"Cem Graves\" rpt.txt"
echo
echo "[[[[ test case 8: EXPECTED TO WORK ]]]]"
echo '********************************************************************************'
print_and_run "./report data.csv \"Eryn Pham\" rpt.txt"
echo
echo "[[[[ test case 9: EXPECTED TO WORK ]]]]"
echo '********************************************************************************'
print_and_run "./report data.csv \"Jenny Cooley\" rpt.txt"
echo
echo "[[[[ test case 10: EXPECTED TO FAIL ]]]]"
echo '********************************************************************************'
chmod a-r data.csv
print_and_run "./report data.csv \"Jenny Cooley\" rpt.txt"
echo
echo "[[[[ test case 11: EXPECTED TO FAIL ]]]]"
echo '********************************************************************************'
chmod a-w rpt.txt
print_and_run "./report data.csv \"Jenny Cooley\" rpt.txt"


# CLEAN UP
rm -r "$tmpdir"