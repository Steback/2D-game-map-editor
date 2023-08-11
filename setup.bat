@echo off
set build_directory="%cd%\build"
if not exist %build_directory% (
    echo "Build directory created: %build_directory%"
    mkdir %build_directory%
)

set conan_profile="%cd%\conan\windows\conan_profile"
if not exist %conan_profile% (
    echo "Create conan profile: %conan_profile%"
    conan profile detect --name %conan_profile%
)

set build_directory_debug="%build_directory%\debug"
if not exist %build_directory_debug% (
    echo "Create conan profile: %build_directory_debug%"
    mkdir %build_directory_debug%
)

conan install . -pr:h=%conan_profile% -pr:b=%conan_profile% -of=%build_directory_debug% --build=missing -s build_type="Debug"

set build_directory_release="%build_directory%\release"
if not exist %build_directory_debug% (
    echo "Create conan profile: %build_directory_release%"
    mkdir %build_directory_release%
)

conan install . -pr:h=%conan_profile% -pr:b=%conan_profile% -of=%build_directory_release% --build=missing -s build_type="Release"
