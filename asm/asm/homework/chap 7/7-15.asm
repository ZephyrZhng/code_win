; 内存子buff单元开始的存储区连续存放100个学生的某科分数，编制程序统计
; 100,90-99,80-89,70-79,60-69,59以下分数段的人数，
; 并把结果连续存放在resut开始的单元
dseg		segment
buff		db		100,99,95,80,81,88,79,77,65,66,50,32
resut		db		12 dup (0)
dseg		ends

cseg		segment
		assume	cs: cseg, ds: dseg
		
start:		mov		ax, dseg
		mov		ds, ax
		mov		cx, 12
		lea		si, buff
		
again:		mov		al, [si]
		cmp		al, 59
		ja		case60
		mov		di, 5
		jmp		next
		
case60:		cmp		al, 69
		ja		case70
		mov		di, 4
		jmp		next
		
case70:		cmp		al, 79
		ja		case80
		mov		di, 3
		jmp		next
		
case80:		cmp		al, 89
		ja		case90
		mov		di, 2
		jmp		next
		
case90:		cmp		al, 99
		ja		case100
		mov		di, 1
		jmp		next
	
case100:	xor		di, di

next:		inc		resut[di]
		inc		si
		loop	again
		mov		ah, 4ch
		int		21h
			
cseg		ends
		end		start