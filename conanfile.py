from conans import ConanFile, CMake, RunEnvironment, tools, __version__ as conan_version

assert conan_version >= tools.Version('1.35'), 'Conan version is too old.'


class QtTgBotConan(ConanFile):
    name = 'qttgbot'
    version = '0.0.1'
    generators = 'cmake'

    exports_sources = (
        'CMakeLists.txt',
        'main.cpp',
        'src/*',
        'examples/*',
    )

    requires = 'qt/6.4.0@nap/devel'

    def build(self):
        build_env = RunEnvironment(self)
        with tools.environment_append(build_env.vars):
            self.cmake.build()

    def package(self):
        self.cmake.install()

    @property
    def cmake(self):
        cmake = CMake(self, generator='Ninja', set_cmake_flags=True)
        cmake.definitions['USE_CONAN'] = True
        cmake.configure()
        return cmake

    def package_info(self):
        self.cpp_info.libs = ["qttgbot"]
