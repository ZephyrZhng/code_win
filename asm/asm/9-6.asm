dseg	segment
table	db	2, 4, 6, 8, 10, 12, 14, 16
len	dw	8
elem	db	7
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

	mov	al, elem
	lea	si, table
	mov	cx, len
again1:	cmp	[si], al
	ja	next
	je	stop
	inc	si
	loop	again1
next:	dec	si
	lea	di, table
	add	di, len
again2:	dec	di
	cmp	di, si
	je	insrt
	mov	bx, [di]
	mov	[di + 2], bx
	jmp	again2
insrt:	mov	[di + 2], al

stop:	mov	ah, 4ch
	int	21h
cseg	ends
	end 	start