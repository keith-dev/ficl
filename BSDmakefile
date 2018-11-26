.POSIX:

OS := $(shell uname)
OSVER := $(shell uname -r)
ARCH := $(shell uname -m)

TARGET += -DOS="$(OS)" -D$(OS)="$(OSVER)" -DARCH="$(ARCH)"

.include "defs.bsd.mk"
.include "ficl.mk"
