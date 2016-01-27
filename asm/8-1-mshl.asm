; 将si所指单元开始，长度为cx的一个多字节数据逻辑左移1位
; 数据高对高，低对低
	public	mshl
cseg	segment
	assume	cs: cseg
mshl	proc	far

	push	bx
	push	cx
	clc
again:	rcl	byte ptr [bx], 1
	loop	again
	pop	cx
	pop	bx

	ret
mshl	endp
cseg	ends
	end