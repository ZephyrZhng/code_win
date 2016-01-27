dseg		segment
adrx		db	01h
adry		db	80h
flag		db	?
dseg		ends

cseg		segment
		assume	cs: cseg, ds: dseg

start:		mov	ax, dseg
		mov	ds, ax

		mov	al, adrx
		mov	ah, adry
		and	al, al
		js	negative
		and	ah, ah
		js	different
		mov	bl, 0
		jmp	move

negative:	and	ah, ah
		jns	different
		mov	bl, 1
		jmp	move

different:	mov	bl, 0ffh

move:		mov	flag, bl
		mov	ax, 4c00h
		int	21h

cseg		ends
		end	start