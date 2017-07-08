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
    default_options = "shared=True", "Poco:shared=True", "Boost:shared=True",
    "Boost:without_atomic=True", "Boost:without_chrono=True", "Boost:without_exception=True",
    "Boost:without_container=True", "Boost:without_context=True", "Boost:without_timer=True",
    "Boost:without_coroutine2=True", "Boost:without_date_time=True", "Boost:without_coroutine=True",
    "Boost:without_type_erasure=True", "Boost:without_wave=True", "Boost:without_iostreams=True",
    "Boost:without_graph=True", "Boost:without_graph_parallel=True", "Boost:without_locale=True",
    "Boost:without_log=True", "Boost:without_math=True", "Boost:without_mpi=True",
    "Boost:without_random=True", "Boost:without_serialization=True", "Boost:without_test=True",
    "Boost:without_thread=True", "Poco:enable_mongodb=False", "Poco:enable_net=False",
    "Poco:enable_netssl=False", "Poco:enable_netssl_win=False", "Poco:enable_util=False",
    "Poco:enable_xml=False", "Poco:force_openssl=False", "Poco:enable_zip=False",
    "Poco:enable_json=False", "Poco:enable_crypto=False", "Poco:enable_data=False",
    "Poco:enable_data_sqlite=False"

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
