cmake -E remove_directory build/win32
cmake -E make_directory build/win32
cmake -E chdir build/win32 cmake -G "Visual Studio 15 2017" -A x64 ../..
