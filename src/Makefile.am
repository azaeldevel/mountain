

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

lib_LTLIBRARIES = liboctetos-mountain.la

noinst_PROGRAMS = mountain




liboctetos_mountain_la_CXXFLAGS = $(OCTETOS_MOUNTAIN_CFLGAS)  
liboctetos_mountain_la_LIBADD = $(OCTETOS_MOUNTAIN_LIBS) 
liboctetos_mountain_la_SOURCES = Database.cc Exception.cc Field.cc Table.cc

mountain_SOURCES = main.cc
mountain_LDFLAGS = 
mountain_LDADD = liboctetos-mountain.la


if NATIVE_WIN32
mountain_LDFLAGS += -mwindows
endif
