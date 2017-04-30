## Author: Ali Morshid
## numberarray.asm --- manipulate an array of numbers
## 1- Ask for the number of numbers to be entered and set it to max
## 2- load max into $t0
## 3- load 0 into $t1 as index
## 4- load 0 into $t2 as counter and initialize
## 5- prompt for the set of numbers
## 6- save inputted number into array at the index
## 7- increment the index and the count at $t2
## 8- save the incremented $t1 into index for use in the print loop as a max
## 9- check if the count is less than the max, if yes, then loop, if no, then continue to print the numbers
## 10-load the index at $t0 to act as the max for the print loop
## 11-load 0 at $t1 as counter
## 12-print number at byte $t1
## 13-increment $t1
## 14-if pindex is less than index, loop, if not continue to step 15
## 15-ask the user if they wish to enter another set of numbers
## 16-if 1 loop the program if not, continue
## 17-EOP

        .text
        .globl main

main:


begin:  la $a0,prompt           #Prompt for max
	li $v0,4
	syscall

	li $v0,5                #ask for input
	syscall

        bgt $v0,20,begin


        move $t0,$v0              #load max into $t0
        li $t1,0                  #load index into $t1
        li $t2,0                  #load count into $t2



loop:   la $a0,promptN          #prompt for numbers
        li $v0,4
        syscall

        li $v0,5                #ask for input
	syscall

        sw $v0,array($t1)       #save inputted number into array at byte $t1

        addi $t1,$t1,4          #increment index
        addi $t2,$t2,1          #increment count

        sw $t1,index            #save $t1 into index

        blt $t2,$t0,loop        #if count is < max, then branch to loop


        lw $t0,index            #load index into $t0
        li $t1,0                #load pindex into $t1

        la $a0,startu
        li $v0,4
        syscall

        la $a0,newl            #add a newline
        li $v0,4
        syscall

print:  lw $a0, array($t1)      #print byte at $t1 from array into $a0
        li $v0,1                #one indicates the printing of an integer
        syscall

        la $a0, newl            #add a newline
        li $v0,4
        syscall

        addi $t1,$t1,4          #increment pindex by 1
        blt $t1,$t0,print

        la $a0,endu
        li $v0,4
        syscall

        la $a0,newl            #add a newline
        li $v0,4
        syscall

sort:   lw $t0,array($t2)
        lw $t1,array($t3)

        lw $t2,index
        addi $t3,$t2,-4


sloop:  lw $t4,array($t2)
        lw $t5,array($t3)

        ble $t4,$t5,noswap

swap:   move $t6,$t5
        sw $t4,array($t3)
        sw $t6,array($t2)


noswap: lw $t1,array($t2)
        addi $t3,$t3,-4
        bne $t3,0,sloop

        addi $t2,$t2,-4
        move $t3,$t2
        beq $t2,0,send

        lw $t1,array($t2)

        j sloop

send:   lw $t0,index            #load index into $t0
        li $t1,0                #load pindex into $t1

        la $a0,starts
        li $v0,4
        syscall

        la $a0,newl            #add a newline
        li $v0,4
        syscall

sprint: lw $a0, array($t1)      #print byte at $t1 from array into $a0
        li $v0,1                #one indicates the printing of an integer
        syscall

        la $a0,newl            #add a newline
        li $v0,4
        syscall

        addi $t1,$t1,4          #increment pindex by 1
        blt $t1,$t0,sprint

        la $a0,ends
        li $v0,4
        syscall

        la $a0,again            #prompt the user to enter another set of numbers
        li $v0,4
        syscall

        li $v0,5
        syscall

        beq $v0,1,begin         #if the user inputs 1, branch to begin

        li $v0,10               #EOP
        syscall



        .data

A:      .word  0

prompt: .asciiz "Enter the number of numbers to be entered (max 20): "
promptN:.asciiz "Enter number:"
again:  .asciiz "Do you want to try another set of numbers? (yes = 1, no = 0)"
max:    .word 0
index:  .word 0
pindex: .word 0
count:  .word 0
array:	.space	80
newl:   .asciiz "\n"
startu:   .asciiz "---------Start Unsorted Array----------"
endu:   .asciiz "---------End Unsorted Array----------"
starts:   .asciiz "---------Start Sorted Array----------"
ends:   .asciiz "---------End Sorted Array----------"


#output
#Enter the number of numbers to be entered: (max 20)21
#Enter the number of numbers to be entered: (max 20)21
#Enter the number of numbers to be entered: (max 20)30
#Enter the number of numbers to be entered: (max 20)10
#Enter number:123
#Enter number:1234
#Enter number:12345
#Enter number:114
#Enter number:2135
#Enter number:124
#Enter number:21314
#Enter number:01314
#Enter number:134131
#Enter number:1212
#123
#1234
#12345
#114
#2135
#124
#21314
#1314
#134131
#1212
#Do you want to try another set of numbers? (yes = 1, no = 0)1
#Enter the number of numbers to be entered: (max 20)21
#Enter the number of numbers to be entered: (max 20)1
#Enter number:1
#1
#Do you want to try another set of numbers? (yes = 1, no = 0)0
