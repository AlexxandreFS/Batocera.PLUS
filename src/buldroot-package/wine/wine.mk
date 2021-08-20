################################################################################
#
# wine
#
################################################################################

WINE_LICENSE            = LGPL-2.1+
WINE_LICENSE_FILES      = COPYING.LIB LICENSE
WINE_DEPENDENCIES       = host-bison host-flex host-wine vulkan-headers vulkan-loader vkd3d
WINE_DEPENDENCIES      += faudio orc gstreamer1 gst1-libav gst1-plugins-good gst1-plugins-ugly gst1-plugins-bad
HOST_WINE_DEPENDENCIES  = host-bison host-flex

################################################################################

# Wine Stable
#WINE_VERSION = 6.0.1
#WINE_SOURCE = wine-$(WINE_VERSION).tar.xz
#WINE_SITE = https://dl.winehq.org/wine/source/6.0
#WINE_FOLDER_INSTALL = /opt/Wine/wine-stable

# Wine Old Stable
#WINE_VERSION = 5.0.5
#WINE_SOURCE = wine-$(WINE_VERSION).tar.xz
#WINE_SITE = https://dl.winehq.org/wine/source/5.0
#WINE_FOLDER_INSTALL = /opt/Wine/wine-old-stable

# Wine Staging 
#WINE_VERSION = 6.15
#WINE_SOURCE = wine-staging-$(WINE_VERSION).tar.xz
#WINE_SITE = https://dl.winehq.org/wine/source/6.x
#WINE_FOLDER_INSTALL = /opt/Wine/wine-staging

# Wine Lutris 6.14-3 (Commits on Aug 7, 2021) (BR lutris-6.10.7)
#WINE_VERSION = fd901db6e95c46e9d04776f071c9b84bfa46dd39
#WINE_SITE = $(call github,lutris,wine,$(WINE_VERSION))
#WINE_FOLDER_INSTALL = /opt/Wine/wine-lutris

# Proton Valve proton_6.3-6-rc4 (Commits on Aug 17, 2021)
#WINE_VERSION = 3083b57f002a84b858ca6a093e90527665f61d94
#WINE_SITE = $(call github,ValveSoftware,wine,$(WINE_VERSION))
#WINE_FOLDER_INSTALL = /opt/Wine/proton-valve

# Proton GE Custom 6.15-GE-2"  (Commits on Aug 17, 2021)
#WINE_VERSION = f0ab74112aefeaf372a7d280e7aaa84c9e43107a
#WINE_SITE = $(call github,GloriousEggroll,proton-ge-custom,$(WINE_VERSION))
#WINE_FOLDER_INSTALL = /opt/Wine/proton-ge-custom

################################################################################

# Wine needs its own directory structure and tools for cross compiling
WINE_CONF_OPTS  = --with-wine-tools=../host-wine-$(WINE_VERSION)
WINE_CONF_OPTS += --prefix=$(WINE_FOLDER_INSTALL)
WINE_CONF_OPTS += --bindir=$(WINE_FOLDER_INSTALL)/bin
WINE_CONF_OPTS += --datarootdir=$(WINE_FOLDER_INSTALL)/share

ifeq ($(BR2_PACKAGE_BATOCERA_TARGET_X86),y)
WINE_CONF_OPTS += --libdir=$(WINE_FOLDER_INSTALL)/lib32
WINE_CONF_OPTS += --with-wine64=$(BR2_EXTERNAL_BATOCERA_PATH)/output/x86_64/build/wine-$(WINE_VERSION)
WINE_CONF_OPTS += --without-netapi
endif

ifeq ($(BR2_PACKAGE_BATOCERA_TARGET_X86_64),y)
WINE_CONF_OPTS += --libdir=$(WINE_FOLDER_INSTALL)/lib64
WINE_CONF_OPTS += --enable-win64
WINE_CONF_OPTS += --with-netapi
endif

WINE_CONF_OPTS += --without-gtk3
WINE_CONF_OPTS += --with-x 

ifeq ($(BR2_TOOLCHAIN_EXTERNAL),y)
WINE_CONF_OPTS += TARGETFLAGS="-b $(TOOLCHAIN_EXTERNAL_PREFIX)"
endif

# Suport DXVK
WINE_CONF_OPTS += --with-vkd3d
WINE_CONF_OPTS += --with-vulkan
#HOST_WINE_CONF_OPTS += --with-vkd3d
#HOST_WINE_CONF_OPTS += --with-vulkan

#WINE_CONF_OPTS += --without-gnutls
#HOST_WINE_CONF_OPTS += --without-gnutls

#ifeq ($(BR2_PACKAGE_FAUDIO),y)
#    WINE_CONF_OPTS += --with-faudio
#else
    WINE_CONF_OPTS += --without-faudio
#endif

################################################################################

# Wine uses a wrapper around gcc, and uses the value of --host to
# construct the filename of the gcc to call.  But for external
# toolchains, the GNU_TARGET_NAME tuple that we construct from our
# internal variables may differ from the actual gcc prefix for the
# external toolchains. So, we have to override whatever the gcc
# wrapper believes what the real gcc is named, and force the tuple of
# the external toolchain, not the one we compute in GNU_TARGET_NAME.
ifeq ($(BR2_TOOLCHAIN_EXTERNAL),y)
WINE_CONF_OPTS += TARGETFLAGS="-b $(TOOLCHAIN_EXTERNAL_PREFIX)"
endif

ifeq ($(BR2_PACKAGE_ALSA_LIB)$(BR2_PACKAGE_ALSA_LIB_SEQ)$(BR2_PACKAGE_ALSA_LIB_RAWMIDI),yyy)
WINE_CONF_OPTS += --with-alsa
WINE_DEPENDENCIES += alsa-lib
else
WINE_CONF_OPTS += --without-alsa
endif

ifeq ($(BR2_PACKAGE_CUPS),y)
WINE_CONF_OPTS += --with-cups
WINE_DEPENDENCIES += cups
WINE_CONF_ENV += CUPS_CONFIG=$(STAGING_DIR)/usr/bin/cups-config
else
WINE_CONF_OPTS += --without-cups
endif

ifeq ($(BR2_PACKAGE_DBUS),y)
WINE_CONF_OPTS += --with-dbus
WINE_DEPENDENCIES += dbus
else
WINE_CONF_OPTS += --without-dbus
endif

ifeq ($(BR2_PACKAGE_FONTCONFIG),y)
WINE_CONF_OPTS += --with-fontconfig
WINE_DEPENDENCIES += fontconfig
else
WINE_CONF_OPTS += --without-fontconfig
endif

# To support freetype in wine we also need freetype in host-wine for the cross compiling tools
ifeq ($(BR2_PACKAGE_FREETYPE),y)
WINE_CONF_OPTS += --with-freetype
HOST_WINE_CONF_OPTS += --with-freetype
WINE_DEPENDENCIES += freetype
HOST_WINE_DEPENDENCIES += host-freetype
WINE_CONF_ENV += FREETYPE_CONFIG=$(STAGING_DIR)/usr/bin/freetype-config
else
WINE_CONF_OPTS += --without-freetype
HOST_WINE_CONF_OPTS += --without-freetype
endif

ifeq ($(BR2_PACKAGE_GNUTLS),y)
WINE_CONF_OPTS += --with-gnutls
WINE_DEPENDENCIES += gnutls
else
WINE_CONF_OPTS += --without-gnutls
endif

ifeq ($(BR2_PACKAGE_GST1_PLUGINS_BASE),y)
WINE_CONF_OPTS += --with-gstreamer
WINE_DEPENDENCIES += gst1-plugins-base
else
WINE_CONF_OPTS += --without-gstreamer
endif

ifeq ($(BR2_PACKAGE_JPEG),y)
WINE_CONF_OPTS += --with-jpeg
WINE_DEPENDENCIES += jpeg
else
WINE_CONF_OPTS += --without-jpeg
endif

ifeq ($(BR2_PACKAGE_LCMS2),y)
WINE_CONF_OPTS += --with-cms
WINE_DEPENDENCIES += lcms2
else
WINE_CONF_OPTS += --without-cms
endif

ifeq ($(BR2_PACKAGE_HAS_LIBGL),y)
WINE_CONF_OPTS += --with-opengl
WINE_DEPENDENCIES += libgl
else
WINE_CONF_OPTS += --without-opengl
endif

ifeq ($(BR2_PACKAGE_LIBGLU),y)
WINE_CONF_OPTS += --with-glu
WINE_DEPENDENCIES += libglu
else
WINE_CONF_OPTS += --without-glu
endif

ifeq ($(BR2_PACKAGE_LIBKRB5),y)
WINE_CONF_OPTS += --with-krb5
WINE_DEPENDENCIES += libkrb5
else
WINE_CONF_OPTS += --without-krb5
endif

ifeq ($(BR2_PACKAGE_LIBPCAP),y)
WINE_CONF_OPTS += --with-pcap
WINE_DEPENDENCIES += libpcap
else
WINE_CONF_OPTS += --without-pcap
endif

ifeq ($(BR2_PACKAGE_LIBPNG),y)
WINE_CONF_OPTS += --with-png
WINE_DEPENDENCIES += libpng
else
WINE_CONF_OPTS += --without-png
endif

ifeq ($(BR2_PACKAGE_LIBV4L),y)
WINE_CONF_OPTS += --with-v4l
WINE_DEPENDENCIES += libv4l
else
WINE_CONF_OPTS += --without-v4l
endif

ifeq ($(BR2_PACKAGE_LIBXML2),y)
WINE_CONF_OPTS += --with-xml
WINE_DEPENDENCIES += libxml2
WINE_CONF_ENV += XML2_CONFIG=$(STAGING_DIR)/usr/bin/xml2-config
else
WINE_CONF_OPTS += --without-xml
endif

ifeq ($(BR2_PACKAGE_LIBXSLT),y)
WINE_CONF_OPTS += --with-xslt
WINE_DEPENDENCIES += libxslt
WINE_CONF_ENV += XSLT_CONFIG=$(STAGING_DIR)/usr/bin/xslt-config
else
WINE_CONF_OPTS += --without-xslt
endif

ifeq ($(BR2_PACKAGE_MPG123),y)
WINE_CONF_OPTS += --with-mpg123
WINE_DEPENDENCIES += mpg123
else
WINE_CONF_OPTS += --without-mpg123
endif

ifeq ($(BR2_PACKAGE_NCURSES),y)
WINE_CONF_OPTS += --with-curses
WINE_DEPENDENCIES += ncurses
else
WINE_CONF_OPTS += --without-curses
endif

ifeq ($(BR2_PACKAGE_OPENAL),y)
WINE_CONF_OPTS += --with-openal
WINE_DEPENDENCIES += openal
else
WINE_CONF_OPTS += --without-openal
endif

ifeq ($(BR2_PACKAGE_OPENLDAP),y)
WINE_CONF_OPTS += --with-ldap
WINE_DEPENDENCIES += openldap
else
WINE_CONF_OPTS += --without-ldap
endif

ifeq ($(BR2_PACKAGE_MESA3D_OSMESA_CLASSIC),y)
WINE_CONF_OPTS += --with-osmesa
WINE_DEPENDENCIES += mesa3d
else
WINE_CONF_OPTS += --without-osmesa
endif

ifeq ($(BR2_PACKAGE_PULSEAUDIO),y)
WINE_CONF_OPTS += --with-pulse
WINE_DEPENDENCIES += pulseaudio
else
WINE_CONF_OPTS += --without-pulse
endif

#ifeq ($(BR2_PACKAGE_SAMBA4),y)
#WINE_CONF_OPTS += --with-netapi
#WINE_DEPENDENCIES += samba4
#else
#WINE_CONF_OPTS += --without-netapi
#endif

ifeq ($(BR2_PACKAGE_SANE_BACKENDS),y)
WINE_CONF_OPTS += --with-sane
WINE_DEPENDENCIES += sane-backends
WINE_CONF_ENV += SANE_CONFIG=$(STAGING_DIR)/usr/bin/sane-config
else
WINE_CONF_OPTS += --without-sane
endif

ifeq ($(BR2_PACKAGE_SDL2),y)
WINE_CONF_OPTS += --with-sdl
WINE_DEPENDENCIES += sdl2
else
WINE_CONF_OPTS += --without-sdl
endif

ifeq ($(BR2_PACKAGE_TIFF),y)
WINE_CONF_OPTS += --with-tiff
WINE_DEPENDENCIES += tiff
else
WINE_CONF_OPTS += --without-tiff
endif

ifeq ($(BR2_PACKAGE_HAS_UDEV),y)
WINE_CONF_OPTS += --with-udev
WINE_DEPENDENCIES += udev
else
WINE_CONF_OPTS += --without-udev
endif

ifeq ($(BR2_PACKAGE_XLIB_LIBX11),y)
WINE_CONF_OPTS += --with-x
WINE_DEPENDENCIES += xlib_libX11
else
WINE_CONF_OPTS += --without-x
endif

ifeq ($(BR2_PACKAGE_XLIB_LIBXCOMPOSITE),y)
WINE_CONF_OPTS += --with-xcomposite
WINE_DEPENDENCIES += xlib_libXcomposite
else
WINE_CONF_OPTS += --without-xcomposite
endif

ifeq ($(BR2_PACKAGE_XLIB_LIBXCURSOR),y)
WINE_CONF_OPTS += --with-xcursor
WINE_DEPENDENCIES += xlib_libXcursor
else
WINE_CONF_OPTS += --without-xcursor
endif

ifeq ($(BR2_PACKAGE_XLIB_LIBXEXT),y)
WINE_CONF_OPTS += --with-xshape --with-xshm
WINE_DEPENDENCIES += xlib_libXext
else
WINE_CONF_OPTS += --without-xshape --without-xshm
endif

ifeq ($(BR2_PACKAGE_XLIB_LIBXI),y)
WINE_CONF_OPTS += --with-xinput --with-xinput2
WINE_DEPENDENCIES += xlib_libXi
else
WINE_CONF_OPTS += --without-xinput --without-xinput2
endif

ifeq ($(BR2_PACKAGE_XLIB_LIBXINERAMA),y)
WINE_CONF_OPTS += --with-xinerama
WINE_DEPENDENCIES += xlib_libXinerama
else
WINE_CONF_OPTS += --without-xinerama
endif

ifeq ($(BR2_PACKAGE_XLIB_LIBXRANDR),y)
WINE_CONF_OPTS += --with-xrandr
WINE_DEPENDENCIES += xlib_libXrandr
else
WINE_CONF_OPTS += --without-xrandr
endif

ifeq ($(BR2_PACKAGE_XLIB_LIBXRENDER),y)
WINE_CONF_OPTS += --with-xrender
WINE_DEPENDENCIES += xlib_libXrender
else
WINE_CONF_OPTS += --without-xrender
endif

ifeq ($(BR2_PACKAGE_XLIB_LIBXXF86VM),y)
WINE_CONF_OPTS += --with-xxf86vm
WINE_DEPENDENCIES += xlib_libXxf86vm
else
WINE_CONF_OPTS += --without-xxf86vm
endif

ifeq ($(BR2_PACKAGE_ZLIB),y)
WINE_CONF_OPTS += --with-zlib
WINE_DEPENDENCIES += zlib
else
WINE_CONF_OPTS += --without-zlib
endif

# host-gettext is essential for .po file support in host-wine wrc
ifeq ($(BR2_SYSTEM_ENABLE_NLS),y)
HOST_WINE_DEPENDENCIES += host-gettext
HOST_WINE_CONF_OPTS += --with-gettext --with-gettextpo
else
HOST_WINE_CONF_OPTS += --without-gettext --without-gettextpo
endif

# Wine needs to enable 64-bit build tools on 64-bit host
ifeq ($(HOSTARCH),x86_64)
HOST_WINE_CONF_OPTS += --enable-win64
endif

# Wine only needs the host tools to be built, so cut-down the
# build time by building just what we need.
define HOST_WINE_BUILD_CMDS
    $(HOST_MAKE_ENV) $(MAKE) -C $(@D) __tooldeps__
endef

# Wine only needs its host variant to be built, not that it is
# installed, as it uses the tools from the build directory. But
# we have no way in Buildroot to state that a host package should
# not be installed. So, just provide an noop install command.
define HOST_WINE_INSTALL_CMDS
	:
endef

# We are focused on the cross compiling tools, disable everything else
HOST_WINE_CONF_OPTS += \
	--disable-tests    \
	--without-gnutls   \
	--without-capi     \
	--without-cups     \
	--without-oss      \
	--without-pulse    \
	--without-sane

$(eval $(autotools-package))
$(eval $(host-autotools-package))

