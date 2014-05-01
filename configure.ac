AC_INIT(omxplayer.cpp)

PACKAGE=omxplayer
VERSION=0.4.0
PKG_CONFIG_PATH="./ffmpeg_compiled/lib/pkgconfig/:$PKG_CONFIG_PATH"
export PKG_CONFIG_PATH



AM_INIT_AUTOMAKE($PACKAGE, $VERSION)

#export PATH=../tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/:$PATH
#bind mount your mounted
#sudo mount /mnt/ /home/thorsten/workspace2/rpi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/../arm-linux-gnueabihf/libc --bind
# bind mount the SDCard to the Sysroot of your gcc. which is printed with arm-linux-gnueabihf-g++  -print-sysroot
#/home/thorsten/workspace2/rpi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/../arm-linux-gnueabihf/libc
#
# ./configure --prefix=/tmp/omx --with-cross-root=/mnt  --host=arm-linux-gnueabihf --with-cross-ffmpeg=/mnt/home/pi/dvd/omxplayer-0.4.0/ffmpeg_compiled/


VCDIR="/opt/vc"
AC_ARG_WITH([vc], 
    [--with-vc     Which videocore libs to use:  default=/opt/vc],
     [
        VCDIR="$withval"
    ], []
)


ROOTDIR=
AC_ARG_WITH([cross-root],
	[--with-cross-root    where to find the mounted SDCARD],
	[
	  ROOTDIR="$withval"
     PKG_CONFIG_PATH="$ROOTDIR/usr/lib/pkgconfig/:$ROOTDIR/usr/lib/arm-linux-gnueabihf/pkgconfig/:./ffmpeg_compiled/lib/pkgconfig/:$PKG_CONFIG_PATH"
     PKG_CONFIG_LIBDIR="$ROOTDIR/usr/lib/pkgconfig/:$ROOTDIR/usr/lib/arm-linux-gnueabihf/pkgconfig/"
          CFLAGS="--sysroot=$ROOTDIR -I$ROOTDIR/$VCDIR/include -I$ROOTDIR/$VCDIR/include/interface/vcos/pthreads/ -I$ROOTDIR/$VCDIR/include/interface/vmcs_host/linux/ $CFLAGS"
     CXXFLAGS="--sysroot=$ROOTDIR -I$ROOTDIR/$VCDIR/include  -I$ROOTDIR/$VCDIR/include/interface/vcos/pthreads/ -I$ROOTDIR/$VCDIR/include/interface/vmcs_host/linux/ $CXXFLAGS"
     CPPFLAGS="--sysroot=$ROOTDIR -I$ROOTDIR//usr/include/c++/4.7/arm-linux-gnueabihf/ -I$ROOTDIR/usr/include/c++/4.7/ -I$ROOTDIR/usr/include/arm-linux-gnueabihf -I$ROOTDIR/$VCDIR/include  -I$ROOTDIR/$VCDIR/include/interface/vcos/pthreads/ -I$ROOTDIR/$VCDIR/include/interface/vmcs_host/linux/ -I$ROOTDIR/usr/include/freetype2 -I$ROOTDIR/usr/lib/arm-linux-gnueabihf/dbus-1.0/include -I$ROOTDIR/usr/include/dbus-1.0 $CPPFLAGS"
export PKG_CONFIG_SYSROOT_DIR=$ROOTDIR
 	LDFLAGS="--sysroot=$ROOTDIR -L$ROOTDIR/lib/arm-linux-gnueabihf/ -L$ROOTDIR/usr/lib/arm-linux-gnueabihf/ -L$ROOTDIR/opt/vc/lib"

   ],
   [

   ]
)


AC_ARG_WITH([cross-ffmpeg],
	[--with-cross-ffmpeg    where to find the crosscompile ffpmeg],
	[
	  PKG_CONFIG_LIBDIR="$withval/lib/pkgconfig/:PKG_CONFIG_LIBDIR"
     PKG_CONFIG_PATH="$withval/lib/pkgconfig/:$PKG_CONFIG_PATH"
     CPPFLAGS="$CPPFLAGS -I$withval/include"
     LDFLAGS="$LDFLAGS -L$withval/lib   "
   ],
   []
)

   

AC_PROG_CXX(g++-4.7 g++)
AC_PROG_CC(gcc-4.7 gcc)

#AC_CONFIG_HEADER(config.h)

   AC_LANG_PUSH([C++])
AC_CHECK_HEADERS([boost/circular_buffer.hpp], [],
    [AC_MSG_ERROR(You need the Boost libraries.)])
AC_CHECK_HEADERS([boost/algorithm/string.hpp], [],
    [AC_MSG_ERROR(You need the Boost libraries.)])
AC_CHECK_HEADERS([boost/config.hpp], [],
    [AC_MSG_ERROR(You need the Boost libraries.)])
AC_LANG_POP([C++])

DVDNAV_REQUIRED_VERSION=4.2.0
PKG_CHECK_MODULES(DVDNAV, dvdnav >= $DVDNAV_REQUIRED_VERSION)
AC_SUBST(DVDNAV_CFLAGS)
AC_SUBST(DVDNAV_LIBS)

DBUS_REQUIRED_VERSION=1.6.8
PKG_CHECK_MODULES(DBUS, dbus-1 >= $DBUS_REQUIRED_VERSION)
AC_SUBST(DBUS_CFLAGS)
AC_SUBST(DBUS_LIBS)

AVCODEC_REQUIRED_VERSION=55.52.102
PKG_CHECK_MODULES(AVCODEC, libavcodec >= $AVCODEC_REQUIRED_VERSION)
AC_SUBST(AVCODEC_CFLAGS)
AC_SUBST(AVCODEC_LIBS)

AVUTIL_REQUIRED_VERSION=52.66.100
PKG_CHECK_MODULES(AVUTIL, libavutil >= $AVUTIL_REQUIRED_VERSION)
AC_SUBST(AVUTIL_CFLAGS)
AC_SUBST(AVUTIL_LIBS)

AVFORMAT_REQUIRED_VERSION=55.33.100
PKG_CHECK_MODULES(AVFORMAT, libavformat >= $AVFORMAT_REQUIRED_VERSION)
AC_SUBST(AVFORMAT_CFLAGS)
AC_SUBST(AVFORMAT_LIBS)

SWSCALE_REQUIRED_VERSION=2.5.102
PKG_CHECK_MODULES(SWSCALE, libswscale >= $SWSCALE_REQUIRED_VERSION)
AC_SUBST(SWSCALE_CFLAGS)
AC_SUBST(SWSCALE_LIBS)

SWRESAMPLE_REQUIRED_VERSION=0.18.100
PKG_CHECK_MODULES(SWRESAMPLE, libswresample >= $SWRESAMPLE_REQUIRED_VERSION)
AC_SUBST(SWRESAMPLE_CFLAGS)
AC_SUBST(SWRESAMPLE_LIBS)

PCRE_REQUIRED_VERSION=8.30
PKG_CHECK_MODULES(PCRE, libpcre >= $PCRE_REQUIRED_VERSION)
AC_SUBST(PCRE_CFLAGS)
AC_SUBST(PCRE_LIBS)

FREETYPE2_REQUIRED_VERSION=14.1.8
PKG_CHECK_MODULES(FREETYPE2, freetype2 >= $FREETYPE2_REQUIRED_VERSION)
AC_SUBST(FREETYPE2_CFLAGS)
AC_SUBST(FREETYPE2_LIBS)





VC_CFLAGS="-I$VCDIR/include -I$VCDIR/include/interface/vcos/pthreads -I$VCDIR/include/interface/vmcs_host/linux/"
VC_LIBS="-L$VCDIR/lib -lvchiq_arm -lvcos -lWFC -lGLESv2 -lopenmaxil  -lbcm_host -lEGL"
AC_SUBST(VC_CFLAGS)
AC_SUBST(VC_LIBS)
AC_SUBST(VCDIR)
export CPPFLAGS="$CPPFLAGS $VC_CFLAGS"
AC_CHECK_HEADERS(bcm_host.h, [] ,  AC_MSG_ERROR("--with-vc points to wrong directory"))





AC_OUTPUT(Makefile omxplayer)
