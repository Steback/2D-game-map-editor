import os

from conan import ConanFile
from conan.tools.files import copy


class MultiplayerGameRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires("opengl/system")
        self.requires("glew/2.2.0")
        self.requires("glfw/3.3.8")
        self.requires("imgui/1.89.8")
        self.requires("glm/cci.20230113")
        self.requires("lua/5.4.4")
        self.requires("sol2/3.3.0")
        self.requires("tinyxml2/9.0.0")
        self.requires("stb/cci.20220909")
        self.requires("fmt/10.0.0")

    def generate(self):
        copy(self, "*glfw*", os.path.join(self.dependencies["imgui"].package_folder,
            "res", "bindings"), os.path.join(self.source_folder, "bindings"))
        copy(self, "*opengl3*", os.path.join(self.dependencies["imgui"].package_folder,
            "res", "bindings"), os.path.join(self.source_folder, "bindings"))
