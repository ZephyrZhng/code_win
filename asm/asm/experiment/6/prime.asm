; 数存在ax
; 是素数：cf = 0，否则：cf = 1

	public	prime
cseg	segment
	assume	cs: cseg

prime	proc	far
	push	cx
	push	bx
	mov	cx, ax
	dec	cx
	dec	cx
	mov	bl, 2
again:	push	ax
	div	bl
	and	ah, ah
	pop	ax
	jz	no
	inc	bl
	loop	again
	jmp	yes
no:	stc
	jmp	return
yes:	clc
return:	pop	bx
	pop	cx
	ret
prime	endp
cseg	ends
	end