; 将al中的数以16进制输出
print		proc
		pushf
		push	ax
		mov	ah, al
		mov	cl, 4
		shr	ah, cl
		shl	al, cl
		shr	al, cl
		cmp	ah, 10
		jb	small
		add	ah, 37h
		jmp	next
small:		add	ah, 30h
next:		cmp	al, 10
		jb	small2
		add	al, 37h
		jmp	display
small2:		add	al, 30h
display:	push	ax
		mov	dl, 0ah
		mov	ah, 2
		int	21h
		pop	ax
		push	ax
		mov	dl, ah
		mov	ah, 2
		int	21h
		pop	ax
		push	ax
		mov	dl, al
		mov	ah, 2
		int	21h
		pop	ax
		pop	ax
		popf
		ret
print		endp