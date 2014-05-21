# Makefile for the octave sockets package.
# The intent is to keep this makefile working for
# * Octave>=3.2
# * Windows
# straight out of the box.

OCT := socket.oct
SRC := $(OCT:.oct=.cc)

MKOCTFILE ?= mkoctfile -Wall
OCTAVE ?= octave

#The following is necessary to get the sockets package working in Windows.
#It has been tried on Win7 and XP, in Octave 3.8.0 using mxe-octave (mingw)
EXTRALIBS := 
ifeq ($(OS),Windows_NT)
  EXTRALIBS := -lws2_32
endif

all: $(OCT)

%.oct: %.cc
	$(MKOCTFILE) $< $(EXTRALIBS)

# We need to generate a PKG_ADD file for this to work. We could also
# get a string with the stuff in PKG_ADD and eval it before the test
# command, but it messes up the quotes.
check: $(OCT)
	grep PKG_ADD $(SRC) | sed 's/\/\/ PKG_ADD: //' > PKG_ADD
	$(OCTAVE) -q --no-window-system --eval "test $(SRC)"
	rm PKG_ADD

clean:
	-rm -f *.o octave-core octave-workspace core *.oct *~ PKG_ADD

#This creates a package for distribution. It requires the checked out hg
#repo to be named sockets, or that a symlink of name sockets point to the
#checked out repo.
pkgversion:=$(word 2,$(shell grep ^Version ../DESCRIPTION|head -n1))
pkg:
	cd ../.. && tar cvfzh sockets-${pkgversion}.tar.gz --exclude=.hg sockets/

.PHONY: all clean check pkg
