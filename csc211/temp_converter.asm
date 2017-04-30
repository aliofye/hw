########### cel2fah.asm on p. 41-42 ############
# Ali Morshid                                  #
# temp_converter.asm                           #
# Description                                  #
#     Program to convert celsius to fahrenheit #
# Program Logic                                #
# 1.  prompt for type of conversion needed     #
# 2.  prompt to enter a temperature in c/f     #
# 3.  enter the temperature                    #
# 4.  calculate the temperature conversion     #
# 5.  display the temperature as converted     #
# 6.  ask if the user wants to run the program #
# -again                                       #
################################################

        .text
        .globl __start
__start:

begin:  la $a0,prompt    #display "Convert from celsius or fahrenheit? (0=c, 1=f):"
        li $v0,4
        syscall

        li $v0,5
        syscall

        beq $v0,1,fah    #if $v0 == 1, branch to subroutine fah
        beq $v0,0,cel    #if $v0 == 2, branch to subroutine cel
	ble $v0,-1,invld
	bge $v0,2,invld





cel:    la $a0,prompt1     # display "Enter temperature (Celsius):"
        li $v0,4
        syscall

        li $v0,5          # enter temperature -> v0
        syscall

        mul $t0, $v0, 9   # 9*temperature
        div $t0, $t0, 5   # 9*temperature/5
        add $t0, $t0, 32  # 9*temperature/5 + 32 -> t0

        la $a0, ans1      # display "The Temperature in Fahrenheit is "
        li $v0,4
        syscall

        move $a0,$t0      # t0 -> a0 for display
        li  $v0,1         # display temperature
        syscall

        la $a0,endl       # display cr/lf
        li $v0,4
        syscall

        la $a0,again      # display "Would you like to start the program again? (0=no, 1=yes):"
        li $v0, 4
        syscall

        li $v0, 5         # 0/1 ----> $v0
        syscall

        beq $v0, 1, loop  #if $v0 == 1, branch to subroutine loop, loop then jumps to subroutine begin
        beq $v0, 0, endCel   #if $v0 == 0, branch to subroutine endCel, and promptly end the program
	ble $v0,-1,error
	bge $v0,2,error

endCel: li $v0,10         # EOP
        syscall




fah:    la $a0,prompt2     # display "Enter temperature (Fahrenheit):"
        li $v0,4
        syscall

        li $v0,5          # enter temperature -> v0
        syscall

        sub $t0, $v0, 32  # temperature - 32
        mul $t0, $t0, 5   # temperature - 32 * 5
        div $t0, $t0, 9   # (temperature - 32 * 5) / 9 -> t0

        la $a0, ans2      # display "The Temperature in Fahrenheit is "
        li $v0,4
        syscall

        move $a0,$t0      # t0 -> a0 for display
        li  $v0,1         # display temperature
        syscall

        la $a0,endl       # display cr/lf
        li $v0,4
        syscall

ask:    la $a0,again      # display "Would you like to start the program again? (0=no, 1=yes):"
        li $v0, 4
        syscall

        li $v0, 5         # 0/1 ----> $v0
        syscall

        beq $v0, 1, loop   #if $v0 == 1, branch to subroutine loop, loop then jumps to subroutine begin
        beq $v0, 0, endFah #if $v0 == 0, branch to subroutine endFah, and promptly end the program
	ble $v0,-1,error
	bge $v0,2,error

endFah: li $v0,10         # EOP
        syscall

loop:  j begin

error: la $a0,prompt3
       li $v0,4
       syscall

       j ask

invld: la $a0,prompt3
       li $v0,4
       syscall

       j begin



.data

prompt:  .asciiz "Convert from celsius or fahrenheit? (0=c, 1=f):\n"
prompt1: .asciiz "Enter temperature (Celsius): "
prompt2: .asciiz "Enter temperature (Fahrenheit): "
prompt3: .asciiz "Invalid input\n"
again:   .asciiz "Would you like to start the program again? (0=no, 1=yes):\n"
ans1:    .asciiz "The Temperature in Fahrenheit is: "
ans2:    .asciiz "The Temperature in Celsius is: "
endl:    .asciiz "\n"


######################output###############################
# Convert from celsius or fahrenheit? (0=c, 1=f):
# 0
# Enter temperature (Celsius): 0
# The Temperature in Fahrenheit is: 32
# Would you like to start the program again? (0=no, 1=yes):
# 1
# Convert from celsius or fahrenheit? (0=c, 1=f):
# 1
# Enter temperature (Fahrenheit): 32
# The Temperature in Celsius is: 0
# Would you like to start the program again? (0=no, 1=yes):
# 1
# Convert from celsius or fahrenheit? (0=c, 1=f):
# 5
# Invalid input
# Convert from celsius or fahrenheit? (0=c, 1=f):
# 1
# Enter temperature (Fahrenheit): 32
# The Temperature in Celsius is: 0
# Would you like to start the program again? (0=no, 1=yes):
# 5
# Invalid input
# Would you like to start the program again? (0=no, 1=yes):
# 0
