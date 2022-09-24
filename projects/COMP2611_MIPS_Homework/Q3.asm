.data
str:.byte 0:50
substr1: .byte 0:50
substr2: .byte 0:50

inputStrMsg:.asciiz "\nInput the string (with length at most 50): \n"
inputSubstr1Msg:.asciiz "Input the substring you want to replace: \n"
inputSubstr2Msg:.asciiz "Input the substring you want to replace with (in the same length): \n"
failMsg:.asciiz  "\nsubstring not found!"
successMsg: .asciiz "\nThe processed string is :"

.text
main:	
	la $s0, str  # s0 = address of target string
	la $s1, substr1     # s1 = address of substr1
	la $s2, substr2     # s2 = address of substr2

	# print input message
	li $v0,4
	la $a0, inputStrMsg
	syscall
	
        # getting the original/target string from user 
	add $a0, $s0, $zero
	li $a1, 50
	li $v0, 8
	syscall              
	
	li $v0,4
	la $a0, inputSubstr1Msg
	syscall
	
        # getting the substr1 from user 
	add $a0, $s1, $zero
	li $a1, 50
	li $v0, 8
	syscall               

	li $v0,4
	la $a0, inputSubstr2Msg
	syscall
	
	# getting the substr2 from user 
	add $a0, $s2, $zero
	li $a1, 50
	li $v0, 8
	syscall               
	

	add $a0,$s0,$zero #$a0 address of the target/original string	
	add $a1,$s1,$zero #$a1 the address of substr1
	add $a2,$s2,$zero #$a2 the address of substr1
	
	#pass $a0,$a1,$a2 to the function call
	#$a0 is address of the target/original string
	#$a1 is the address of substr1 (the substring to search for)
	#$a2 is the address of substr2 (the substring to replace substr1 with)
	jal findAndReplaceSubstring
	j end
	

####TODO BELOW
#inputs $a0:  address of the target/original string
#       $a1:  the address of substr1 (the substring to search for)
#       $a2:  the address of substr2 (the substring to replace substr1 with)
# hint: 1. you can call the strlen() to find the lengths of str, substr1 and substr2 as needed
#       2. you can use "lbu" to load a character
#       3. you can call replace() to do the substr replacement directly in str[], at the end just need to output str if replacement has been done
#You can add labels as you wish
#remember to preserve the save registers and the $ra according to slide 76 of https://course.cse.ust.hk/comp2611/note/COMP2611_ISA_Spring21.pdf       
findAndReplaceSubstring:
	# PUSH - make a list of variables we need to save the stack. Remember to pop them at the end of the function.
	# Recall it is the callee's responsibility to save the $ra and $s registers to the stack so that they are preserved once we are done with this function
	# However, we are allowed to change values of the v, a, and t registers freely (that was the caller's responsibility)
	addi $sp, $sp, -16
	sw $ra, 12($sp)
	sw $s0, 8($sp)
	sw $s1, 4($sp)
	sw $s2, 0($sp)
	#if old sp = 32
	#sp new =16
	#ra = 28-32
	#s0 = 24-28
	#s1 = 20-24
	#s2 = 16-20
	
	li $s3, 0 # processed=false <=> $s3=0
	
	addi $sp, $sp, -36
	sw $t0, 0($sp)
	sw $t1, 4($sp)
	sw $t2, 8($sp)
	sw $t3, 12($sp)
	sw $t4, 16($sp)
	sw $t5, 20($sp)
	sw $t6, 24($sp)
	sw $t7, 28($sp)
	sw $t8, 32($sp)
	jal strlen
	lw $t0, 0($sp)
	lw $t1, 4($sp)
	lw $t2, 8($sp)
	lw $t3, 12($sp)
	lw $t4, 16($sp)
	lw $t5, 20($sp)
	lw $t6, 24($sp)
	lw $t7, 28($sp)
	lw $t8, 32($sp)
	addi $sp, $sp, 36
	move $t7, $v0 # $t7 stores length of original string
	
	move $a0, $a1
	addi $sp, $sp, -36
	sw $t0, 0($sp)
	sw $t1, 4($sp)
	sw $t2, 8($sp)
	sw $t3, 12($sp)
	sw $t4, 16($sp)
	sw $t5, 20($sp)
	sw $t6, 24($sp)
	sw $t7, 28($sp)
	sw $t8, 32($sp)
	jal strlen
	lw $t0, 0($sp)
	lw $t1, 4($sp)
	lw $t2, 8($sp)
	lw $t3, 12($sp)
	lw $t4, 16($sp)
	lw $t5, 20($sp)
	lw $t6, 24($sp)
	lw $t7, 28($sp)
	lw $t8, 32($sp)
	addi $sp, $sp, 36
	move $t8, $v0 # $t8 stores length of substring1, which is by definition same as length of substring2
	
	# after making all the strlen calls, need to reset the values of the registers that it used; namely $t0-$t3
	li $t0, 0
	li $t1, 0
	li $t2, 0
	li $t3, 0 # $t3 = i counts the index of the original string
	li $t4, 0 # $t4 = j counts the index of substring1
	
	lw $t6, 4($sp)
	lb $t2, 0($t6) # pre-load $t2 = substr1[0] (since it's always the same)
	li $t6, 0
	
	lw $a0, 8($sp)
	# after this point, we have loaded the lengths into temp registers $t7-$t8. This is OK and will not conflict since no other function uses these.
	# $a0, $a1, and $a2 have also been reset to the values they originally had when we first called this function.
LookForSubstring:
	lw $t0, 8($sp) # $t0 gets address of ith char of original string using $t0 = $s0 + $t3 = str + i
	add $t0, $t0, $t3
	lb $t5, 0($t0) # $t5 contains str[i]
	
	beq $t5, $t2, nextCharOfSubstring # look at next char of substring1 if and only if there is a match between 1st char of substr1 and ith char of str.
failedSubstringMatch:
	addi $t3, $t3, 1 # look at next index of original string
	beq $t3, $t7, exitLoop # exit loop if we finished iterating through all chars of the original string i.e. if i=strlen(str)
	j LookForSubstring
nextCharOfSubstring:
	lw $t0, 8($sp)
	add $t0, $t0, $t3
	add $t0, $t0, $t4
	lb $t5, 0($t0) # $t5 = str[i+j]
	
	lw $t1, 4($sp) # get address of jth char of substring1 using $t1 = $s1 + $t4 = substr1 + j
	add $t1, $t1, $t4
	lb $t6, 0($t1) # now $t6 = substr1[j]
	
	# *** this is debug statement! Uncomment to see $t3-$t6 values
	#addi $sp, $sp, -4
	#sw $a0, 0($sp)
	
	#li $v0,4
	#la $a0, successMsg
	#syscall
	
	#move $a0, $t3
	#li $v0, 1
	#syscall
	
	#li $v0,4
	#la $a0, successMsg
	#syscall
	
	#move $a0, $t4
	#li $v0, 1
	#syscall 
	
	#li $v0,4
	#la $a0, failMsg
	#syscall
	
	#move $a0, $t5
	#li $v0, 1
	#syscall
	
	#li $v0,4
	#la $a0, failMsg
	#syscall
	
	#move $a0, $t6
	#li $v0, 1
	#syscall 
	
	#lw $a0, 0($sp)
	#addi $sp, $sp, 4
	# *** END debug statement
	
	beq $t6, $t5, nextCharMatch # if substr1[j] != str[i+j], return to outer loop
	li $t4, 0
	j failedSubstringMatch
nextCharMatch:
	addi $t4, $t4, 1 # j+=1
	beq $t4, $t8, callReplaceFunction # if $t4 = $t8 = length of substring 1, we have found a match
	j nextCharOfSubstring # if not, then keep looking
callReplaceFunction:
	li $s3, 1 # set processed=true. Meaning we found substr1 in str
	
	# $a0 needs to be equal to address of 1st char of str[]. By definition this has been stored in $s0
	lw $a0, 8($sp)
	# $a1 = index of where substr1 is found in the target string = current index of str[] = $t3
	move $a1, $t3
	# address of substr2 is in $s2.
	lw $a2, 0($sp)
	move $a3, $t8 # copy length of substr2 to $a3
	
	# caller's responsibility to save the $t0-$t8 registers since we're using them
	addi $sp, $sp, -36
	sw $t0, 0($sp)
	sw $t1, 4($sp)
	sw $t2, 8($sp)
	sw $t3, 12($sp)
	sw $t4, 16($sp)
	sw $t5, 20($sp)
	sw $t6, 24($sp)
	sw $t7, 28($sp)
	sw $t8, 32($sp)
	jal replace
	lw $t0, 0($sp)
	lw $t1, 4($sp)
	lw $t2, 8($sp)
	lw $t3, 12($sp)
	lw $t4, 16($sp)
	lw $t5, 20($sp)
	lw $t6, 24($sp)
	lw $t7, 28($sp)
	lw $t8, 32($sp)
	addi $sp, $sp, 36
	
	# i=i+substrlength-1
	add $t3, $t3, $t8
	subi $t3, $t3, 1
	
	# reset j=$t4 to 0
	li $t4, 0
	j failedSubstringMatch
exitLoop:
	beq $s3, 1, printSuccessMsg
	
	li $v0,4
	la $a0, failMsg # print fail message
	syscall
	
	j realExitLoop
printSuccessMsg:
	# print success message + substituted string
	li $v0,4
	la $a0, successMsg
	syscall
	
	li $v0,4
	lw $a0, 8($sp) # load $a0 = $s0
	syscall
	
	j realExitLoop
realExitLoop:
	# POP
	lw $ra, 12($sp)
	lw $s0, 8($sp)
	lw $s1, 4($sp)
	lw $s2, 0($sp)
	addi $sp, $sp, 16
	
 	jr $ra        
###TODO above 	


 #input $a0: the address of the string
 #output $v0: the length of the string
 #this is the same strlen() function as in Q2
 #*you can copy and paste the same function from Q2 to here*
 #TODO BELOW
 #add labels as you wish
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
###TODO ABOVE
        
         	
 ### TODO BELOW
#inputs $a0: address of target string
#	$a1: index of where substr1 is found in the target string
#	$a2: address of substr2
#	$a3: length of substr2
#IMPORT! This function write directly to str[] updaing str[] by replacing substr1 starting at str[i] with substr2
#add labels as you wish
#remember to preserve the save registers and the $ra according to slide 76 of https://course.cse.ust.hk/comp2611/note/COMP2611_ISA_Spring21.pdf       
replace:
	# PUSH: the caller function, findAndReplaceSubstring, used registers $s0-$s3. So it is our responsibility to back those up
	addi $sp, $sp, -20
	sw $ra, 0($sp)
	sw $s0, 4($sp)
	sw $s1, 8($sp)
	sw $s2, 12($sp)
	sw $s3, 16($sp)
	
	li $s0, 0 # $s0 counts i as we replace
loopReplace:
	add $s1, $a2, $s0 # $s1 = address of substr2[i]
	lb $s3, 0($s1) # load the byte in that address
	
	# save 
	move $s2, $a0 # $s2 = $a0 = str
	add $s2, $s2, $a1 # $s2 = str + index = str[index] 
	add $s2, $s2, $s0 # $s2 = str + index + i = str[index+i] 
	
	sb $s3, 0($s2) # store $s2 = $s3 => str[index+i] = contents of substr2[i] (this works since since substr1 same length as substr2)
		
	addi $s0, $s0, 1 # i+=1
	beq $s0, $a3, exitLoopReplace # i = $a3 = length of substr2 = substrLength
	j loopReplace
exitLoopReplace:
	# POP
	lw $ra, 0($sp)
	lw $s0, 4($sp)
	lw $s1, 8($sp)
	lw $s2, 12($sp)
	lw $s3, 16($sp)
	addi $sp, $sp, 20
	
	jr $ra
### TODO ABOVE
	
#do not remove this label!	
end:
