sseg	segment	stack
sktop	db	100 dup (0)
sseg	ends

cseg	segment
	assume	cs: cseg, ss: sseg

start:	mov	ax, sseg
	mov	ss, ax
	mov	sp, size sktop
	
again:	mov	ah, 01h
	int	21h
	push	ax
	cmp	al, 0dh
	je	stop
	mov	dl, ' '
	mov	ah, 02h
	int	21h
	pop	ax
	call	outputascii
	mov	dl, 0ah
	mov	ah, 02h
	int	21h
	jmp	again

stop:	mov	ah, 4ch
	int	21h

	include	7-2-1.asm

cseg	ends
	end	start