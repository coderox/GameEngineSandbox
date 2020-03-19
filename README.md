# GameEngineSandbox

![Azure pipeline badge](https://coderox.visualstudio.com/Game%20Engine%20Sandbox/_apis/build/status/Build%20master%20branch)

To try this small game engine follow these steps:

`git clone https://github.com/coderox/GameEngineSandbox.git`


Make sure to fetch the thirdparty submodules:

`git submodule update --init`


If you want to build Win32 version, make sure to bootstrap vcpkg and fetch Win32 specific dependencies

`./dependencies/thirdparty/vcpkg/bootstrap-vcpkg.bat`

`./dependencies/thirdparty/vcpkg/vcpkg.exe install glew:x64-windows`

`./dependencies/thirdparty/vcpkg/vcpkg.exe install libpng:x64-windows`

`./dependencies/thirdparty/vcpkg/vcpkg.exe install opengl:x64-windows`


You can leverage the pipeline.ps1 Powershell command to automate the creation of the projects for your preferred platform.

### Here are a couple of examples:

#### Generate and build a release version for Universal Windows Platform
`pipeline.ps1 -uwp -build`

#### Generate and build a debug version with tests for Universal Windows Platform
`pipeline.ps1 -uwp -debug -build -tests`

This will create two runnable client projects, one game client and an additional 'tests' client which will run all the tests leveraging gtest as the testing framework

#### Only generate a debug version for Win32
`pipeline.ps1 -win32 -debug -generate`

#### Compile an already existing debug configuration for Win32
`pipeline.ps1 -win32 -debug -compile`

#### Generate and build a release version of Win32, leveraging an already installed vcpkg-toolchain
`pipeline.ps1 -win32 -build -toolchainFile:[path to explicit toolchain file for vcpkg]`
