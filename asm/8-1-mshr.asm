; 将si所指单元开始，长度为cx的一个多字节数据逻辑右移1位
; 数据高对高，低对低
	public	mshr
cseg	segment
	assume	cs: cseg
mshr	proc	far

	push	si
	push	cx
	add	si, cx
	dec	si
	clc
again:	rcr	byte ptr [si], 1
	dec	si
	loop	again
	pop	cx
	pop	si

	ret
mshr	endp
cseg	ends
	end