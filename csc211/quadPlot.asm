#############################################################
# Ali Morshid
# quadPlot.asm
# Description
#     A quadratic plot formula program
# Program Logic
# 1.  Enter A, B and C  ($t0,$t1,$t2)
# 2.  Enter x1 and x2   ($t3,$t4)
# 3.  Enter ymax and ymin ($t7,$t6)
# 4.  y = ymax          ($t8 = $t7)
# 5.  x = x1            ($t9 = $t3)
# 6.  f(x) = (Ax+B)x+C
# 7.  if (y == f(x)) display '*' and go to step 11
# 8.  if (x == 0)  display '|' and go to step 11
# 9.  if (y == 0)  display '-' and go to step 11
# 10.  display ' '
# 11.  if (x == x2) display '\n' and go to step 13
# 12.  x++ and go to step 6
# 13.  if (y == ymin) end of program
# 14.  y-- and go to step 5
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


        la $a0,prmtLowX
        li $v0,4                #$v0 = 4, displays "Please enter lower bound for x:"
        syscall

        li $v0,5
        syscall

        sw $v0,xLow

        la $a0,prmtUpX        #$v0 = 4, displays "Please enter upper bound for x:"
        li $v0,4
        syscall

        li $v0,5
        syscall

        sw $v0,xUp

        la $a0,prmtLowY
        li $v0,4                #$v0 = 4, displays "Please enter lower bound for x:"
        syscall

        li $v0,5
        syscall

        sw $v0,yLow

        la $a0,prmtUpY       #$v0 = 4, displays "Please enter upper bound for x:"
        li $v0,4
        syscall

        li $v0,5
        syscall

        sw $v0,yUp

        lw $t0,A                #$t0 = A, lw indicates loading of A into $t0 like wise for the next 4 lines
        lw $t1,B
        lw $t2,C
        lw $t3,xLow
        lw $t4,xUp
        lw $t6,yLow
        lw $t7,yUp



        move $t8,$t7           #y = ymax
mveX:   move $t9,$t3           #x = x1


func:   mul $t5,$t0,$t9        #$t5 = (A*x)
        add $t5,$t5,$t1        #$t5 = (A*x)+B
        mul $t5,$t5,$t9        #$t5 = ((A*x)+B)*x
        add $t5,$t5,$t2        #$t5 = (((A*x)+B)*x)+C


        beq $t8,$t5,dotgrph    #if (y == f(x)) display '*'
        beq $t9,0,bargrph      #if (x == 0)  display '|'
        beq $t8,0,dshgrph      #if (y == 0)  display '-'

        la $a0,blnk            #display ' '
        li $v0,4
        syscall



chkx:   beq $t9,$t4,elgrph     #if (x == x2) display '\n'
        addi $t9,$t9,1         #increment inside loop counter

        j func                 #jump to f(x)


chky:   beq $t8,$t6,again      #if (y == ymin) branch to loop prompt "again"
        sub $t8,$t8,1          #decrement outside loop counter

        j mveX                 #jump tp x = x1



dotgrph:la $a0,dot             #display "*"
        li $v0,4
        syscall

        j chkx                 #jump to if (x == x2)

bargrph:la $a0,bar             #display "|"
        li $v0,4
        syscall

        j chkx                 #jump to if (x == x2)

dshgrph:la $a0,dash            #display "-"
        li $v0,4
        syscall

        j chkx                 #jump to if (x == x2)

elgrph: la $a0,endl            #display "\n"
        li $v0,4
        syscall

        j chky                 #jump to if (y == ymin)




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
prmtUpX:      .asciiz "\nPlease enter upper bound for x:\n"
prmtLowX:     .asciiz "\nPlease enter lower bound for x:\n"
prmtUpY:      .asciiz "\nPlease enter upper bound for y:\n"
prmtLowY:     .asciiz "\nPlease enter lower bound for y:\n"
err:          .asciiz "\nInvalid input!\n"
qHead:        .asciiz "\n*******Quadratic Plot*******\n"
dot:          .asciiz "*"
endl:         .asciiz "\n"
bar:          .asciiz "|"
dash:         .asciiz "-"
blnk:         .asciiz " "
A:            .word 0
B:            .word 0
C:            .word 0
xUp:          .word 0
xLow:         .word 0
yUp:          .word 0
yLow:         .word 0








#######################output##########################


# Please enter any value for A:
# 1

# Please enter any value for B:
# -1

# Please enter any value for C:
# -6

# Please enter lower bound for x:
# -10

# Please enter upper bound for x:
# 10

# Please enter lower bound for y:
# -10

# Please enter upper bound for y:
# 10
#          |
#          |
#          |
#          |
#       *  |   *
#          |
#          |
#          |
#          |
#          |
#--------*-|--*-------
#          |
#          |
#          |
#         *| *
#          |
#          **
#          |
#          |
#          |
#          |

# Would you like to start the program again? (0=no, 1=yes):
# 0



#Would you like to start the program again? (0=no, 1=yes):
#0
