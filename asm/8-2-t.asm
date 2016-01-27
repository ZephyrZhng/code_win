	public	trans
cseg	segment
	assume	cs: cseg
trans	proc	far

	push	dx
	push	cx
	push	bx
	push	si
	xor	bh, bh
	xor	ax, ax
	mov	bl, [si]
	cmp	bl, '-'
	jne	again
	mov	dl, bl
	inc	si
again:	mov	bl, [si]
	cmp	bl, '$'
	je	next
	sub	bl, 30h
	mov	cx, ax
	shl	ax, 1
	shl	ax, 1
	add	ax, cx
	shl	ax, 1
	add	ax, bx
	inc	si
	jmp	again
next:	cmp	dl, '-'
	jnz	return
	neg	ax
return:	pop	si
	pop	bx
	pop	cx
	pop	dx

	ret
trans	endp
cseg	ends
	end