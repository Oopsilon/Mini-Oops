#!/usr/bin/env ksh

# Oopsilon
# Nightly: build assistant for Oopsilon projects.
#
#       Copyright Notice
#
# Copyright (c) 2017 D. Mackay. All rights reserved.
#
# This file and its contents are supplied under the terms of the Peer
# Production Licence as found in the Oopsilon project's source repository,
# and D. Mackay. is the sole copyright holder.

root_dir=$(pwd)
src_root=${root_dir}/src
output_dir=${root_dir}/build/out

toolpath=${src_root}/tools/windows

DATE=date
EXPR=expr
PRINTF=printf
MAKE=make
RM=rm
MKDIR="mkdir -p"

analyse=0
clean=1
debug=1
jobs=5
run_cmake=1
SCAN_BUILD=

if [ -e "./nightly.opt" ]
then
    source ./nightly.opt
fi

while getopts aA:ij:o:rs: opt
do
    case "$opt" in
     a) analyse=1;;
     A) SCAN_BUILD="$OPTARG";;
     i) clean=0 run_cmake=0;;
     j) jobs="$OPTARG";;
     r) debug=0;;
     s) src_root="$OPTARG";;
     o) output_dir="$OPTARG";;
     \?) echo >&2 \
         "Usage: $0 [-a] [-A <scan-build>] [-i] [-r] [-s <source root>]"
         exit 1;;
    esac
done
shift `$EXPR $OPTIND - 1`

RELEASE_VERINFO="Oopsilon ${RELEASE}"
DEBUG_VERINFO="Oopsilon Development: `$DATE +%c`"

set_opts()
{
    install_dir=${output_dir}/instroot
    cmake_opts+="-DCMAKE_INSTALL_PREFIX=${install_dir}
        -DOOPS_VERINFO:STRING=\"${VERINFO}\" "
}

if [ ${analyse} = "1" ]
then
    SCAN_BUILD= ${SCAN_BUILD:-scan-build}
fi

if [ ${debug} = "1" ]
then
    cmake_opts+="-DCMAKE_BUILD_TYPE=Debug "
    VERINFO="${DEBUG_VERINFO}"
else
    VERINFO="${RELEASE_VERINFO}"
fi

set_opts

if [ ${clean} = "1" ]
then
    $RM -rf ${output_dir} ${install_dir}
fi

echo "==== Building C/FL at `$DATE` ===="
start_time=$SECONDS

$MKDIR ${output_dir}
cd ${output_dir}

if [ ${run_cmake} = "1" ]
then
    # The `eval` is bizarrely necessary.
    eval ${SCAN_BUILD} cmake ${cmake_opts} ${src_root}
fi

${SCAN_BUILD} $MAKE -j ${jobs} install

end_time=$SECONDS
echo "==== Finished building C/FL at `$DATE` ===="

elapsed=$((end_time - start_time))

$PRINTF "==== Elapsed build time: %02d:%02d\n" \
    $((elapsed / 60 % 60)) $((elapsed % 60))
