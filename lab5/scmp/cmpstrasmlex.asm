section .text
	global cmpstr
cmpstr:
	push	ebp
	mov	ebp, esp
.repeat:
	mov	ebx, DWORD [ebp+8]
	movzx	ebx, BYTE [ebx]
	mov	ecx, DWORD [ebp+12]
	movzx	ecx, BYTE [ecx]
	cmp	ebx, 0
	je	.eqzero
	cmp	ebx, ecx
	jg	.greater
	jl	.smaller
	add	DWORD [ebp+8], 1
	add	DWORD [ebp+12], 1
	jmp	.repeat
.eqzero:
	cmp	ecx, 0
	jne	.smaller
	mov	eax, 0
	jmp	.end
.greater:
	mov	eax, 1
	jmp	.end
.smaller:
	mov	eax, 2
	jmp	.end
.end:
	mov	esp, ebp
	pop	ebp
	ret