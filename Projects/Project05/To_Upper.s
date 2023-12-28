	.file	"To_Upper.s"
	.text
	.globl	To_Upper
	.type	To_Upper, @function

/* **********************
    Name: Seungju Lee
    Wisc ID Number: 9080213961
    Wisc Email: slee887@wisc.edu
************************ */


To_Upper:

# C version
/* **********************
    assuming that char arr[] is the passed in array

    int i = 0;

    while (arr[i] != '\0') {
        if (arr[i] >= 97 && arr[i] <= 122) {
            arr[i] -= 32;
        }
        i++;
    }

************************ */


# Memory Layout
/* ************************ 
    Make a table showing the stack frame for your function (in the comment block)
    The first column should have a memory address (e.g. 8(%rsp))
    The second column should be the name of the C variable used above
    Update the example below with your variables and memory addresses
        -4(%rbp)  |  int i
************************ */


# Prologue
	pushq	%rbp
	movq	%rsp, %rbp

# This code prints the letter 'a' (ascii value 97)
# Use this for debugging
# Comment out when finished - your function should not print anything
# Note putchar overwrites all caller saved registers including argument registers
/*
	movl	$97, %eax
	movl	%eax, %edi
	call	putchar@PLT
*/

# Body of function
# INITIALIZE VARIABLES
	movl	$0, -16(%rbp)	# int i = 0;

TOP_OF_LOOP:
	jmp CONDITIONAL

LOOP_BODY:
IF_CONDITION:
# if (arr[i] >= 97 && arr[i] <=122)
# exit if arr[i] < 97, so arr[i] - 97 < 0
	cmpb	$97, %cl
	jl	INCREMENT
# also exit if arr[i] > 122, so arr[i] - 122 > 0
	cmpb	$122, %cl
	jg	INCREMENT		

IF_BODY:
	subl	$32, (%rax, %rdx)	# arr[i] -= 32	
	movl	-16(%rbp), %edx		# i
	incl	%edx			# i++
	movl	%edx, -16(%rbp)
	jmp	CONDITIONAL

INCREMENT:
	movl	-16(%rbp), %edx		# i
	incl	%edx			# i++
	movl	%edx, -16(%rbp)

CONDITIONAL:
# arr is null
	cmpq	$0, %rdi
	je	END
# arr[i] != '\0'
	movl	-16(%rbp), %edx		# i
	movq	%rdi, %rax		# base address of arr[]
	movb	(%rax, %rdx), %cl	# arr[i] character to %cl
	cmpb	$0, %cl
	jne	LOOP_BODY	

END:
# Epilogue
	popq	%rbp
   	ret
