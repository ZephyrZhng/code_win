; 子程序名：		fib
; 子程序功能：		求第n项fibonacci级数的值
; 入口条件：		n存在cx中
; 出口条件：		f(n)存入ax
; 受影响的寄存器：	ax, f

	public	fib
cseg	segment
	assume	cs: cseg
fib	proc	far
	push	cx
	xor	ax, ax
	and	cx, cx
	jz	return
	cmp	cx, 1
	jz	exit
	dec	cx
	call	fib
	push	bx
	mov	bx, ax
	dec	cx
	call	fib
	add	ax, bx
	pop	bx
	jmp	return
exit:	mov	ax, 1
return:	pop	cx
	ret
fib	endp
cseg	ends
	end