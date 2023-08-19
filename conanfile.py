from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps


class juce_visual_regressionsRecipe(ConanFile):
    name = "juce_visual_regressions"
    version = "0.1.0"
    package_type = "library"

    # Optional metadata
    license = "<Put the package license here>"
    author = "Pedro Tacla Yamada <tacla.yamada@gmail.com>"
    url = "https://github.com/yamadapc/juce-visual-regressions"
    description = "Visual regression testing for JUCE projects"
    topics = ()

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    requires = [
        ("juce/7.0.6@juce/release"),
        ("fmt/10.1.0"),
    ]

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = "CMakeLists.txt", "src/*", "include/*"

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure({'CMAKE_EXPORT_COMPILE_COMMANDS': 'ON'})
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["juce_visual_regressions"]
