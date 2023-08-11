build_directory="$PWD/build"
if [ ! -d  "$build_directory" ]; then
    mkdir "$build_directory"
    echo "Build directory created: $build_directory"
fi

conan_profile="$PWD/conan/linux/conan_profile"
if [ ! -f "$conan_profile" ]; then
    echo "Create conan profile: $conan_profile"
    conan profile detect --name "$conan_profile"
fi

build_directory_debug="$build_directory/debug"
if [ ! -d "$build_directory_debug" ]; then
    mkdir "$build_directory_debug"
    echo "Debug build directory created: $build_directory_debug"
fi

conan install . -pr:h="$conan_profile" -pr:b="$conan_profile" -of="$build_directory_debug" --build=missing -s build_type="Debug"

build_directory_release="$build_directory/release"
if [ ! -d "$build_directory_release" ]; then
    mkdir "$build_directory_release"
    echo "Release build directory created: $build_directory_release"
fi

conan install . -pr:h="$conan_profile" -pr:b="$conan_profile" -of="$build_directory_release" --build=missing -s build_type="Release"
