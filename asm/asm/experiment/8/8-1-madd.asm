	public	madd
cseg	segment
	assume	cs: cseg
madd	proc	far

	push	di
	push	ax
	push	cx
	push	bx

again:	mov	al, [bx]
	adc	[di], al
	inc	di
	inc	si
	loop	again
	jnc	return
	xor	al, al
	pop	cx
	push	cx
again2:	adc	[di], al
	inc	di
	loop	again2
return:	pop	bx
	pop	cx
	pop	ax
	pop	di

	ret
madd	endp
cseg	ends
	end