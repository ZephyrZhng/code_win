; ; 将bin单元开始存放的二进制数据以八进制形式显示在屏幕上

sseg	segment	stack
sktop	db	100 dup (0)
sseg	ends

dseg	segment
bin	db	00110101b, 00111100b, 10101111b
cnt	db	3
dseg	ends

cseg	segment
	assume	cs: cseg, ds:dseg, ss: sseg

printo	proc
	push	dx
	add	dl, 30h
	mov	ah, 02h
	int	21h
	pop	dx
	ret
printo	endp

start:	mov	ax, dseg
	mov	ds, ax
	mov	ax, sseg
	mov	ss, ax
	mov	sp, size sktop

	xor	bl, bl
	lea	si, bin
again:	mov	dl, [si]
	mov	cl, 6
	shr	dl, cl
	call	printo
	mov	dl, [si]
	and	dl, 00111000b
	mov	cl, 3
	shr	dl, cl
	call	printo
	mov	dl, [si]
	and	dl, 00000111b
	call	printo
	inc	si
	inc	bl
	cmp	bl, cnt
	jb	again

	mov	ah, 4ch
	int	21h
cseg	ends
	end 	start