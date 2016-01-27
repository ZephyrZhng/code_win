; data开始的内存单元连续存放着3个1位16进制数，找出其中最大数与最小数，存放在指定内存单元中

dseg	segment
data	db	0bh, 0ah, 0dh
max	db	?
min	db	?
cnt	db	3
dseg	ends

sseg	segment	stack
sktop	db	100 dup (0)
sseg	ends

cseg	segment
	assume	cs: cseg, ds: dseg, ss: sseg
start:	mov	ax, dseg
	mov	ds, ax
	mov	ax, sseg
	mov	ss, ax
	mov	sp, size sktop
	mov	cx, word ptr cnt
	lea	si, data
	mov	al, [si]
	mov	ah, [si]
	inc	si
	dec	cx
again:	cmp	al, [si]
	jae	next1
	mov	al, [si]
next1:	cmp	ah, [si]
	jbe	next2
	mov	ah, [si]
next2:	inc	si
	loop	again
	mov	max, al
	mov	min, ah
	mov	ah, 4ch
	int	21h
cseg	ends
	end 	start