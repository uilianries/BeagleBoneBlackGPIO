from conans import ConanFile, CMake
import os


class BeagleboneblackgpioTestConan(ConanFile):
    channel = os.getenv("CONAN_CHANNEL", "testing")
    username = os.getenv("CONAN_USERNAME", "uilianries")
    settings = "os", "compiler", "build_type", "arch"
    requires = "BeagleBoneBlackGPIO/0.2.0@%s/%s" % (username, channel), "Boost/1.62.0@lasote/stable", "Catch/1.9.4@uilianries/stable"
    generators = "cmake"

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_dir=self.conanfile_directory, build_dir="./")
        cmake.build()

    def imports(self):
        self.copy("*.so", dst="bin", src="lib")

    def test(self):
        cmake = CMake(self)
        cmake.configure(source_dir=self.conanfile_directory, build_dir="./")
        cmake.test()
