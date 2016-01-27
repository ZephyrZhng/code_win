; Êä³ö¾Å¾Å±í

sseg	segment	stack
sktop	db	50 dup (0)
sseg	ends

cseg	segment
	assume	cs: cseg, ss: sseg
start:	mov	ax, sseg
	mov	ss, ax
	mov	sp, size sktop

	mov	ch, 1
	mov	dh, 10
again:	mov	cl, 1
again2:	mov	dl, ch
	add	dl, 30h
	mov	ah, 02h
	int	21h
	mov	dl, '*'
	mov	ah, 02h
	int	21h
	mov	dl, cl
	add	dl, 30h
	mov	ah, 02h
	int	21h
	mov	dl, '='
	mov	ah, 02h
	int	21h
	xor	ah, ah
	mov	al, cl
	mul	ch
	div	dh
	push	ax
	and	al, al
	jz	next
	mov	dl, al
	add	dl, 30h
	mov	ah, 02h
	int	21h
	pop	ax
next:	mov	dl, ah
	add	dl, 30h
	mov	ah, 02h
	int	21h
	mov	dl, ' '
	mov	ah, 02h
	int	21h
	inc	cl
	cmp	cl, ch
	jbe	again2
	mov	dl, 0ah
	mov	ah, 02h
	int	21h
	inc	ch
	cmp	ch, 9
	jbe	again
	mov	ah, 4ch
	int	21h
	
	mov	ah, 4ch
	int	21h
cseg	ends
	end 	start