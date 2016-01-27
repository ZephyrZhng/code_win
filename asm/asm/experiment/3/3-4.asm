; 从键盘输入0-9之间任意一个数字，利用查表法计算其平方值，
; 并将结果以十进制形式在屏幕上显示出来

dseg		segment
square		db	0, 1, 4, 9, 16, 25, 36, 49, 64, 81
dseg		ends

cseg		segment
		assume	cs: cseg, ds: dseg

start:		mov	ax, dseg
		mov	ds, ax

		mov	ah, 01h
		int	21h
		sub	al, 30h
		lea	bx, square
		xlat
		xor	ah, ah
		mov	cl, 10
		div	cl
		add	al, 30h
		add	ah, 30h
		mov	bl, ah
		cmp	al, 30h
		jz	print
		mov	dl, al
		mov	ah, 02h
		int	21h

print:		mov	dl, bl
		mov	ah, 02h
		int	21h
		mov	ax, 4c00h
		int	21h

cseg		ends
		end	start