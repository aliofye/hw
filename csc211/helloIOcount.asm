########### helloIOcount.asm on p. 26-27 #######
# Ali Morshid                                  #
# helloIOcount.asm                             #
# Description                                  #
#     Program which displays a message         #
# Program Logic                                #
# 1.  Ask for input 		  	       #
# 2.  Input a message 		               #
# 3.  display a message from data area	       #
# 4.  count the number of characters in the msg#
# 5.  display the count	   	               #
# 6.  ask to run the program again             #
# 7.  return to operating system               #
################################################


.globl main
.text


main:

begin:  la $a0,str1    # a0 = address of string
	li $v0,4       # v0 = 4, indicates display a string
	syscall

	la $a0,input1  # a0 <- address of string
        li $a1,100     # v0 = 8, indicates input of a string
	li $v0, 8      # a1 = 100, indicates string length
        syscall

	la $a0,input1  # a0 = address of string
	li $v0,4       # v0 = 4, indicates display a string
	syscall

	la $t0,input1  	 #t0 = address of string
	li $t1,0	 #t1 = address of counter set to 0
step3:	lb $t2,($t0)
	sub $t3, $t2, 10	#t3 = address of the decremented counter
	beqz $t3, step9		#branch to step 9
	addi $t0, $t0, 1	#increment address of the str
	addi $t1, $t1, 1	#increment the counter
	j step3
	syscall

step9:  move $a0, $t1
	li $v0,1
	syscall


again:  la $a0,prompt
	li $v0,4
	syscall

	li $v0,5
	syscall

	beq $v0, 1, loop
	beq $v0, 0, end

loop:   j begin


end:    li $v0,10   # End Of Program
        syscall     # Call to system



.data

prompt: .asciiz "\nWould you like to run the program again? (0=no, 1=yes):\n"
str1:  	.asciiz "\nEnter a message: \n"
input1: .space 100
input2: .space 1



#######################output##########################
# Enter a message:
# My name is Ali
# My name is Ali
# 14
# Would you like to run the program again? (0=no, 1=yes)
# 1

# Enter a message:
# And I like turtles!
# And I like turtles!
# 19
# Would you like to run the program again? (0=no, 1=yes)
# 0
