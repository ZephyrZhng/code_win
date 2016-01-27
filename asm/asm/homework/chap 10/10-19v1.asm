; 将bin单元开始存放的二进制数据以八进制形式显示在屏幕上

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
	mov	cl, 5
	shr	dl, cl
	call	printo
	mov	dl, [si]
	and	dl, 00011100b
	shr	dl, 1
	shr	dl, 1
	call	printo
	mov	dl, [si]
	inc	si
	mov	dh, [si]
	shl	dh, 1
	rcl	dl, 1
	and	dl, 00000111b
	call	printo
	mov	dl, [si]
	and	dl, 01110000b
	mov	cl, 4
	shr	dl, cl
	call	printo
	mov	dl, [si]
	and	dl, 00001110b
	shr	dl, 1
	call	printo
	mov	dl, [si]
	shr	dl, 1
	inc	si
	mov	dl, [si]
	rcr	dl, 1
	mov	cl, 5
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
	add	bl, 3
	inc	si
	cmp	bl, cnt
	jb	again

	mov	ah, 4ch
	int	21h
cseg	ends
	end 	start