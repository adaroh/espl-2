section .text
	global cmpstr
cmpstr:
	push	ebp
	mov	ebp, esp
	sub	esp, 4
	mov	DWORD [ebp-4], 0
	mov	DWORD [ebp-8], 0
	jmp	.L2
.L3:
	mov	eax, DWORD [ebp-4]
	mov ebx, eax
	sal eax, 3
	sal ebx, 1
	add eax, ebx
	mov	ebx, DWORD [ebp+8]
	movzx	ebx, BYTE [ebx]
	movsx	ebx, bl
	add	eax, ebx
;	sub	eax, 48
	mov	DWORD [ebp-4], eax
	add	DWORD [ebp+8], 1
.L2:
	mov	eax, DWORD [ebp+8]
	movzx	eax, BYTE [eax]
	test	al, al
	jne	.L3
	je	.L5
.L4:
	mov	eax, DWORD [ebp-8]
	mov ebx, eax
	sal eax, 3
	sal ebx, 1
	add eax, ebx
	mov	ebx, DWORD [ebp+12]
	movzx	ebx, BYTE [ebx]
	movsx	ebx, bl
	add	eax, ebx
;	sub	eax, 48
	mov	DWORD [ebp-8], eax
	add	DWORD [ebp+12], 1
.L5:
	mov	eax, DWORD [ebp+12]
	movzx	eax, BYTE [eax]
	test	al, al
	jne	.L4
.end:
	mov	ecx, [ebp-8]
	cmp	ecx, [ebp-4]
	je	.equal
	jg	.larger
.smaller:
	mov	eax, 1
	mov esp, ebp
	pop ebp
	ret
.equal:
	mov	eax, 0
	mov esp, ebp
	pop ebp
	ret
.larger:
	mov	eax, 2
	mov esp, ebp
	pop ebp
	ret