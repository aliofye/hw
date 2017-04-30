########### dectohexandbin.asm on p. 76-78 #############
#1- prompt user for a base10 integer
#2- make two copies of the input to convert to hexidecimal and binary
#3- convert and print
#4- prompt user for another number
       .text
       .globl main

main:

begin:	la $a0,prompt   # display prompt on terminal
        li $v0,4
        syscall

        li $v0,5        # read an integer
        syscall

        move $a0,$v0    # and store it in a0 for transfer
	move $t0,$v0	#store a copy of $v0 to use in bin

        jal hex

	move $a0,$t0

	jal bin

	jal again

        li $v0,10       # eop
        syscall


hex:    sub $sp,$sp,24  # push registers onto stack
        sw $a0,0($sp)
        sw $s0,4($sp)
        sw $s1,8($sp)
        sw $s2,12($sp)
        sw $s3,16($sp)
        sw $ra,20($sp)

        move $s2,$a0    # transfer argument

        la $a0, ans1    # display the string before result
        li $v0,4
        syscall

        li $s0,8        # eight hex digits in word
        la $s3,result   # answer string set up here

loop:   rol $s2,$s2,4   # start with left most digit
        and $s1,$s2,0xf # mask one digit in s2 and place results in s1
        ble $s1,9,print # is s1 <= 9, if so go to print
        add $s1,$s1,7   # if not add 7 to get to A..F

print:  add $s1,$s1,48  # add 48 (30 hex) to get ascii character
        sb $s1,($s3)    # store the byte in result - (s3) points to result
        add $s3,$s3,1   # s3++
        add $s0,$s0,-1  # s0--
        bnez $s0,loop   # repeat loop as long as s0 != 0
        la $a0,result   # display result on terminal

        li  $v0,4
        syscall

        la $a0,endl     # display cr/lf
        li $v0,4
        syscall

        lw $a0,0($sp)   # pop registers from stack
        lw $s0,4($sp)
        lw $s1,8($sp)
        lw $s2,12($sp)
        lw $s3,16($sp)
        lw $ra,20($sp)
        add $sp,$sp,24

        jr $ra          # return

########################################################################

bin:    sub $sp,$sp,24  # push registers onto stack
        sw $a0,0($sp)
        sw $s0,4($sp)
        sw $s1,8($sp)
        sw $s2,12($sp)
        sw $s3,16($sp)
        sw $ra,20($sp)

        move $s2,$a0    # transfer argument

        la $a0,ans2     # display the string before result
        li $v0,4
        syscall

        li $s0,32       # 32 digits in word
        la $s3,result2   # answer string set up here

bloop:  rol $s2,$s2,1   # start with left most digit
        and $s1,$s2,0x1 # mask one digit in s2 and place results in s1


	add $s1,$s1,48  # add 48 (30 hex) to get ascii character
        sb $s1,($s3)    # store the byte in result - (s3) points to result
        add $s3,$s3,1   # s3++
        add $s0,$s0,-1  # s0--
        bnez $s0,bloop  # repeat loop as long as s0 != 0
        la $a0,result2  # display result on terminal

        li  $v0,4
        syscall

        la $a0,endl     # display cr/lf
        li $v0,4
        syscall

        lw $a0,0($sp)   # pop registers from stack
        lw $s0,4($sp)
        lw $s1,8($sp)
        lw $s2,12($sp)
        lw $s3,16($sp)
        lw $ra,20($sp)
        add $sp,$sp,24

        jr $ra          # return

	again:	la $a0,aprompt
	li $v0,4
	syscall

	li $v0,5
	syscall

	beq $v0,1,begin

	jr $ra

        .data

result: .space 8
	.space 4
result2:.space 32
endl:   .asciiz "\n"
prompt: .asciiz "Enter number to convert: "
aprompt:.asciiz "Do you want to run this program again? (Yes = 1, No = 0)"
ans1:   .asciiz "The number in hexidecimal is "
ans2:   .asciiz "The number in binary is "


################# OUTPUT ################
# Enter decimal number: 10
#The number in hexidecimal is 0000000A
#The number in binary is 00000000000000000000000000001010
#
#Do you want to run this program again? (Yes = 1, No = 0)1
#Enter decimal number: 15
#The number in hexidecimal is 0000000F
#The number in binary is 00000000000000000000000000001111
#
#Do you want to run this program again? (Yes = 1, No = 0)1
#Enter decimal number: 0
#The number in hexidecimal is 00000000
#The number in binary is 00000000000000000000000000000000
#
#Do you want to run this program again? (Yes = 1, No = 0)1
#Enter decimal number: 2001
#The number in hexidecimal is 000007D1
#The number in binary is 00000000000000000000011111010001
#
#Do you want to run this program again? (Yes = 1, No = 0)0
##########################################
