DSEG	SEGMENT
NUM	DB	5
SUM	DW	?
DSEG	ENDS
CSEG	SEGMENT
	ASSUME	CS: CSEG, DS: DSEG
START:	MOV	AX, DSEG
	mov	ds, ax
	mov	cl, num
	mov	al, 1
	mov	bl, 1
data:	mul	bl
	inc	bl
	loop	data
	mov	sum, ax
	mov	cl, 4
	shr	al, cl
	add	al, 30h
	cmp	al, 39h
	jbe	next1
	add	al, 07h
next1:	mov	dl, al
	mov	ah, 02h
	int	21h
	mov	ax, sum
	and	al, 0fh
	add	al, 30h
	cmp	al, 39h
	jbe	next2
	add	al, 07h
next2:	mov	dl, al
	mov	ah, 02h
	int	21h
	mov	ah, 4ch
	int	21h
cseg	ends
	end	start