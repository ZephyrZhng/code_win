dseg	segment
i	db	04h
mem	db	31h
dseg	ends
cseg	segment
	assume	cs: cseg, ds: dseg
code:	mov	ax, dseg
	mov	ds, ax
	mov	al, 10h
	mov	dl, 03h
	mov	bl, al
	mov	cl, i
	shl	dl, cl
	and	bl, dl
	not	dl
	and	mem, dl
	or	mem, bl
cseg	ends
	end	code