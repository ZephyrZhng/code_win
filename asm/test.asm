	;extrn	madd: far

dseg	segment
data1	db	1,1,1,1,1,1,1,1,1,1
data2	db	2,2,2,2,2
addr	dw	offset stop
	mov	ah, 1
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

	lea	si, data1
	lea	di, data2
	cld
	mov	cx, 3
	rep	cmps ds: data2, es: data1

	call	word ptr ds:[si]
	call	ax
	jmp	addr

stop:	mov	ah, 4ch
	int	21h
cseg	ends
	end 	start