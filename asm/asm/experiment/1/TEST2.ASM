SSEG    SEGMENT         STACK
STK     DB              80H DUP (?)
SSEG    ENDS
CSEG    SEGMENT
        ASSUME          CS: CSEG, SS: SSEG
HTOA    PROC            NEAR
        AND             AL, 0FH
        CMP             AL, 10
        JC              HTOA1
        ADD             AL, 07
HTOA1:  ADD             AL, 30H
        RET
HTOA    ENDP
BHTOA   PROC            NEAR
        PUSH            CX
        MOV             CH, AL
        MOV             CL, 04
        SHR             AL, CL
        CALL            HTOA
        MOV             AH, AL
        MOV             AL, CH
        CALL            HTOA
        POP             CX
        RET
BHTOA   ENDP
DISASC  PROC            NEAR
        PUSH            AX
        MOV             AH, 14
        INT             10H
        POP             AX
        RET
DISASC  ENDP
DISAL   PROC            NEAR
        PUSH            AX
        CALL            BHTOA
        XCHG            AH, AL
        CALL            DISASC
        MOV             AL, AH
        CALL            DISASC
        POP             AX
        RET
DISAL   ENDP
BIOS:   PUSH            DS
        XOR             AX, AX
        PUSH            AX
AGAIN:  MOV             AH, 0
        INT             16H
        PUSH            AX
        CALL            DISAL
        MOV             AL, '-'
        CALL            DISASC
        MOV             AL, AH
        CALL            DISAL
        MOV             AL, ' '
        CALL            DISASC
        POP             AX
        CMP             AL, 03H
        JNZ             AGAIN
        MOV             AH, 4CH
        INT             21H
CSEG    ENDS
        END             BIOS

