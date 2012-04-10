	.file	"vec_generic.c"
	.text
.Ltext0:
	.p2align 4,,15
	.globl	myrt_vec_dot
	.type	myrt_vec_dot, @function
myrt_vec_dot:
.LFB33:
	.file 1 "arch/vec_generic.c"
	.loc 1 28 0
	.cfi_startproc
.LVL0:
	.loc 1 30 0
	movss	(%rdi), %xmm0
	movss	4(%rdi), %xmm1
	mulss	(%rsi), %xmm0
	mulss	4(%rsi), %xmm1
	addss	%xmm1, %xmm0
	movss	8(%rdi), %xmm1
	mulss	8(%rsi), %xmm1
	addss	%xmm1, %xmm0
	movss	12(%rdi), %xmm1
	mulss	12(%rsi), %xmm1
	addss	%xmm1, %xmm0
	.loc 1 32 0
	ret
	.cfi_endproc
.LFE33:
	.size	myrt_vec_dot, .-myrt_vec_dot
	.p2align 4,,15
	.globl	myrt_vec_magnitude
	.type	myrt_vec_magnitude, @function
myrt_vec_magnitude:
.LFB34:
	.loc 1 34 0
	.cfi_startproc
.LVL1:
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
.LBB20:
.LBB21:
	.loc 1 30 0
	movss	(%rdi), %xmm1
	movss	4(%rdi), %xmm3
	mulss	%xmm1, %xmm1
	mulss	%xmm3, %xmm3
	movss	8(%rdi), %xmm2
	mulss	%xmm2, %xmm2
	movss	12(%rdi), %xmm0
	mulss	%xmm0, %xmm0
	addss	%xmm3, %xmm1
	addss	%xmm2, %xmm1
	addss	%xmm0, %xmm1
.LBE21:
.LBE20:
	.loc 1 36 0
	sqrtss	%xmm1, %xmm0
	ucomiss	%xmm0, %xmm0
	jp	.L6
.LVL2:
.L3:
	.loc 1 38 0
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.LVL3:
.L6:
	.cfi_restore_state
	.loc 1 36 0
	movaps	%xmm1, %xmm0
	call	sqrtf@PLT
.LVL4:
	.p2align 4,,2
	jmp	.L3
	.cfi_endproc
.LFE34:
	.size	myrt_vec_magnitude, .-myrt_vec_magnitude
	.p2align 4,,15
	.globl	myrt_vec_angle
	.type	myrt_vec_angle, @function
myrt_vec_angle:
.LFB35:
	.loc 1 40 0
	.cfi_startproc
.LVL5:
	subq	$56, %rsp
	.cfi_def_cfa_offset 64
.LBB22:
.LBB23:
	.loc 1 30 0
	movss	(%rdi), %xmm0
	movss	4(%rdi), %xmm4
	movss	(%rsi), %xmm1
	movss	4(%rsi), %xmm5
	mulss	%xmm0, %xmm1
	mulss	%xmm4, %xmm5
	movss	8(%rdi), %xmm3
.LBE23:
.LBE22:
.LBB28:
.LBB29:
	mulss	%xmm0, %xmm0
.LBE29:
.LBE28:
.LBB34:
.LBB24:
	movss	12(%rdi), %xmm2
.LBE24:
.LBE34:
.LBB35:
.LBB30:
	mulss	%xmm4, %xmm4
.LBE30:
.LBE35:
.LBB36:
.LBB25:
	addss	%xmm5, %xmm1
	movss	8(%rsi), %xmm5
	mulss	%xmm3, %xmm5
.LBE25:
.LBE36:
.LBB37:
.LBB31:
	addss	%xmm4, %xmm0
	mulss	%xmm3, %xmm3
.LBE31:
.LBE37:
.LBB38:
.LBB26:
	addss	%xmm5, %xmm1
	movss	12(%rsi), %xmm5
	mulss	%xmm2, %xmm5
.LBE26:
.LBE38:
.LBB39:
.LBB32:
	addss	%xmm3, %xmm0
	mulss	%xmm2, %xmm2
.LBE32:
.LBE39:
.LBB40:
.LBB27:
	addss	%xmm5, %xmm1
.LVL6:
.LBE27:
.LBE40:
.LBB41:
.LBB33:
	addss	%xmm2, %xmm0
.LBE33:
.LBE41:
	.loc 1 43 0
	sqrtss	%xmm0, %xmm2
	ucomiss	%xmm2, %xmm2
	jp	.L12
.LVL7:
.L8:
.LBB42:
.LBB43:
	.loc 1 30 0
	movss	(%rsi), %xmm3
	movss	4(%rsi), %xmm5
	mulss	%xmm3, %xmm3
	mulss	%xmm5, %xmm5
	movss	8(%rsi), %xmm4
	mulss	%xmm4, %xmm4
	movss	12(%rsi), %xmm0
	mulss	%xmm0, %xmm0
	addss	%xmm5, %xmm3
	addss	%xmm4, %xmm3
	addss	%xmm0, %xmm3
.LBE43:
.LBE42:
	.loc 1 44 0
	sqrtss	%xmm3, %xmm0
	ucomiss	%xmm0, %xmm0
	jp	.L13
.LVL8:
.L10:
	.loc 1 43 0
	mulss	%xmm0, %xmm2
.LVL9:
	.loc 1 46 0
	movaps	%xmm1, %xmm0
	.loc 1 48 0
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	.loc 1 46 0
	divss	%xmm2, %xmm0
	jmp	acosf@PLT
.LVL10:
.L12:
	.cfi_restore_state
	.loc 1 43 0
	movq	%rsi, 40(%rsp)
	movss	%xmm1, (%rsp)
	call	sqrtf@PLT
.LVL11:
	movss	(%rsp), %xmm1
	movaps	%xmm0, %xmm2
	movq	40(%rsp), %rsi
	jmp	.L8
.LVL12:
.L13:
	.loc 1 44 0
	movaps	%xmm3, %xmm0
	movss	%xmm1, (%rsp)
	movss	%xmm2, 16(%rsp)
	call	sqrtf@PLT
.LVL13:
	movss	16(%rsp), %xmm2
	movss	(%rsp), %xmm1
	jmp	.L10
	.cfi_endproc
.LFE35:
	.size	myrt_vec_angle, .-myrt_vec_angle
	.p2align 4,,15
	.globl	myrt_vec_normalize
	.type	myrt_vec_normalize, @function
myrt_vec_normalize:
.LFB36:
	.loc 1 50 0
	.cfi_startproc
.LVL14:
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	.loc 1 50 0
	movq	%rdi, %rax
.LBB50:
.LBB51:
.LBB52:
.LBB53:
	.loc 1 30 0
	movss	(%rdi), %xmm5
	movss	4(%rdi), %xmm4
	movaps	%xmm5, %xmm1
	movaps	%xmm4, %xmm0
	mulss	%xmm5, %xmm1
	movss	8(%rdi), %xmm3
	mulss	%xmm4, %xmm0
	movss	12(%rdi), %xmm2
	addss	%xmm0, %xmm1
	movaps	%xmm3, %xmm0
	mulss	%xmm3, %xmm0
	addss	%xmm0, %xmm1
	movaps	%xmm2, %xmm0
	mulss	%xmm2, %xmm0
	addss	%xmm0, %xmm1
.LBE53:
.LBE52:
	.loc 1 36 0
	sqrtss	%xmm1, %xmm0
	ucomiss	%xmm0, %xmm0
	jp	.L17
.LVL15:
.L15:
.LBE51:
.LBE50:
	.loc 1 52 0
	movss	.LC0(%rip), %xmm1
	divss	%xmm0, %xmm1
.LVL16:
.LBB55:
.LBB56:
	.loc 1 82 0
	mulss	%xmm1, %xmm5
	.loc 1 83 0
	mulss	%xmm1, %xmm4
	.loc 1 84 0
	mulss	%xmm1, %xmm3
	.loc 1 85 0
	mulss	%xmm2, %xmm1
.LVL17:
	.loc 1 82 0
	movss	%xmm5, (%rax)
	.loc 1 83 0
	movss	%xmm4, 4(%rax)
	.loc 1 84 0
	movss	%xmm3, 8(%rax)
	.loc 1 85 0
	movss	%xmm1, 12(%rax)
.LBE56:
.LBE55:
	.loc 1 54 0
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.LVL18:
.L17:
	.cfi_restore_state
.LBB57:
.LBB54:
	.loc 1 36 0
	movaps	%xmm1, %xmm0
	movq	%rdi, 8(%rsp)
	call	sqrtf@PLT
.LVL19:
	movq	8(%rsp), %rax
	movss	(%rax), %xmm5
	movss	4(%rax), %xmm4
	movss	8(%rax), %xmm3
	movss	12(%rax), %xmm2
	jmp	.L15
.LBE54:
.LBE57:
	.cfi_endproc
.LFE36:
	.size	myrt_vec_normalize, .-myrt_vec_normalize
	.p2align 4,,15
	.globl	myrt_vec_add
	.type	myrt_vec_add, @function
myrt_vec_add:
.LFB37:
	.loc 1 57 0
	.cfi_startproc
.LVL20:
	.loc 1 59 0
	movss	(%rdi), %xmm0
	.loc 1 57 0
	movq	%rdi, %rax
	.loc 1 59 0
	addss	(%rsi), %xmm0
	movss	%xmm0, (%rdi)
	.loc 1 60 0
	movss	4(%rdi), %xmm0
	addss	4(%rsi), %xmm0
	movss	%xmm0, 4(%rdi)
	.loc 1 61 0
	movss	8(%rdi), %xmm0
	addss	8(%rsi), %xmm0
	movss	%xmm0, 8(%rdi)
	.loc 1 62 0
	movss	12(%rdi), %xmm0
	addss	12(%rsi), %xmm0
	movss	%xmm0, 12(%rdi)
	.loc 1 66 0
	ret
	.cfi_endproc
.LFE37:
	.size	myrt_vec_add, .-myrt_vec_add
	.p2align 4,,15
	.globl	myrt_vec_sub
	.type	myrt_vec_sub, @function
myrt_vec_sub:
.LFB38:
	.loc 1 69 0
	.cfi_startproc
.LVL21:
	.loc 1 71 0
	movss	(%rdi), %xmm0
	.loc 1 69 0
	movq	%rdi, %rax
	.loc 1 71 0
	subss	(%rsi), %xmm0
	movss	%xmm0, (%rdi)
	.loc 1 72 0
	movss	4(%rdi), %xmm0
	subss	4(%rsi), %xmm0
	movss	%xmm0, 4(%rdi)
	.loc 1 73 0
	movss	8(%rdi), %xmm0
	subss	8(%rsi), %xmm0
	movss	%xmm0, 8(%rdi)
	.loc 1 74 0
	movss	12(%rdi), %xmm0
	subss	12(%rsi), %xmm0
	movss	%xmm0, 12(%rdi)
	.loc 1 78 0
	ret
	.cfi_endproc
.LFE38:
	.size	myrt_vec_sub, .-myrt_vec_sub
	.p2align 4,,15
	.globl	myrt_vec_scale
	.type	myrt_vec_scale, @function
myrt_vec_scale:
.LFB39:
	.loc 1 80 0
	.cfi_startproc
.LVL22:
	.loc 1 82 0
	xorps	%xmm1, %xmm1
	.loc 1 80 0
	movq	%rdi, %rax
	.loc 1 82 0
	shufps	$0, %xmm0, %xmm0
.LVL23:
	movlps	(%rdi), %xmm1
	movhps	8(%rdi), %xmm1
	mulps	%xmm0, %xmm1
	movlps	%xmm1, (%rdi)
	movhps	%xmm1, 8(%rdi)
	.loc 1 89 0
	ret
	.cfi_endproc
.LFE39:
	.size	myrt_vec_scale, .-myrt_vec_scale
	.p2align 4,,15
	.globl	myrt_vec_cross
	.type	myrt_vec_cross, @function
myrt_vec_cross:
.LFB40:
	.loc 1 92 0
	.cfi_startproc
.LVL24:
	.loc 1 95 0
	movss	4(%rdi), %xmm4
	.loc 1 92 0
	movq	%rdi, %rax
	.loc 1 95 0
	movss	8(%rdi), %xmm1
	movaps	%xmm4, %xmm2
	movaps	%xmm1, %xmm7
	movss	8(%rsi), %xmm6
	movss	4(%rsi), %xmm5
.LVL25:
	mulss	%xmm6, %xmm2
	.loc 1 96 0
	movss	(%rsi), %xmm3
	.loc 1 95 0
	mulss	%xmm5, %xmm7
	.loc 1 96 0
	movss	(%rdi), %xmm0
.LVL26:
	mulss	%xmm3, %xmm1
	mulss	%xmm0, %xmm6
	.loc 1 97 0
	mulss	%xmm4, %xmm3
	mulss	%xmm5, %xmm0
	.loc 1 95 0
	subss	%xmm7, %xmm2
	.loc 1 96 0
	subss	%xmm6, %xmm1
	.loc 1 97 0
	subss	%xmm3, %xmm0
	.loc 1 99 0
	movss	%xmm2, (%rdi)
	.loc 1 100 0
	movss	%xmm1, 4(%rdi)
	.loc 1 101 0
	movss	%xmm0, 8(%rdi)
	.loc 1 105 0
	ret
	.cfi_endproc
.LFE40:
	.size	myrt_vec_cross, .-myrt_vec_cross
	.p2align 4,,15
	.globl	myrt_vec_reflection
	.type	myrt_vec_reflection, @function
myrt_vec_reflection:
.LFB41:
	.loc 1 108 0
	.cfi_startproc
.LVL27:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsi, %rbp
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rdi, %rbx
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	.loc 1 112 0
	movq	%rsp, %rdi
.LVL28:
	call	myrt_vec_copy@PLT
.LVL29:
.LBB58:
.LBB59:
	.loc 1 30 0
	movss	(%rbx), %xmm7
.LBE59:
.LBE58:
	.loc 1 115 0
	movq	%rsp, %rsi
.LBB63:
.LBB60:
	.loc 1 30 0
	movss	4(%rbx), %xmm6
.LBE60:
.LBE63:
	.loc 1 115 0
	movq	%rbx, %rdi
.LBB64:
.LBB61:
	.loc 1 30 0
	movss	0(%rbp), %xmm0
	movss	4(%rbp), %xmm1
	mulss	%xmm7, %xmm0
	mulss	%xmm6, %xmm1
	movss	8(%rbx), %xmm5
	movss	12(%rbx), %xmm4
.LBE61:
.LBE64:
.LBB65:
.LBB66:
	.loc 1 83 0
	movss	4(%rsp), %xmm3
	.loc 1 84 0
	movss	8(%rsp), %xmm2
.LBE66:
.LBE65:
.LBB69:
.LBB62:
	.loc 1 30 0
	addss	%xmm1, %xmm0
	movss	8(%rbp), %xmm1
	mulss	%xmm5, %xmm1
	addss	%xmm1, %xmm0
	movss	12(%rbp), %xmm1
	mulss	%xmm4, %xmm1
	addss	%xmm1, %xmm0
.LBE62:
.LBE69:
.LBB70:
.LBB67:
	.loc 1 85 0
	movss	12(%rsp), %xmm1
.LBE67:
.LBE70:
	.loc 1 113 0
	addss	%xmm0, %xmm0
.LVL30:
.LBB71:
.LBB68:
	.loc 1 83 0
	mulss	%xmm0, %xmm3
	.loc 1 84 0
	mulss	%xmm0, %xmm2
	.loc 1 85 0
	mulss	%xmm0, %xmm1
.LVL31:
	.loc 1 82 0
	mulss	(%rsp), %xmm0
.LVL32:
.LBE68:
.LBE71:
.LBB72:
.LBB73:
	.loc 1 72 0
	subss	%xmm6, %xmm3
	.loc 1 73 0
	subss	%xmm5, %xmm2
	.loc 1 74 0
	subss	%xmm4, %xmm1
	.loc 1 72 0
	movss	%xmm3, 4(%rsp)
	.loc 1 71 0
	subss	%xmm7, %xmm0
	.loc 1 73 0
	movss	%xmm2, 8(%rsp)
	.loc 1 74 0
	movss	%xmm1, 12(%rsp)
	.loc 1 71 0
	movss	%xmm0, (%rsp)
.LBE73:
.LBE72:
	.loc 1 115 0
	call	myrt_vec_copy@PLT
.LVL33:
	.loc 1 119 0
	addq	$24, %rsp
	.cfi_def_cfa_offset 24
.LVL34:
	movq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 16
.LVL35:
	popq	%rbp
	.cfi_def_cfa_offset 8
.LVL36:
	ret
	.cfi_endproc
.LFE41:
	.size	myrt_vec_reflection, .-myrt_vec_reflection
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC0:
	.long	1065353216
	.text
.Letext0:
	.file 2 "/home/alex/c-programs/git-programs/myrt/include/vec.h"
	.file 3 "/usr/include/bits/types.h"
	.file 4 "/usr/lib/gcc/x86_64-redhat-linux/4.6.2/include/stddef.h"
	.file 5 "/usr/include/libio.h"
	.file 6 "/usr/include/stdio.h"
	.file 7 "/usr/include/bits/mathcalls.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x83f
	.value	0x4
	.long	.Ldebug_abbrev0
	.byte	0x8
	.uleb128 0x1
	.long	.LASF67
	.byte	0x1
	.long	.LASF68
	.long	.LASF69
	.quad	.Ltext0
	.quad	.Letext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x4
	.byte	0x4
	.long	.LASF0
	.uleb128 0x3
	.long	.LASF14
	.byte	0x10
	.byte	0x2
	.byte	0x1d
	.long	0x69
	.uleb128 0x4
	.string	"x"
	.byte	0x2
	.byte	0x1f
	.long	0x2d
	.byte	0
	.uleb128 0x4
	.string	"y"
	.byte	0x2
	.byte	0x20
	.long	0x2d
	.byte	0x4
	.uleb128 0x4
	.string	"z"
	.byte	0x2
	.byte	0x21
	.long	0x2d
	.byte	0x8
	.uleb128 0x4
	.string	"w"
	.byte	0x2
	.byte	0x22
	.long	0x2d
	.byte	0xc
	.byte	0
	.uleb128 0x5
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF1
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF2
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF3
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF4
	.uleb128 0x6
	.byte	0x8
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF5
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF6
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.long	.LASF7
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF8
	.uleb128 0x7
	.long	.LASF9
	.byte	0x3
	.byte	0x8d
	.long	0xa3
	.uleb128 0x7
	.long	.LASF10
	.byte	0x3
	.byte	0x8e
	.long	0xa3
	.uleb128 0x8
	.byte	0x8
	.long	0x85
	.uleb128 0x7
	.long	.LASF11
	.byte	0x4
	.byte	0xd4
	.long	0x7e
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF12
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF13
	.uleb128 0x9
	.long	.LASF15
	.byte	0xd8
	.byte	0x5
	.value	0x111
	.long	0x266
	.uleb128 0xa
	.long	.LASF16
	.byte	0x5
	.value	0x112
	.long	0x69
	.byte	0
	.uleb128 0xa
	.long	.LASF17
	.byte	0x5
	.value	0x117
	.long	0xc0
	.byte	0x8
	.uleb128 0xa
	.long	.LASF18
	.byte	0x5
	.value	0x118
	.long	0xc0
	.byte	0x10
	.uleb128 0xa
	.long	.LASF19
	.byte	0x5
	.value	0x119
	.long	0xc0
	.byte	0x18
	.uleb128 0xa
	.long	.LASF20
	.byte	0x5
	.value	0x11a
	.long	0xc0
	.byte	0x20
	.uleb128 0xa
	.long	.LASF21
	.byte	0x5
	.value	0x11b
	.long	0xc0
	.byte	0x28
	.uleb128 0xa
	.long	.LASF22
	.byte	0x5
	.value	0x11c
	.long	0xc0
	.byte	0x30
	.uleb128 0xa
	.long	.LASF23
	.byte	0x5
	.value	0x11d
	.long	0xc0
	.byte	0x38
	.uleb128 0xa
	.long	.LASF24
	.byte	0x5
	.value	0x11e
	.long	0xc0
	.byte	0x40
	.uleb128 0xa
	.long	.LASF25
	.byte	0x5
	.value	0x120
	.long	0xc0
	.byte	0x48
	.uleb128 0xa
	.long	.LASF26
	.byte	0x5
	.value	0x121
	.long	0xc0
	.byte	0x50
	.uleb128 0xa
	.long	.LASF27
	.byte	0x5
	.value	0x122
	.long	0xc0
	.byte	0x58
	.uleb128 0xa
	.long	.LASF28
	.byte	0x5
	.value	0x124
	.long	0x29e
	.byte	0x60
	.uleb128 0xa
	.long	.LASF29
	.byte	0x5
	.value	0x126
	.long	0x2a4
	.byte	0x68
	.uleb128 0xa
	.long	.LASF30
	.byte	0x5
	.value	0x128
	.long	0x69
	.byte	0x70
	.uleb128 0xa
	.long	.LASF31
	.byte	0x5
	.value	0x12c
	.long	0x69
	.byte	0x74
	.uleb128 0xa
	.long	.LASF32
	.byte	0x5
	.value	0x12e
	.long	0xaa
	.byte	0x78
	.uleb128 0xa
	.long	.LASF33
	.byte	0x5
	.value	0x132
	.long	0x8e
	.byte	0x80
	.uleb128 0xa
	.long	.LASF34
	.byte	0x5
	.value	0x133
	.long	0x95
	.byte	0x82
	.uleb128 0xa
	.long	.LASF35
	.byte	0x5
	.value	0x134
	.long	0x2aa
	.byte	0x83
	.uleb128 0xa
	.long	.LASF36
	.byte	0x5
	.value	0x138
	.long	0x2ba
	.byte	0x88
	.uleb128 0xa
	.long	.LASF37
	.byte	0x5
	.value	0x141
	.long	0xb5
	.byte	0x90
	.uleb128 0xa
	.long	.LASF38
	.byte	0x5
	.value	0x14a
	.long	0x8c
	.byte	0x98
	.uleb128 0xa
	.long	.LASF39
	.byte	0x5
	.value	0x14b
	.long	0x8c
	.byte	0xa0
	.uleb128 0xa
	.long	.LASF40
	.byte	0x5
	.value	0x14c
	.long	0x8c
	.byte	0xa8
	.uleb128 0xa
	.long	.LASF41
	.byte	0x5
	.value	0x14d
	.long	0x8c
	.byte	0xb0
	.uleb128 0xa
	.long	.LASF42
	.byte	0x5
	.value	0x14e
	.long	0xc6
	.byte	0xb8
	.uleb128 0xa
	.long	.LASF43
	.byte	0x5
	.value	0x150
	.long	0x69
	.byte	0xc0
	.uleb128 0xa
	.long	.LASF44
	.byte	0x5
	.value	0x152
	.long	0x2c0
	.byte	0xc4
	.byte	0
	.uleb128 0xb
	.long	.LASF70
	.byte	0x5
	.byte	0xb6
	.uleb128 0x3
	.long	.LASF45
	.byte	0x18
	.byte	0x5
	.byte	0xbc
	.long	0x29e
	.uleb128 0xc
	.long	.LASF46
	.byte	0x5
	.byte	0xbd
	.long	0x29e
	.byte	0
	.uleb128 0xc
	.long	.LASF47
	.byte	0x5
	.byte	0xbe
	.long	0x2a4
	.byte	0x8
	.uleb128 0xc
	.long	.LASF48
	.byte	0x5
	.byte	0xc2
	.long	0x69
	.byte	0x10
	.byte	0
	.uleb128 0x8
	.byte	0x8
	.long	0x26d
	.uleb128 0x8
	.byte	0x8
	.long	0xdf
	.uleb128 0xd
	.long	0x85
	.long	0x2ba
	.uleb128 0xe
	.long	0x7e
	.byte	0
	.byte	0
	.uleb128 0x8
	.byte	0x8
	.long	0x266
	.uleb128 0xd
	.long	0x85
	.long	0x2d0
	.uleb128 0xe
	.long	0x7e
	.byte	0x13
	.byte	0
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.long	.LASF49
	.uleb128 0x8
	.byte	0x8
	.long	0x34
	.uleb128 0xf
	.long	.LASF50
	.byte	0x1
	.byte	0x1c
	.long	0x2d
	.byte	0x3
	.long	0x300
	.uleb128 0x10
	.string	"a"
	.byte	0x1
	.byte	0x1c
	.long	0x2d7
	.uleb128 0x10
	.string	"b"
	.byte	0x1
	.byte	0x1c
	.long	0x2d7
	.byte	0
	.uleb128 0xf
	.long	.LASF51
	.byte	0x1
	.byte	0x50
	.long	0x2d7
	.byte	0x3
	.long	0x325
	.uleb128 0x10
	.string	"a"
	.byte	0x1
	.byte	0x50
	.long	0x2d7
	.uleb128 0x11
	.long	.LASF52
	.byte	0x1
	.byte	0x50
	.long	0x2d
	.byte	0
	.uleb128 0xf
	.long	.LASF53
	.byte	0x1
	.byte	0x44
	.long	0x2d7
	.byte	0x3
	.long	0x348
	.uleb128 0x10
	.string	"a"
	.byte	0x1
	.byte	0x44
	.long	0x2d7
	.uleb128 0x10
	.string	"b"
	.byte	0x1
	.byte	0x45
	.long	0x2d7
	.byte	0
	.uleb128 0x12
	.long	0x2dd
	.quad	.LFB33
	.quad	.LFE33
	.uleb128 0x1
	.byte	0x9c
	.long	0x372
	.uleb128 0x13
	.long	0x2ed
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x13
	.long	0x2f6
	.uleb128 0x1
	.byte	0x54
	.byte	0
	.uleb128 0xf
	.long	.LASF54
	.byte	0x1
	.byte	0x22
	.long	0x2d
	.byte	0x3
	.long	0x38c
	.uleb128 0x10
	.string	"a"
	.byte	0x1
	.byte	0x22
	.long	0x2d7
	.byte	0
	.uleb128 0x12
	.long	0x372
	.quad	.LFB34
	.quad	.LFE34
	.uleb128 0x1
	.byte	0x9c
	.long	0x3ec
	.uleb128 0x14
	.long	0x382
	.long	.LLST0
	.uleb128 0x15
	.long	0x2dd
	.quad	.LBB20
	.quad	.LBE20
	.byte	0x1
	.byte	0x24
	.long	0x3de
	.uleb128 0x14
	.long	0x2f6
	.long	.LLST0
	.uleb128 0x14
	.long	0x2ed
	.long	.LLST0
	.byte	0
	.uleb128 0x16
	.quad	.LVL4
	.long	0x802
	.byte	0
	.uleb128 0x17
	.long	.LASF56
	.byte	0x1
	.byte	0x28
	.long	0x2d
	.quad	.LFB35
	.quad	.LFE35
	.uleb128 0x1
	.byte	0x9c
	.long	0x4ed
	.uleb128 0x18
	.string	"a"
	.byte	0x1
	.byte	0x28
	.long	0x2d7
	.long	.LLST3
	.uleb128 0x18
	.string	"b"
	.byte	0x1
	.byte	0x28
	.long	0x2d7
	.long	.LLST4
	.uleb128 0x19
	.string	"num"
	.byte	0x1
	.byte	0x2a
	.long	0x2d
	.uleb128 0x1
	.byte	0x62
	.uleb128 0x1a
	.long	.LASF55
	.byte	0x1
	.byte	0x2b
	.long	0x2d
	.long	.LLST5
	.uleb128 0x1b
	.long	0x2dd
	.quad	.LBB22
	.long	.Ldebug_ranges0+0
	.byte	0x1
	.byte	0x2a
	.long	0x46d
	.uleb128 0x14
	.long	0x2f6
	.long	.LLST4
	.uleb128 0x14
	.long	0x2ed
	.long	.LLST3
	.byte	0
	.uleb128 0x1b
	.long	0x2dd
	.quad	.LBB28
	.long	.Ldebug_ranges0+0x60
	.byte	0x1
	.byte	0x2b
	.long	0x497
	.uleb128 0x14
	.long	0x2f6
	.long	.LLST8
	.uleb128 0x14
	.long	0x2ed
	.long	.LLST8
	.byte	0
	.uleb128 0x15
	.long	0x2dd
	.quad	.LBB42
	.quad	.LBE42
	.byte	0x1
	.byte	0x2c
	.long	0x4c5
	.uleb128 0x14
	.long	0x2f6
	.long	.LLST10
	.uleb128 0x14
	.long	0x2ed
	.long	.LLST10
	.byte	0
	.uleb128 0x1c
	.quad	.LVL10
	.long	0x817
	.uleb128 0x16
	.quad	.LVL11
	.long	0x802
	.uleb128 0x16
	.quad	.LVL13
	.long	0x802
	.byte	0
	.uleb128 0x17
	.long	.LASF57
	.byte	0x1
	.byte	0x32
	.long	0x2d7
	.quad	.LFB36
	.quad	.LFE36
	.uleb128 0x1
	.byte	0x9c
	.long	0x5a2
	.uleb128 0x18
	.string	"a"
	.byte	0x1
	.byte	0x32
	.long	0x2d7
	.long	.LLST12
	.uleb128 0x1b
	.long	0x372
	.quad	.LBB50
	.long	.Ldebug_ranges0+0xc0
	.byte	0x1
	.byte	0x34
	.long	0x577
	.uleb128 0x14
	.long	0x382
	.long	.LLST12
	.uleb128 0x15
	.long	0x2dd
	.quad	.LBB52
	.quad	.LBE52
	.byte	0x1
	.byte	0x24
	.long	0x569
	.uleb128 0x14
	.long	0x2f6
	.long	.LLST12
	.uleb128 0x14
	.long	0x2ed
	.long	.LLST12
	.byte	0
	.uleb128 0x16
	.quad	.LVL19
	.long	0x802
	.byte	0
	.uleb128 0x1d
	.long	0x300
	.quad	.LBB55
	.quad	.LBE55
	.byte	0x1
	.byte	0x34
	.uleb128 0x14
	.long	0x319
	.long	.LLST16
	.uleb128 0x14
	.long	0x310
	.long	.LLST17
	.byte	0
	.byte	0
	.uleb128 0x17
	.long	.LASF58
	.byte	0x1
	.byte	0x38
	.long	0x2d7
	.quad	.LFB37
	.quad	.LFE37
	.uleb128 0x1
	.byte	0x9c
	.long	0x5da
	.uleb128 0x1e
	.string	"a"
	.byte	0x1
	.byte	0x38
	.long	0x2d7
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x1e
	.string	"b"
	.byte	0x1
	.byte	0x39
	.long	0x2d7
	.uleb128 0x1
	.byte	0x54
	.byte	0
	.uleb128 0x12
	.long	0x325
	.quad	.LFB38
	.quad	.LFE38
	.uleb128 0x1
	.byte	0x9c
	.long	0x604
	.uleb128 0x13
	.long	0x335
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x13
	.long	0x33e
	.uleb128 0x1
	.byte	0x54
	.byte	0
	.uleb128 0x12
	.long	0x300
	.quad	.LFB39
	.quad	.LFE39
	.uleb128 0x1
	.byte	0x9c
	.long	0x630
	.uleb128 0x13
	.long	0x310
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x14
	.long	0x319
	.long	.LLST18
	.byte	0
	.uleb128 0x17
	.long	.LASF59
	.byte	0x1
	.byte	0x5b
	.long	0x2d7
	.quad	.LFB40
	.quad	.LFE40
	.uleb128 0x1
	.byte	0x9c
	.long	0x6ce
	.uleb128 0x1e
	.string	"a"
	.byte	0x1
	.byte	0x5b
	.long	0x2d7
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x1e
	.string	"b"
	.byte	0x1
	.byte	0x5c
	.long	0x2d7
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x19
	.string	"x"
	.byte	0x1
	.byte	0x5e
	.long	0x2d
	.uleb128 0x18
	.byte	0x75
	.sleb128 4
	.byte	0xf6
	.byte	0x4
	.uleb128 0x2d
	.byte	0x74
	.sleb128 8
	.byte	0xf6
	.byte	0x4
	.uleb128 0x2d
	.byte	0x1e
	.byte	0x75
	.sleb128 8
	.byte	0xf6
	.byte	0x4
	.uleb128 0x2d
	.byte	0x74
	.sleb128 4
	.byte	0xf6
	.byte	0x4
	.uleb128 0x2d
	.byte	0x1e
	.byte	0x1c
	.byte	0x9f
	.uleb128 0x19
	.string	"y"
	.byte	0x1
	.byte	0x5e
	.long	0x2d
	.uleb128 0x18
	.byte	0x75
	.sleb128 8
	.byte	0xf6
	.byte	0x4
	.uleb128 0x2d
	.byte	0x74
	.sleb128 0
	.byte	0xf6
	.byte	0x4
	.uleb128 0x2d
	.byte	0x1e
	.byte	0x74
	.sleb128 8
	.byte	0xf6
	.byte	0x4
	.uleb128 0x2d
	.byte	0x75
	.sleb128 0
	.byte	0xf6
	.byte	0x4
	.uleb128 0x2d
	.byte	0x1e
	.byte	0x1c
	.byte	0x9f
	.uleb128 0x19
	.string	"z"
	.byte	0x1
	.byte	0x5e
	.long	0x2d
	.uleb128 0x18
	.byte	0x74
	.sleb128 4
	.byte	0xf6
	.byte	0x4
	.uleb128 0x2d
	.byte	0x75
	.sleb128 0
	.byte	0xf6
	.byte	0x4
	.uleb128 0x2d
	.byte	0x1e
	.byte	0x75
	.sleb128 4
	.byte	0xf6
	.byte	0x4
	.uleb128 0x2d
	.byte	0x74
	.sleb128 0
	.byte	0xf6
	.byte	0x4
	.uleb128 0x2d
	.byte	0x1e
	.byte	0x1c
	.byte	0x9f
	.byte	0
	.uleb128 0x17
	.long	.LASF60
	.byte	0x1
	.byte	0x6b
	.long	0x2d7
	.quad	.LFB41
	.quad	.LFE41
	.uleb128 0x1
	.byte	0x9c
	.long	0x7d6
	.uleb128 0x18
	.string	"inc"
	.byte	0x1
	.byte	0x6b
	.long	0x2d7
	.long	.LLST19
	.uleb128 0x1f
	.long	.LASF61
	.byte	0x1
	.byte	0x6c
	.long	0x2d7
	.long	.LLST20
	.uleb128 0x20
	.long	.LASF62
	.byte	0x1
	.byte	0x6e
	.long	0x34
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x1b
	.long	0x2dd
	.quad	.LBB58
	.long	.Ldebug_ranges0+0xf0
	.byte	0x1
	.byte	0x71
	.long	0x745
	.uleb128 0x14
	.long	0x2f6
	.long	.LLST21
	.uleb128 0x14
	.long	0x2ed
	.long	.LLST22
	.byte	0
	.uleb128 0x1b
	.long	0x300
	.quad	.LBB65
	.long	.Ldebug_ranges0+0x140
	.byte	0x1
	.byte	0x71
	.long	0x76f
	.uleb128 0x14
	.long	0x319
	.long	.LLST23
	.uleb128 0x14
	.long	0x310
	.long	.LLST24
	.byte	0
	.uleb128 0x15
	.long	0x325
	.quad	.LBB72
	.quad	.LBE72
	.byte	0x1
	.byte	0x72
	.long	0x79d
	.uleb128 0x14
	.long	0x33e
	.long	.LLST25
	.uleb128 0x14
	.long	0x335
	.long	.LLST26
	.byte	0
	.uleb128 0x21
	.quad	.LVL29
	.long	0x82c
	.long	0x7bb
	.uleb128 0x22
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x2
	.byte	0x77
	.sleb128 0
	.uleb128 0x22
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x2
	.byte	0x76
	.sleb128 0
	.byte	0
	.uleb128 0x23
	.quad	.LVL33
	.long	0x82c
	.uleb128 0x22
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x2
	.byte	0x73
	.sleb128 0
	.uleb128 0x22
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x2
	.byte	0x77
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x24
	.long	.LASF63
	.byte	0x6
	.byte	0xa9
	.long	0x2a4
	.uleb128 0x24
	.long	.LASF64
	.byte	0x6
	.byte	0xaa
	.long	0x2a4
	.uleb128 0x24
	.long	.LASF63
	.byte	0x6
	.byte	0xa9
	.long	0x2a4
	.uleb128 0x24
	.long	.LASF64
	.byte	0x6
	.byte	0xaa
	.long	0x2a4
	.uleb128 0x25
	.long	.LASF65
	.byte	0x7
	.byte	0x9e
	.long	0x2d
	.long	0x817
	.uleb128 0x26
	.long	0x2d
	.byte	0
	.uleb128 0x25
	.long	.LASF66
	.byte	0x7
	.byte	0x37
	.long	0x2d
	.long	0x82c
	.uleb128 0x26
	.long	0x2d
	.byte	0
	.uleb128 0x27
	.long	.LASF71
	.byte	0x2
	.byte	0x3a
	.long	0x2d7
	.uleb128 0x26
	.long	0x2d7
	.uleb128 0x26
	.long	0x2d7
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
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
	.uleb128 0x3
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
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x5
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
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xf
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
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
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
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x2115
	.uleb128 0x19
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x2111
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x25
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
	.uleb128 0x26
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x27
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
	.uleb128 0x27
	.uleb128 0x19
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.quad	.LVL1-.Ltext0
	.quad	.LVL2-.Ltext0
	.value	0x1
	.byte	0x55
	.quad	.LVL2-.Ltext0
	.quad	.LVL3-.Ltext0
	.value	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x55
	.byte	0x9f
	.quad	.LVL3-.Ltext0
	.quad	.LVL4-1-.Ltext0
	.value	0x1
	.byte	0x55
	.quad	.LVL4-1-.Ltext0
	.quad	.LFE34-.Ltext0
	.value	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x55
	.byte	0x9f
	.quad	0
	.quad	0
.LLST3:
	.quad	.LVL5-.Ltext0
	.quad	.LVL7-.Ltext0
	.value	0x1
	.byte	0x55
	.quad	.LVL7-.Ltext0
	.quad	.LVL10-.Ltext0
	.value	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x55
	.byte	0x9f
	.quad	.LVL10-.Ltext0
	.quad	.LVL11-1-.Ltext0
	.value	0x1
	.byte	0x55
	.quad	.LVL11-1-.Ltext0
	.quad	.LFE35-.Ltext0
	.value	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x55
	.byte	0x9f
	.quad	0
	.quad	0
.LLST4:
	.quad	.LVL5-.Ltext0
	.quad	.LVL7-.Ltext0
	.value	0x1
	.byte	0x54
	.quad	.LVL7-.Ltext0
	.quad	.LVL10-.Ltext0
	.value	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x54
	.byte	0x9f
	.quad	.LVL10-.Ltext0
	.quad	.LVL11-1-.Ltext0
	.value	0x1
	.byte	0x54
	.quad	.LVL11-1-.Ltext0
	.quad	.LFE35-.Ltext0
	.value	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x54
	.byte	0x9f
	.quad	0
	.quad	0
.LLST5:
	.quad	.LVL8-.Ltext0
	.quad	.LVL9-.Ltext0
	.value	0x8
	.byte	0xf5
	.uleb128 0x13
	.uleb128 0x2d
	.byte	0xf5
	.uleb128 0x11
	.uleb128 0x2d
	.byte	0x1e
	.byte	0x9f
	.quad	.LVL9-.Ltext0
	.quad	.LVL10-1-.Ltext0
	.value	0x1
	.byte	0x63
	.quad	0
	.quad	0
.LLST8:
	.quad	.LVL6-.Ltext0
	.quad	.LVL7-.Ltext0
	.value	0x1
	.byte	0x55
	.quad	.LVL7-.Ltext0
	.quad	.LVL10-.Ltext0
	.value	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x55
	.byte	0x9f
	.quad	.LVL10-.Ltext0
	.quad	.LVL11-1-.Ltext0
	.value	0x1
	.byte	0x55
	.quad	.LVL11-1-.Ltext0
	.quad	.LFE35-.Ltext0
	.value	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x55
	.byte	0x9f
	.quad	0
	.quad	0
.LLST10:
	.quad	.LVL7-.Ltext0
	.quad	.LVL8-.Ltext0
	.value	0x1
	.byte	0x54
	.quad	.LVL12-.Ltext0
	.quad	.LVL13-1-.Ltext0
	.value	0x1
	.byte	0x54
	.quad	0
	.quad	0
.LLST12:
	.quad	.LVL14-.Ltext0
	.quad	.LVL15-.Ltext0
	.value	0x1
	.byte	0x55
	.quad	.LVL15-.Ltext0
	.quad	.LVL18-.Ltext0
	.value	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x55
	.byte	0x9f
	.quad	.LVL18-.Ltext0
	.quad	.LVL19-1-.Ltext0
	.value	0x1
	.byte	0x50
	.quad	.LVL19-1-.Ltext0
	.quad	.LFE36-.Ltext0
	.value	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x55
	.byte	0x9f
	.quad	0
	.quad	0
.LLST16:
	.quad	.LVL16-.Ltext0
	.quad	.LVL17-.Ltext0
	.value	0x1
	.byte	0x62
	.quad	0
	.quad	0
.LLST17:
	.quad	.LVL16-.Ltext0
	.quad	.LVL18-.Ltext0
	.value	0x1
	.byte	0x50
	.quad	0
	.quad	0
.LLST18:
	.quad	.LVL22-.Ltext0
	.quad	.LVL23-.Ltext0
	.value	0x1
	.byte	0x61
	.quad	.LVL23-.Ltext0
	.quad	.LFE39-.Ltext0
	.value	0x6
	.byte	0xf3
	.uleb128 0x3
	.byte	0xf5
	.uleb128 0x11
	.uleb128 0x2d
	.byte	0x9f
	.quad	0
	.quad	0
.LLST19:
	.quad	.LVL27-.Ltext0
	.quad	.LVL28-.Ltext0
	.value	0x1
	.byte	0x55
	.quad	.LVL28-.Ltext0
	.quad	.LVL35-.Ltext0
	.value	0x1
	.byte	0x53
	.quad	.LVL35-.Ltext0
	.quad	.LFE41-.Ltext0
	.value	0x1
	.byte	0x50
	.quad	0
	.quad	0
.LLST20:
	.quad	.LVL27-.Ltext0
	.quad	.LVL29-1-.Ltext0
	.value	0x1
	.byte	0x54
	.quad	.LVL29-1-.Ltext0
	.quad	.LVL36-.Ltext0
	.value	0x1
	.byte	0x56
	.quad	.LVL36-.Ltext0
	.quad	.LFE41-.Ltext0
	.value	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x54
	.byte	0x9f
	.quad	0
	.quad	0
.LLST21:
	.quad	.LVL29-.Ltext0
	.quad	.LVL35-.Ltext0
	.value	0x1
	.byte	0x53
	.quad	.LVL35-.Ltext0
	.quad	.LFE41-.Ltext0
	.value	0x1
	.byte	0x50
	.quad	0
	.quad	0
.LLST22:
	.quad	.LVL29-.Ltext0
	.quad	.LVL36-.Ltext0
	.value	0x1
	.byte	0x56
	.quad	.LVL36-.Ltext0
	.quad	.LFE41-.Ltext0
	.value	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x54
	.byte	0x9f
	.quad	0
	.quad	0
.LLST23:
	.quad	.LVL30-.Ltext0
	.quad	.LVL32-.Ltext0
	.value	0x1
	.byte	0x61
	.quad	0
	.quad	0
.LLST24:
	.quad	.LVL30-.Ltext0
	.quad	.LVL34-.Ltext0
	.value	0x1
	.byte	0x57
	.quad	.LVL34-.Ltext0
	.quad	.LFE41-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -48
	.byte	0x9f
	.quad	0
	.quad	0
.LLST25:
	.quad	.LVL31-.Ltext0
	.quad	.LVL35-.Ltext0
	.value	0x1
	.byte	0x53
	.quad	.LVL35-.Ltext0
	.quad	.LFE41-.Ltext0
	.value	0x1
	.byte	0x50
	.quad	0
	.quad	0
.LLST26:
	.quad	.LVL31-.Ltext0
	.quad	.LVL34-.Ltext0
	.value	0x1
	.byte	0x57
	.quad	.LVL34-.Ltext0
	.quad	.LFE41-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -48
	.byte	0x9f
	.quad	0
	.quad	0
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
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.quad	.LBB22-.Ltext0
	.quad	.LBE22-.Ltext0
	.quad	.LBB34-.Ltext0
	.quad	.LBE34-.Ltext0
	.quad	.LBB36-.Ltext0
	.quad	.LBE36-.Ltext0
	.quad	.LBB38-.Ltext0
	.quad	.LBE38-.Ltext0
	.quad	.LBB40-.Ltext0
	.quad	.LBE40-.Ltext0
	.quad	0
	.quad	0
	.quad	.LBB28-.Ltext0
	.quad	.LBE28-.Ltext0
	.quad	.LBB35-.Ltext0
	.quad	.LBE35-.Ltext0
	.quad	.LBB37-.Ltext0
	.quad	.LBE37-.Ltext0
	.quad	.LBB39-.Ltext0
	.quad	.LBE39-.Ltext0
	.quad	.LBB41-.Ltext0
	.quad	.LBE41-.Ltext0
	.quad	0
	.quad	0
	.quad	.LBB50-.Ltext0
	.quad	.LBE50-.Ltext0
	.quad	.LBB57-.Ltext0
	.quad	.LBE57-.Ltext0
	.quad	0
	.quad	0
	.quad	.LBB58-.Ltext0
	.quad	.LBE58-.Ltext0
	.quad	.LBB63-.Ltext0
	.quad	.LBE63-.Ltext0
	.quad	.LBB64-.Ltext0
	.quad	.LBE64-.Ltext0
	.quad	.LBB69-.Ltext0
	.quad	.LBE69-.Ltext0
	.quad	0
	.quad	0
	.quad	.LBB65-.Ltext0
	.quad	.LBE65-.Ltext0
	.quad	.LBB70-.Ltext0
	.quad	.LBE70-.Ltext0
	.quad	.LBB71-.Ltext0
	.quad	.LBE71-.Ltext0
	.quad	0
	.quad	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF24:
	.string	"_IO_buf_end"
.LASF54:
	.string	"myrt_vec_magnitude"
.LASF27:
	.string	"_IO_save_end"
.LASF22:
	.string	"_IO_write_end"
.LASF7:
	.string	"short int"
.LASF11:
	.string	"size_t"
.LASF50:
	.string	"myrt_vec_dot"
.LASF37:
	.string	"_offset"
.LASF21:
	.string	"_IO_write_ptr"
.LASF16:
	.string	"_flags"
.LASF23:
	.string	"_IO_buf_base"
.LASF61:
	.string	"norm"
.LASF67:
	.string	"GNU C 4.6.2 20111027 (Red Hat 4.6.2-1) -fpreprocessed -mtune=generic -march=x86-64 -ggdb -O3 -fPIC"
.LASF28:
	.string	"_markers"
.LASF18:
	.string	"_IO_read_end"
.LASF0:
	.string	"float"
.LASF13:
	.string	"long long int"
.LASF65:
	.string	"sqrtf"
.LASF36:
	.string	"_lock"
.LASF8:
	.string	"long int"
.LASF33:
	.string	"_cur_column"
.LASF48:
	.string	"_pos"
.LASF47:
	.string	"_sbuf"
.LASF58:
	.string	"myrt_vec_add"
.LASF15:
	.string	"_IO_FILE"
.LASF1:
	.string	"unsigned char"
.LASF60:
	.string	"myrt_vec_reflection"
.LASF6:
	.string	"signed char"
.LASF12:
	.string	"long long unsigned int"
.LASF66:
	.string	"acosf"
.LASF2:
	.string	"unsigned int"
.LASF45:
	.string	"_IO_marker"
.LASF35:
	.string	"_shortbuf"
.LASF32:
	.string	"_old_offset"
.LASF20:
	.string	"_IO_write_base"
.LASF44:
	.string	"_unused2"
.LASF17:
	.string	"_IO_read_ptr"
.LASF52:
	.string	"factor"
.LASF42:
	.string	"__pad5"
.LASF5:
	.string	"short unsigned int"
.LASF55:
	.string	"denom"
.LASF4:
	.string	"char"
.LASF14:
	.string	"myrt_vector"
.LASF69:
	.string	"/home/alex/c-programs/git-programs/myrt/src"
.LASF38:
	.string	"__pad1"
.LASF39:
	.string	"__pad2"
.LASF40:
	.string	"__pad3"
.LASF41:
	.string	"__pad4"
.LASF56:
	.string	"myrt_vec_angle"
.LASF46:
	.string	"_next"
.LASF57:
	.string	"myrt_vec_normalize"
.LASF3:
	.string	"long unsigned int"
.LASF49:
	.string	"double"
.LASF10:
	.string	"__off64_t"
.LASF9:
	.string	"__off_t"
.LASF29:
	.string	"_chain"
.LASF26:
	.string	"_IO_backup_base"
.LASF63:
	.string	"stdin"
.LASF51:
	.string	"myrt_vec_scale"
.LASF31:
	.string	"_flags2"
.LASF43:
	.string	"_mode"
.LASF19:
	.string	"_IO_read_base"
.LASF68:
	.string	"arch/vec_generic.c"
.LASF34:
	.string	"_vtable_offset"
.LASF59:
	.string	"myrt_vec_cross"
.LASF25:
	.string	"_IO_save_base"
.LASF53:
	.string	"myrt_vec_sub"
.LASF30:
	.string	"_fileno"
.LASF71:
	.string	"myrt_vec_copy"
.LASF64:
	.string	"stdout"
.LASF70:
	.string	"_IO_lock_t"
.LASF62:
	.string	"scaled_n"
	.ident	"GCC: (GNU) 4.6.2 20111027 (Red Hat 4.6.2-1)"
	.section	.note.GNU-stack,"",@progbits
