.data
inputMsg: .asciiz "\nInput R, G, B value of a point!\n"
redMsg: .asciiz "Red: (0-255)\n"
greenMsg: .asciiz "Green: (0-255)\n"
blueMsg: .asciiz "Blue: (0-255)\n"
grayscaleMsg: .asciiz "The grayscale is: "
rgb: .word 0:3

.text
.globl main
main:
	la $s0, rgb	#s0 = red
	la $s1, 4($s1)	#s1 = green
	la $s1, 8($s1)	#s2 = blue
	
	li $v0, 4
	la $a0, inputMsg
	syscall
	
	li $v0, 4
	la $a0, redMsg
	syscall
	
	li $v0,5
	syscall
	add $s0, $v0, $zero	
		
	li $v0, 4
	la $a0, greenMsg
	syscall
	
	li $v0,5
	syscall
	add $s1, $v0, $zero	
		
	li $v0, 4
	la $a0, blueMsg
	syscall
	
	li $v0,5
	syscall
	add $s2, $v0, $zero	
	
	add $a0, $s0, $zero
	add $a1, $s1, $zero
	add $a2, $s2, $zero
	jal rgb2gray
	
	add $s3, $v0, $zero
	
	li $v0, 4
	la $a0, grayscaleMsg
	syscall
	
	li $v0, 1
	add $a0, $s3, $zero
	syscall
	
	li $a0,52
	li $a1,103
	jal multiply
	
	
	j exit
	
## TODO BELOW
#input : $a0: red value
#	 $a1: green value
#	 $a2: blue value
#output: $v0: grayscale value
#hint: you can use the multiply function provided below 
#      to multiple two integers, the result will be in $v0
#You can add labels as you wish
#remember to preserve the save registers and the $ra according to slide 76 of https://course.cse.ust.hk/comp2611/note/COMP2611_ISA_Spring21.pdf       
rgb2gray:
	# this function only uses $t0-$t3 registers
	# PUSH - default lines that are always needed when we have a nested function call (since we plan to call 'multiply' later)
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	
	move $t0, $a0 # $t0=$a0
	move $t1, $a1 # $t1=$a1
	move $t2, $a2 # $t2=$a2
	li $t3, 0 # load constant value of 0 into $t3
	
	# first multiplication
	li $a1, 19595
	jal multiply
	add $t3, $t3, $v0
	
	# second multiplication
	move $a0, $t1
	li $a1, 38469
	jal multiply
	add $t3, $t3, $v0
	
	# third multiplication
	move $a0, $t2
	li $a1, 7472
	jal multiply
	addu $t3, $t3, $v0
	
	# Indeed it can be verified that the possible values of $t3 are in [0, 16711680] (the max is reached iff R=G=B=255)
	# And our register $t3 is a 32-bit register which can indeed store all these values
	
	# right shift 16 bits then save in $v0
	srl $t3, $t3, 16
	move $v0, $t3
	
	# POP - default lines always needed to pop $ra off the stack after completing a nested function call
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	
	jr $ra
###TODO ABOVE


#mutiply()
#input : $a0: a
#	 $a1: b
#output: $v0: a*b
multiply:
	addi $sp, $sp, -4
	sw $s0, ($sp)
	li $s0, 0
	li $v0, 0
mult_loop:
	beq $s0, $a1, end_mult
	add $v0, $v0, $a0
	addi $s0, $s0, 1
	j mult_loop
end_mult:
	lw $s0, ($sp)
	addi $sp, $sp, 4
	jr $ra

exit:
	li $v0,10
	syscall
	
	


