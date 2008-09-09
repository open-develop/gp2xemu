.include "ARMasm.h"


.section .rodata
.align 4
condFuncs:
	.long matchEQUAL,matchNEQUAL,matchUHS,matchUL,matchNEG,matchPOS,matchOVERF,matchNOVERF,matchUH
	.long matchULS,matchSGE,matchSL,matchSG,matchSLE,matchALWAYS,matchNEVER

.section .text

.align 4
.func matchCondition
matchCondition:
.endfunc



.func matchEQUAL
matchEQUAL:
.endfunc

.func matchNEQUAL
matchNEQUAL:
.endfunc


.func matchUHS
matchUHS:
.endfunc


.func matchUL
matchUL:
.endfunc


.func matchNEG
matchNEG:
.endfunc

.func matchPOS
matchPOS:
.endfunc

.func matchOVERF
matchOVERF:
.endfunc

.func matchNOVERF
matchNOVERF:
.endfunc

.func matchUH
matchUH:
.endfunc


.func matchULS
matchULS:
.endfunc


.func matchSGE
matchSGE:
.endfunc


.func matchSL
matchSL:
.endfunc


.func matchSG
matchSG:
.endfunc

.func matchSLE
matchSLE:
.endfunc

.func matchALWAYS
matchALWAYS:
.endfunc

.func matchNEVER
matchNEVER:
.endfunc
