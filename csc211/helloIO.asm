########### hello.asm on p. 26-27 #############
# Ali Morshid                                 #
# hello.asm                                   #
# Description                                 #
#     Program which displays a message        #
# Program Logic                               #
# 1.  Ask for input 		  	      #
# 2.  Input a message 		 	      #
# 3.  display a message from data area 	      #
# 4.  return to operating system              #
###############################################

        .text
	.globl __start
        
__start:
        
	la $a0,str1 # a0 = address of string
	li $v0,4    # v0 = 4, indicates display a string
	syscall 		
		
	la $a0,str  # a0 <- address of string
        li $a1,100  # v0 = 8, indicates input of a string
	li $v0, 8   # a1 = 100, indicates string length
        syscall  

	la $a0,str  # a0 = address of string
	li $v0,4    # v0 = 4, indicates display a string
	syscall 

        li $v0,10   # End Of Program	
        syscall     # Call to system

        .data
str1:   .asciiz "Enter a message \n"
str:    .space 100


############## Output ##############

#	Enter a message 
#	Hello There!
#	Hello There!                             
#                       	                               
####################################

