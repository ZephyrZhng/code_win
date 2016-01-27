; 从键盘读入两个一位十六进制数，乘积存入sum单元

dseg		segment
sum		db	?
dseg		ends

cseg		segment
		assume	cs: cseg, ds: dseg

start:		mov	ax, dseg
		mov	ds, ax

		mov	ah, 01h
		int	21h
		cmp	al, 39h
		ja	big
		sub	al, 30h
		mov	bl, al
		jmp	enter

big:		sub	al, 37h
		mov	bl, al

enter:		mov	ah, 01h
		int	21h
		cmp	al, 39h
		ja	big2
		sub	al, 30h
		jmp	multiply

big2:		sub	al, 37h

multiply:	mul	bl
		mov	sum, al
		mov	ax, 4c00h
		int	21h

cseg		ends
		end	start