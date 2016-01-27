; 输入一个字符，显示其ascii码
sseg	segment	stack
sktop	db	100 dup (0)
sseg	ends

cseg	segment
	assume	cs: cseg, ss: sseg

start:	mov	ax, sseg
	mov	ss, ax
	mov	sp, size sktop
	
	mov	ah, 1
	int	21h
	call	print

stop:	mov	ah, 4ch
	int	21h

	include	7-2-1-.asm

cseg	ends
	end	start