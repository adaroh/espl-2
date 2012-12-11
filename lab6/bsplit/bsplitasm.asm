section .text

global main
global fopenr
global freadr
global fcloser
global fopenw
global fwriter
global innerloop
extern strcat
main:

	mov	DWORD eax, [esp+8]	;eax = argv
	mov	eax, [eax+4]		;eax = argv[1]
	mov	[filename],eax		;[filename] = second argument from command line
	jmp	mainfunc
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
	mov	edx, [ebp+8]	;eax=*done
	mov	edx, [edx]	;eax=done
	cmp	edx, 0
	je	innerloopdone
	mov	edx, [flag]
	cmp	edx, 0
	je	innerloopdone
	mov	DWORD [sizeRead], 0	;sizeRead=0
	mov	ecx,[count]
	cmp	ecx, 0		;begining of file
	jne	readbytes
	push	DWORD 4		;size of xsum
	push	xsum		;xsum	
	push	DWORD [ebp+12]	;pfile
	call	fwriter
	add	esp,12
	mov	DWORD [count], 4
	mov	edx, [count]
readbytes:
	push	DWORD 4
	push	buffer 
	push	DWORD [ebp+16]
	call	freadr
	add	esp, 12
	mov	DWORD edx, [count]
	add	edx, eax
	mov	DWORD [count], edx
	mov	DWORD [sizeRead], eax
	cmp	eax, 0
	jle	innerloopdone
	mov	DWORD edx, [count]
	push	DWORD eax
	push	buffer
	push	DWORD [ebp+12]
	call	fwriter
	add	esp, 12
	mov	ecx, [count]
	cmp	ecx, 2048	; count>=2048
	jl	firstwhile
innerloopdone:
	mov	DWORD [flag],0
	push	DWORD [ebp+12]	;pfile
	call	fcloser
	add	esp, 4
	mov	ecx, [sizeRead]
	test	ecx,ecx
	je	filedone
	mov	eax, 1
	mov	esp,ebp
	pop	ebp
	ret
filedone:
	mov	ecx,[ebp+8]
	mov	DWORD [ecx],0
	mov	eax, 0
	mov	esp, ebp
	pop	ebp
	ret
	
mainfunc:
	mov	DWORD [sizeRead], 0
	mov	DWORD [count], 0
	mov	DWORD [fileindex], 1
	mov	DWORD [flag], 1
	push	DWORD 0
	push	DWORD [filename]
	call	fopenr		;open main file for reading
	add	esp, 8
	mov	[sfile], eax	;saves sfile number
	mov	DWORD [done], 1
mainloop:
	cmp	DWORD [done],1
	jne	mainends
	mov	BYTE [partname], 0
	push	DWORD [fileindex]
	push	DWORD [filename]
	push	DWORD partname
	call	merge		;create new pfile name
	add	esp, 12
	push	DWORD 577
	push	partname
	call	fopenw
	mov	[pfile], eax
	mov	DWORD [count], 0
	mov	DWORD [flag], 1
	push	DWORD [sfile]
	push	DWORD [pfile]
	push	DWORD done
	call	innerloop
	add	esp, 12
	mov	[done], eax
	mov	DWORD ebx, [fileindex]
	inc	DWORD ebx
	mov	[fileindex], ebx
	jmp	mainloop
mainends:
	push	DWORD [sfile]
	call	fcloser
	add	esp, 4
        mov     ebx,eax
	mov	eax,1
	int 0x80	

merge:
	mov	eax, [esp+4]
	mov	ebx, [esp+8]
	mov	ecx, [esp+12]
	;add part/
	push	DWORD part
	push	DWORD partname
	call	strcat
	add	esp, 8
	;add filename
	push	DWORD [filename]
	push	DWORD partname
	call	strcat
	add	esp, 8
	;add dot
	push	DWORD dot
	push	DWORD partname
	call	strcat
	add	esp, 8

	mov	eax, [fileindex]	; get file index
	
	xor	edx, edx
	mov	esi, 10
	idiv	esi
	mov	esi, edx
	add	esi, 48
	mov	[seconddigit], esi	; get second digit of index
	
	xor	edx, edx
	mov	esi, 10
	idiv	esi
	mov	esi, edx
	add	esi, 48
	mov	[firstdigit], esi	; get first digit of index
	
	;add index
	push	DWORD firstdigit
	push	DWORD partname
	call	strcat
	add	esp, 8
	push	DWORD seconddigit
	push	DWORD partname
	call	strcat
	add	esp, 8
	ret

section .data
buffer TIMES 4 DB 0
xsum DB 'aaaa'
flag DD 1
done DD 1
count DD 0
sizeRead DD 0
filename RESB 100
partname RESB 100
fileindex DD 1
sfile RESD 1
pfile RESD 1
part	DB	'part/',0
dot	DB	'.',0
firstdigit RESB	4
seconddigit RESB 4