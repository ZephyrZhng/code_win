	extrn	prime: far

dseg	segment
sum	dw	?
data	dw	100
dseg	ends

sseg	segment	stack
sktop	db	100 dup (0)
sseg	ends

cseg	segment
	assume	cs: cseg, ss: sseg

start:	mov	ax, sseg
	mov	ss, ax
	mov	sp, size sktop
	
	mov	ax, 3
	lea	si, sum
	lea	di, data
again:	push	ax
	call	prime
	pop	ax
	jc	no
	mov	[di], ax
	inc	di
	inc	di
	add	[si], ax
no:	inc	ax
	cmp	ax, 255
	ja	stop
	jmp	again

stop:	mov	ax, data
	mov	ah, 4ch
	int	21h

cseg	ends
	end	start