		public	maxmin
cseg		segment
		assume	cs: cseg

maxmin		proc	far
		push	cx
		mov	ah, [si]
		mov	al, [si]
		inc	si
		dec	cl
again:		cmp	ah, [si]
		jae	next1
		mov	ah, [si]
next1:		cmp	al, [si]
		jbe	next2
		mov	al, [si]
next2:		inc	si
		dec	cl
		and	cl, cl
		jnz	again
		pop	cx
		ret
maxmin		endp
cseg		ends
		end