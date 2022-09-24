.data
inputMsg: .asciiz "Type the string (with length at most 50):\n"
trueMsg: .asciiz "True!\n"
falseMsg: .asciiz "False!\n"
string: .byte 0:50

.text
.globl main
main:
	la $s0, string
	
	# print input message
	li $v0, 4
	la $a0, inputMsg
	syscall
	
	#read the string
	li $v0, 8
	add $a0, $s0, $zero #string
	li $a1, 50 #length
	syscall
	add $a0, $s0, $zero
	jal strlen
	add $s1, $v0, $zero
	
	add $a0, $s0, $zero
	add $a1, $s1, $zero
	jal isPalindrome
	add $s2, $v0, $zero
	
	bgtz $s2, printTrue 
	j printFalse
	
 ### TODO BELOW
 #input a0: the address of the string
 #output v0: the length
 #hints: 1. assume the last character of the string is a '\n' (with ascii value of 10)
 #       2. you just need to count the number of characters before encountering '\n'
 #       3. you can use lbu/lb to load the characters from the "string" array, 
 #          the base address is already in $a0. 
 #You can add labels as you wish
#remember to preserve the save registers and the $ra according to slide 76 of https://course.cse.ust.hk/comp2611/note/COMP2611_ISA_Spring21.pdf       
strlen:
	add $t0, $zero, $zero # set $t0=0 ($t0 = offset)
	li $t3, 10 # load 10 (ascii value of \n char) into $t3
countLength:
	add $t1, $t0, $a0 # set $t1 = $a0 + $t0 = first char of string + offset
	lbu $t2, 0($t1) # load the (offset)-th character into $t2
	beq $t2, $t3, stopCounting
	# if not equal, add 1 to $t0
	addi $t0, $t0, 1
	j countLength # return to loop start
stopCounting:
	# ** uncomment this section to print the length to console
	#move $a0, $t0
	#li $v0, 1
	#syscall
	# **
	
	move $v0, $t0 # copy final value to desired $v0 address 
        jr $ra
### TODO ABOVE
	

### TODO BELOW
# input: a0: address of string
#	 a1: length of string
# output:v0: 1 if true, 0 if false
#hints: refer to the C++ program for the logic
#You can add labels as you wish
#remember to preserve the save registers and the $ra according to slide 76 of https://course.cse.ust.hk/comp2611/note/COMP2611_ISA_Spring21.pdf       
isPalindrome:
	add $t0, $a0, $zero # load address of first char into $t0
	add $t1, $a0, $a1 # load address of last char into $t1 (char array beginning + length - 1)
	subi $t1, $t1, 1
	
	add $t4, $zero, $zero # counts number of characters we've searched
Loop:	
	# load the bytes in the first and last char into $t2 and $t3 respectively
	lb $t2, 0($t0)
	lb $t3, 0($t1)
	
	# compare them, if the same, increment $t0, decrement $t1, and go to next iteration of loop, else obviously cannot be palindrome
	bne $t2, $t3, noPalindrome
	addi $t0, $t0, 1
	subi $t1, $t1, 1
	
	addi $t4, $t4, 1 # once this reaches length of the string, that means we have not found evidence of a not palindrome. So this string must be a palindrome
	beq $t4, $a1, yesPalindrome
	j Loop
noPalindrome:
	li $v0, 0 # make palindrome false
	j exitLoop
yesPalindrome:
	li $v0, 1
	j exitLoop
exitLoop:
	jr $ra
### TODO ABOVE
	
	
printFalse:
	li $v0,4
	la $a0,falseMsg
	syscall
	j exit
printTrue:
	li $v0,4
	la $a0,trueMsg
	syscall
	j exit
exit:
	li $v0,10
	syscall
	
	


