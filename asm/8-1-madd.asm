; ��di��ָ�ĵ�Ԫ��ʼ������Ϊ2 * cx��һ�����ֽ����ݼ���
; bx��ָ�ĵ�Ԫ��ʼ������Ϊcx��һ�����ֽ�����
	public	madd
cseg	segment
	assume	cs: cseg
madd	proc	far

	push	di
	push	ax
	push	bx
	push	cx
	clc

again:	mov	al, [bx]
	adc	[di], al
	inc	di
	inc	bx
	loop	again
	jnc	return
	xor	al, al
	pop	cx
	push	cx
again2:	adc	[di], al
	inc	di
	loop	again2
return:	pop	cx
	pop	bx
	pop	ax
	pop	di

	ret
madd	endp
cseg	ends
	end