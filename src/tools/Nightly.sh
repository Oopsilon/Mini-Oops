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

platform_name="`uname -s`-`uname -p`"
output_dir="${root_dir}/Objs/${platform_name}"
inst_dir="${root_dir}/Dest/${platform_name}"

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
    cmake_opts+="-DCMAKE_INSTALL_PREFIX=${inst_dir}
        -DOOPS_VERINFO:STRING=\"${VERINFO}\""
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
    echo ${output_dir}
    $RM -rf ${output_dir} ${inst_dir}
    $MKDIR ${output_dir}
    $MKDIR ${inst_dir}
    cp ${src_root}/tools/.gitignore.tpl ${output_dir}/.gitignore
    cp ${src_root}/tools/.gitignore.tpl ${inst_dir}/.gitignore
fi

# $1: start time
# $2: end time
calcelapsed()
{
    elapsed=$(($2 - $1))

    $PRINTF "==== Elapsed build time: %02d:%02d\n" \
        $((elapsed / 60 % 60)) $((elapsed % 60))
}

echo "==== Building C/FL at `$DATE` ===="
start_time=$SECONDS

failedbuild()
{
    echo "==== Failure building C/FL at `$DATE` ===="
    calcelapsed $start_time $SECONDS
    exit 1
}

passedbuild()
{
    echo "==== Finished building C/FL at `$DATE` ===="
    calcelapsed $start_time $SECONDS
    exit 0
}

trap 'failedbuild' ERR

cd ${output_dir}

if [ ${run_cmake} = "1" ]
then
    # The `eval` is bizarrely necessary.
    eval ${SCAN_BUILD} cmake ${cmake_opts} ${src_root}
fi

${SCAN_BUILD} $MAKE -j ${jobs} install

passedbuild $start_time