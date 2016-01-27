dseg		segment
adr		db	3 dup (?)
flag		db	?
dseg		ends

cseg		segment
		assume	cs: cseg, ds: dseg

start:		mov	ax, dseg
		mov	ds, ax

		mov	adr, 06h
		mov	adr + 1, 04h
		mov	adr + 2, 06h
		mov	al, adr
		mov	ah, adr + 1
		mov	bl, adr + 2

		test	al, 01h
		jpo	odd
		test	ah, ah
		jpo	different
		test	bl, bl
		jpo	different	
		mov	bh, 1
		jmp	move

odd:		test	ah, 01h
		jpe	different
		test	bl, 01h
		jpe	different
		mov	bh, 0
		jmp	move

different:	mov	bh, 0ffh

move:		mov	flag, bh
		mov	ax, 4c00h
		int	21h

cseg		ends
		end	start