from conans import ConanFile, CMake


class BeagleboneblackgpioConan(ConanFile):
    name = "BeagleBoneBlackGPIO"
    version = "0.2.0"
    license = "MIT"
    url = "https://github.com/uilianries/BeagleBoneBlackGPIO"
    settings = "os", "compiler", "build_type", "arch"
    description = "GPIO library for BeagleBone Black"
    author = "Uilian Ries <uilianries@gmail.com>"
    options = {"shared": [True, False]}
    generators = "cmake"
    exports_sources = "CMakeLists.txt", "src/*", "include/*"
    requires = "Poco/1.7.8p3@pocoproject/stable", "Boost/1.62.0@lasote/stable"
    default_options = "shared=True", "Poco:shared=True", "Boost:shared=True"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.hpp", dst="include", src="include")
        self.copy("*.a", dst="lib", src="lib", keep_path=False)
        self.copy("*.so*", dst="lib", src="src", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ['bbbgpio']
