# FICL_WANT_MINIMAL
# If set to nonzero, build the smallest possible Ficl interpreter.
ifdef FICL_WANT_MINIMAL
CFLAGS += -DFICL_WANT_MINIMAL=$(FICL_WANT_MINIMAL)
endif

# FICL_WANT_COMPATIBILITY 
# Changes Ficl 4 at compile-time so it is source-compatible
# with the Ficl 3 API.  If you are a new user to Ficl you
# don't need to worry about this setting; if you are upgrading
# from a pre-4.0 version of Ficl, see doc/upgrading.html for
# more information.
ifdef FICL_WANT_COMPATIBILITY
CFLAGS += -DFICL_WANT_COMPATIBILITY=$(FICL_WANT_COMPATIBILITY)
endif

# FICL_WANT_PLATFORM
# Includes words defined in ficlCompilePlatform
# (see ficlplatform/win32.c and ficlplatform/unix.c for example)
ifdef FICL_WANT_PLATFORM
CFLAGS += -DFICL_WANT_PLATFORM=$(FICL_WANT_PLATFORM)
endif

# FICL_WANT_LZ_SOFTCORE
# If nonzero, the softcore words are stored compressed
# with patent-unencumbered Lempel-Ziv '77 compression.
# This results in a smaller Ficl interpreter, and adds
# only a *tiny* runtime speed hit.
#
# As of version 4.0.27, all the runtime code for the decompressor
# is 688 bytes on a single-threaded release build, but saves 14179
# bytes of data.  That's a net savings of over 13k!  Plus, it makes
# the resulting executable harder to hack :)
#
# On my 850MHz Duron machine, decompression took 0.00384 seconds
# if QueryPerformanceCounter() can be believed... it claims that it
# took 13765 cycles to complete, and that my machine runs 3579545
# cycles/second.
ifdef FICL_WANT_LZ_SOFTCORE
CFLAGS += -DFICL_WANT_LZ_SOFTCORE=$(FICL_WANT_LZ_SOFTCORE)
endif

# FICL_WANT_FILE
# Includes the FILE and FILE-EXT wordset and associated code.
# Turn this off if you do not have a file system!
# Contributed by Larry Hastings
ifdef FICL_WANT_FILE
CFLAGS += -DFICL_WANT_FILE=$(FICL_WANT_FILE)
endif

# FICL_WANT_FLOAT
# Includes a floating point stack for the VM, and words to do float operations.
# Contributed by Guy Carver 
ifdef FICL_WANT_FLOAT
CFLAGS += -DFICL_WANT_FLOAT=$(FICL_WANT_FLOAT)
endif

# FICL_WANT_DEBUGGER
# Inludes a simple source level debugger
ifdef FICL_WANT_DEBUGGER
CFLAGS += -DFICL_WANT_DEBUGGER=$(FICL_WANT_DEBUGGER)
endif

# FICL_EXTENDED_PREFIX
# Enables a bunch of extra prefixes in prefix.c
# and prefix.fr (if included as part of softcore.c)
ifdef FICL_EXTENDED_PREFIX
CFLAGS += -DFICL_EXTENDED_PREFIX=$(FICL_EXTENDED_PREFIX)
endif

# FICL_WANT_USER
# Enables user variables: per-instance variables bound to the VM.
# Kind of like thread-local storage. Could be implemented in a
# VM private dictionary, but I've chosen the lower overhead
# approach of an array of CELLs instead.
ifdef FICL_WANT_USER
CFLAGS += -DFICL_WANT_USER=$(FICL_WANT_USER)
endif

# FICL_WANT_LOCALS
# Controls the creation of the LOCALS wordset
# and a private dictionary for local variable compilation.
ifdef FICL_WANT_LOCALS
CFLAGS += -DFICL_WANT_LOCALS=$(FICL_WANT_LOCALS)
endif

# FICL_WANT_OOP
# Inludes object oriented programming support (in softwords)
# OOP support requires locals and user variables!
ifdef FICL_WANT_OOP
CFLAGS += -DFICL_WANT_OOP=$(FICL_WANT_OOP)
endif

# FICL_WANT_SOFTWORDS
# Controls inclusion of all softwords in softcore.c.
ifdef FICL_WANT_SOFTWORDS
CFLAGS += -DFICL_WANT_SOFTWORDS=$(FICL_WANT_SOFTWORDS)
endif

# FICL_WANT_MULTITHREADED
# Enables dictionary mutual exclusion wia the
# ficlLockDictionary() system dependent function.
#
# Note: this implementation is experimental and poorly
# tested. Further, it's unnecessary unless you really
# intend to have multiple SESSIONS (poor choice of name
# on my part) - that is, threads that modify the dictionary
# at the same time.
ifdef FICL_MULTITHREAD
CFLAGS += -DFICL_MULTITHREAD=$(FICL_MULTITHREAD)
endif

# FICL_WANT_OPTIMIZE
# Do you want to optimize for size, or for speed?
# Note that this doesn't affect Ficl very much one way
# or the other at the moment.
# Contributed by Larry Hastings 
ifdef FICL_WANT_OPTIMIZE
CFLAGS += -DFICL_WANT_OPTIMIZE=$(FICL_WANT_OPTIMIZE)
endif

# FICL_WANT_VCALL
# Ficl OO support for calling vtable methods.  Win32 only.
# Contributed by Guy Carver
ifdef FICL_WANT_VCALL
CFLAGS += -DFICL_WANT_VCALL=$(FICL_WANT_VCALL)
endif

# FICL_PLATFORM_ARCHITECTURE
# String constant describing the current hardware architecture.
ifdef FICL_PLATFORM_ARCHITECTURE
CFLAGS += -DFICL_PLATFORM_ARCHITECTURE=$(FICL_PLATFORM_ARCHITECTURE)
endif

# FICL_PLATFORM_OS
# String constant describing the current hardware architecture.
ifdef FICL_PLATFORM_OS
CFLAGS += -DFICL_PLATFORM_OS=$(FICL_PLATFORM_OS)
endif

# FICL_PLATFORM_HAS_2INTEGER
# Indicates whether or not the current architecture
# supports a native double-width integer type.
# If you set this to 1 in your ficlplatform/ *.h file,
# you *must* create typedefs for the following two types:
#        ficl2Unsigned
#        ficl2Integer 
# If this is set to 0, Ficl will implement double-width
# integer math in C, which is both bigger *and* slower
# (the double whammy!).  Make sure your compiler really
# genuinely doesn't support native double-width integers
# before setting this to 0.
ifdef FICL_PLATFORM_HAS_2INTEGER
CFLAGS += -DFICL_PLATFORM_HAS_2INTEGER=$(FICL_PLATFORM_HAS_2INTEGER)
endif

# FICL_PLATFORM_HAS_FTRUNCATE
# Indicates whether or not the current platform provides
# the ftruncate() function (available on most UNIXes).
# This function is necessary to provide the complete
# File-Access wordset.
#
# If your platform does not have ftruncate() per se,
# but does have some method of truncating files, you
# should be able to implement ftruncate() yourself and
# set this constant to 1.  For an example of this see
# "ficlplatform/win32.c".
ifdef FICL_PLATFORM_HAS_FTRUNCATE
CFLAGS += -DFICL_PLATFORM_HAS_FTRUNCATE=$(FICL_PLATFORM_HAS_FTRUNCATE)
endif

# FICL_PLATFORM_INLINE
# Must be defined, should be a function prototype type-modifying
# keyword that makes a function "inline".  Ficl does not assume
# that the local platform supports inline functions; it therefore
# only uses "inline" where "static" would also work, and uses "static"
# in the absence of another keyword.
ifdef FICL_PLATFORM_INLINE
CFLAGS += -DFICL_PLATFORM_INLINE=$(FICL_PLATFORM_INLINE)
endif

# FICL_PLATFORM_EXTERN
# Must be defined, should be a keyword used to declare
# a function prototype as being a genuine prototype.
# You should only have to fiddle with this setting if
# you're not using an ANSI-compliant compiler, in which
# case, good luck!
ifdef FICL_PLATFORM_EXTERN
CFLAGS += -DFICL_PLATFORM_EXTERN=$(FICL_PLATFORM_EXTERN)
endif

# FICL_ROBUST enables bounds checking of stacks and the dictionary.
# This will detect stack over and underflows and dictionary overflows.
# Any exceptional condition will result in an assertion failure.
# (As generated by the ANSI assert macro)
# FICL_ROBUST == 1 --> stack checking in the outer interpreter
# FICL_ROBUST == 2 also enables checking in many primitives
ifdef FICL_ROBUST
CFLAGS += -DFICL_ROBUST=$(FICL_ROBUST)
endif

# FICL_DEFAULT_STACK_SIZE Specifies the default size (in CELLs) of
# a new virtual machine's stacks, unless overridden at
# create time.
ifdef FICL_DEFAULT_STACK_SIZE
CFLAGS += -DFICL_DEFAULT_STACK_SIZE=$(FICL_DEFAULT_STACK_SIZE)
endif

# FICL_DEFAULT_DICTIONARY_SIZE specifies the number of ficlCells to allocate
# for the system dictionary by default. The value
# can be overridden at startup time as well.
ifdef FICL_DEFAULT_DICTIONARY_SIZE
CFLAGS += -DFICL_DEFAULT_DICTIONARY_SIZE=$(FICL_DEFAULT_DICTIONARY_SIZE)
endif

# FICL_DEFAULT_ENVIRONMENT_SIZE specifies the number of cells
# to allot for the environment-query dictionary.
ifdef FICL_DEFAULT_ENVIRONMENT_SIZE
CFLAGS += -DFICL_DEFAULT_ENVIRONMENT_SIZE=$(FICL_DEFAULT_ENVIRONMENT_SIZE)
endif

# FICL_MAX_WORDLISTS specifies the maximum number of wordlists in
# the dictionary search order. See Forth DPANS sec 16.3.3
# (file://dpans16.htm#16.3.3)
ifdef FICL_MAX_WORDLISTS
CFLAGS += -DFICL_MAX_WORDLISTS=$(FICL_MAX_WORDLISTS)
endif

# FICL_MAX_PARSE_STEPS controls the size of an array in the FICL_SYSTEM structure
# that stores pointers to parser extension functions. I would never expect to have
# more than 8 of these, so that's the default limit. Too many of these functions
# will probably exact a nasty performance penalty.
ifdef FICL_MAX_PARSE_STEPS
CFLAGS += -DFICL_MAX_PARSE_STEPS=$(FICL_MAX_PARSE_STEPS)
endif

# Maximum number of local variables per definition.
# This only affects the size of the locals dictionary,
# and there's only one per entire ficlSystem, so it
# doesn't make sense to be a piker here.
ifdef FICL_WANT_LOCALS
ifdef FICL_MAX_LOCALS
CFLAGS += -DFICL_MAX_LOCALS=$(FICL_MAX_LOCALS)
endif
endif

# The pad is a small scratch area for text manipulation. ANS Forth
# requires it to hold at least 84 characters.
ifdef FICL_PAD_SIZE
CFLAGS += -DFICL_PAD_SIZE=$(FICL_PAD_SIZE)
endif

# ANS Forth requires that a word's name contain {1..31} characters.
ifdef FICL_NAME_LENGTH
CFLAGS += -DFICL_NAME_LENGTH=$(FICL_NAME_LENGTH)
endif

# Default size of hash table. For most uniform
# performance, use a prime number!
ifdef FICL_HASH_SIZE
CFLAGS += -DFICL_HASH_SIZE=$(FICL_HASH_SIZE)
endif

# Default number of USER flags.
ifdef FICL_WANT_USER
ifdef FICL_USER_CELLS
CFLAGS += -DFICL_USER_CELLS=$(FICL_USER_CELLS)
endif
endif

# FICL_WANT_LIBEDIT
# User libedit for command-line editing.
#    LIBEDIT_PATH_INC custom path to editline's readline.h
#    LIBEDIT_PATH_LIB custom path to libedline.so
ifdef FICL_WANT_LIBEDIT
LIBEDIT_PATH_INC ?= /usr/local/include/edit/readline
LIBEDIT_PATH_LIB ?= /usr/lib
LDADD += -L$(LIBEDIT_PATH_LIB) -ledit
CFLAGS += -I$(LIBEDIT_PATH_INC) -DFICL_WANT_LIBEDIT=$(FICL_WANT_LIBEDIT)
endif
