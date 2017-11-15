#
#  Makefile for MIPS(EL) XINU.
#

include makeVars

BOOTIMAGE = xinu.boot

LIB       = ../lib

LDFLAGS   = -static --gc-sections -no-warn-mismatch -T ld.script

#-----------------------------------------------------------------------
# source files
#-----------------------------------------------------------------------

# Bootloader
LDR = 

LDRS = start.S flushcache.S

# System
SYS = queue.c create.c devtable.c ready.c resched.c kill.c getpid.c xdone.c main.c kprintf.c insert.c clockinit.c clockintr.c xtrap.c newsem.c freesem.c signal.c signaln.c wait.c scount.c freemem.c getmem.c insertd.c sleep.c wakeup.c ionull.c ioerr.c open.c close.c read.c write.c getc.c putc.c control.c seek.c receive.c send.c

SYSS = startup.S ctxsw.S irq.S clockirq.S intr.S halt.S

# Serial Port Driver
UART = uartInit.c uartIntr.c uartPutChar.c uartRead.c uartWrite.c uartGetChar.c uartControl.c

# TTY Driver
TTY = ttyAlloc.c ttyControl.c ttyOpen.c ttyRead.c ttyClose.c ttyGetChar.c ttyInit.c ttyPutChar.c ttyWrite.c

# Shell
SHL = shell.c lexan.c xsh_exit.c xsh_gpiostat.c xsh_help.c xsh_kill.c xsh_led.c xsh_memstat.c xsh_ps.c xsh_reset.c xsh_sleep.c xsh_uartstat.c xsh_test.c xsh_testsuite.c xsh_command.c xsh_palindrome.c xsh_cyclic.c xsh_synchronization.c xsh_mutual.c xsh_chat.c

# Tests
TST = test-hw4.c test-hw5.c test-sem.c test-sem2.c test-sem3.c test-sem4.c test-dqueue.c test-pqueue.c testhelper.c

SRC =	${LDR:%.c=../loader/%.c} \
	${SYS:%.c=../system/%.c} \
	${UART:%.c=../uart/%.c}  \
	${TTY:%.c=../tty/%.c}    \
 	${SHL:%.c=../shell/%.c}  \
	${TST:%.c=../test/%.c}  

#-----------------------------------------------------------------------
# object files
#-----------------------------------------------------------------------
LDRASM = ${LDRS:%.S=../loader/%.S}
SYSASM = ${SYSS:%.S=../system/%.S}

# Order matters here!  LDRASM (loader/start.S) *must* come first!
KRNOBJ = ${LDRASM:%.S=%.o} ${SYSASM:%.S=%.o} ${SRC:%.c=%.o}

#-----------------------------------------------------------------------
# make targets
#-----------------------------------------------------------------------
all: ${BOOTIMAGE} 

${BOOTIMAGE}: ${KRNOBJ} initialize.o ld.script ${LIB}/libxc.a 
	${LD} -o $@ ${LDFLAGS} $^

clean:
	rm -f *.o ${KRNOBJ} ${BOOTIMAGE}
	rm -rf ${DOCS}

realclean: clean
	${MAKEDEP}

depend:
	${MAKEDEP} -Y../include $(LDRASM) $(SYSASM) $(SRC)

#-----------------------------------------------------------------------
# targets for files outside of this directory
#-----------------------------------------------------------------------
initialize.o: ../system/initialize.c
	sh mkvers.sh
	VERS=`cat version`
	${CC} -DVERSION=\""`cat version`"\" -c ${CFLAGS} ../system/initialize.c

library: ${LIB}/libxc.a

${LIB}/libxc.a:
	(cd ${LIB}/libxc; make install; cp libxc.a ../)

# DO NOT DELETE
