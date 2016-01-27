cseg	segment
	assume	cs: cseg
code:	mov	al, 9ah
	mov	al, bl
	and	al, 0
	and	dl, 0
	mov	cl, 02h
	mov	ch, 11h
	rol	bl, 1
	MOV	DL, BL
	AND	DL, CH
	OR	AL, DL
	ROL	BL, CL
	MOV	DL, BL
	SHL	CH, 1
	and	dl, ch
	or	al, dl
	ROL	BL, CL
	MOV	DL, BL
	SHL	CH, 1
	and	dl, ch
	or	al, dl
	ROL	BL, CL
	MOV	DL, BL
	SHL	CH, 1
	and	dl, ch
	or	al, dl
cseg	ends
	end	code