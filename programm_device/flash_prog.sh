#!/bin/bash

# directory of script
script=$(readlink -f "$0")
scriptDir=$(dirname "$script")

# default mode and user options
MODE=flash

if [ "$#" != 1 ]; then
    echo 
	echo "Specify the location of the program as the first parameter!"
    echo "Files need to be in .hex or .elf format!"
else
	eval "$scriptDir"/ccs_base/DebugServer/bin/DSLite $MODE -c user_files/configs/cc2650f128.ccxml -l user_files/settings/generated.ufsettings -e -f -v $1
fi

rc=$?
if [[ $rc != 0 ]]; then exit $rc; fi
