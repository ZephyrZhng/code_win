dseg	segment
list	dw	9435h, 6248h, 4734h, 8965h, 7227h, 8727h, 2846h, 5638h, 4932h
lent	db	10
dseg	ends

sseg	segment	stack
sktop	db	50 dup (0)
sseg	ends

cseg	segment
	assume	cs: cseg, ss: sseg, ds: dseg

start:	mov	ax, sseg
	mov	ss, ax
	mov	sp, size sktop
	mov	ax, dseg
	mov	ds, ax

	lea	si, list
	xor	ch, ch
again1:	mov	ax, [si + 2]
	cmp	[si], ax
	jbe	next1
	mov	cl, ch
	mov	di, si
again2:	mov	bx, [di]
	mov	[di + 2], bx
	dec	di
	dec	di
	dec	cl
	jns	next2
	jmp	next3
next2:	cmp	[di], ax
	ja	again2
next3:	mov	[di + 2], ax
next1:	inc	si
	inc	si
	inc	ch
	cmp	ch, lent	
	jb	again1

	mov	ah, 4ch
	int	21h
cseg	ends
	end 	start