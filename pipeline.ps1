[CmdletBinding()]
Param(
    [Parameter(Mandatory = $False)]
    [string]$toolchainFile,

    [Parameter(Mandatory = $False)]
    [switch]$generate,

    [Parameter(Mandatory = $False)]
    [switch]$update,

    [Parameter(Mandatory = $False)]
    [switch]$compile,

    [Parameter(Mandatory = $False)]
    [switch]$build,

    [Parameter(Mandatory = $False)]
    [switch]$win32,

    [Parameter(Mandatory = $False)]
    [switch]$uwp,

    [Parameter(Mandatory = $False)]
    [switch]$release,
    
    [Parameter(Mandatory = $False)]
    [switch]$vs2017
    
)

$Cmake = "cmake.exe"
$BuildDirectory = ""
$PlatformParameters = ""
$Generator = "Visual Studio 16 2019"
$BuildType = ""
$BuildConfiguration = "Debug"
$toolchainFile = "dependencies/thirdparty/vcpkg/scripts/buildsystems/vcpkg.cmake"

If($vs2017){
    $Generator = "Visual Studio 15 2017"
}

If($win32) {
    $BuildDirectory = "build/win32"
    if(-NOT $toolchainFile -AND -NOT $compile) {
        $toolchainFile = "dependencies/thirdparty/vcpkg/scripts/buildsystems/vcpkg.cmake"
    }
    $PlatformParameters = "-DCMAKE_TOOLCHAIN_FILE='$toolchainFile'"
} ElseIf($uwp) {
    $BuildDirectory = "build/uwp"
    $PlatformParameters = @("-DCMAKE_TOOLCHAIN_FILE='$toolchainFile'", "-DCMAKE_SYSTEM_NAME='WindowsStore'", "-DCMAKE_SYSTEM_VERSION='10.0'")
}

If($release) {
    If($win32) {
        $BuildType = "-DCMAKE_CONFIGURATION_TYPES=Release"
        $BuildConfiguration = "Release"
    } ElseIf($uwp) {
        $BuildType = "-DCMAKE_CONFIGURATION_TYPES=RelWithDebInfo"
        $BuildConfiguration = "RelWithDebInfo"
    }
} Else {
    $BuildDirectory += "-debug"
}

if($generate -OR $build) {
    & $Cmake @("-E", "remove_directory", $BuildDirectory)
    & $Cmake @("-E", "make_directory", $BuildDirectory)
}
if($generate -OR $build -OR $update) {
    $GenerateParameters = @("-E", "chdir", $BuildDirectory, "cmake", "-G", $Generator)
    $GenerateParameters += $PlatformParameters
    $GenerateParameters += $BuildType
    $GenerateParameters += ("-A", "x64", "../..")
    & $Cmake $GenerateParameters
    
    if($uwp) {
        $ProjectFile = $BuildDirectory + "/game/game.vcxproj"
        & python @("pipeline/inject.py", $ProjectFile)
    }
}
if($compile -OR $build) {
    & $Cmake @("--build", $BuildDirectory, "--config", $BuildConfiguration)
}
