; ����ʽ y = a * x ^ 2 + b * x + c��
; a��b��c�ֱ�����dataa��datab��datac�ֽڵ�Ԫ��
; ����������datay�ֵ�Ԫ
; a��b��c��x��Ϊ0-9֮�������

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