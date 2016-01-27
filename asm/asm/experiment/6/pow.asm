; 求x的n次方
; x送bl
; n送cx
; 结果送ax
; f受影响

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