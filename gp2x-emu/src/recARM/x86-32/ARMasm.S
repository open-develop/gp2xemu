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
xorl %eax,%eax
movl 4(%esp),%ecx
andl $0x0f,%ecx
movl condFuncs(,%ecx,4),%edx
movl (CPU+CPSROFFSET),%ecx
jmpl *%edx
.endfunc



.func matchEQUAL
matchEQUAL:
andl $(1<<ZERO),%ecx
setnz %al
ret
.endfunc

.func matchNEQUAL
matchNEQUAL:
andl $(1<<ZERO),%ecx
setz %al
ret
.endfunc


.func matchUHS
matchUHS:
andl $(1<<CARRY),%ecx
setz %al
ret
.endfunc


.func matchUL
matchUL:
andl $(1<<CARRY),%ecx
setnz %al
ret
.endfunc


.func matchNEG
matchNEG:
andl $(1<<SIGN),%ecx
setnz %al
ret

.endfunc

.func matchPOS
matchPOS:
andl $(1<<SIGN),%ecx
setz %al
ret
.endfunc

.func matchOVERF
matchOVERF:
andl $(1<<OVERF),%ecx
setnz %al
ret
.endfunc

.func matchNOVERF
matchNOVERF:
andl $(1<<OVERF),%ecx
setz %al
ret
.endfunc

.func matchUH
matchUH:
movl %ecx,%edx
andl $(1<<CARRY),%ecx
setnz %al
andl $(1<<ZERO),%edx
setz %cl
andb %cl,%al
ret
.endfunc


.func matchULS
matchULS:
movl %ecx,%edx
andl $(1<<CARRY),%ecx
setz %al
andl $(1<<ZERO),%edx
setnz %cl
andb %cl,%al
ret
.endfunc

.func matchSGE
matchSGE:
movl %ecx,%edx
andl $(1<<SIGN),%ecx
setnz %al
xorl %ecx,%ecx
andl $(1<<OVERF),%edx
setnz %cl
andb %al,%cl
setz %al
ret
.endfunc


.func matchSL
matchSL:
test $(1<<SIGN),%ecx
setnz %al
test $(1<<OVERF),%ecx
setnz %cl
andb %cl,%al
ret
.endfunc


.func matchSG
matchSG:
test $(1<<ZERO),%ecx
setz %al
test $(1<<SIGN),%ecx
setnz %dl
test $(1<<OVERF),%ecx
setnz %dh
test %dl,%dh
sete %dl
andb %dl,%al
ret
.endfunc

.func matchSLE
matchSLE:
test $(1<<ZERO),%ecx
setnz %al
test $(1<<SIGN),%ecx
setnz %dl
test $(1<<OVERF),%ecx
setnz %dh
test %dl,%dh
setne %dl
andb %dl,%al
ret
.endfunc

.func matchALWAYS
matchALWAYS:
inc %eax
ret
.endfunc

.func matchNEVER
matchNEVER:
ret
.endfunc
