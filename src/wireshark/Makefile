# Makefile.in generated by automake 1.9.6 from Makefile.am.
# plugins/r14p/Makefile.  Generated from Makefile.in by configure.

# Copyright (C) 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002,
# 2003, 2004, 2005  Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.



# Makefile.common for generic ASN.1-based plugin
#     Contains the stuff from Makefile.am and Makefile.nmake that is
#     a) common to both files and
#     b) portable between both files
#
# $Id$
#
# Wireshark - Network traffic analyzer
# By Gerald Combs <gerald@wireshark.org>
# Copyright 1998 Gerald Combs
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

top_srcdir = ../..

pkgdatadir = $(datadir)/wireshark
pkglibdir = $(libdir)/wireshark
pkgincludedir = $(includedir)/wireshark
top_builddir = ../..
am__cd = CDPATH="$${ZSH_VERSION+.}$(PATH_SEPARATOR)" && cd
INSTALL = /usr/bin/install -c
install_sh_DATA = $(install_sh) -c -m 644
install_sh_PROGRAM = $(install_sh) -c
install_sh_SCRIPT = $(install_sh) -c
INSTALL_HEADER = $(INSTALL_DATA)
transform = $(program_transform_name)
NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
build_triplet = x86_64-unknown-linux-gnu
host_triplet = x86_64-unknown-linux-gnu
target_triplet = x86_64-unknown-linux-gnu
DIST_COMMON = README $(srcdir)/Makefile.am $(srcdir)/Makefile.common \
	$(srcdir)/Makefile.in AUTHORS COPYING ChangeLog INSTALL NEWS \
	TODO
subdir = plugins/r14p
ACLOCAL_M4 = $(top_srcdir)/aclocal.m4
am__aclocal_m4_deps = $(top_srcdir)/aclocal-fallback/glib-2.0.m4 \
	$(top_srcdir)/aclocal-fallback/gtk-2.0.m4 \
	$(top_srcdir)/aclocal-fallback/libgcrypt.m4 \
	$(top_srcdir)/aclocal-fallback/libsmi.m4 \
	$(top_srcdir)/acinclude.m4 $(top_srcdir)/configure.in
am__configure_deps = $(am__aclocal_m4_deps) $(CONFIGURE_DEPENDENCIES) \
	$(ACLOCAL_M4)
mkinstalldirs = $(install_sh) -d
CONFIG_HEADER = $(top_builddir)/config.h
CONFIG_CLEAN_FILES =
am__vpath_adj_setup = srcdirstrip=`echo "$(srcdir)" | sed 's|.|.|g'`;
am__vpath_adj = case $$p in \
    $(srcdir)/*) f=`echo "$$p" | sed "s|^$$srcdirstrip/||"`;; \
    *) f=$$p;; \
  esac;
am__strip_dir = `echo $$p | sed -e 's|^.*/||'`;
am__installdirs = "$(DESTDIR)$(plugindir)"
pluginLTLIBRARIES_INSTALL = $(INSTALL)
LTLIBRARIES = $(plugin_LTLIBRARIES)
r14p_la_DEPENDENCIES =
am__objects_1 = packet-r14p.lo
am__objects_2 =
am_r14p_la_OBJECTS = plugin.lo $(am__objects_1) $(am__objects_2)
r14p_la_OBJECTS = $(am_r14p_la_OBJECTS)
DEFAULT_INCLUDES = -I. -I$(srcdir) -I$(top_builddir)
depcomp = $(SHELL) $(top_srcdir)/depcomp
am__depfiles_maybe = depfiles
COMPILE = $(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	$(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
LTCOMPILE = $(LIBTOOL) --tag=CC --mode=compile $(CC) $(DEFS) \
	$(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) \
	$(AM_CFLAGS) $(CFLAGS)
CCLD = $(CC)
LINK = $(LIBTOOL) --tag=CC --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) \
	$(AM_LDFLAGS) $(LDFLAGS) -o $@
SOURCES = $(r14p_la_SOURCES)
DIST_SOURCES = $(r14p_la_SOURCES)
ETAGS = etags
CTAGS = ctags
DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)
srcdir = .
ACLOCAL = ${SHELL} /home/dfranusic/wireshark-1.6.9/missing --run aclocal-1.9
ADNS_LIBS = 
AMDEP_FALSE = #
AMDEP_TRUE = 
AMTAR = ${SHELL} /home/dfranusic/wireshark-1.6.9/missing --run tar
AR = ar
AUTOCONF = ${SHELL} /home/dfranusic/wireshark-1.6.9/missing --run autoconf
AUTOHEADER = ${SHELL} /home/dfranusic/wireshark-1.6.9/missing --run autoheader
AUTOMAKE = ${SHELL} /home/dfranusic/wireshark-1.6.9/missing --run automake-1.9
AWK = gawk
CC = gcc
CCDEPMODE = depmode=gcc3
CC_FOR_BUILD = gcc
CFLAGS = -DINET6 -D_U_="__attribute__((unused))" -g -O2 -Wall -W -Wextra -Wdeclaration-after-statement -Wendif-labels -Wpointer-arith -Wno-pointer-sign -Warray-bounds -Wcast-align -Wformat-security -I/usr/local/include -pthread -I/usr/include/gtk-2.0 -I/usr/lib64/gtk-2.0/include -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/pango-1.0 -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng15 -I/usr/include/libdrm   -I/usr/include
CORESERVICES_FRAMEWORKS = 
CPP = gcc -E
CPPFLAGS =  -I/usr/local/include -I/usr/include '-DPLUGIN_DIR="$(plugindir)"'
CXX = g++
CXXCPP = g++ -E
CXXDEPMODE = depmode=gcc3
CXXFLAGS = -g -O2 -pthread -I/usr/include/gtk-2.0 -I/usr/lib64/gtk-2.0/include -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/pango-1.0 -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng15 -I/usr/include/libdrm  
CYGPATH_W = echo
C_ARES_LIBS = 
DEFS = -DHAVE_CONFIG_H
DEPDIR = .deps
DOXYGEN = /usr/bin/doxygen
DSYMUTIL = 
DUMPBIN = 
DUMPCAP_GROUP = 
ECHO_C = 
ECHO_N = -n
ECHO_T = 
EGREP = /bin/grep -E
ELINKS = 
ENABLE_STATIC = 
ENABLE_STATIC_FALSE = 
ENABLE_STATIC_TRUE = #
EXEEXT = 
FGREP = /bin/grep -F
FOP = 
GEOIP_LIBS = 
GETOPT_LO = 
GLIB_CFLAGS = -pthread -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include  
GLIB_GENMARSHAL = glib-genmarshal
GLIB_LIBS = -pthread -Wl,--export-dynamic -lgthread-2.0 -lgmodule-2.0 -lrt -lglib-2.0  
GLIB_MKENUMS = glib-mkenums
GOBJECT_QUERY = gobject-query
GREP = /bin/grep
GTK_CFLAGS = -pthread -I/usr/include/gtk-2.0 -I/usr/lib64/gtk-2.0/include -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/pango-1.0 -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng15 -I/usr/include/libdrm  
GTK_LIBS = -pthread -lgtk-x11-2.0 -lgdk-x11-2.0 -latk-1.0 -lgio-2.0 -lpangoft2-1.0 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lcairo -lpango-1.0 -lfreetype -lfontconfig -lgobject-2.0 -lgmodule-2.0 -lgthread-2.0 -lrt -lglib-2.0  
HAVE_BLESS = no
HAVE_DOXYGEN = yes
HAVE_DOXYGEN_FALSE = #
HAVE_DOXYGEN_TRUE = 
HAVE_DPKG_BUILDPACKAGE = no
HAVE_DUMPCAP_GROUP_FALSE = 
HAVE_DUMPCAP_GROUP_TRUE = #
HAVE_ELINKS = no
HAVE_ELINKS_FALSE = 
HAVE_ELINKS_TRUE = #
HAVE_FOP = no
HAVE_FOP_FALSE = 
HAVE_FOP_TRUE = #
HAVE_HDIUTIL = no
HAVE_HHC = no
HAVE_HHC_FALSE = 
HAVE_HHC_TRUE = #
HAVE_LIBLUA_FALSE = #
HAVE_LIBLUA_TRUE = 
HAVE_LIBPORTAUDIO_FALSE = 
HAVE_LIBPORTAUDIO_TRUE = #
HAVE_LIBPY_FALSE = 
HAVE_LIBPY_TRUE = #
HAVE_LYNX = yes
HAVE_LYNX_FALSE = #
HAVE_LYNX_TRUE = 
HAVE_OSX_PACKAGING = no
HAVE_PKGMK = no
HAVE_PKGPROTO = no
HAVE_PKGTRANS = no
HAVE_PLUGINS_FALSE = #
HAVE_PLUGINS_TRUE = 
HAVE_RPM = 
HAVE_SVR4_PACKAGING = no
HAVE_WARNINGS_AS_ERRORS_FALSE = 
HAVE_WARNINGS_AS_ERRORS_TRUE = #
HAVE_XCODEBUILD = no
HAVE_XMLLINT = yes
HAVE_XMLLINT_FALSE = #
HAVE_XMLLINT_TRUE = 
HAVE_XSLTPROC = yes
HAVE_XSLTPROC_FALSE = #
HAVE_XSLTPROC_TRUE = 
HHC = 
HTML_VIEWER = /usr/bin/xdg-open
INET_ATON_LO = 
INET_NTOP_LO = 
INET_PTON_LO = 
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_PROGRAM = ${INSTALL}
INSTALL_SCRIPT = ${INSTALL}
INSTALL_STRIP_PROGRAM = ${SHELL} $(install_sh) -c -s
KRB5_CONFIG = 
KRB5_LIBS = 
LAUNCHSERVICES_FRAMEWORKS = 
LD = /usr/x86_64-pc-linux-gnu/bin/ld -m elf_x86_64
LDFLAGS =  -Wl,--as-needed -L/usr/local/lib -L/usr/local/lib -L/usr/local/lib -L/usr/local/lib -L/usr/local/lib
LDFLAGS_SHAREDLIB = 
LEX = /usr/bin/flex
LEXLIB = -lfl
LEX_OUTPUT_ROOT = lex.yy
LIBCAP_LIBS = -lcap
LIBGCRYPT_CFLAGS = 
LIBGCRYPT_CONFIG = /usr/bin/libgcrypt-config
LIBGCRYPT_LIBS = -L/usr/lib64 -lgcrypt -lgpg-error
LIBGNUTLS_CFLAGS =  
LIBGNUTLS_LIBS = -lgnutls  
LIBOBJS = 

# Libs must be cleared, or else libtool won't create a shared module.
# If your module needs to be linked against any particular libraries,
# add them here.
LIBS = 
LIBSMI_CFLAGS = 
LIBSMI_LDFLAGS = 
LIBSMI_VERSION = 
LIBTOOL = $(SHELL) $(top_builddir)/libtool
LIBTOOL_DEPS = ./ltmain.sh
LIPO = 
LN_S = ln -s
LTLIBOBJS = 
LUA_INCLUDES = 
LUA_LIBS = -llua -lm
LYNX = /usr/bin/lynx
MAKEINFO = ${SHELL} /home/dfranusic/wireshark-1.6.9/missing --run makeinfo
NEED_GETOPT_LO_FALSE = 
NEED_GETOPT_LO_TRUE = #
NEED_INET_ATON_LO_FALSE = 
NEED_INET_ATON_LO_TRUE = #
NEED_INET_NTOP_LO_FALSE = 
NEED_INET_NTOP_LO_TRUE = #
NEED_INET_PTON_LO_FALSE = 
NEED_INET_PTON_LO_TRUE = #
NEED_STRNCASECMP_LO_FALSE = 
NEED_STRNCASECMP_LO_TRUE = #
NEED_STRPTIME_LO_FALSE = 
NEED_STRPTIME_LO_TRUE = #
NM = /usr/bin/nm -B
NMEDIT = 
NSL_LIBS = 
OBJDUMP = objdump
OBJEXT = o
OTOOL = 
OTOOL64 = 
PACKAGE = wireshark
PACKAGE_BUGREPORT = 
PACKAGE_NAME = wireshark
PACKAGE_STRING = wireshark 1.6.9
PACKAGE_TARNAME = wireshark
PACKAGE_URL = 
PACKAGE_VERSION = 1.6.9
PATH_SEPARATOR = :
PCAP_CONFIG = /usr/bin/pcap-config
PCAP_LIBS = -L/usr/lib64 -Wl,-rpath,/usr/lib64 -lpcap
PCRE_LIBS = 
PERL = /usr/bin/perl
PKG_CONFIG = /usr/bin/pkg-config
PKG_CONFIG_LIBDIR = 
PKG_CONFIG_PATH = 
PLUGIN_LIBS = 
POD2HTML = /usr/bin/pod2html
POD2MAN = /usr/bin/pod2man
PORTAUDIO_INCLUDES = 
PORTAUDIO_LIBS = 
PYTHON = /usr/bin/python
PY_CFLAGS = 
PY_LIBS = 
RANLIB = ranlib
SED = /bin/sed
SETCAP = 
SETCAP_INSTALL_FALSE = 
SETCAP_INSTALL_TRUE = #
SETUID_INSTALL_FALSE = 
SETUID_INSTALL_TRUE = #
SET_MAKE = 
SHELL = /bin/sh
SOCKET_LIBS = 
SSL_LIBS = 
STRIP = strip
STRNCASECMP_LO = 
STRPTIME_C = 
STRPTIME_LO = 
USE_PROFILE_BUILD_FALSE = 
USE_PROFILE_BUILD_TRUE = #
VERSION = 1.6.9
XMLLINT = /usr/bin/xmllint
XSLTPROC = /usr/bin/xsltproc
YACC = bison -y
YACCDUMMY = /usr/bin/bison
YFLAGS = 
ac_ct_CC = gcc
ac_ct_CXX = g++
ac_ct_DUMPBIN = 
ac_cv_wireshark_have_rpm = no
ac_ws_python_config = 
am__fastdepCC_FALSE = #
am__fastdepCC_TRUE = 
am__fastdepCXX_FALSE = #
am__fastdepCXX_TRUE = 
am__include = include
am__leading_dot = .
am__quote = 
am__tar = tar --format=ustar -chf - "$$tardir"
am__untar = tar -xf -
bindir = ${exec_prefix}/bin
build = x86_64-unknown-linux-gnu
build_alias = 
build_cpu = x86_64
build_os = linux-gnu
build_vendor = unknown
capinfos_bin = capinfos$(EXEEXT)
capinfos_man = capinfos.1
datadir = ${datarootdir}
datarootdir = ${prefix}/share
dftest_bin = dftest$(EXEEXT)
dftest_man = dftest.1
docdir = /usr/local/share/doc/wireshark
dumpcap_bin = dumpcap$(EXEEXT)
dumpcap_man = dumpcap.1
dvidir = ${docdir}
editcap_bin = editcap$(EXEEXT)
editcap_man = editcap.1
exec_prefix = ${prefix}
host = x86_64-unknown-linux-gnu
host_alias = 
host_cpu = x86_64
host_os = linux-gnu
host_vendor = unknown
htmldir = ${docdir}
idl2wrs_bin = idl2wrs
idl2wrs_man = idl2wrs.1
includedir = ${prefix}/include
infodir = ${datarootdir}/info
install_sh = /home/dfranusic/wireshark-1.6.9/install-sh
libdir = ${exec_prefix}/lib
libexecdir = ${exec_prefix}/libexec
localedir = ${datarootdir}/locale
localstatedir = ${prefix}/var
mandir = ${datarootdir}/man
mergecap_bin = mergecap$(EXEEXT)
mergecap_man = mergecap.1
mkdir_p = mkdir -p --
oldincludedir = /usr/include
pdfdir = ${docdir}
plugindir = ${libdir}/wireshark/plugins/${VERSION}
prefix = /usr/local
program_transform_name = s,x,x,
psdir = ${docdir}
pythondir = 
randpkt_bin = randpkt$(EXEEXT)
randpkt_man = randpkt.1
rawshark_bin = rawshark$(EXEEXT)
rawshark_man = rawshark.1
sbindir = ${exec_prefix}/sbin
sharedstatedir = ${prefix}/com
sysconfdir = ${prefix}/etc
target = x86_64-unknown-linux-gnu
target_alias = 
target_cpu = x86_64
target_os = linux-gnu
target_vendor = unknown
text2pcap_bin = text2pcap$(EXEEXT)
text2pcap_man = text2pcap.1
tshark_bin = tshark$(EXEEXT)
tshark_man = tshark.1
wireshark_SUBDIRS = codecs gtk
wireshark_bin = wireshark$(EXEEXT)
wireshark_man = wireshark.1
wiresharkfilter_man = wireshark-filter.4

# Makefile.am
# Automake file for generic ASN.1-based plugin
# By Edward J. Beroset
# Copyright 2010 Edward J. Beroset
#
# $Id$
#
# Wireshark - Network traffic analyzer
# By Gerald Combs <gerald@wireshark.org>
# Copyright 1998 Gerald Combs
# 
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#
INCLUDES = -I$(top_srcdir) -I$(includedir)

# the name of the plugin
PLUGIN_NAME = r14p
PLUG = r14p

# the dissector sources (without any helpers)
DISSECTOR_SRC = \
	packet-r14p.c


# corresponding headers
DISSECTOR_INCLUDES = \
	packet-r14p.h

DISSECTOR_FILES = $(DISSECTOR_SRC) $(DISSECTOR_INCLUDES) 
BUILT_FILES = packet-$(PLUG)-template.c packet-$(PLUG)-template.h $(PLUG).cnf $(PLUG).asn
SRC_FILES = \
	$(EXT_ASN_FILE_LIST) \
	$(EXTRA_DIST)

A2W_FLAGS = -b -L
ASN_FILE_LIST = $(PLUGIN_NAME).asn
PROTO_OPT = -p $(PLUGIN_NAME)
EXTRA_CNF = 

# Dissector helpers. They're included in the source files in this
# directory, but they're not dissectors themselves, i.e. they're not
# used to generate "plugin.c".
DISSECTOR_SUPPORT_SRC = 
#AM_CFLAGS = -Werror
BUILT_SOURCES = packet-r14p.h
plugin_LTLIBRARIES = r14p.la
r14p_la_SOURCES = \
	plugin.c \
	moduleinfo.h \
	$(DISSECTOR_SRC) \
	$(DISSECTOR_INCLUDES)

r14p_la_LDFLAGS = -module -avoid-version
r14p_la_LIBADD = 

#
# Currently plugin.c can be included in the distribution because
# we always build all protocol dissectors. We used to have to check
# whether or not to build the snmp dissector. If we again need to
# variably build something, making plugin.c non-portable, uncomment
# the dist-hook line below.
#
# Oh, yuk.  We don't want to include "plugin.c" in the distribution, as
# its contents depend on the configuration, and therefore we want it
# to be built when the first "make" is done; however, Automake insists
# on putting *all* source into the distribution.
#
# We work around this by having a "dist-hook" rule that deletes
# "plugin.c", so that "dist" won't pick it up.
#
#dist-hook:
#	@rm -f $(distdir)/plugin.c
CLEANFILES = \
	parsetab.py \
	parsetab.pyc \
	$(DISSECTOR_FILES) \
	*-exp.cnf \
	packet-*-{dis-tab,ettarr,ett,fn,hfarr,hf,table*,val,exp}.[hc] \
	*~

MAINTAINERCLEANFILES = \
	Makefile.in	\
	plugin.c

EXTRA_DIST = \
	Makefile.common		\
	Makefile.nmake		\
	$(ASN_FILE_LIST) \
	packet-$(PLUGIN_NAME)-template.c \
	packet-$(PLUGIN_NAME)-template.h \
	$(PLUGIN_NAME).cnf \
	$(PLUGIN_NAME).asn \
	moduleinfo.nmake	\
	plugin.rc.in

all: $(BUILT_SOURCES)
	$(MAKE) $(AM_MAKEFLAGS) all-am

.SUFFIXES:
.SUFFIXES: .c .lo .o .obj
$(srcdir)/Makefile.in:  $(srcdir)/Makefile.am $(srcdir)/Makefile.common $(am__configure_deps)
	@for dep in $?; do \
	  case '$(am__configure_deps)' in \
	    *$$dep*) \
	      cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh \
		&& exit 0; \
	      exit 1;; \
	  esac; \
	done; \
	echo ' cd $(top_srcdir) && $(AUTOMAKE) --gnu  plugins/r14p/Makefile'; \
	cd $(top_srcdir) && \
	  $(AUTOMAKE) --gnu  plugins/r14p/Makefile
.PRECIOUS: Makefile
Makefile: $(srcdir)/Makefile.in $(top_builddir)/config.status
	@case '$?' in \
	  *config.status*) \
	    cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh;; \
	  *) \
	    echo ' cd $(top_builddir) && $(SHELL) ./config.status $(subdir)/$@ $(am__depfiles_maybe)'; \
	    cd $(top_builddir) && $(SHELL) ./config.status $(subdir)/$@ $(am__depfiles_maybe);; \
	esac;

$(top_builddir)/config.status: $(top_srcdir)/configure $(CONFIG_STATUS_DEPENDENCIES)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh

$(top_srcdir)/configure:  $(am__configure_deps)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh
$(ACLOCAL_M4):  $(am__aclocal_m4_deps)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh
install-pluginLTLIBRARIES: $(plugin_LTLIBRARIES)
	@$(NORMAL_INSTALL)
	test -z "$(plugindir)" || $(mkdir_p) "$(DESTDIR)$(plugindir)"
	@list='$(plugin_LTLIBRARIES)'; for p in $$list; do \
	  if test -f $$p; then \
	    f=$(am__strip_dir) \
	    echo " $(LIBTOOL) --mode=install $(pluginLTLIBRARIES_INSTALL) $(INSTALL_STRIP_FLAG) '$$p' '$(DESTDIR)$(plugindir)/$$f'"; \
	    $(LIBTOOL) --mode=install $(pluginLTLIBRARIES_INSTALL) $(INSTALL_STRIP_FLAG) "$$p" "$(DESTDIR)$(plugindir)/$$f"; \
	  else :; fi; \
	done

uninstall-pluginLTLIBRARIES:
	@$(NORMAL_UNINSTALL)
	@set -x; list='$(plugin_LTLIBRARIES)'; for p in $$list; do \
	  p=$(am__strip_dir) \
	  echo " $(LIBTOOL) --mode=uninstall rm -f '$(DESTDIR)$(plugindir)/$$p'"; \
	  $(LIBTOOL) --mode=uninstall rm -f "$(DESTDIR)$(plugindir)/$$p"; \
	done

clean-pluginLTLIBRARIES:
	-test -z "$(plugin_LTLIBRARIES)" || rm -f $(plugin_LTLIBRARIES)
	@list='$(plugin_LTLIBRARIES)'; for p in $$list; do \
	  dir="`echo $$p | sed -e 's|/[^/]*$$||'`"; \
	  test "$$dir" != "$$p" || dir=.; \
	  echo "rm -f \"$${dir}/so_locations\""; \
	  rm -f "$${dir}/so_locations"; \
	done
r14p.la: $(r14p_la_OBJECTS) $(r14p_la_DEPENDENCIES) 
	$(LINK) -rpath $(plugindir) $(r14p_la_LDFLAGS) $(r14p_la_OBJECTS) $(r14p_la_LIBADD) $(LIBS)

mostlyclean-compile:
	-rm -f *.$(OBJEXT)

distclean-compile:
	-rm -f *.tab.c

include ./$(DEPDIR)/packet-r14p.Plo
include ./$(DEPDIR)/plugin.Plo

.c.o:
	if $(COMPILE) -MT $@ -MD -MP -MF "$(DEPDIR)/$*.Tpo" -c -o $@ $<; \
	then mv -f "$(DEPDIR)/$*.Tpo" "$(DEPDIR)/$*.Po"; else rm -f "$(DEPDIR)/$*.Tpo"; exit 1; fi
#	source='$<' object='$@' libtool=no \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(COMPILE) -c $<

.c.obj:
	if $(COMPILE) -MT $@ -MD -MP -MF "$(DEPDIR)/$*.Tpo" -c -o $@ `$(CYGPATH_W) '$<'`; \
	then mv -f "$(DEPDIR)/$*.Tpo" "$(DEPDIR)/$*.Po"; else rm -f "$(DEPDIR)/$*.Tpo"; exit 1; fi
#	source='$<' object='$@' libtool=no \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(COMPILE) -c `$(CYGPATH_W) '$<'`

.c.lo:
	if $(LTCOMPILE) -MT $@ -MD -MP -MF "$(DEPDIR)/$*.Tpo" -c -o $@ $<; \
	then mv -f "$(DEPDIR)/$*.Tpo" "$(DEPDIR)/$*.Plo"; else rm -f "$(DEPDIR)/$*.Tpo"; exit 1; fi
#	source='$<' object='$@' libtool=yes \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(LTCOMPILE) -c -o $@ $<

mostlyclean-libtool:
	-rm -f *.lo

clean-libtool:
	-rm -rf .libs _libs

distclean-libtool:
	-rm -f libtool
uninstall-info-am:

ID: $(HEADERS) $(SOURCES) $(LISP) $(TAGS_FILES)
	list='$(SOURCES) $(HEADERS) $(LISP) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	mkid -fID $$unique
tags: TAGS

TAGS:  $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) \
		$(TAGS_FILES) $(LISP)
	tags=; \
	here=`pwd`; \
	list='$(SOURCES) $(HEADERS)  $(LISP) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	if test -z "$(ETAGS_ARGS)$$tags$$unique"; then :; else \
	  test -n "$$unique" || unique=$$empty_fix; \
	  $(ETAGS) $(ETAGSFLAGS) $(AM_ETAGSFLAGS) $(ETAGS_ARGS) \
	    $$tags $$unique; \
	fi
ctags: CTAGS
CTAGS:  $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) \
		$(TAGS_FILES) $(LISP)
	tags=; \
	here=`pwd`; \
	list='$(SOURCES) $(HEADERS)  $(LISP) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	test -z "$(CTAGS_ARGS)$$tags$$unique" \
	  || $(CTAGS) $(CTAGSFLAGS) $(AM_CTAGSFLAGS) $(CTAGS_ARGS) \
	     $$tags $$unique

GTAGS:
	here=`$(am__cd) $(top_builddir) && pwd` \
	  && cd $(top_srcdir) \
	  && gtags -i $(GTAGS_ARGS) $$here

distclean-tags:
	-rm -f TAGS ID GTAGS GRTAGS GSYMS GPATH tags

distdir: $(DISTFILES)
	@srcdirstrip=`echo "$(srcdir)" | sed 's|.|.|g'`; \
	topsrcdirstrip=`echo "$(top_srcdir)" | sed 's|.|.|g'`; \
	list='$(DISTFILES)'; for file in $$list; do \
	  case $$file in \
	    $(srcdir)/*) file=`echo "$$file" | sed "s|^$$srcdirstrip/||"`;; \
	    $(top_srcdir)/*) file=`echo "$$file" | sed "s|^$$topsrcdirstrip/|$(top_builddir)/|"`;; \
	  esac; \
	  if test -f $$file || test -d $$file; then d=.; else d=$(srcdir); fi; \
	  dir=`echo "$$file" | sed -e 's,/[^/]*$$,,'`; \
	  if test "$$dir" != "$$file" && test "$$dir" != "."; then \
	    dir="/$$dir"; \
	    $(mkdir_p) "$(distdir)$$dir"; \
	  else \
	    dir=''; \
	  fi; \
	  if test -d $$d/$$file; then \
	    if test -d $(srcdir)/$$file && test $$d != $(srcdir); then \
	      cp -pR $(srcdir)/$$file $(distdir)$$dir || exit 1; \
	    fi; \
	    cp -pR $$d/$$file $(distdir)$$dir || exit 1; \
	  else \
	    test -f $(distdir)/$$file \
	    || cp -p $$d/$$file $(distdir)/$$file \
	    || exit 1; \
	  fi; \
	done
check-am: all-am
check: $(BUILT_SOURCES)
	$(MAKE) $(AM_MAKEFLAGS) check-am
all-am: Makefile $(LTLIBRARIES)
installdirs:
	for dir in "$(DESTDIR)$(plugindir)"; do \
	  test -z "$$dir" || $(mkdir_p) "$$dir"; \
	done
install: $(BUILT_SOURCES)
	$(MAKE) $(AM_MAKEFLAGS) install-am
install-exec: install-exec-am
install-data: install-data-am
uninstall: uninstall-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am

installcheck: installcheck-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	  install_sh_PROGRAM="$(INSTALL_STRIP_PROGRAM)" INSTALL_STRIP_FLAG=-s \
	  `test -z '$(STRIP)' || \
	    echo "INSTALL_PROGRAM_ENV=STRIPPROG='$(STRIP)'"` install
mostlyclean-generic:

clean-generic:
	-test -z "$(CLEANFILES)" || rm -f $(CLEANFILES)

distclean-generic:
	-test -z "$(CONFIG_CLEAN_FILES)" || rm -f $(CONFIG_CLEAN_FILES)

maintainer-clean-generic:
	@echo "This command is intended for maintainers to use"
	@echo "it deletes files that may require special tools to rebuild."
	-test -z "$(BUILT_SOURCES)" || rm -f $(BUILT_SOURCES)
	-test -z "$(MAINTAINERCLEANFILES)" || rm -f $(MAINTAINERCLEANFILES)
clean: clean-am

clean-am: clean-generic clean-libtool clean-pluginLTLIBRARIES \
	mostlyclean-am

distclean: distclean-am
	-rm -rf ./$(DEPDIR)
	-rm -f Makefile
distclean-am: clean-am distclean-compile distclean-generic \
	distclean-libtool distclean-tags

dvi: dvi-am

dvi-am:

html: html-am

info: info-am

info-am:

install-data-am: install-pluginLTLIBRARIES

install-exec-am:

install-info: install-info-am

install-man:

installcheck-am:

maintainer-clean: maintainer-clean-am
	-rm -rf ./$(DEPDIR)
	-rm -f Makefile
maintainer-clean-am: distclean-am maintainer-clean-generic

mostlyclean: mostlyclean-am

mostlyclean-am: mostlyclean-compile mostlyclean-generic \
	mostlyclean-libtool

pdf: pdf-am

pdf-am:

ps: ps-am

ps-am:

uninstall-am: uninstall-info-am uninstall-pluginLTLIBRARIES

.PHONY: CTAGS GTAGS all all-am check check-am clean clean-generic \
	clean-libtool clean-pluginLTLIBRARIES ctags distclean \
	distclean-compile distclean-generic distclean-libtool \
	distclean-tags distdir dvi dvi-am html html-am info info-am \
	install install-am install-data install-data-am install-exec \
	install-exec-am install-info install-info-am install-man \
	install-pluginLTLIBRARIES install-strip installcheck \
	installcheck-am installdirs maintainer-clean \
	maintainer-clean-generic mostlyclean mostlyclean-compile \
	mostlyclean-generic mostlyclean-libtool pdf pdf-am ps ps-am \
	tags uninstall uninstall-am uninstall-info-am \
	uninstall-pluginLTLIBRARIES


#
# Build plugin.c, which contains the plugin version[] string, a
# function plugin_register() that calls the register routines for all
# protocols, and a function plugin_reg_handoff() that calls the handoff
# registration routines for all protocols.
#
# We do this by scanning sources.  If that turns out to be too slow,
# maybe we could just require every .o file to have an register routine
# of a given name (packet-aarp.o -> proto_register_aarp, etc.).
#
# Formatting conventions:  The name of the proto_register_* routines an
# proto_reg_handoff_* routines must start in column zero, or must be
# preceded only by "void " starting in column zero, and must not be
# inside #if.
#
# DISSECTOR_SRC is assumed to have all the files that need to be scanned.
#
# For some unknown reason, having a big "for" loop in the Makefile
# to scan all the files doesn't work with some "make"s; they seem to
# pass only the first few names in the list to the shell, for some
# reason.
#
# Therefore, we have a script to generate the plugin.c file.
# The shell script runs slowly, as multiple greps and seds are run
# for each input file; this is especially slow on Windows.  Therefore,
# if Python is present (as indicated by PYTHON being defined), we run
# a faster Python script to do that work instead.
#
# The first argument is the directory in which the source files live.
# The second argument is "plugin", to indicate that we should build
# a plugin.c file for a plugin.
# All subsequent arguments are the files to scan.
#
plugin.c: $(DISSECTOR_SRC) $(top_srcdir)/tools/make-dissector-reg \
    $(top_srcdir)/tools/make-dissector-reg.py
	@if test -n "$(PYTHON)"; then \
		echo Making plugin.c with python ; \
		$(PYTHON) $(top_srcdir)/tools/make-dissector-reg.py $(srcdir) \
		    plugin $(DISSECTOR_SRC) ; \
	else \
		echo Making plugin.c with shell script ; \
		$(top_srcdir)/tools/make-dissector-reg $(srcdir) \
		    $(plugin_src) plugin $(DISSECTOR_SRC) ; \
	fi

generate_dissector: $(DISSECTOR_FILES)

generate_export: $(EXPORT_FILES)

PROTO_OPT ?= -p $(PLUGIN_NAME)

$(DISSECTOR_FILES): $(top_srcdir)/tools/asn2wrs.py $(SRC_FILES) $(EXTRA_CNF)
	python $(top_srcdir)/tools/asn2wrs.py \
		$(A2W_FLAGS) \
		$(PROTO_OPT) \
		-c $(srcdir)/$(PLUGIN_NAME).cnf \
		-s $(srcdir)/packet-$(PLUGIN_NAME)-template \
		-D $(srcdir) $(EXT_ASN_FILE_LIST) $(ASN_FILE_LIST) $(EXT_ASN_FILE_LIST_LATE)

$(EXPORT_FILES): $(top_srcdir)/tools/asn2wrs.py $(SRC_FILES)
	python $(top_srcdir)/tools/asn2wrs.py \
		-E $(A2W_FLAGS) \
		$(PROTO_OPT) \
		-c $(srcdir)/$(PLUGIN_NAME).cnf \
		-D $(srcdir) $(EXT_ASN_FILE_LIST) $(ASN_FILE_LIST) $(EXT_ASN_FILE_LIST_LATE)

checkapi:
	$(PERL) $(top_srcdir)/tools/checkAPIs.pl -g abort -g termoutput $(DISSECTOR_SRC) $(DISSECTOR_INCLUDES)
# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
