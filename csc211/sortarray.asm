## Author: Ali Morshid
## numberarray.asm --- manipulate an array of numbers
## MAIN PROGRAM LOGIC (Look at the lines of the subprograms for logic specific to those programs) ##
## 1-Call the input subprogram, which asks for the number of numbers to be entered and then adds each inputted number to the index of the array
## 2-Call the output subprogram, of which it in turn outputs the numbers in the order they were inputted
## 3-Call the decending sort subprogram, of which it in turn sorts the set of numbers in decending order
## 4-Call the output subprogram, of which it in turn outputs the numbers in the order they were inputted
## 5-Call the acending sort subprogram, of which it in turn sorts the set of numbers in acending order
## 6-Call the output subprogram, of which it in turn outputs the numbers in the order they were inputted
## 7-Call the again subprogram, of which it in turn asks the user if they want to rerun the program

        .text
        .globl __start

__start:

begin:	jal input
	jal output
	jal dsort
	jal output
        jal asort
	jal output
	jal again

	li $v0,10
	syscall


input:  la $a0,prompt           #prompt user for the number of numbers to be entered
	li $v0,4
	syscall

	li $v0,5
	syscall

        bgt $v0,20,input	#if the number of numbers is bigger than 20, prompt again
        blt $v0,1,input		#if the number of numbers is less than 1, prompt again

        move $t1,$v0		#t1 = $v0
	sw $t1,count		#count = $t1

	li $t0,0		#$t0 = 0
        li $t2,0		#$t2 = 0

iloop:	la $a0,nprompt		#prompt user for the numbers in the array
	li $v0,4
	syscall

	li $v0,5		#take input from user in the form of a word (int)
	syscall

	sw $v0,array($t0)	#save the inputted number to the array at byte $t0

	addi $t0,$t0,4		#increment $t0 by 4
	addi $t2,$t2,1		#increment #t2 by 1

	blt $t2,$t1,iloop	#if $t2 < $t1 branch to iloop

        sw $t0,index		#index = $t0

	jr $ra			#go back to the main program


output: li $t0,0		#$t0 = 0
        li $t1,0
	lw $t1,index		#$t1 = index

        la $a0,line		#print a top line for better visibility
        li $v0,4
        syscall

ploop:  lw $a0,array($t0)	#load number at byte $t0 from array into $a0
        li $v0,1
        syscall

        la $a0,newl		#print a new line between numbers
        li $v0,4
        syscall

        addi $t0,$t0,4		#increment $t0 by 4

        blt $t0,$t1,ploop	#if $t0 < $t1, branch to ploop

        la $a0,line		#print a bottom line for better visibility
        li $v0,4
        syscall

        jr $ra			#go back to main program


dsort:  li $t2,0
	li $t3,0
	lw $t2,index            # t2 = count    (i counter)
        addi $t3,$t2,-4         # t2 = count-1,  t3 = t2  (j counter)


dsloop: li $t4,0
	li $t5,0
	lw $t4,array($t2)       # t4 = a[i]
        lw $t5,array($t3)       # t5 = a[j]

        ble $t4,$t5,dnoswap     # if (a[i] <= a[j]) do not swap
        bgt $t4,$t5,dswap       # if (a[i] > a[j]) swap

dswap:  li $t6,0
	move $t6,$t5            # swap a[i] and a[j]
        sw $t4,array($t3)
        sw $t6,array($t2)


dnoswap:addi $t3,$t3,-4         # j count --
        bgez  $t3,dsloop        # if j count is bigger than -4 go back to sort loop

        addi $t2,$t2,-4         # i count --
        move $t3,$t2            # j count = i count

        beqz $t2,dendsort       # if i count = 0 sort is complete

        j dsloop                # jump to sort loop

dendsort:jr $ra                 # return to main procedure

asort:  li $t2,0
	li $t3,0
	lw $t2,index            # t2 = count    (i counter)
	addi $t2,$t2,-4
        addi $t3,$t2,-4         # t2 = count-1,  t3 = t2  (j counter)


asloop: li $t4,0
	li $t5,0
	lw $t4,array($t2)       # t4 = a[i]
        lw $t5,array($t3)       # t5 = a[j]

        blt $t4,$t5,aswap       # if (a[i] < a[j]) swap
        bge $t4,$t5,anoswap     # if (a[i] >= a[j]) do not swap

aswap:  li $t6,0
	move $t6,$t5            # swap a[i] and a[j]
        sw $t4,array($t3)
        sw $t6,array($t2)


anoswap:addi $t3,$t3,-4         # j count --
        bgez  $t3,asloop        # if j count is bigger than -4 go back to sort loop



        addi $t2,$t2,-4         # i count --
        move $t3,$t2            # j count = i count

        beqz $t2,aendsort       # if i count = 0 sort is complete


        j asloop                # jump to sort loop

aendsort:jr $ra                 # return to main procedure


again:  la $a0,continue         #prompt user to enter another set of numbers
	li $v0,4
	syscall

	li $v0,5                #take input
	syscall

        beq $v0,1,begin          #if input is equal to 1, rerun the program
        bgt $v0,1,again         #if input is bigger than 1, reprompt for a valid input
        blt $v0,-1,again        #if input is less than 1, reprompt for a valid input

        jr $ra                  # return to main procedure

        .data

count:      .word 0
index:      .word 0
array:      .space 80

prompt: .asciiz "Enter the number of numbers to be entered (max 20): "
nprompt:.asciiz "Enter number:"
continue:.asciiz "Do you want to try another set of numbers? (yes = 1, no = 0)"
newl:   .asciiz "\n"
line:   .asciiz "---------------------------\n"


#output#
#=========================
#Enter the number of numbers to be entered (max 20): 3
#Enter number:1
#Enter number:2
#Enter number:3
#-------------------------------------
#1
#2
#3
#-------------------------------------
#-------------------------------------
#3
#2
#1
#-------------------------------------
#-------------------------------------
#1
#2
#3
#-------------------------------------
#Do you want to try another set of numbers? (yes = 1, no = 0)1
#Enter the number of numbers to be entered (max 20): 50
#Enter the number of numbers to be entered (max 20): 5
#Enter number:15
#Enter number:30
#Enter number:10
#Enter number:5
#Enter number:100
#-------------------------------------
#15
#30
#10
#5
#100
#-------------------------------------
#-------------------------------------
#100
#30
#15
#10
#5
#-------------------------------------
#-------------------------------------
#5
#10
#15
#30
#100
#-------------------------------------
#Do you want to try another set of numbers? (yes = 1, no = 0)0
##end output#
