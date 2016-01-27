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