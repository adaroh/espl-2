section .text

global main
global fopenr
global freadr
global fcloser
global fopenw
global fwriter

extern main2
main:
	;push ebp
	;mov ebp,esp
;	mov	eax, 5
;	mov	ebx, [esp+8]
;	mov	ecx, 0
;	int	0x80	
	call	main2
        mov     ebx,eax
	mov	eax,1
	int 0x80

fopenr:
	mov	eax, 5
	mov	ebx, [esp+4]
	mov	ecx, [esp+8]
	mov	edx, [esp+12]
	int	0x80
	ret
freadr:
	mov	eax, 3
	mov	ebx, [esp+4]
	mov	ecx, [esp+8]
	mov	edx, [esp+12]
	int	0x80
	ret
fcloser:
	mov	eax, 6
	mov	ebx, [esp+4]
	int	0x80
	ret
fopenw:
	mov	eax, 5
	mov	ebx, [esp+4]
	mov	ecx, [esp+8]
	mov	edx, 666o
	int	0x80
	ret	
fwriter:
	mov	eax, 4
	mov	ebx, [esp+4]
	mov	ecx, [esp+8]
	mov	edx, [esp+12]
	int	0x80
	ret