dseg	segment
a1	db	1, 18, 25h, 80h, -128, 'ABC'
a2	db	3 * 5, 48 / 4, 36 - 5, 26 mod 10
a3	db	?, ?, 36h, -1, 36q
a4	db	5 dup (26), 3 dup (?)
a5	db	2 dup (2 dup (4), 15), 7fh
dseg	ends
	end