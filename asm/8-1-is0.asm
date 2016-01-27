; 判断si所指单元开始，长度为cx的一个多字节数据是否=0
; 数据高对高，低对低
; cf = 1: 数据为0，cf = 0: 数据不为0
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