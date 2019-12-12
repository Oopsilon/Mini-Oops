find ./src -name '*.cxx' -o -name '*.h' \
  -o -name '*.c' | grep -v "tpl" | \
  xargs /mnt/c/Program\ Files\ \(x86\)/LLVM/bin/clang-format.exe  -i
