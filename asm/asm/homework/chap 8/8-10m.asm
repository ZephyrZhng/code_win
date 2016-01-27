; 利用递归方法计算fibonacci级数的第n项，设0 <= n <= 20
; 已知f(n) =	n			(n <= 1)
;		f(n - 1) + f(n - 2)	(n >  1)
; 写出子程序说明文件，
; 利用此子程序产生100-500之间的fibonacci级数项，
; 并存入tirm开始的存储区

	extrn	fib: far
dseg	segment
tirm	dw	10 dup (?)
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
	xor	cx, cx
	lea	si, tirm

again:	call	fib
	cmp	ax, 100
	jb	next
	cmp	ax, 500
	ja	stop
	mov	[si], ax
	inc	si
	inc	si

next:	inc	cx
	jmp	again

stop:	lea	si, tirm
	mov	ax, [si]
	inc	si
	inc	si
	mov	bx, [si]

	mov	ah, 4ch
	int	21h

cseg	ends
	end	start