cd ..\obj\MSVC-Win32
cmake ..\..\src -DCMAKE_BUILD_TYPE="Debug" -G "Visual Studio 16 2019" -DOOPS_VERINFO="Win32 Debug" -DCMAKE_INSTALL_PREFIX="./"
msbuild INSTALL.vcxproj