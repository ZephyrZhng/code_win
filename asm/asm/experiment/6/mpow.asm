	extrn	pow: far

sseg	segment	stack
sktop	db	100 dup (0)
sseg	ends

cseg	segment
	assume	cs: cseg, ss: sseg

start:	mov	ax, sseg
	mov	ss, ax
	mov	sp, size sktop
	
	mov	bl, 2
	mov	cx, 3
	call	pow

	mov	cl, 4

	push	ax
	shr	ah, cl
	cmp	ah, 9
	ja	big1
	add	ah, 30h
	jmp	print1
big1:	add	ah, 37h
print1:	mov	dl, ah
	mov	ah, 2
	int	21h

	pop	ax
	push	ax
	shl	ah, cl
	shr	ah, cl
	cmp	ah, 9
	ja	big2
	add	ah, 30h
	jmp	print2
big2:	add	ah, 37h
print2:	mov	dl, ah
	mov	ah, 2
	int	21h

	pop	ax
	push	ax
	shr	al, cl
	cmp	al, 9
	ja	big3
	add	al, 30h
	jmp	print3
big3:	add	al, 37h
print3:	mov	dl, al
	mov	ah, 2
	int	21h

	pop	ax
	push	ax
	shl	al, cl
	shr	al, cl
	cmp	al, 9
	ja	big4
	add	al, 30h
	jmp	print4
big4:	add	al, 37h
print4:	mov	dl, al
	mov	ah, 2
	int	21h
	
	pop	ax

stop:	mov	ah, 4ch
	int	21h

cseg	ends
	end	start