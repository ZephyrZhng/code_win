	public	print
cseg	segment
	assume	cs: cseg
print	proc	far

	push	ax
	push	bx
	push	cx
	push	dx
	push	si
	pushf

	xor	ch, ch
	xor	si, si
	mov	bl, 10
	and	ax, ax
	jns	again
	neg	ax
	push	ax
	mov	ah, 02h
	mov	dl, '-'
	int	21h
	pop	ax
again:	inc	si
	div	bl
	mov	cl, ah
	push	cx
	xor	ah, ah
	and	al, al
	jnz	again
again2:	pop	dx
	add	dl, 30h
	mov	ah, 02h
	int	21h
	dec	si
	jnz	again2

	popf
	pop	si
	pop	dx
	pop	cx
	pop	bx
	pop	ax

	ret
print	endp
cseg	ends
	end