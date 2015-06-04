# mapico
AUTOMAKE_OPTIONS = foreign
bin_PROGRAMS = mapico
mapico_SOURCES = MAPiCO.c 
mapico_LDADD = ./.libs/libmapico.a -L../constsys/ -lCS -ldl -lm

INCLUDES =  -I../constsys/ -I../include/
CFLAGS = -O2 -std=c99

lib_LTLIBRARIES = libmapico.la 
libmapico_la_SOURCES = HeapSort.c BinaryTree.c Parameters.c Proceso.c Loader.c StoreMA.c PlugIns.c
#libmapico_la_CFLAGS = -std=c99