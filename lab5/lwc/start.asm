section .text
	
global _start
global read
global write
global open
global close
global strlen

extern main
_start:
	call	main
        mov     ebx,eax
	mov	eax,1
	int 0x80

read:
write:
open:
	mov	eax, 5
	mov	ebx, [esp+4]
	mov	ecx, [esp+8]
	mov	edx, [esp+12]
	int	0x80
	ret
close:
strlen:
	ret
