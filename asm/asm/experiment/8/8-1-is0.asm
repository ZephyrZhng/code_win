	public	is0
cseg	segment
	assume	cs: cseg
is0	proc	far

	push	si
	push	ax
	push	cx
	pushf

again:	mov	al, [si]
	and	al, al
	jnz	no
	inc	si
	loop	again
	popf
	stc
	jmp	return
no:	popf
	clc
return:	pop	cx
	pop	ax
	pop	si

	ret
is0	endp
cseg	ends
	end