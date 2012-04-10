/*
 * (C) Copyright 2011
 * Alex Waterman <imNotListening@gmail.com>
 *
 * myrt is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * myrt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with myrt.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Assembly implementation of basic vector algebra.
 */

#include <asm/vec.h>

.extern	myrt_vec_copy@PLT
.extern acosf@PLT

/*
 * inline struct myrt_vector *myrt_vec_add(struct myrt_vector *a,
 *					   struct myrt_vector *b)
 *
 * Add two vectors. The vectors are stored as packed floating point values
 * aligned on a 16 byte boundary.
 */
.globl	myrt_vec_add
.type	myrt_vec_add @function
myrt_vec_add:
	NORBP_PROLOG

	movaps	(%rsi), %xmm8
	addps	(%rdi), %xmm8
	movaps	%xmm8, (%rdi)
	mov	%rdi, %rax

	NORBP_EPILOG

.globl	myrt_vec_sub
.type	myrt_vec_sub @function
myrt_vec_sub:
	NORBP_PROLOG

	movaps	(%rdi), %xmm8
	subps	(%rsi), %xmm8
	movaps	%xmm8, (%rdi)
	mov	%rdi, %rax

	NORBP_EPILOG

.globl	myrt_vec_dot
.type	myrt_vec_dot @function
myrt_vec_dot:
	NORBP_PROLOG

	movaps	(%rsi), %xmm0
#ifdef	__HAVE_SSE4
	dpps	$0xf1, (%rdi), %xmm0
#else
	mulps	(%rdi), %xmm0
	haddps	%xmm0, %xmm0
	haddps	%xmm0, %xmm0
#endif
	NORBP_EPILOG

.globl	myrt_vec_magnitude
.type	myrt_vec_magnitude @function
myrt_vec_magnitude:
	NORBP_PROLOG

	movaps	(%rdi), %xmm0
#ifdef	__HAVE_SSE4
	dpps	$0xf1, %xmm0, %xmm0
#else
	mulps	%xmm0, %xmm0
	haddps	%xmm0, %xmm0
	haddps	%xmm0, %xmm0
#endif

	sqrtss	%xmm0, %xmm0

	NORBP_EPILOG

.globl	myrt_vec_angle
.type	myrt_vec_angle @function
myrt_vec_angle:
	NORBP_PROLOG

	/* First compute the dot product of a and b. */
	movaps	(%rsi), %xmm0
	movaps	(%rdi), %xmm1
	movaps	%xmm0, %xmm2
#ifdef	__HAVE_SSE4
	dpps	$0xf1, %xmm1, %xmm0
#else
	mulps	%xmm1, %xmm0
	haddps	%xmm0, %xmm0
	haddps	%xmm0, %xmm0
#endif

	/*
	 * We now have dot(a, b) in xmm0. Next we must compute the magnitude
	 * of a and b and multiply them.
	 */
#ifdef	__HAVE_SSE4
	dpps	$0xf1, %xmm1, %xmm1
#else
	mulps	%xmm1, %xmm1
	haddps	%xmm1, %xmm1
	haddps	%xmm1, %xmm1
#endif
	sqrtss	%xmm1, %xmm1
	
#ifdef	__HAVE_SSE4
	dpps	$0xf1, %xmm2, %xmm2
#else
	mulps	%xmm2, %xmm2
	haddps	%xmm2, %xmm2
	haddps	%xmm2, %xmm2
#endif
	sqrtss	%xmm2, %xmm2

	/*
	 * Ok, compute product and then inverse cosine.
	 */
	mulss	%xmm1, %xmm2
	divss	%xmm2, %xmm0
	emms
	call	acosf@PLT
	
	NORBP_EPILOG

.globl	myrt_vec_normalize
.type	myrt_vec_normalize @function
myrt_vec_normalize:
	NORBP_PROLOG

	movaps	(%rdi), %xmm0
	movaps	%xmm0, %xmm1
#ifdef	__HAVE_SSE4
	dpps	$0xff, %xmm0, %xmm0
#else
	mulps	%xmm0, %xmm0
	haddps	%xmm0, %xmm0
	haddps	%xmm0, %xmm0
#endif
	
	sqrtps	%xmm0, %xmm0
	divps	%xmm0, %xmm1
	movaps	%xmm1, (%rdi)
	
	mov	%rdi, %rax
	
	NORBP_EPILOG

.globl	myrt_vec_scale
.type	myrt_vec_scale @function
myrt_vec_scale:
	NORBP_PROLOG

	movaps	(%rdi), %xmm1
	shufps	$0x0, %xmm0, %xmm0
	mulps	%xmm0, %xmm1
	movaps	%xmm1, (%rdi)
	mov	%rdi, %rax

	NORBP_EPILOG

.globl	myrt_vec_cross
.type	myrt_vec_cross @function
myrt_vec_cross:
	NORBP_PROLOG

	/* Load the passed vectors. */
	movaps	(%rdi), %xmm0
	movaps	(%rsi), %xmm1

	/* Set up the vectors to be multiplied and what not. */
	pshufd	$0xc9, %xmm0, %xmm8  /* A0 */
	pshufd	$0xd2, %xmm0, %xmm9  /* A1 */
	pshufd	$0xc9, %xmm1, %xmm10 /* B1 */
	pshufd	$0xd2, %xmm1, %xmm11 /* B0 */

	/* Compute the intermediate products */
	mulps	%xmm8, %xmm11
	mulps	%xmm9, %xmm10

	/* Subtract. */
	subps	%xmm10, %xmm11
	movaps	%xmm11, (%rdi)
	mov	%rdi, %rax
	
	NORBP_EPILOG

.globl	myrt_vec_reflection
.type	myrt_vec_reflection @function
myrt_vec_reflection:
	NORBP_PROLOG

	/* Load inc and norm, then copy norm. */
	movaps	(%rdi), %xmm0
	movaps	(%rsi), %xmm1
	movaps	%xmm1, %xmm8
	
	/* Dot of norm and inc. */
#ifdef	__HAVE_SSE4
	dpps	$0xf1, %xmm0, %xmm1
#else
	mulps	%xmm0, %xmm1
	haddps	%xmm1, %xmm1
	haddps	%xmm1, %xmm1
#endif
	/* 2 * dot(inc, norm) */
	addps	%xmm1, %xmm1
	
	/* Scale the vector xmm1 */
	shufps	$0x0, %xmm1, %xmm1
	mulps	%xmm1, %xmm8

	subps	%xmm0, %xmm8
	movaps	%xmm8, (%rdi)
	mov	%rdi, %rax
	
	NORBP_EPILOG