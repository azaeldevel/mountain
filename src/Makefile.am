

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = mountain

mountain_SOURCES = \
	main.cc

mountain_LDFLAGS = 

mountain_LDADD = 


if NATIVE_WIN32
mountain_LDFLAGS += -mwindows
endif
