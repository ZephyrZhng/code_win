; ��x��n�η�
; x��bl
; n��cx
; �����ax
; f��Ӱ��

	public	pow
cseg	segment
	assume	cs: cseg
pow	proc	far
	and	cx, cx
	jz	exit
	push	cx
	dec	cx
	call	pow
	pop	cx
	mul	bl
	ret
exit:	mov	ax, 1
	ret
pow	endp
cseg	ends
	end