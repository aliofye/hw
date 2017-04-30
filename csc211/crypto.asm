#######################crypto.asm##################################
# Crypto
#
# Authors:Ali Morshid && Alex Wickert
#
# Description:
#
# Encrypt a string of characters using the linear function y = a-x+b.
# Also, decrypt the encrypted string using the inverse function x = a+x-b.
# Input the string and the values of a and b.
#
# Theory:
#
# A B C D E F G H I J K L M N O P Q R S T U V W X Y Z space 0 1 2 3 4 5 6 7 8 9
# 1 2 3 4 5 6 7 8 9 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2   2   2 2 3 3 3 3 3 3 3 3
#                   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6   7   8 9 0 1 2 3 4 5 6 7
#
# Example:  a = 1, b = 2 => y = x + 2
#
# Thus 1=>3, 2=>4, 3=>5, etc, 32=>34, 33=>35, 34=>1, 35=>2
# which means A=>C, B=>D, C=>E, . . . , Y=>space, Z=>0,  space=>1,
# and 7=>9, 8=>A and 9=B
#
# Therefore  HELLO BUDDY => JGNNQ1DWFFspace upon encryption.
# Conversely JGNNQ1DWFFspace => HELLO BUDDY upon decryption.

##############################PROGRAM LOGIC###############################
# 1- Ask for the message to be encrypted
# 2- Ask for a and b to act as the key for encryption and decryption
# 3- Count the number of characters in the message and set it to max (to be used in encryption and decryption loops)
# 4- Ask the user for which subprogram to run (encryption/decryption)
# 5- encrypt or decrypt message
# 6- Ask the user if they want to run the program again
############################REGISTERS#####################################
#   message counter registers:
#   $t0 - will be used as the address of the string
#   $t1 - counter to keep track of message length
#   $t2 - individual character from string($t0)
#   $t3 - next address of the string
#
#   encrypt/decrypt program registers:
#   $t0 - the value stored in A from user
#   $t1 - the value stored in B from user
#   $t3 - counter of the array
#   $t4 - holds the current byte from the string to be manipulated
#   $t5 - holds the max string length from the counter
#   $t6 - a catch register to restore a character to its original form if it wont fit into the ascii table
##########################################################################
	.text
        .globl main


main:
###################main program############################################
begin:	jal input               #call input program
        jal count               #call count program

chk:    jal type                #call type program
        beq $v0,1,che           #if program type returns 1, encrypt message
        beq $v0,0,chd           #if program type returns 0, decrypt message
        j chk

che:    jal ncrypt              #call ncrypt program
	j agn

chd:    jal dcrypt              #call dcrypt program

agn:  	jal zero		#call zero program
  	jal again               #call again program

        li $v0,10
        syscall                 #EOP

#########################input############################################
input:  la $a0,prompt           #display message "Enter the message to be encrypted/decrypted:\n" to user
        li $v0,4
        syscall

        la $a0,msg              # a0   address of string
        li $a1,100              # v0 = 8, indicates input of a string
	li $v0, 8               # a1 = 100, indicates string length
        syscall


        la $a0,prompth          #display info message warning user that they will be prompted for 2 keys to encrypt their message
        li $v0,4
        syscall

        la $a0,prompta          #prompt for a (first key)
        li $v0,4
        syscall

        li $v0,5                #input
        syscall

        sw $v0,akey             #save input in akey

        la $a0,promptb          #prompt for b (second key)
        li $v0,4
        syscall

        li $v0,5                #input
        syscall

        sw $v0,bkey             #save input in bkey

        jr $ra                  #return to main program

#######################message counter#####################################
count:  la $t0,msg  	        #t0 = address of string
	li $t1,0	        #t1 = address of counter set to 0

cloop:	lb $t2,($t0)            #load byte at $t2 from $t0
	sub $t3, $t2, 10	#t3 = address of the decremented counter
	beqz $t3,cmove		#branch to step 9
	addi $t0, $t0, 1	#increment address of the str
	addi $t1, $t1, 1	#increment the counter
	j cloop
	syscall

cmove:  sw $t1,max              #save $t1 in max

        jr $ra                  #return to main program

#######################encryption choice##################################
type:   la $a0,prmted           #Asks user if they would like to encrypt of decrypt a message
        li $v0,4
        syscall

        li $v0,5                #read user input and store in $v0
        syscall

        jr $ra                  #return to main program

######################encryption loop#####################################
ncrypt: lw $t5,max              #set up max for nloop
        lw $t0,akey             #set up first key
        lw $t1,bkey             #set up second key
        li $t2,0                #set up array index
        li $t3,0                #set up counter
        li $t6,0                #set up restore register

nloop:  lb $t4,msg($t2)         #take char at byte $t2 from msg

        move $t6,$t4            #make a copy of x to restore if need be
        sub $t4,$t4,$t0         #encrypt using formula y = a-x+b
        add $t4,$t4,$t1

        ble $t4,31,nrstr        #if x is <= 31, that means the character won't be legible to the user so we restore the original one
        bge $t4,127,nrstr       #if x is >= 127, that means the character won't be legible to the user so we restore the original one
        j ngo

nrstr:  move $t4,$t6            #restore original character
ngo:    sb $t4,nmsg($t2)        #save char at byte $t2 from nmsg

        beq $t3,$t5,nprint      #if $t3 = $t5, print character
        addi $t2,$t2,1          #increment $t2
        addi $t3,$t3,1          #increment $t3
        j nloop

nprint: la $a0,nmsg             #print encrypted message
        li $v0,4
        syscall

	la $a0,promptc          #Asks the user if they would like to decrypt their recently encryped message
	li $v0,4
	syscall

	li $v0,5                #reads user input and stores in $v0
	syscall

	beq $v0,1,adcrypt       #if user input is equalk to 1, it will jump to the immediate decryption program

        jr $ra                  #return to main program

#########################immediate decryption loop###################################
adcrypt:lw $t5,max              #set up max for nloop
        sub $t5,$t5,1           #offset the max by one (for some reason the program will only work like so)
        lw $t0,akey             #set up first key
        lw $t1,bkey             #set up second key
        li $t2,0                #set up array index
        li $t3,0                #set up counter
        li $t6,0                #set up restore register

adloop: lb $t4,nmsg($t2)       #take char at byte $t2 from msg

        move $t6,$t4            #make a copy of x to restore if need be
        add $t4,$t4,$t0         #encrypt using formula y = a+x-b
        sub $t4,$t4,$t1

        ble $t4,31,adrstr       #if x is <= 31, that means the character won't be legible to the user so we restore the original one
        bge $t4,127,adrstr      #if x is >= 127, that means the character won't be legible to the user so we restore the original one
        j adgo

adrstr: move $t4,$t6           #restore original character
adgo:   sb $t4,smsg($t2)       #save char at byte $t0 from nmsg

        beq $t3,$t5,adprint     #if $t3 = $t5, print character
        addi $t2,$t2,1          #increment $t2
        addi $t3,$t3,1          #increment $t3
        j adloop

adprint:la $a0,smsg             #print encrypted message
        li $v0,4
        syscall

#################################reinitialize arrays####################################
zero: 	lw $t5,max              #set up max for nloop
	sub $t5,$t5,1           #offset the max by one (for some reason the program will only work like so)
	lw $t0,akey             #set up first key
        lw $t1,bkey             #set up second key
        li $t2,0                #set up array index
        li $t3,0                #set up counter
        li $t4,0                #set up zero out register

zloop:  sb $t4,msg($t2)		#save char at byte $t0 from msg
	sb $t4,nmsg($t2)        #save char at byte $t0 from nmsg
	sb $t4,smsg($t2)        #save char at byte $t0 from smsg

	beq $t3,$t5,end      #if $t3 = $t5, print character
	addi $t2,$t2,1          #increment $t2
	addi $t3,$t3,1          #increment $t3
	j zloop

end:    jr $ra                  #return to main program


###############################decryption loop######################################
dcrypt: lw $t5,max              #set up max for nloop
        sub $t5,$t5,1           #offset the max by one (for some reason the program will only work like so)
        lw $t0,akey             #set up first key
        lw $t1,bkey             #set up second key
        li $t2,0                #set up array index
        li $t3,0                #set up counter
        li $t6,0                #set up restore register

dloop:  lb $t4,msg($t2)         #take char at byte $t2 from msg

        move $t6,$t4            #make a copy of x to restore if need be
        add $t4,$t4,$t0         #encrypt using formula y = a+x-b
        sub $t4,$t4,$t1

        ble $t4,31,drstr        #if x is <= 31, that means the character won't be legible to the user so we restore the original one
        bge $t4,127,drstr       #if x is >= 127, that means the character won't be legible to the user so we restore the original one
        j dgo

drstr:  move $t4,$t6            #restore original character
dgo:    sb $t4,nmsg($t2)        #save char at byte $t0 from nmsg

        beq $t3,$t5,dprint      #if $t3 = $t5, print character
        addi $t2,$t2,1          #increment $t2
        addi $t3,$t3,1          #increment $t3
        j dloop

dprint: la $a0,nmsg             #print encrypted message
        li $v0,4
        syscall

        jr $ra                  #return to main program

####################user choice to try again######################################
again:  la $a0,ask              #prompt the user if they want to run the program again
        li $v0,4
        syscall

        li $v0,5                #input
        syscall

        beq $v0,1,begin         #if 1, rerun the program
        bge $v0,2,again         #if >= 2, reask
        blt $v0,0,again         #if < 0,reask

        jr $ra                  #return to main program


.data
msg:    .space 100
nmsg:   .space 100
smsg:   .space 100
akey:   .word 0
bkey:   .word 0
max:    .word 0
prompt: .asciiz "Enter the message to be encrypted/decrypted:\n"
prompth:.asciiz "\n***********************************************************************\nYou will now be prompted for two distinct keys, that you will take note\nof, that will be used to encrypt or decrypt your message!\n***********************************************************************\n"
prompta:.asciiz "Enter first key: \n"
promptb:.asciiz "Enter second key: \n"
prmted: .asciiz "Do you want to encrypt or decrypt the message? (1 = ENCRYPT, 0 = DECRYPT) \n"
promptc:.asciiz "Would you like to decrypt your message?(1 = YES, 0 = NO):\n"
ask:    .asciiz "\nWould you like to run the program again? (1 = YES, 0 = NO):\n"
endl:   .asciiz "\n"

#Enter the message to be encrypted/decrypted:
#This message will be encrypted!
#
#***********************************************************************
#You will now be prompted for two distinct keys, that you will take note
#of, that will be used to encrypt or decrypt your message!
#***********************************************************************
#Enter first key:
#3
#Enter second key:
#5
#Do you want to encrypt or decrypt the message? (1 = ENCRYPT, 0 = DECRYPT)
#1
#Vjku"oguucig"yknn"dg"gpet{rvgf#
#Would you like to decrypt your message?(1 = YES, 0 = NO):
#1
#This message will be encrypted!
#Would you like to run the program again? (1 = YES, 0 = NO):
#1
#Enter the message to be encrypted/decrypted:
#Made with top craftsmanship nyu ugh I cant delete stupid mips
#***********************************************************************
#You will now be prompted for two distinct keys, that you will take note
#of, that will be used to encrypt or decrypt your message!
#***********************************************************************
#Enter first key:
#2
#Enter second key:
#5
#Do you want to encrypt or decrypt the message? (1 = ENCRYPT, 0 = DECRYPT)
#1
#Pdgh#zlwk#wrs#fudiwvpdqvkls#q|x#xjk#L#fdqw#ghohwh#vwxslg#plsv
#Would you like to decrypt

#your message?(1 = YES, 0 = NO):
#1
#Made with top craftsmanship nyu ugh I cant delete stupid mips
#Would you like to run the program again? (1 = YES, 0 = NO):
#0
