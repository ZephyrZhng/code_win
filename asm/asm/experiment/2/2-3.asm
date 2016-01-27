dseg	segment
b1	dw	1234h, 5678h, 8000h, 'XY'
b2	dw	256 * 16, 46h, -25
b3	dw	?, offset b1
b4	dw	3 dup (1234h)
dseg	ends
	end