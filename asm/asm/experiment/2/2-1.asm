cseg	segment
x1	db	0ah, 0bh, 0ch, 0dh, 31h, 32h, 33h, 34h
x2	db	10, 11, 12, 13, 14, 15, 16, 17
x3	db	-1, -2, -3, -4, -5, -6, -7, -8
y1	db	25 + 25, 78 - 34, 15 * 4, 90 / 3
y2	db	80 mod 9, 3 dup (50h)
y3	DB	'ABCDEFGH'
z1	dw	1234h, 5678h, 0abcdh, 0abefh
z2	dw	-1, -2, -3, -4, -5, -6, -7, -8
z3	dw	offset y3, 3 dup (0), offset z2, 3 dup (?)
cseg	ends
	end