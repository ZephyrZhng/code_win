dseg	segment
memb	db	01h
dseg	ends
cseg	segment
	assume	cs: cseg, ds: dseg
code:	mov	ax, dseg
	mov	ds, ax
	mov	al, memb
	mov	cl, 04h
	shl	al, cl
	shr	memb, cl
	or	memb, al
cseg	ends
	end	code