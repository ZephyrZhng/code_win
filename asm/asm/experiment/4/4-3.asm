;  从键盘接收字符，若为字幕，在屏幕上显示l，若为数字，显示d，否则显示o。

sseg	segment	stack
sktop	db	50 dup (0)
sseg	ends

cseg	segment
	assume	cs: cseg, ss: sseg
start:	mov	ax, sseg
	mov	ss, ax
	mov	sp, size sktop

	mov	ah, 01h
	int	21h
	cmp	al, 30h
	jb	o
	cmp	al, 39h
	jbe	d
	cmp	al, 41h
	jb	o
	cmp	al, 5ah
	jbe 	l
	cmp	al, 61h
	jb	o
	cmp	al, 7ah
	jbe 	l
o:	mov	dl, 'o'
	jmp	print
d:	mov	dl, 'd'
	jmp	print
l:	mov	dl, 'l'
print:	mov	ah, 02h
	int	21h
	
	mov	ah, 4ch
	int	21h
cseg	ends
	end 	start