/*******************************************************************
** s o f t c o r e . c
** Forth Inspired Command Language - 
** Words from CORE set written in FICL
** Author: John Sadler (john_sadler@alum.mit.edu)
** Created: 27 December 1997
** Last update: Sat Aug  4 16:47:07 2001
*******************************************************************/
/*
** DO NOT EDIT THIS FILE -- it is generated by softwords/softcore.pl
** Make changes to the .fr files in ficl/softwords instead.
** This file contains definitions that are compiled into the
** system dictionary by the first virtual machine to be created.
** Created automagically by ficl/softwords/softcore.pl 
*/
/*
** Copyright (c) 1997-2001 John Sadler (john_sadler@alum.mit.edu)
** All rights reserved.
**
** Get the latest Ficl release at http://ficl.sourceforge.net
**
** I am interested in hearing from anyone who uses ficl. If you have
** a problem, a success story, a defect, an enhancement request, or
** if you would like to contribute to the ficl release, please send
** contact me by email at the address above.
**
** L I C E N S E  and  D I S C L A I M E R
** 
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
** 1. Redistributions of source code must retain the above copyright
**    notice, this list of conditions and the following disclaimer.
** 2. Redistributions in binary form must reproduce the above copyright
**    notice, this list of conditions and the following disclaimer in the
**    documentation and/or other materials provided with the distribution.
**
** THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
** ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
** DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
** OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
** HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
** LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
** OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
** SUCH DAMAGE.
*/


#include "ficl.h"

static char softWords[] = 
#if FICL_WANT_SOFTWORDS
/*
** ficl/softwords/softcore.fr
** FICL soft extensions
** John Sadler (john_sadler@alum.mit.edu)
** September, 1998
*/
/*
** Ficl USER variables
** See words.c for primitive def'n of USER
*/
    ".( loading ficl soft extensions ) cr "
#if FICL_WANT_USER
    "variable nUser  0 nUser ! "
    ": user "
    "nUser dup @ user 1 swap +! ; "
#endif
/*
** ficl extras
*/
    ": empty depth 0 ?do drop loop ; "
    ": cell-  [ 1 cells ] literal -  ; "
    ": -rot  2 -roll ; "
/*
** CORE 
*/
    ": abs "
    "dup 0< if negate endif ; "
    "decimal 32 constant bl "
    ": space     bl emit ; "
    ": spaces   0 ?do space loop ; "
    ": abort\" "
    "state @ if "
    "postpone if "
    "postpone .\" "
    "postpone cr "
    "-2 "
    "postpone literal "
    "postpone throw "
    "postpone endif "
    "else "
    "[char] \" parse "
    "rot if "
    "type "
    "cr "
    "-2 throw "
    "else "
    "2drop "
    "endif "
    "endif "
    "; immediate "
/*
** CORE EXT
*/
    ".( loading CORE EXT words ) cr "
    "0  constant false "
    "false invert constant true "
    ": <>   = 0= ; "
    ": 0<>  0= 0= ; "
    ": compile,  , ; "
    ": erase    0 fill ; "
    ": nip     swap drop ; "
    ": tuck  swap over ; "
    ": within   over - >r - r>  u<  ; "
/*
** LOCAL EXT word set
*/
#if FICL_WANT_LOCALS
    ": locals| "
    "begin "
    "bl word   count "
    "dup 0= abort\" where's the delimiter??\" "
    "over c@ "
    "[char] | - over 1- or "
    "while "
    "(local) "
    "repeat 2drop   0 0 (local) "
    "; immediate "
    ": local  bl word count (local) ;  immediate "
    ": 2local bl word count (2local) ; immediate "
    ": end-locals  0 0 (local) ;  immediate "
#endif
/*
** TOOLS word set...
*/
    ": ?  @ . ; "
    ": dump "
    "0 ?do "
    "dup c@ . 1+ "
    "i 7 and 7 = if cr endif "
    "loop drop "
    "; "
/*
** SEARCH+EXT words and ficl helpers
*/
    ".( loading SEARCH & SEARCH-EXT words ) cr "
    ": brand-wordlist   last-word >name drop wid-set-name ; "
    ": ficl-named-wordlist "
    "ficl-wordlist dup create , brand-wordlist does> @ ; "
    ": wordlist "
    "1 ficl-wordlist ; "
    ": ficl-set-current "
    "get-current swap set-current ; "
    ": do-vocabulary "
    "does>  @ search> drop >search ; "
    ": ficl-vocabulary "
    "ficl-named-wordlist do-vocabulary ; "
    ": vocabulary "
    "1 ficl-vocabulary ; "
    ": previous  search> drop ; "
    "1 ficl-named-wordlist hidden "
    ": hide     hidden dup >search ficl-set-current ; "
    ": also "
    "search> dup >search >search ; "
    ": forth "
    "search> drop "
    "forth-wordlist >search ; "
    ": only "
    "-1 set-order ; "
    "hide "
    ": list-wid "
    "dup wid-get-name "
    "?dup if "
    "type drop "
    "else "
    "drop .\" (unnamed wid) \" x. "
    "endif cr "
    "; "
    "set-current "
    ": order "
    ".\" Search:\" cr "
    "get-order  0 ?do 3 spaces list-wid loop cr "
    ".\" Compile: \" get-current list-wid cr "
    "; "
    ": debug  ' debug-xt ; "
    ": on-step   .\" S: \" .s cr ; "
    ": strdup "
    "0 locals| addr2 length c-addr | end-locals "
    "length 1 + allocate "
    "0= if "
    "to addr2 "
    "c-addr addr2 length move "
    "addr2 length 0 "
    "else "
    "0  -1 "
    "endif "
    "; "
    ": strcat "
    "0 locals|  b-length b-u b-addr a-u a-addr | end-locals "
    "b-u  to b-length "
    "b-addr a-addr a-u + b-length  move "
    "a-addr a-u b-length + "
    "; "
    ": strcpy "
    "locals| b-u b-addr a-u a-addr | end-locals "
    "a-addr 0  b-addr b-u  strcat "
    "; "
    "previous "
/*
** E N D   S O F T C O R E . F R
*/
#if FICL_WANT_LOCALS
/*
** ficl/softwords/jhlocal.fr
** stack comment style local syntax...
*/
    ".( loading Johns-Hopkins locals ) cr "
    "hide "
    "0 constant zero "
    ": ?-- "
    "2dup s\" --\" compare 0= ; "
    ": ?} "
    "2dup s\" }\"  compare 0= ; "
    ": ?| "
    "2dup s\" |\"  compare 0= ; "
    ": ?2loc "
    "over dup c@ [char] 2 = "
    "swap 1+  c@ [char] : = and "
    "if "
    "2 - swap char+ char+ swap "
    "true "
    "else "
    "false "
    "endif "
    "; "
    ": ?delim "
    "?|  if  2drop 1 exit endif "
    "?-- if  2drop 2 exit endif "
    "?}  if  2drop 3 exit endif "
    "dup 0= "
    "if  2drop 4 exit endif "
    "0 "
    "; "
    "set-current "
    ": { "
    "0 dup locals| locstate | "
    "begin "
    "parse-word "
    "?delim dup to locstate "
    "0= while "
    "rot 1+ "
    "repeat "
    "0 ?do "
    "?2loc if (2local) else (local) endif "
    "loop "
    "locstate 1 = if "
    "begin "
    "parse-word "
    "?delim dup to locstate "
    "0= while "
    "?2loc if "
    "postpone zero postpone zero  (2local) "
    "else "
    "postpone zero  (local) "
    "endif "
    "repeat "
    "endif "
    "0 0 (local) "
    "locstate 2 = if "
    "begin "
    "parse-word "
    "?delim dup to locstate "
    "0= while "
    "2drop "
    "repeat "
    "endif "
    "locstate 3 <> abort\" syntax error in { } local line\" "
    "; immediate compile-only "
    "previous "
#endif
/*
** ficl/softwords/marker.fr
** Ficl implementation of CORE EXT MARKER
*/
    ".( loading MARKER ) cr "
    ": marker "
    "create "
    "get-current , "
    "get-order dup , "
    "0 ?do , loop "
    "does> "
    "0 set-order "
    "dup body> >name drop "
    "here - allot "
    "dup @ "
    "dup set-current forget-wid "
    "cell+ dup @ swap "
    "over cells + swap "
    "0 ?do "
    "dup @ dup "
    ">search forget-wid "
    "cell- "
    "loop "
    "drop "
    "; "
/*
** 
** Prefix words for ficl
** submitted by Larry Hastings, larry@hastings.org
**
*/
    "variable save-current "
    ": start-prefixes   get-current save-current ! <prefixes> set-current ; "
    ": end-prefixes     save-current @ set-current ; "
    ": show-prefixes    <prefixes> >search  words  search> drop ; "
#if (FICL_EXTENDED_PREFIX)
    "start-prefixes "
    ": \" postpone s\" ; immediate "
    ": .(  .( ; "
/*
** add 0b, 0o, 0d, and 0x as prefixes 
** these temporarily shift the base to 2, 8, 10, and 16 respectively
** and consume the next number in the input stream, pushing/compiling
** as normal
*/
    ": 0b  2 __tempbase ; immediate "
    ": 0o  8 __tempbase ; immediate "
    "end-prefixes "
#endif
/*
** ficl/softwords/ifbrack.fr
** ANS conditional compile directives [if] [else] [then]
** Requires ficl 2.0 or greater...
*/
    "hide "
    ": ?[if] "
    "2dup s\" [if]\" compare-insensitive 0= "
    "; "
    ": ?[else] "
    "2dup s\" [else]\" compare-insensitive 0= "
    "; "
    ": ?[then] "
    "2dup s\" [then]\" compare-insensitive 0= >r "
    "2dup s\" [endif]\" compare-insensitive 0= r> "
    "or "
    "; "
    "set-current "
    ": [else] "
    "1 "
    "begin "
    "begin "
    "parse-word dup  while "
    "?[if] if "
    "2drop 1+ "
    "else "
    "?[else] if "
    "2drop 1- dup if 1+ endif "
    "else "
    "?[then] if 2drop 1- else 2drop endif "
    "endif "
    "endif ?dup 0=  if exit endif "
    "repeat  2drop "
    "refill 0= until "
    "drop "
    ";  immediate "
    ": [if] "
    "0= if postpone [else] then ;  immediate "
    ": [then]  ;  immediate "
    ": [endif]  ;  immediate "
    "previous "
#if FICL_WANT_OOP
/*
** ficl/softwords/oo.fr
** F I C L   O - O   E X T E N S I O N S
** john sadler aug 1998
*/
    ".( loading ficl O-O extensions ) cr "
    "17 ficl-vocabulary oop "
    "also oop definitions "
    "user current-class "
    "0 current-class ! "
/*
** L A T E   B I N D I N G
*/
    "hide "
    ": parse-method "
    "parse-word "
    "postpone sliteral "
    "; compile-only "
    ": lookup-method  { class 2:name -- class xt } "
    "name class cell+ @ "
    "search-wordlist "
    "0= if "
    "name type .\"  not found in \" "
    "class body> >name type "
    "cr abort "
    "endif "
    "class swap "
    "; "
    ": find-method-xt "
    "parse-word lookup-method "
    "; "
    "set-current "
    ": catch-method "
    "lookup-method catch "
    "; "
    ": exec-method "
    "lookup-method execute "
    "; "
    ": --> "
    "state @ 0= if "
    "find-method-xt execute "
    "else "
    "parse-method  postpone exec-method "
    "endif "
    "; immediate "
    ": c-> "
    "state @ 0= if "
    "find-method-xt catch "
    "else "
    "parse-method  postpone catch-method "
    "endif "
    "; immediate "
    ": method   create does> body> >name lookup-method execute ; "
/*
** E A R L Y   B I N D I N G
*/
    "1 ficl-named-wordlist instance-vars "
    "instance-vars dup >search ficl-set-current "
    ": => "
    "drop find-method-xt compile, drop "
    "; immediate compile-only "
    ": my=> "
    "current-class @ dup postpone => "
    "; immediate compile-only "
    ": my=[ "
    "current-class @ "
    "begin "
    "parse-word 2dup "
    "s\" ]\" compare while "
    "lookup-method  nip  dup "
    "compile,  >body cell+ @ "
    "repeat 2drop drop "
    "; immediate compile-only "
/*
** I N S T A N C E   V A R I A B L E S
*/
    ": do-instance-var "
    "does> "
    "nip @ + "
    "; "
    ": addr-units: "
    "create over , + "
    "do-instance-var "
    "; "
    ": chars: "
    "chars addr-units: ; "
    ": char: "
    "1 chars: ; "
    ": cells: "
    "cells >r aligned r> addr-units: "
    "; "
    ": cell: "
    "1 cells: ; "
    ": do-aggregate "
    "does> "
    "2@ "
    "2swap drop "
    "+ swap "
    "; "
    ": obj: "
    "locals| meta class offset | "
    "create  offset , class , "
    "class meta --> get-size  offset + "
    "do-aggregate "
    "; "
    ": array: "
    "locals| meta class nobjs offset | "
    "create offset , class , "
    "class meta --> get-size  nobjs * offset + "
    "do-aggregate "
    "; "
    ": ref: "
    "locals| meta class offset | "
    "create offset , class , "
    "offset cell+ "
    "does> "
    "2@ "
    "2swap drop + @ swap "
    "; "
#if FICL_WANT_VCALL
    ": vcall: "
    "current-class @ 8 + dup @ dup 1+ rot ! "
    "create , , "
    "does> "
    "nip 2@ vcall "
    "; "
    ": vcallr: 0x80000000 or vcall: ; "
#if FICL_WANT_FLOAT
    ": vcallf: "
    "0x80000000 or "
    "current-class @ 8 + dup @ dup 1+ rot ! "
    "create , , "
    "does> "
    "nip 2@ vcall f> "
    "; "
#endif /* FLOAT */
#endif /* VCALL */
    ": end-class "
    "swap ! set-current "
    "search> drop "
    "; "
    ": suspend-class   end-class ; "
    "set-current previous "
    ": do-do-instance "
    "s\" : .do-instance does> [ current-class @ ] literal ;\" "
    "evaluate "
    "; "
/*
** M E T A C L A S S 
*/
    ":noname "
    "wordlist "
    "create "
    "immediate "
    "0       , "
    "dup     , "
#if FICL_WANT_VCALL
    "4 cells , "
#else
    "3 cells , "
#endif
    "ficl-set-current "
    "does> dup "
    ";  execute metaclass "
    "metaclass drop cell+ @ brand-wordlist "
    "metaclass drop current-class ! "
    "do-do-instance "
    "instance-vars >search "
    "create .super "
    "0 cells , do-instance-var "
    "create .wid "
    "1 cells , do-instance-var "
#if FICL_WANT_VCALL
    "create .vtCount "
    "2 cells , do-instance-var "
    "create  .size "
    "3 cells , do-instance-var "
#else
    "create  .size "
    "2 cells , do-instance-var "
#endif
    ": get-size    metaclass => .size  @ ; "
    ": get-wid     metaclass => .wid   @ ; "
    ": get-super   metaclass => .super @ ; "
#if FICL_WANT_VCALL
    ": get-vtCount metaclass => .vtCount @ ; "
    ": get-vtAdd   metaclass => .vtCount ; "
#endif
    ": instance "
    "locals| meta parent | "
    "create "
    "here parent --> .do-instance "
    "parent meta metaclass => get-size "
    "allot "
    "; "
    ": array "
    "locals| meta parent nobj | "
    "create  nobj "
    "here parent --> .do-instance "
    "parent meta metaclass => get-size "
    "nobj *  allot "
    "; "
    ": new "
    "metaclass => instance --> init "
    "; "
    ": new-array "
    "metaclass => array "
    "--> array-init "
    "; "
    ": alloc "
    "locals| meta class | "
    "class meta metaclass => get-size allocate "
    "abort\" allocate failed \" "
    "class 2dup --> init "
    "; "
    ": alloc-array "
    "locals| meta class nobj | "
    "class meta metaclass => get-size "
    "nobj * allocate "
    "abort\" allocate failed \" "
    "nobj over class --> array-init "
    "class "
    "; "
    ": allot   { 2:this -- 2:instance } "
    "here "
    "this my=> get-size  allot "
    "this drop 2dup --> init "
    "; "
    ": allot-array   { nobj 2:this -- 2:instance } "
    "here "
    "this my=> get-size  nobj * allot "
    "this drop 2dup "
    "nobj -rot --> array-init "
    "; "
    ": ref "
    "drop create , , "
    "does> 2@ "
    "; "
    ": resume-class   { 2:this -- old-wid addr[size] size } "
    "this --> .wid @ ficl-set-current "
    "this --> .size dup @ "
    "instance-vars >search "
    "; "
    ": sub "
    "wordlist "
    "locals| wid meta parent | "
    "parent meta metaclass => get-wid "
    "wid wid-set-super "
    "create  immediate "
    "wid brand-wordlist "
    "here current-class ! "
    "parent , "
    "wid    , "
#if FICL_WANT_VCALL
    "parent meta --> get-vtCount , "
#endif
    "here parent meta --> get-size dup , "
    "metaclass => .do-instance "
    "wid ficl-set-current -rot "
    "do-do-instance "
    "instance-vars >search "
    "; "
    ": offset-of "
    "drop find-method-xt nip >body @ ; "
    ": id "
    "drop body> >name  ; "
    ": methods "
    "locals| meta class | "
    "begin "
    "class body> >name type .\"  methods:\" cr "
    "class meta --> get-wid >search words cr previous "
    "class meta metaclass => get-super "
    "dup to class "
    "0= until  cr "
    "; "
    ": pedigree "
    "locals| meta class | "
    "begin "
    "class body> >name type space "
    "class meta metaclass => get-super "
    "dup to class "
    "0= until  cr "
    "; "
    ": see "
    "metaclass => get-wid >search see previous ; "
    ": debug "
    "metaclass => get-wid >search debug previous ; "
    "previous set-current "
/*
** META is a nickname for the address of METACLASS...
*/
    "metaclass drop "
    "constant meta "
/*
** SUBCLASS is a nickname for a class's SUB method...
*/
    ": subclass   --> sub ; "
#if FICL_WANT_VCALL
    ": hasvtable 4 + ; immediate "
#endif
/*
** O B J E C T
*/
    ":noname "
    "wordlist "
    "create  immediate "
    "0       , "
    "dup     , "
    "0       , "
    "ficl-set-current "
    "does> meta "
    ";  execute object "
    "object drop cell+ @ brand-wordlist "
    "object drop current-class ! "
    "do-do-instance "
    "instance-vars >search "
    ": class "
    "nip meta ; "
    ": init "
    "meta "
    "metaclass => get-size "
    "erase ; "
    ": array-init "
    "0 dup locals| &init &next class inst | "
    "class s\" init\" lookup-method to &init "
    "s\" next\" lookup-method to &next "
    "drop "
    "0 ?do "
    "inst class 2dup "
    "&init execute "
    "&next execute  drop to inst "
    "loop "
    "; "
    ": free "
    "drop free "
    "abort\" free failed \" "
    "; "
    ": super "
    "meta  metaclass => get-super ; "
    ": pedigree "
    "object => class "
    "metaclass => pedigree ; "
    ": size "
    "object => class "
    "metaclass => get-size ; "
    ": methods "
    "object => class "
    "metaclass => methods ; "
    ": index "
    "locals| class inst | "
    "inst class "
    "object => class "
    "metaclass => get-size  * "
    "inst +  class ; "
    ": next "
    "locals| class inst | "
    "inst class "
    "object => class "
    "metaclass => get-size "
    "inst + "
    "class ; "
    ": prev "
    "locals| class inst | "
    "inst class "
    "object => class "
    "metaclass => get-size "
    "inst swap - "
    "class ; "
    ": debug "
    "find-method-xt debug-xt ; "
    "previous set-current "
    "only definitions "
#endif
#if (FICL_WANT_OOP)
/*
** ficl/softwords/classes.fr
** F I C L   2 . 0   C L A S S E S
*/
    ".( loading ficl utility classes ) cr "
    "also oop definitions "
    "object subclass c-ref "
    "cell: .class "
    "cell: .instance "
    ": get "
    "drop 2@ ; "
    ": set "
    "drop 2! ; "
    "end-class "
    "object subclass c-byte "
    "char: .payload "
    ": get  drop c@ ; "
    ": set  drop c! ; "
    "end-class "
    "object subclass c-2byte "
    "2 chars: .payload "
    ": get  drop w@ ; "
    ": set  drop w! ; "
    "end-class "
    "object subclass c-4byte "
    "4 chars: .payload "
    ": get  drop q@ ; "
    ": set  drop q! ; "
    "end-class "
    "object subclass c-cell "
    "cell: .payload "
    ": get  drop @ ; "
    ": set  drop ! ; "
    "end-class "
/*
** C - P T R 
*/
    "object subclass c-ptr "
    "c-cell obj: .addr "
    ": get-ptr "
    "c-ptr  => .addr "
    "c-cell => get "
    "; "
    ": set-ptr "
    "c-ptr  => .addr "
    "c-cell => set "
    "; "
    ": clr-ptr "
    "0 -rot  c-ptr => .addr  c-cell => set "
    "; "
    ": ?null "
    "c-ptr => get-ptr 0= "
    "; "
    ": inc-ptr "
    "2dup 2dup "
    "c-ptr => get-ptr  -rot "
    "--> @size  +  -rot "
    "c-ptr => set-ptr "
    "; "
    ": dec-ptr "
    "2dup 2dup "
    "c-ptr => get-ptr  -rot "
    "--> @size  -  -rot "
    "c-ptr => set-ptr "
    "; "
    ": index-ptr   { index 2:this -- } "
    "this --> get-ptr "
    "this --> @size  index *  + "
    "this --> set-ptr "
    "; "
    "end-class "
/*
** C - C E L L P T R 
*/
    "c-ptr subclass c-cellPtr "
    ": @size   2drop  1 cells ; "
    ": get "
    "c-ptr => get-ptr @ "
    "; "
    ": set "
    "c-ptr => get-ptr ! "
    "; "
    "end-class "
/*
** C - 4 B Y T E P T R
*/
    "c-ptr subclass c-4bytePtr "
    ": @size   2drop  4  ; "
    ": get "
    "c-ptr => get-ptr q@ "
    "; "
    ": set "
    "c-ptr => get-ptr q! "
    "; "
    "end-class "
/*
** C - 2 B Y T E P T R 
*/
    "c-ptr subclass c-2bytePtr "
    ": @size   2drop  2  ; "
    ": get "
    "c-ptr => get-ptr w@ "
    "; "
    ": set "
    "c-ptr => get-ptr w! "
    "; "
    "end-class "
/*
** C - B Y T E P T R 
*/
    "c-ptr subclass c-bytePtr "
    ": @size   2drop  1  ; "
    ": get "
    "c-ptr => get-ptr c@ "
    "; "
    ": set "
    "c-ptr => get-ptr c! "
    "; "
    "end-class "
    "previous definitions "
#endif
#if (FICL_WANT_OOP)
/*
** ficl/softwords/string.fr
*/
/*
** C - S T R I N G
*/
    ".( loading ficl string class ) cr "
    "also oop definitions "
    "object subclass c-string "
    "c-cell obj: .count "
    "c-cell obj: .buflen "
    "c-ptr  obj: .buf "
    "32 constant min-buf "
    ": get-count  my=[ .count  get ] ; "
    ": set-count  my=[ .count  set ] ; "
    ": ?empty  --> get-count 0= ; "
    ": get-buflen  my=[ .buflen  get ] ; "
    ": set-buflen  my=[ .buflen  set ] ; "
    ": get-buf     my=[ .buf get-ptr ] ; "
    ": set-buf   { ptr len 2:this -- } "
    "ptr this my=[ .buf set-ptr ] "
    "len this my=> set-buflen "
    "; "
    ": clr-buf "
    "0 0 2over  my=> set-buf "
    "0 -rot     my=> set-count "
    "; "
    ": free-buf   { 2:this -- } "
    "this my=> get-buf "
    "?dup if "
    "free "
    "abort\" c-string free failed\" "
    "this  my=> clr-buf "
    "endif "
    "; "
    ": size-buf  { size 2:this -- } "
    "size 0< abort\" need positive size for size-buf\" "
    "size 0= if "
    "this --> free-buf exit "
    "endif "
    "my=> min-buf size over / 1+ * chars to size "
    "this --> get-buflen  0= "
    "if "
    "size allocate "
    "abort\" out of memory\" "
    "size this --> set-buf "
    "size this --> set-buflen "
    "exit "
    "endif "
    "size this --> get-buflen > if "
    "this --> get-buf size resize "
    "abort\" out of memory\" "
    "size this --> set-buf "
    "endif "
    "; "
    ": set   { c-addr u 2:this -- } "
    "u this --> size-buf "
    "u this --> set-count "
    "c-addr this --> get-buf  u move "
    "; "
    ": get   { 2:this -- c-addr u } "
    "this --> get-buf "
    "this --> get-count "
    "; "
    ": cat   { c-addr u 2:this -- } "
    "this --> get-count u +  dup >r "
    "this --> size-buf "
    "c-addr  this --> get-buf this --> get-count +  u move "
    "r> this --> set-count "
    "; "
    ": type   { 2:this -- } "
    "this --> ?empty if .\" (empty) \" exit endif "
    "this --> .buf --> get-ptr "
    "this --> .count --> get "
    "type "
    "; "
    ": compare "
    "--> get "
    "2swap "
    "--> get "
    "2swap compare "
    "; "
    ": hashcode "
    "--> get  hash "
    "; "
    ": free  2dup --> free-buf  object => free ; "
    "end-class "
    "c-string subclass c-hashstring "
    "c-2byte obj: .hashcode "
    ": set-hashcode   { 2:this -- } "
    "this  --> super --> hashcode "
    "this  --> .hashcode --> set "
    "; "
    ": get-hashcode "
    "--> .hashcode --> get "
    "; "
    ": set "
    "2swap 2over --> super --> set "
    "--> set-hashcode "
    "; "
    ": cat "
    "2swap 2over --> super --> cat "
    "--> set-hashcode "
    "; "
    "end-class "
    "previous definitions "
#endif
#if FICL_WANT_FILE
/*
** 
** File Access words for ficl
** submitted by Larry Hastings, larry@hastings.org
**
*/
    ": r/o 1 ; "
    ": r/w 3 ; "
    ": w/o 2 ; "
    ": bin 8 or ; "
    ": included "
    "r/o bin open-file 0= if "
    "locals| f | end-locals "
    "f include-file "
    "f close-file drop "
    "else "
    "drop "
    "endif "
    "; "
    ": include parse-word included ; immediate "
#endif
#endif /* WANT_SOFTWORDS */
    "quit ";


void ficlCompileSoftCore(FICL_SYSTEM *pSys)
{
    FICL_VM *pVM = pSys->vmList;
    CELL id = pVM->sourceID;
    int ret = sizeof (softWords);
    assert(pVM);
    pVM->sourceID.i = -1;
    ret = ficlExec(pVM, softWords);
    pVM->sourceID = id;
    if (ret == VM_ERREXIT)
        assert(FALSE);
    return;
}


