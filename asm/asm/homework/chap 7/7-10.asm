dseg		segment
data	dw	2,5,9,8,7,4,2,5,3,1,1,5,4,2,5,4,2,4,5,5,2,3,2,5,3
count	db	25
numb	db	?
datam	dw	?
d	dw	25 dup (?)
n	db	25 dup (0)
c	db	0
dseg	ends

cseg	segment
	assume	cs: cseg, ds: dseg

start:	mov	ax, dseg
	mov	ds, ax
	mov	es, ax
	lea	bp, data
	mov	bx, word ptr count

again:	lea	di, d
	mov	cx, word ptr c
	mov	ax, [bp]
	cld
	repne	scasw
	jne	append
	dec	di
	dec	di
	jmp	next

append:	mov	[di], ax
	inc	c

next:	sub	di, offset d
	shr	di, 1
	inc	n[di]
	inc	bp
	inc	bp
	and	bx, bx
	jnz	again

	xor	al, al
	mov	cx, word ptr c
	lea	si, n

again2:	cmp	al, [si]
	jb	update
	jmp	next2

update:	mov	al, [si]
	mov	di, si
	shl	di, 1
	mov	bx, d[di]

next2:	inc	si
	loop	again2

	mov	numb, al
	mov	datam, bx
	mov	ah, 4ch
	int	21h

cseg	ends
	end	start