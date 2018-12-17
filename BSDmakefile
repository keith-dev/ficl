.POSIX:

OS := $(shell uname)
OSVER := $(shell uname -r)
ARCH := $(shell uname -m)
CLFAGS =

TARGET += -DOS="$(OS)" -D$(OS)="$(OSVER)" -DARCH="$(ARCH)"

.include "defs.bsd.mk"

.ifdef FICL_WANT_MINIMAL
.include "ficl-minimal.mk"
.else
.ifdef FICL_WANT_COMPATIBILITY
.include "ficl-compatibility.mk"
.else
.include "ficl-default.mk"
.endif
.endif

.include "ficl.mk"
