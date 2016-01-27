; 将di所指的单元开始，长度为2 * cx的一个多字节数据加上
; bx所指的单元开始，长度为cx的一个多字节数据
	public	madd
cseg	segment
	assume	cs: cseg
madd	proc	far

	push	di
	push	ax
	push	bx
	push	cx
	clc

again:	mov	al, [bx]
	adc	[di], al
	inc	di
	inc	bx
	loop	again
	jnc	return
	xor	al, al
	pop	cx
	push	cx
again2:	adc	[di], al
	inc	di
	loop	again2
return:	pop	cx
	pop	bx
	pop	ax
	pop	di

	ret
madd	endp
cseg	ends
	end