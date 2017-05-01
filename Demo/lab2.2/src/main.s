	 .syntax unified
	 .cpu cortex-m4
	 .thumb

.data
	X: .word 5
	Y: .word 10
	PTR: .space 240
.text
	.global main
	.equ AA,10
main:
	ldr r1,=X
	ldr r0,[r1]
	ldr r7,=PTR
	movs r2,#AA
	mul r3,r0,r2
	ldr r4,=Y
	ldr r5,[r4]
	adds r3,r3,r5
	subs r2,r5,r3
	str r2,[r7]
L:B L
