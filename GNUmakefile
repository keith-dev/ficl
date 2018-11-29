.POSIX:

OS := $(shell uname)
OSVER := $(shell uname -r)
ARCH := $(shell uname -m)

TARGET += -DOS="$(OS)" -D$(OS)="$(OSVER)" -DARCH="$(ARCH)"

include defs.gnu.mk

ifdef FICL_WANT_MINIMAL
include ficl-minimal.mk
else
ifdef FICL_WANT_COMPATIBLE
include ficl-compatible.mk
else
include ficl-default.mk
endif
endif

include ficl.mk
