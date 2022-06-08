from conans import ConanFile, CMake, RunEnvironment, tools, __version__ as conan_version

assert conan_version >= tools.Version('1.35'), 'Conan version is too old.'


class Qt6CmdAppConan(ConanFile):
    name = 'qt6-cmd-app'
    version = '0.0.0'
    generators = 'cmake', 'cmake_find_package'

    exports_sources = (
        'CMakeLists.txt',
        'main.cpp',
    )

    requires = 'qt/6.3.0@nap/devel'

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
