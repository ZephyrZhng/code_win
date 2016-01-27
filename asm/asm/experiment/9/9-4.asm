; 在以$结尾的ascii字符串中找出A，并统计个数，在屏幕显示结果，没找到则显示NOT FOUND
dseg	segment
str	db	'I AM YOUR FATHER'
len	dw	16
nf	db	'NOT FOUND$'
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

	lea	si, str
	xor	bl, bl
	mov	cx, len

again:	cmp	byte ptr [si], 'A'
	jne	next
	inc	bl
next:	inc	si
	loop	again

	and	bl, bl
	jz	none
	mov	cl, 4
	mov	bh, bl
	shr	bh, cl
	cmp	bh, 10
	jae	big1
	add	bh, 30h
	jmp	print1
big1:	add	bh, 37h
print1:	mov	dl, bh
	mov	ah, 2
	int	21h
	shl	bl, cl
	shr	bl, cl
	cmp	bl, 10
	jae	big2
	add	bl, 30h	
	jmp	print2
big2:	add	bl, 37h
print2:	mov	dl, bl
	mov	ah, 2
	int	21h
	jmp	stop
none:	lea	dx, nf
	mov	ah, 9
	int	21h

stop:	mov	ah, 4ch
	int	21h
cseg	ends
	end 	start