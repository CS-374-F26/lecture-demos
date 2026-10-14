	.file	"volumesofspheres.c"
	.text
.Ltext0:
	.file 0 "/home/alex/instructor/f26/cs374/lecture-demos/concurrency" "volumesofspheres.c"
	.globl	compute_volume_of_sphere_and_add_to_sum
	.type	compute_volume_of_sphere_and_add_to_sum, @function
compute_volume_of_sphere_and_add_to_sum:
.LFB0:
	.file 1 "volumesofspheres.c"
	.loc 1 32 66
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	.loc 1 33 25
	movq	-24(%rbp), %rax
	movq	%rax, -16(%rbp)
	.loc 1 34 65
	movq	-16(%rbp), %rax
	movsd	(%rax), %xmm1
	.loc 1 34 53
	movsd	.LC0(%rip), %xmm0
	mulsd	%xmm0, %xmm1
	.loc 1 35 13
	movq	-16(%rbp), %rax
	movsd	(%rax), %xmm0
	.loc 1 34 74
	mulsd	%xmm0, %xmm1
	.loc 1 35 34
	movq	-16(%rbp), %rax
	movsd	(%rax), %xmm0
	.loc 1 34 9
	mulsd	%xmm1, %xmm0
	movsd	%xmm0, -8(%rbp)
	.loc 1 42 14
	movq	-16(%rbp), %rax
	movq	8(%rax), %rax
	.loc 1 42 2
	movsd	(%rax), %xmm0
	.loc 1 42 14
	movq	-16(%rbp), %rax
	movq	8(%rax), %rax
	.loc 1 42 25
	addsd	-8(%rbp), %xmm0
	movsd	%xmm0, (%rax)
	.loc 1 45 9
	movl	$0, %eax
	.loc 1 46 1
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	compute_volume_of_sphere_and_add_to_sum, .-compute_volume_of_sphere_and_add_to_sum
	.section	.rodata
.LC2:
	.string	"Sum: %.3f\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.loc 1 48 16
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$2448, %rsp
	.loc 1 48 16
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	.loc 1 51 9
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -2424(%rbp)
.LBB2:
	.loc 1 53 11
	movl	$0, -2436(%rbp)
	.loc 1 53 2
	jmp	.L4
.L5:
.LBB3:
	.loc 1 54 29
	pxor	%xmm0, %xmm0
	cvtsi2sdl	-2436(%rbp), %xmm0
	movl	-2436(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	subq	$1616, %rax
	movsd	%xmm0, (%rax)
	.loc 1 55 30
	movl	-2436(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	leaq	-1608(%rax), %rdx
	leaq	-2424(%rbp), %rax
	movq	%rax, (%rdx)
	.loc 1 60 4
	leaq	-1616(%rbp), %rax
	movl	-2436(%rbp), %edx
	movslq	%edx, %rdx
	salq	$4, %rdx
	leaq	(%rax,%rdx), %rcx
	.loc 1 57 4
	leaq	-2416(%rbp), %rax
	movl	-2436(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	.loc 1 56 23
	leaq	compute_volume_of_sphere_and_add_to_sum(%rip), %rdx
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_create@PLT
	movl	%eax, -2428(%rbp)
.LBE3:
	.loc 1 53 27 discriminator 1
	addl	$1, -2436(%rbp)
.L4:
	.loc 1 53 20 discriminator 2
	cmpl	$99, -2436(%rbp)
	jle	.L5
.LBE2:
.LBB4:
	.loc 1 65 11
	movl	$0, -2432(%rbp)
	.loc 1 65 2
	jmp	.L6
.L7:
	.loc 1 66 3
	movl	-2432(%rbp), %eax
	cltq
	movq	-2416(%rbp,%rax,8), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_join@PLT
	.loc 1 65 27 discriminator 1
	addl	$1, -2432(%rbp)
.L6:
	.loc 1 65 20 discriminator 2
	cmpl	$99, -2432(%rbp)
	jle	.L7
.LBE4:
	.loc 1 69 2
	movq	-2424(%rbp), %rax
	leaq	.LC2(%rip), %rdx
	movq	%rax, %xmm0
	movq	%rdx, %rdi
	movl	$1, %eax
	call	printf@PLT
	movl	$0, %eax
	.loc 1 70 1
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L9
	call	__stack_chk_fail@PLT
.L9:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC0:
	.long	942502757
	.long	1074839890
	.text
.Letext0:
	.file 2 "/usr/include/bits/pthreadtypes.h"
	.file 3 "/usr/include/stdio.h"
	.file 4 "/usr/include/pthread.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x2b6
	.value	0x5
	.byte	0x1
	.byte	0x8
	.long	.Ldebug_abbrev0
	.uleb128 0xf
	.long	.LASF29
	.byte	0x1d
	.byte	0x3
	.long	0x31647
	.long	.LASF0
	.long	.LASF1
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.long	.Ldebug_line0
	.uleb128 0x1
	.byte	0x8
	.byte	0x7
	.long	.LASF2
	.uleb128 0x1
	.byte	0x4
	.byte	0x7
	.long	.LASF3
	.uleb128 0x10
	.byte	0x8
	.uleb128 0x5
	.long	0x41
	.uleb128 0x1
	.byte	0x1
	.byte	0x8
	.long	.LASF4
	.uleb128 0x1
	.byte	0x2
	.byte	0x7
	.long	.LASF5
	.uleb128 0x1
	.byte	0x1
	.byte	0x6
	.long	.LASF6
	.uleb128 0x1
	.byte	0x2
	.byte	0x5
	.long	.LASF7
	.uleb128 0x11
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x1
	.byte	0x8
	.byte	0x5
	.long	.LASF8
	.uleb128 0x1
	.byte	0x1
	.byte	0x6
	.long	.LASF9
	.uleb128 0x9
	.long	0x72
	.uleb128 0x3
	.long	0x79
	.uleb128 0x1
	.byte	0x8
	.byte	0x7
	.long	.LASF10
	.uleb128 0xa
	.long	.LASF13
	.byte	0x1b
	.byte	0x1b
	.long	0x33
	.uleb128 0x12
	.long	.LASF14
	.byte	0x38
	.byte	0x2
	.byte	0x38
	.byte	0x7
	.long	0xb9
	.uleb128 0xb
	.long	.LASF11
	.byte	0x3a
	.byte	0x8
	.long	0xb9
	.uleb128 0xb
	.long	.LASF12
	.byte	0x3b
	.byte	0xc
	.long	0x6b
	.byte	0
	.uleb128 0x6
	.long	0x72
	.long	0xc9
	.uleb128 0x7
	.long	0x33
	.byte	0x37
	.byte	0
	.uleb128 0xa
	.long	.LASF14
	.byte	0x3e
	.byte	0x1e
	.long	0x95
	.uleb128 0x9
	.long	0xc9
	.uleb128 0x1
	.byte	0x8
	.byte	0x5
	.long	.LASF15
	.uleb128 0x13
	.long	.LASF30
	.byte	0x10
	.byte	0x1
	.byte	0x17
	.byte	0x8
	.long	0x106
	.uleb128 0xc
	.long	.LASF16
	.byte	0x18
	.byte	0x9
	.long	0x106
	.byte	0
	.uleb128 0xc
	.long	.LASF17
	.byte	0x19
	.byte	0xa
	.long	0x10d
	.byte	0x8
	.byte	0
	.uleb128 0x1
	.byte	0x8
	.byte	0x4
	.long	.LASF18
	.uleb128 0x3
	.long	0x106
	.uleb128 0x14
	.long	.LASF19
	.byte	0x3
	.value	0x172
	.byte	0xc
	.long	0x64
	.long	0x12a
	.uleb128 0x2
	.long	0x7e
	.uleb128 0x15
	.byte	0
	.uleb128 0xd
	.long	.LASF20
	.byte	0xdb
	.long	0x64
	.long	0x143
	.uleb128 0x2
	.long	0x8a
	.uleb128 0x2
	.long	0x143
	.byte	0
	.uleb128 0x3
	.long	0x41
	.uleb128 0xd
	.long	.LASF21
	.byte	0xca
	.long	0x64
	.long	0x16b
	.uleb128 0x2
	.long	0x170
	.uleb128 0x2
	.long	0x17a
	.uleb128 0x2
	.long	0x17f
	.uleb128 0x2
	.long	0x43
	.byte	0
	.uleb128 0x3
	.long	0x8a
	.uleb128 0x5
	.long	0x16b
	.uleb128 0x3
	.long	0xd4
	.uleb128 0x5
	.long	0x175
	.uleb128 0x3
	.long	0x184
	.uleb128 0x16
	.long	0x41
	.long	0x193
	.uleb128 0x2
	.long	0x41
	.byte	0
	.uleb128 0x17
	.long	.LASF25
	.byte	0x1
	.byte	0x30
	.byte	0x5
	.long	0x64
	.quad	.LFB1
	.quad	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.long	0x246
	.uleb128 0x4
	.long	.LASF22
	.byte	0x31
	.byte	0xc
	.long	0x246
	.uleb128 0x3
	.byte	0x91
	.sleb128 -2432
	.uleb128 0x4
	.long	.LASF23
	.byte	0x32
	.byte	0x18
	.long	0x256
	.uleb128 0x3
	.byte	0x91
	.sleb128 -1632
	.uleb128 0x8
	.string	"sum"
	.byte	0x33
	.byte	0x9
	.long	0x106
	.uleb128 0x3
	.byte	0x91
	.sleb128 -2440
	.uleb128 0x18
	.quad	.LBB2
	.quad	.LBE2-.LBB2
	.long	0x226
	.uleb128 0x8
	.string	"i"
	.byte	0x35
	.byte	0xb
	.long	0x64
	.uleb128 0x3
	.byte	0x91
	.sleb128 -2452
	.uleb128 0xe
	.quad	.LBB3
	.quad	.LBE3-.LBB3
	.uleb128 0x4
	.long	.LASF24
	.byte	0x38
	.byte	0x7
	.long	0x64
	.uleb128 0x3
	.byte	0x91
	.sleb128 -2444
	.byte	0
	.byte	0
	.uleb128 0xe
	.quad	.LBB4
	.quad	.LBE4-.LBB4
	.uleb128 0x8
	.string	"i"
	.byte	0x41
	.byte	0xb
	.long	0x64
	.uleb128 0x3
	.byte	0x91
	.sleb128 -2448
	.byte	0
	.byte	0
	.uleb128 0x6
	.long	0x8a
	.long	0x256
	.uleb128 0x7
	.long	0x33
	.byte	0x63
	.byte	0
	.uleb128 0x6
	.long	0xe0
	.long	0x266
	.uleb128 0x7
	.long	0x33
	.byte	0x63
	.byte	0
	.uleb128 0x19
	.long	.LASF26
	.byte	0x1
	.byte	0x20
	.byte	0x7
	.long	0x41
	.quad	.LFB0
	.quad	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.long	0x2b4
	.uleb128 0x1a
	.long	.LASF31
	.byte	0x1
	.byte	0x20
	.byte	0x35
	.long	0x41
	.uleb128 0x2
	.byte	0x91
	.sleb128 -40
	.uleb128 0x4
	.long	.LASF27
	.byte	0x21
	.byte	0x19
	.long	0x2b4
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x4
	.long	.LASF28
	.byte	0x22
	.byte	0x9
	.long	0x106
	.uleb128 0x2
	.byte	0x91
	.sleb128 -24
	.byte	0
	.uleb128 0x3
	.long	0xe0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0x21
	.sleb128 8
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0x37
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 2
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 2
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 1
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0x21
	.sleb128 4
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0x21
	.sleb128 12
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x90
	.uleb128 0xb
	.uleb128 0x91
	.uleb128 0x6
	.uleb128 0x3
	.uleb128 0x1f
	.uleb128 0x1b
	.uleb128 0x1f
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x17
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x7
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x7a
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x39
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.long	0x2c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x8
	.byte	0
	.value	0
	.value	0
	.quad	.Ltext0
	.quad	.Letext0-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF16:
	.string	"radius"
.LASF13:
	.string	"pthread_t"
.LASF26:
	.string	"compute_volume_of_sphere_and_add_to_sum"
.LASF28:
	.string	"volume"
.LASF20:
	.string	"pthread_join"
.LASF11:
	.string	"__size"
.LASF24:
	.string	"create_result"
.LASF4:
	.string	"unsigned char"
.LASF2:
	.string	"long unsigned int"
.LASF5:
	.string	"short unsigned int"
.LASF18:
	.string	"double"
.LASF25:
	.string	"main"
.LASF29:
	.string	"GNU C23 16.2.1 20260810 -mtune=generic -march=x86-64 -g"
.LASF3:
	.string	"unsigned int"
.LASF10:
	.string	"long long unsigned int"
.LASF27:
	.string	"casted_arg"
.LASF15:
	.string	"long long int"
.LASF23:
	.string	"all_thread_args"
.LASF30:
	.string	"thread_input_t"
.LASF12:
	.string	"__align"
.LASF19:
	.string	"printf"
.LASF22:
	.string	"threads"
.LASF7:
	.string	"short int"
.LASF31:
	.string	"thread_args"
.LASF21:
	.string	"pthread_create"
.LASF8:
	.string	"long int"
.LASF9:
	.string	"char"
.LASF14:
	.string	"pthread_attr_t"
.LASF6:
	.string	"signed char"
.LASF17:
	.string	"sum_ptr"
	.section	.debug_line_str,"MS",@progbits,1
.LASF1:
	.string	"/home/alex/instructor/f26/cs374/lecture-demos/concurrency"
.LASF0:
	.string	"volumesofspheres.c"
	.ident	"GCC: (GNU) 16.2.1 20260810"
	.section	.note.GNU-stack,"",@progbits
