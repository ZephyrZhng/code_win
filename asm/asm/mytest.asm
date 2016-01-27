	extrn	maxmin: far

dseg	segment
data	db	3, 2, 7, 5, 9
cnt	db	5
index	dw	0
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

	mov	cl, cnt
	lea	si, data
	call	maxmin

stop:	mov	ah, 4ch
	int	21h
cseg	ends
	end 	start