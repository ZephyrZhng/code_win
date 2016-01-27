dseg	segment
c1	dd	12345678h, 'MN'
c2	dd	80000000h, -1
c3	dd	36.625, -36.625
c4	dd	c1, 3 dup (?)
dseg	ends
	end