; 求表达式 y = a * x ^ 2 + b * x + c，
; a，b，c分别存放在dataa，datab，datac字节单元中
; 计算结果存入datay字单元
; a，b，c，x均为0-9之间的数字

dseg		segment
dataa		db	01h
datab		db	02h
datac		db	03h
datax		db	04h
datay		dw	?
dseg	ends

cseg		segment
		assume	cs: cseg, ds: dseg

start:		mov	ax, dseg
		mov	ds, ax

		xor	ah, ah
		mov	al, datax
		mov	cl, datax
		mul	cl
		mov	cl, dataa
		mul	cl
		mov	bx, ax
		xor	ah, ah
		mov	al, datax
		mov	cl, datab
		mul	cl
		add	bx, ax
		xor	ah, ah
		mov	al, datac
		add	bx, ax
		mov	datay, bx
		mov	ax, 4c00h
		int	21h

cseg		ends
		end	start