cmake -E remove_directory build/uwp
cmake -E make_directory build/uwp
cmake -E chdir build/uwp cmake -G "Visual Studio 15 2017" -A x64 -DCMAKE_SYSTEM_NAME="WindowsStore"  -DCMAKE_SYSTEM_VERSION="10.0" ../..
