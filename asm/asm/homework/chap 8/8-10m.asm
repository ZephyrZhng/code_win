; ���õݹ鷽������fibonacci�����ĵ�n���0 <= n <= 20
; ��֪f(n) =	n			(n <= 1)
;		f(n - 1) + f(n - 2)	(n >  1)
; д���ӳ���˵���ļ���
; ���ô��ӳ������100-500֮���fibonacci�����
; ������tirm��ʼ�Ĵ洢��

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