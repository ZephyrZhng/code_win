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