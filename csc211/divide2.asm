#########################################
#  Ali Morshid                          #
# divide.asm - divide(a,b) = a \ b      #
# Example of a recursive program        #
#                                       #
# DIVIDE                                #
#  public static int div(int a, int b)  #
#  {                                    #
#    if (a == b) return 1;              #
#    else if (a < b) return 0;          #
#    else return (1 + div(a-b,b));      #
#  }                                    #
#########################################

        .text
        .globl main

main:

begin:  la $a0,prompt   # display "Enter the numbers to divide: "
        li $v0,4
        syscall

        li $v0,5        #enter a
        syscall

        move $t0,$v0    # call divide method

	la $a0,prompt   # display "Enter the numbers to divide: "
        li $v0,4
        syscall

        li $v0,5        # enter a
        syscall


	move $a0,$t0
	move $a1,$v0    # call divide method

        li $a3,1        # x = 1

        bltz $a0,nega   #if a < 0, negate x
        j chkb          #if a !< 0, check b
nega:   neg $a3,$a3     #negate x
chkb:   bltz $a1,negb   #if b < 0, negate x
        j absab         #if b !< 0, jump to absab
negb:   neg $a3,$a3     #negate x

absab:  abs $a0,$a0     #get absolute value for a and b
        abs $a1,$a1

	jal divide
	move $t0,$v0    # save result in t0

        bltz $a3,negt   #if x < 0, negate t0
        j ansr          #if x !< 0, jump to ansr
negt:   neg $t0,$t0     #negate t0

ansr:   la $a0,ans     # display "a x b = "
        li $v0,4
        syscall

        move $a0,$t0   # display returned result
        li $v0,1
        syscall

        la $a0,endl    # display crlf
        li $v0,4
        syscall

	jal again

        li $v0,10      # EOP
        syscall

################ divide method ####################
# a0 - holds a,the parameter sent to the method #
# a1 - holds b                                  #
# v0 - holds the returned result, (a / b)       #
#################################################

divide: beqz $a1,undef          #if b = 0, print "!Undefined"
        sub $sp,$sp,12          # push registers onto stack
        sw $a0,0($sp)
        sw $a1,4($sp)
        sw $ra,8($sp)


	beq $a0,$a1,one        #if a = b, return one
        blt $a0,$a1,zero       #if a < b, return zero
        bgt $a0,$a1,abgr       #if a > b, calculate

undef:	la $a0,error
	li $v0,4
	syscall
	j again

one:    li $v0,1
        j divret

zero:   li $v0,0
        j divret

abgr:   sub $a0,$a0,$a1         # parameter = a-b
        jal divide	        # compute divide(a-b,b)
        addi $v0,$v0,1          # save compute

divret: lw $a0,0($sp)           # restore registers from stack
        lw $a1,4($sp)
        lw $ra,8($sp)
        add $sp,$sp,12

        jr $ra                   # return

again:	la $a0,aprompt
	li $v0,4
	syscall

	li $v0,5
	syscall

	beq $v0,1,begin

        li $v0,10      # EOP
        syscall

        .data
prompt: .asciiz "Enter the numbers to divide: "
aprompt:.asciiz "Do you want to run this program again? (Yes = 1, No = 0)"
error:	.asciiz "!Undefined \n"
ans:    .asciiz "a / b = "
endl:   .asciiz "\n"

######### Sample Output##########
#Enter the numbers to divide: 4
#Enter the numbers to divide: -4
#a / b = -1
#Do you want to run this program again? (Yes = 1, No = 0)1
#Enter the numbers to divide: -4
#Enter the numbers to divide: 4
#a / b = -1
#Do you want to run this program again? (Yes = 1, No = 0)1
#Enter the numbers to divide: 4
#Enter the numbers to divide: 4
##a / b = 1
#Do you want to run this program again? (Yes = 1, No = 0)1
#Enter the numbers to divide: -4
#Enter the numbers to divide: -4
#a / b = 1
#Do you want to run this program again? (Yes = 1, No = 0)1
#Enter the numbers to divide: 4
#Enter the numbers to divide: 0
#!Undefined
#Do you want to run this program again? (Yes = 1, No = 0)1
#Enter the numbers to divide: 0
#Enter the numbers to divide: 4
#a / b = 0
#Do you want to run this program again? (Yes = 1, No = 0)0

#################################