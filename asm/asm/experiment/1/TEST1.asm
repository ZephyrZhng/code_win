DSEG	SEGMENT
DATA	DB "HELLO WORLD!$"
DSEG	ENDS
CSEG	SEGMENT
	ASSUME	CS: CSEG, DS: DSEG
START:	MOV	AX, DSEG
	MOV	DS, AX
	LEA	DX, DATA
	MOV	AH, 09H
	INT	21H
	MOV	AH, 4CH
	INT	21H
CSEG	ENDS
	END	START