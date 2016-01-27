	extrn	is0: far
	extrn	is1: far
	extrn	madd: far
	extrn	mshl: far
	extrn	mshr: far

dseg	segment
mltor	db	0,0,0,0,1
mlted	db	2,0,0,0,0
len	db	5
prdt	db	10 dup (0)
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

	xor	ch, ch
	mov	cl, len
	lea	si, mltor
	lea	bx, mlted
	lea	di, prdt

	call	is0
	jc	stop
	push	si
	mov	si, bx
	call	is0
	pop	si
	jc	stop
check1:	call	is1
	jnc	next
	
	push	cx
	push	si
	push	di
	pushf
	cld
	mov	si, bx
	rep	movsb
	popf
	pop	di
	pop	si
	pop	cx

	jmp	stop
next:	push	si
	mov	si, bx
	call	is1
	pop	si
	jnc	cal
	
	push	cx
	push	si
	push	di
	pushf
	cld
	rep	movsb
	popf
	pop	di
	pop	si
	pop	cx

	jmp	stop
cal:	call	mshr
	jz	next2
	call	madd
next2:	call	mshl
	call	is0
	jnc	cal

	mov	al, prdt

stop:	mov	ah, 4ch
	int	21h
cseg	ends
	end 	start