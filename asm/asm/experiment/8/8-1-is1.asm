	public	is1
cseg	segment
	assume	cs: cseg
is1	proc	far

	push	si
	push	cx
	push	ax
	pushf

	mov	al, [si]
	cmp	al, 1
	jne	no
	inc	si
again:	mov	ah, [si]
	and	ah, ah
	jnz	no
	inc	si
	loop	again
	popf
	stc
	jmp	return
no:	popf
	clc
return:	pop	ax
	pop	cx
	pop	si

	ret
is1	endp
cseg	ends
	end