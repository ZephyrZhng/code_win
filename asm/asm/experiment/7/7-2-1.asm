; 从键盘接受一个字符将它的ascii码显示在屏幕上

outputh		proc
		push	ax
		cmp	al, 9
		ja	big
		add	al, 30h
		jmp	next
big:		add	al, 37h
next:		mov	dl, al
		mov	ah, 02h
		int	21h
		pop	ax
		ret
outputh		endp

outputascii	proc
		push	ax
		mov	cl, 4
		shr	al, cl
		call	outputh
		pop	ax
		push	ax
		shl	al, cl
		shr	al, cl
		call	outputh
		pop	ax
		ret
outputascii	endp