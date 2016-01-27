dseg		segment
dax		dw	12h
day		dd	?
dseg		ends

cseg		segment
		assume	cs: cseg, ds: dseg

start:		mov	ax, dseg
		mov	ds, ax

		mov	ah, 01h
		int	21h
		cmp	al, '0'
		je	first
		cmp	al, '1'
		je	second
		mov	ax, dax
		cwd
		and	ax, ax
		jns	move
		neg	ax
		cwd
		jmp	move

first:		mov	ax, dax
		cwd
		add	ax, 1000d
		adc	dx, 0
		jmp	move

second:		mov	ax, dax
		cwd
		mov	bx, 05h
		imul	bx
		sub	ax, 2
		sbb	dx, 0

move:		mov	day, ax
		mov	day + 2, dx
		and	dx, dx
		js	negative
		jnz	positive
		and	ax, ax
		jnz	positive
		jmp	zero

negative:	mov	dl, '-'
		mov	ah, 02h
		int	21h
		jmp	final

positive:	mov	dl, '+'
		mov	ah, 02h
		int	21h
		jmp	final

zero:		mov	dl, '0'
		mov	ah, 02h
		int	21h

final:		mov	ax, 4c00h
		int	21h

cseg		ends
		end	start