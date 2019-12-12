# Nightly

<img src="Logo/Oopsilon.png" alt="Oopsilon logo" width="520" height="129">

### Overview
**Nightly** is the tool used for building an Oopsilon nightly build.

#### Running a build
A build may be run by executing `src/tools/Nightly.sh` from within the Oopsilon
source tree root.

#### Options
Nightly provides several command-line options for configuring the build.

Where an option is followed by <text in angles,> this means there is an
argument.

 - `-a`: Enables static analysis with the Clang analyser by using Clang's
   `scan-build` script.
 - `-A <scan-build-exe>`: Specifies an alternative `scan-build` executable tool
   use.
 - `-i`: Performs an *incremental build*. An incremental build does not
   explicitly reinvoke CMake, nor does it delete the output tree. This is a
   prudent option for speedily building after making smaller changes/
 - `-j <number-of-jobs>`: Specifies how many jobs should be used for the build
   process. Similar to `make`'s -j option.
 - `-r`: Enables a release build (default is debug.)
 - `-s <source-root-path>`: Specifies an alternative path to the source root
   (defualt is the current working directory.)
 - `-O <output-directory-path>`: Specifies an alternative build output
    directory.

Nightly also reads the file `nightly.opt` if it exists in the current working
directory. This file contains options to be supplied to Nightly in a different
format. Variables are set to either 0/1, like this `var=1`, or to a string,
like this `var="a string"`.