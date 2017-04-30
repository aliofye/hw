#########################################
#  Ali Morshid                          #
# multi.asm - multi(a,b) = a x b          #
# Example of a recursive program        #
#                                       #
#  // Java Version:  mult.java          #
#  public static int mult(int a, int b) #
#  {                                    #
#    if (b == 1) return a;              #
#    else return (a + mult(a, b-1));    #
#  }                                    #
#########################################

        .text
        .globl main
main:

begin:  la $a0,prompt  # display "Enter the numbers to multiply: "
        li $v0,4
        syscall

        li $v0,5       # enter a
        syscall

        move $t0,$v0   # call mult method

	la $a0,prompt  # display "Enter the numbers to multiply: "
        li $v0,4
        syscall

        li $v0,5       # enter a
        syscall


	move $a0,$t0
	move $a1,$v0   # call mult method

	beqz $a1,swap
	bgtz $a1,jmult
	bltz $a1,chka
chka:	bgtz $a0,absn
	bltz $a0,absb

absn:	neg $a0,$a0
	abs $a1,$a1

	j jmult

absb:	abs $a0,$a0
	abs $a1,$a1

	j jmult

swap:	move $t0,$a0
	move $a0,$a1
	move $a1,$t0


jmult:	jal multi
	move $t0,$v0   # save result in t0

        la $a0,ans     # display "a x b = "
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

################ fact method ####################
# a0 - holds a,the parameter sent to the method #
# a1 - holds b                                  #
# v0 - holds the returned result, (a x b)       #
#################################################

multi:  sub $sp,$sp,12  # push registers onto stack
        sw $a0,0($sp)
        sw $a1,4($sp)
        sw $ra,8($sp)

        bgt $a1,1,notOne
        move $v0,$a0    #
        j multret

notOne: sub $a1,$a1,1   # parameter = b-1
        jal multi	# compute multi(a,b-1)
        add $v0,$a0,$v0 # save multi(a,b-1)

multret:lw $a0,0($sp)   # restore registers from stack
        lw $a1,4($sp)
        lw $ra,8($sp)
        add $sp,$sp,12

        jr $ra          # return

again:	la $a0,aprompt
	li $v0,4
	syscall

	li $v0,5
	syscall

	beq $v0,1,begin

	jr $ra

        .data
prompt: .asciiz "Enter the numbers to multiply: "
aprompt:.asciiz "Do you want to run this program again? (Yes = 1, No = 0)"
ans:    .asciiz "a x b = "
endl:   .asciiz "\n"

######### Sample Output##########
#Enter the numbers to multiply: -4
#Enter the numbers to multiply: -4
#a x b = 16
#Do you want to run this program again? (Yes = 1, No = 0)1
#Enter the numbers to multiply: -4
#Enter the numbers to multiply: 4
#a x b = -16
#Do you want to run this program again? (Yes = 1, No = 0)1
#Enter the numbers to multiply: 4
#Enter the numbers to multiply: -4
#a x b = -16
#Do you want to run this program again? (Yes = 1, No = 0)1
#Enter the numbers to multiply: 4
#Enter the numbers to multiply: 0
#a x b = 0
#Do you want to run this program again? (Yes = 1, No = 0)1
#Enter the numbers to multiply: 0
#Enter the numbers to multiply: 4
#a x b = 0
#Do you want to run this program again? (Yes = 1, No = 0)1
#Enter the numbers to multiply: -4
#Enter the numbers to multiply: 0
#a x b = 0
#Do you want to run this program again? (Yes = 1, No = 0)1
#Enter the numbers to multiply: 0
#Enter the numbers to multiply: -4
#a x b = 0
#Do you want to run this program again? (Yes = 1, No = 0)0
#################################
