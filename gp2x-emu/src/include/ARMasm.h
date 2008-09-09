.globl matchCondition
.extern CPU

.equ 	SHIFT,	(28)
.equ 	SIGN,	(31)
.equ	ZERO,	(30)
.equ	CARRY,	(29)
.equ	OVERF,	(28)
.equ	QFLAG,	(27)

.equ  CPSROFFSET, 80

.type CPU,		@object
.type condFuncs,	@object
.type matchCondition,	@function
.type matchEQUAL,	@function
.type matchNEQUAL,	@function
.type matchUHS,		@function
.type matchUL,		@function
.type matchNEG,		@function
.type matchPOS,		@function
.type matchOVERF,	@function
.type matchNOVERF,	@function
.type matchUH,		@function
.type matchULS,		@function
.type matchSGE,		@function
.type matchSL,		@function
.type matchSLE,		@function
.type matchALWAYS,	@function
.type matchNEVER,	@function
