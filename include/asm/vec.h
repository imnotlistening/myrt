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
 * Assembly stuff for the vector algebra.
 */

#ifndef _ASM_VEC_H_
#define _ASM_VEC_H_

/* If we don't have SSE4 instructions then don't use the dpps instruction. */
#ifndef _NO_SSE4
#define __HAVE_SSE4
#endif

/*
 * Macros the ABI prolog and epilog.
 */
.macro PROLOG
	 push	%rbp
	 mov	%rsp, %rbp
.endm

.macro EPILOG
	 emms
	 mov	%rbp, %rsp
	 pop	%rbp
.endm

/*
 * Macros to preserve ABI compatibility without using the base pointer.
 */
.macro NORBP_PROLOG space=0
.if \space != 0
	 sub	\space, %rsp
.endif
.endm

.macro NORBP_EPILOG space=0
	 emms
.if \space != 0
	 add	\space, %rsp
.endif
	 ret
.endm


#endif
