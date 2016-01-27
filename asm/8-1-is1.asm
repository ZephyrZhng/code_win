; 判断si所指单元开始，长度为cx的一个多字节数据是否=1
; 数据高对高，低对低
; cf = 1: 数据为1，cf = 0: 数据不为1
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
	dec	cx
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