################################################################################
#
# YUZU
#
################################################################################
# Version.: Commits on Jun 5, 2021
YUZU_VERSION = 6e237ce5b818d4e654deb2dedc062f1453ce703e
YUZU_SITE = https://github.com/yuzu-emu/yuzu-mainline.git
YUZU_SITE_METHOD=git
YUZU_GIT_SUBMODULES=YES
YUZU_LICENSE = GPLv2
YUZU_DEPENDENCIES = qt5base qt5tools qt5multimedia fmt boost ffmpeg zstd catch2

# Should be set when the package cannot be built inside the source tree but needs a separate build directory.
YUZU_SUPPORTS_IN_SOURCE_BUILD = NO

YUZU_CONF_OPTS += -DCMAKE_BUILD_TYPE=Release
YUZU_CONF_OPTS += -DARCHITECTURE_x86_64=ON
YUZU_CONF_OPTS += -DBUILD_SHARED_LIBS=OFF

YUZU_CONF_OPTS += -DYUZU_USE_BUNDLED_QT=OFF
YUZU_CONF_OPTS += -DYUZU_USE_BUNDLED_BOOST=OFF
YUZU_CONF_OPTS += -DYUZU_USE_BUNDLED_FFMPEG=OFF
YUZU_CONF_OPTS += -DYUZU_USE_BUNDLED_SDL2=OFF
YUZU_CONF_OPTS += -DENABLE_QT_TRANSLATION=ON
YUZU_CONF_OPTS += -DYUZU_ALLOW_SYSTEM_SDL2=ON

YUZU_CONF_OPTS += -DGLSLANGVALIDATOR="$(HOST_DIR)/x86_64-buildroot-linux-gnu/sysroot/usr/bin/glslangValidator.sh"
YUZU_CONF_OPTS += -DCMAKE_C_COMPILER=gcc-10
YUZU_CONF_OPTS += -DCMAKE_CXX_COMPILER=g++-10
YUZU_CONF_OPTS += -DCMAKE_CXX_FLAGS=""
YUZU_CONF_OPTS += -DYUZU_ENABLE_COMPATIBILITY_REPORTING=OFF

YUZU_CONF_ENV += LDFLAGS=-lpthread
YUZU_CONF_ENV += ARCHITECTURE_x86_64=1

YUZU_CONF_ENV += CI=true
YUZU_CONF_ENV += TRAVIS=true
YUZU_CONF_ENV += TRAVIS_REPO_SLUG=yuzu-emu/yuzu-mainline
YUZU_CONF_ENV += TRAVIS_TAG=$(git describe --tags)

#YUZU_CONF_ENV += LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:/x86_64/host/x86_64-buildroot-linux-gnu/sysroot/usr/lib"
#YUZU_CONF_ENV += PATH="${PATH}:/x86_64/host/x86_64-buildroot-linux-gnu/sysroot/usr/bin/glslangValidator"

define YUZU_INSTALL_TARGET_CMDS
        mkdir -p $(TARGET_DIR)/usr/bin
        mkdir -p $(TARGET_DIR)/usr/lib/yuzu

	$(INSTALL) -D $(@D)/buildroot-build/bin/yuzu $(TARGET_DIR)/usr/bin/
endef

$(eval $(cmake-package))

# atualizei o pacote fmt do buildroot para a versão 7.1.2

#set(GLSLANG_INSTALL_DIR "/x86_64/host/x86_64-buildroot-linux-gnu/sysroot")
#set(GLSLANG_VALIDATOR_NAME "glslangValidator")
#find_package(Vulkan REQUIRED)

