## max.asm --- determine the largest of three floats
## PROGRAM LOGIC
## 1- prompt user for A,B,C
## 2- compare A,B,C to each other to indentify the largest values
## 3- print largest values
## 4- ask user if they want to input another set of numbers
## 5- if no, END PROGRAM
        .text
        .globl main

main:


begin:	#Prompt for A#
	la $a0,promptA
	li $v0,4
	syscall

	li $v0,6
	syscall

	s.s  	$f0,A		#store $f0 in A

	#Prompt for B#
	la $a0,promptB
	li $v0,4
	syscall

	li $v0,6
	syscall

	s.s  	$f0,B		#store $f0 in B

	#Prompt for C#
	la $a0,promptC
	li $v0,4
	syscall

	li $v0,6
	syscall

	s.s  	$f0,C		#store $f0 in C



        # get the values into registers
        l.s     $f0,A 		#load A at $f0
        l.s     $f2,B		#load B at $f2
	l.s	$f3,C		#load C at $f3

        #check from left side
chkA:	c.lt.s  $f2,$f0          # is B < A?
        bc1f    chkB
        c.lt.s	$f3,$f0		 # is C < A?
	bc1t    printA           # yes -- print A
        bc1f    chkB

chkB:	c.lt.s  $f0,$f2          # is A < B?
        bc1f    chkC
	c.lt.s	$f3,$f2		 # is C < B?
        bc1t    printB           # yes -- print B
        bc1f    chkC


chkC:	c.lt.s  $f0,$f3          # is A < C?
        bc1f    equal
	c.lt.s	$f2,$f3		 # is B < C?
        bc1t    printC           # yes -- print C
        bc1f    equal



equal:  la      $a0,EQmsg        # otherwise
        li      $v0,4            # they are equal
        syscall
        mov.s   $f12,$f0         # print one of them
        b       prtnum

printA: la      $a0,Amsg         # message for A
        li      $v0,4
        syscall
        mov.s   $f12,$f0         # print A
        b       prtnum

printB: la      $a0,Bmsg         # message for B
        li      $v0,4
        syscall
        mov.s   $f12,$f2         # print B
        b       prtnum

printC: la      $a0,Cmsg         # message for C
        li      $v0,4
        syscall
        mov.s   $f12,$f3         # print C
        b       prtnum

prtnum: li      $v0,2            # print single precision
                                 # value in $f12
        syscall
        la      $a0,newl
        li      $v0,4            # print new line
        syscall

	la $a0,again		 # prompt user to run program again
	li $v0,4
	syscall

	li $v0,5
	syscall


	beq $v0,1,begin

	jr      $ra              # return to OS

        .data

A:      .float  0.000
B:      .float  0.000
C:	.float 	0.000
promptA:.asciiz "Enter A:"
promptB:.asciiz "Enter B:"
promptC:.asciiz "Enter C:"
again:  .asciiz "Do you want to try another set of numbers? (yes = 1, no = 0)"
Amsg:   .asciiz "\nA is largest: "
Bmsg:   .asciiz "\nB is largest: "
Cmsg:	.asciiz "\nC is largest: "
EQmsg:  .asciiz "\nThey are equal: "
newl:   .asciiz "\n"



############################output###############################################

# Enter A:1
# Enter B:2
# Enter C:3

# C is largest: 3.00000000
# Do you want to try another set of numbers? (yes = 1, no = 0)1
# Enter A:3
# Enter B:2
# Enter C:1

# A is largest: 3.00000000
# Do you want to try another set of numbers? (yes = 1, no = 0)1
# Enter A:1
# Enter B:3
# Enter C:2

# B is largest: 3.00000000
# Do you want to try another set of numbers? (yes = 1, no = 0)1
# Enter A:1
# Enter B:1
# Enter C:1

# They are equal: 1.00000000
# Do you want to try another set of numbers? (yes = 1, no = 0)1
# Enter A:2
# Enter B:2
# Enter C:2

# They are equal: 2.00000000
# Do you want to try another set of numbers? (yes = 1, no = 0)0
