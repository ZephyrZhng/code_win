dseg	segment
data1	db	1, 2, 3, 6, 8, 7, 4, 1, 2, 5
data2	db	10 dup (?)
len	db	10
dseg	ends

sseg	segment	stack
sktop	db	50 dup (0)
sseg	ends

cseg	segment
	assume	cs: cseg, ss: sseg, ds: dseg

start:	mov	ax, sseg
	mov	ss, ax
	mov	sp, size sktop
	mov	ax, dseg
	mov	ds, ax
	mov	es, ax

	mov	cx, word ptr len
	lea	si, data1
	lea	di, data2
	cld
	rep	movsw

	mov	ah, 4ch
	int	21h
cseg	ends
	end 	start