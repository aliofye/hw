#############################################################
# Ali Morshid                                               #
# quadratic.asm                                             #
# Description                                               #
#     A quadratic formula program                           #
# Program Logic                                             #
#1- ask for the coefficients of the quadratic: A, B and C   #
#2- input A and place it in t0                              #
#3- input B and place it in t1                              #
#4- input C and place it in t2                              #
#5- ask for lower and upper bounds of the domain variable x #
#6- input the lower bound and place it in t3                #
#7- input the upper bound and place it in t4                #
#8- calculate the range variable t5 = (A * t3 + B) * t3 + C #
#9- display the ordered pair x and y                        #
#10- t3 = t3 + 1                                            #
#11- if (t3 <= t4) goto step 8                              #
#12- continue again (y/n)?                                  #
#13- if yes goto step 1                                     #
#EOP                                                        #
#############################################################


.globl main
.text


main:

begin:  la $a0,promptA          #$a0 = promptA
        li $v0,4                #$v0 = 4, displays "Please enter any value for A:"
        syscall

        li $v0,5                #$v0 = 5, indicates input of integer
        syscall

        sw $v0,A                #$v0 = A, indicates storing of input


        la $a0,promptB
        li $v0,4                #$v0 = 4, displays "Please enter any value for B:"
        syscall

        li $v0,5
        syscall

        sw $v0,B

        la $a0,promptC
        li $v0,4                #$v0 = 4, displays "Please enter any value for C:"
        syscall

        li $v0,5
        syscall

        sw $v0,C


        la $a0,prmtLwBnd
        li $v0,4                #$v0 = 4, displays "Please enter lower bound for x:"
        syscall

        li $v0,5
        syscall

        sw $v0,xLow

        la $a0,prmtUpBnd        #$v0 = 4, displays "Please enter upper bound for x:"
        li $v0,4
        syscall

        li $v0,5
        syscall

        sw $v0,xUp

        lw $t0,A                #$t0 = A, lw indicates loading of A into $t0 like wise for the next 4 lines
        lw $t1,B
        lw $t2,C
        lw $t3,xLow
        lw $t4,xUp


loop:   mul $t5,$t0,$t3        #$t5 = (A*x)
        add $t5,$t5,$t1        #$t5 = (A*x)+B
        mul $t5,$t5,$t3        #$t5 = ((A*x)+B)*x
        add $t5,$t5,$t2        #$t5 = (((A*x)+B)*x)+C

        la $a0,opnp
        li $v0,4               #$v0 = 4, displays "("
        syscall

        move $a0,$t3
        li $v0, 1              #$v0 = 1, displays x coordinate
        syscall

        la $a0,comma
        li $v0,4               #$v0 = 4, displays ","
        syscall

        move $a0,$t5
        li $v0,1               #$v0 = 1, displays y coordinate
        syscall

        la $a0,clsp
        li $v0,4               #$v0 = 4, displays ")" to achieve a final output of (x,y)
        syscall

        la $a0,endl
        li $v0,4               #$v0 = 4, adds an empty line to output
        syscall

        addi $t3,$t3,1         #increment x value to find next y value
        ble $t3,$t4,loop       #if the lower bound is <= to the upper bound loop to the y value calculation with the incremented x value
        syscall

again:  la $a0,prompt          #ask the user if they want to use the program again
        li $v0,4
        syscall

        li $v0,5
        syscall

        beq $v0,1,begin        #if the user inputs 1 branch to the beginning of the program
        beq $v0,0,end          #if the user inputs 0 branch to the end of the program
        ble $v0,-1,invld       #if the user inputs any number <= to -1 branch to invld
        bge $v0,2,invld        #if the user inputs any number >= to 2 branch to invld


invld:  la $a0,err             #displays "Invalid input!"
        li $v0,4
        syscall

        j again                #jumps to again


end:    li $v0,10
        syscall


.data

prompt:       .asciiz "\nWould you like to start the program again? (0=no, 1=yes):\n"
promptA:      .asciiz "\nPlease enter any value for A:\n"
promptB:      .asciiz "\nPlease enter any value for B:\n"
promptC:      .asciiz "\nPlease enter any value for C:\n"
prmtUpBnd:    .asciiz "\nPlease enter upper bound for x:\n"
prmtLwBnd:    .asciiz "\nPlease enter lower bound for x:\n"
err:          .asciiz "\nInvalid input!\n"
endl:         .asciiz "\n"
comma:        .asciiz ","
opnp:         .asciiz "("
clsp:         .asciiz ")"
A:            .word 0
B:            .word 0
C:            .word 0
xUp:          .word 0
xLow:         .word 0







#######################output##########################

#Please enter any value for A:
#1

#Please enter any value for B:
#-1

#Please enter any value for C:
#-6

#Please enter lower bound for x:
#-5

#Please enter upper bound for x:
#5
#(-5,24)
#(-4,14)
#(-3,6)
#(-2,0)
#(-1,-4)
#(0,-6)
#(1,-6)
#(2,-4)
#(3,0)
#(4,6)
#(5,14)


#Would you like to start the program again? (0=no, 1=yes):
#5

#Invalid input!

#Would you like to start the program again? (0=no, 1=yes):
#1

#Please enter any value for A:
#1

#Please enter any value for B:
#-1

#Please enter any value for C:
#-6

#Please enter lower bound for x:
#-2

#Please enter upper bound for x:
#-1
#(-2,0)
#(-1,-4)


#Would you like to start the program again? (0=no, 1=yes):
#0
