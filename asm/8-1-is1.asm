; �ж�si��ָ��Ԫ��ʼ������Ϊcx��һ�����ֽ������Ƿ�=1
; ���ݸ߶Ըߣ��ͶԵ�
; cf = 1: ����Ϊ1��cf = 0: ���ݲ�Ϊ1
	public	is1
cseg	segment
	assume	cs: cseg
is1	proc	far

	push	si
	push	cx
	push	ax
	pushf

	mov	al, [si]
	cmp	al, 1
	jne	no
	inc	si
	dec	cx
again:	mov	ah, [si]
	and	ah, ah
	jnz	no
	inc	si
	loop	again
	popf
	stc
	jmp	return
no:	popf
	clc
return:	pop	ax
	pop	cx
	pop	si

	ret
is1	endp
cseg	ends
	end