; �ӳ�������		fib
; �ӳ����ܣ�		���n��fibonacci������ֵ
; ���������		n����cx��
; ����������		f(n)����ax
; ��Ӱ��ļĴ�����	ax, f

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