section .text

global main
global fopenr
global freadr
global fcloser
global fopenw
global fwriter
global innerloop

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
	
	
innerloop:
	push	ebp
	mov	ebp, esp
	mov	DWORD [count], 0
	mov	DWORD [flag], 1
firstwhile:
	mov	ecx, [ebp+8]	;eax=*done
	mov	ecx, [ecx]	;eax=done
	test	ecx,ecx		;done==0?
	je	innerloopdone
	mov	ecx, [flag]
	test	ecx,ecx		;flag==0?
	je	innerloopdone
	mov	DWORD [sizeRead], 0	;sizeRead=0
	mov	ecx,count
	mov	ecx,[ecx]	;;;;;;;;;;;;
	test	ecx,ecx
	je	writeXsum
afterXsum:
	push	DWORD 4
	push	buffer 
	push	DWORD [ebp+16]
	call	freadr
	add	esp, 12
	mov	ecx, count
	mov	ebx, [ecx]	;;;;;;;;
	add	ebx, eax	; count+=sizeRead
	mov	[count], ebx
	test	eax,eax
	mov	ecx, sizeRead
	mov	ebx, [ecx]	;;;;;;;;;;;;;
	mov	[ecx], eax
	jle	innerloopdone
	push	DWORD eax
	push	buffer
	push	DWORD [ebp+12]
	call	fwriter
	add	esp, 12
	mov	ecx, count
	mov	ecx, [ecx]
	cmp	ecx, 4096	; count>=2048
	jl	firstwhile
innerloopdone:
	mov	DWORD [flag],0
	push	DWORD [ebp+12]	;pfile
	call	fcloser
	add	esp, 4
	mov	ecx, [sizeRead]
	test	ecx,ecx
	je	filedone
	mov	esp,ebp
	ret
writeXsum:
	push	DWORD 4		;size of xsum
	push	xsum		;xsum	
	push	DWORD [ebp+12]	;pfile

	call	fwriter
	add	esp,12			; check later
	mov	ecx, count
	mov	ebx, [ecx]
	add	DWORD [ecx], 4
	mov	ebx, [ecx]
	jmp	afterXsum
filedone:
	mov	ecx,[ebp+8]
	mov	DWORD [ecx],0
	mov	esp, ebp
	ret
	
	
	
	
	
	
section .data
buffer TIMES 4 DB 0
xsum DB 'aaaa'
flag DW 1
count DW 0
sizeRead DW 0