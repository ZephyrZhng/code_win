DSEG	SEGMENT
DATA1	DB	35H
DATA2	DB	29H
DSEG	ENDS
CSEG	SEGMENT
	ASSUME	CS: CSEG, DS: DSEG
START:	MOV	AX, DSEG
	MOV	DS, AX
	MOV	AL, DATA1
	ADD	AL, DATA2
	PUSH	AX
	MOV	CL, 4
	SHR	AL, CL
	ADD	AL, 30H
	CMP	AL, 39H
	JBE	OK1
	ADD	AL, 07H
OK1:	MOV	DL, AL
	MOV	AH, 02H
	INT	21H
	POP	AX
	AND	AL, 0FH
	ADD	AL, 30H
	CMP	AL, 39H
	JBE	OK2
	ADD	AL, 07H
OK2:	MOV	DL, AL
	MOV	AH, 02H
	INT	21H
	MOV	AH, 4CH
	INT	21H
CSEG	ENDS
	END	START