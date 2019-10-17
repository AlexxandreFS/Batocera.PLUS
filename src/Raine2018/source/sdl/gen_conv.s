#
#  Zapping (TV viewer for the Gnome Desktop)
#  SWAR color conversion routines
#
#  Copyright (C) 2001 Michael H. Schimek <mschimek@users.sf.net>
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License version 2 as
#  published by the Free Software Foundation.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#  Generated file - do not edit

		.data
#ifdef DARWIN
		.align 8
#else
		.align 32
#endif

.L3:
		.long		0x00ff00ff, 0x00ff00ff
.L4:
		.long		0x00800080, 0x00800080
.L5:
		.long		0x4a854a85, 0x4a854a85
.L6:
		.long		0x0c880c88, 0x0c880c88
.L7:
		.long		0x408d408d, 0x408d408d
.L8:
		.long		0x66256625, 0x66256625
.L9:
		.long		0x34053405, 0x34053405
.L12:
		.long		0x00100010, 0x00100010
.L27:
		.long		0xf8f8f8f8, 0xf8f8f8f8
.L28:
		.long		0xe0e0e0e0, 0xe0e0e0e0
.L45:
		.long		0x41bd41bd, 0x41bd41bd
.L46:
		.long		0x40874087, 0x40874087
.L47:
		.long		0x19101910, 0x19101910
.L48:
		.long		0x6dee6dee, 0x6dee6dee
.L49:
		.long		0x36f736f7, 0x36f736f7
.L50:
		.long		0x093c093c, 0x093c093c
.L51:
		.long		0x0bac0bac, 0x0bac0bac
.L52:
		.long		0x01080108, 0x01080108
.L53:
		.long		0x80808080, 0x80808080
.L62:
		.long		0x001f001f, 0x001f001f
		.text
#ifdef DARWIN
		.align 8
#else
		.align		16
#endif
		.globl		mmx_rgb565_yuyv
		.globl		_mmx_rgb565_yuyv
# prototype :
# void mmx_rgb565_yuyv(unsigned char *d, unsigned char *s, int w, int h, int d_stride, int s_stride);
mmx_rgb565_yuyv:
_mmx_rgb565_yuyv:
		pushl		%edi
		pushl		%esi
		pushl		%ebx
		movl		0+12+12(%esp),%ecx
		movl		0+12+24(%esp),%eax
		addl		%ecx,%ecx
		movl		0+12+20(%esp),%ebx
		subl		%ecx,%eax
		movl		0+12+12(%esp),%ecx
		addl		%ecx,%ecx
		movl		0+12+16(%esp),%edx
		subl		%ecx,%ebx
		movl		0+12+8(%esp),%esi
		movl		0+12+4(%esp),%edi
#ifndef DARWIN
		.align 16
#endif
.L61:
		movl		0+12+12(%esp),%ecx
.L60:
		movq		(%esi),%mm2
		movq		8(%esi),%mm6
		addl		$16,%esi
		movq		%mm2,%mm0
		punpcklwd	%mm6,%mm2
		punpckhwd	%mm6,%mm0
		movq		%mm2,%mm6
		punpcklwd	%mm0,%mm2
		punpckhwd	%mm0,%mm6
		movq		.L62,%mm4
		movq		%mm2,%mm0
		pand		%mm4,%mm0
		pxor		%mm0,%mm2
		movq		%mm0,%mm5
		psllw		$3,%mm5
		psrlw		$2,%mm0
		por		%mm5,%mm0
		psllw		$11,%mm4
		pand		%mm2,%mm4
		pxor		%mm4,%mm2
		movq		%mm4,%mm5
		psrlw		$8,%mm5
		psrlw		$13,%mm4
		por		%mm5,%mm4
		movq		%mm2,%mm5
		psrlw		$3,%mm5
		psrlw		$9,%mm2
		por		%mm5,%mm2
		psllw		$4,%mm0
		movq		%mm0,%mm1
		pmulhw		.L45,%mm0
		psllw		$5,%mm2
		pmulhw		.L46,%mm2
		psllw		$4,%mm4
		movq		%mm4,%mm3
		pmulhw		.L47,%mm4
		paddw		%mm2,%mm0
		paddw		%mm4,%mm0
		movq		.L62,%mm4
		movq		%mm6,%mm2
		pand		%mm4,%mm2
		pxor		%mm2,%mm6
		movq		%mm2,%mm5
		psllw		$3,%mm5
		psrlw		$2,%mm2
		por		%mm5,%mm2
		psllw		$11,%mm4
		pand		%mm6,%mm4
		pxor		%mm4,%mm6
		movq		%mm4,%mm5
		psrlw		$8,%mm5
		psrlw		$13,%mm4
		por		%mm5,%mm4
		movq		%mm6,%mm5
		psrlw		$3,%mm5
		psrlw		$9,%mm6
		por		%mm5,%mm6
		psllw		$4,%mm2
		paddw		%mm2,%mm1
		pmulhw		.L45,%mm2
		psllw		$5,%mm6
		pmulhw		.L46,%mm6
		psllw		$4,%mm4
		paddw		%mm4,%mm3
		pmulhw		.L47,%mm4
		movq		.L48,%mm5
		paddw		%mm6,%mm2
		paddw		%mm4,%mm2
		pmulhw		%mm5,%mm1
		movq		%mm0,%mm4
		pmulhw		%mm5,%mm3
		movq		.L52,%mm5
		paddw		%mm2,%mm4
		psrlw		$1,%mm4
		psubw		%mm4,%mm1
		pmulhw		.L51,%mm1
		psubw		%mm4,%mm3
		pmulhw		.L50,%mm3
		packsswb	%mm1,%mm3
		paddw		%mm5,%mm0
		psrlw		$4,%mm0
		pxor		.L53,%mm3
		paddw		%mm5,%mm2
		psrlw		$4,%mm2
		packuswb	%mm2,%mm0
		movq		%mm0,%mm2
		punpcklbw	%mm3,%mm0
		punpckhbw	%mm3,%mm2
		movq		%mm0,%mm3
		punpcklwd	%mm2,%mm0
		punpckhwd	%mm2,%mm3
		movq		%mm0,(%edi)
		movq		%mm3,8(%edi)
		addl		$16,%edi
		subl		$8,%ecx
		jne		.L60

		addl		%eax,%esi
		addl		%ebx,%edi

		decl		%edx
		jne		.L61
		emms
		popl		%ebx
		popl		%esi
		popl		%edi
		ret

		.text
#ifndef DARWIN
		.align		16
#endif
		.globl		mmx_rgb565_yuv420
		.globl		_mmx_rgb565_yuv420
# protocol :
# extern void mmx_rgb565_yuv420(unsigned char *d, unsigned char *d_u, unsigned char *d_v, unsigned char *s, int w, int h, int d_stride, int d_uv_stride, int s_stride);
mmx_rgb565_yuv420:
_mmx_rgb565_yuv420:
		pushl		%ebx
		pushl		%ebp
		pushl		%esi
		pushl		%edi
		leal		-24(%esp),%esp
		t99 = 0
		t100 = 4
		t101 = 8
		t102 = 12
		t103 = 16
		t104 = 20
		movl		24+16+20(%esp),%ebx
		movl		%ebx,t102(%esp)
		shrl		$1,%ebx
		movl		24+16+32(%esp),%eax
		subl		%ebx,%eax
		movl		%eax,t101(%esp)
		movl		24+16+28(%esp),%eax
		addl		%ebx,%ebx
		movl		24+16+4(%esp),%edi
		movl		%eax,%edx
		movl		24+16+36(%esp),%esi
		subl		%ebx,%eax
		movl		%eax,t100(%esp)
		addl		%ebx,%ebx
		movl		%esi,%ebp
		movl		24+16+24(%esp),%eax
		subl		%ebx,%esi
		movl		24+16+12(%esp),%ebx
		movl		%esi,t99(%esp)
		movl		24+16+16(%esp),%esi
		movl		%eax,t103(%esp)
		movl		24+16+8(%esp),%eax
#ifndef DARWIN
		.align 16
#endif
.L78:
		movl		t102(%esp),%ecx
.L77:
		movq		(%esi),%mm2
		movq		8(%esi),%mm6
		movq		%mm2,%mm0
		punpcklwd	%mm6,%mm2
		punpckhwd	%mm6,%mm0
		movq		%mm2,%mm6
		punpcklwd	%mm0,%mm2
		punpckhwd	%mm0,%mm6
		movq		.L62,%mm4
		movq		%mm2,%mm0
		pand		%mm4,%mm0
		pxor		%mm0,%mm2
		movq		%mm0,%mm5
		psllw		$3,%mm5
		psrlw		$2,%mm0
		por		%mm5,%mm0
		psllw		$11,%mm4
		pand		%mm2,%mm4
		pxor		%mm4,%mm2
		movq		%mm4,%mm5
		psrlw		$8,%mm5
		psrlw		$13,%mm4
		por		%mm5,%mm4
		movq		%mm2,%mm5
		psrlw		$3,%mm5
		psrlw		$9,%mm2
		por		%mm5,%mm2
		psllw		$4,%mm0
		movq		%mm0,%mm1
		pmulhw		.L45,%mm0
		psllw		$5,%mm2
		pmulhw		.L46,%mm2
		psllw		$4,%mm4
		movq		%mm4,%mm3
		pmulhw		.L47,%mm4
		paddw		%mm2,%mm0
		paddw		%mm4,%mm0
		movq		.L62,%mm4
		movq		%mm6,%mm2
		pand		%mm4,%mm2
		pxor		%mm2,%mm6
		movq		%mm2,%mm5
		psllw		$3,%mm5
		psrlw		$2,%mm2
		por		%mm5,%mm2
		psllw		$11,%mm4
		pand		%mm6,%mm4
		pxor		%mm4,%mm6
		movq		%mm4,%mm5
		psrlw		$8,%mm5
		psrlw		$13,%mm4
		por		%mm5,%mm4
		movq		%mm6,%mm5
		psrlw		$3,%mm5
		psrlw		$9,%mm6
		por		%mm5,%mm6
		psllw		$4,%mm2
		paddw		%mm2,%mm1
		pmulhw		.L45,%mm2
		psllw		$5,%mm6
		pmulhw		.L46,%mm6
		psllw		$4,%mm4
		paddw		%mm4,%mm3
		pmulhw		.L47,%mm4
		paddw		%mm6,%mm2
		paddw		%mm4,%mm2
		movq		.L52,%mm4
		movq		%mm0,%mm7
		paddw		%mm2,%mm7
		paddw		%mm4,%mm0
		psrlw		$4,%mm0
		packuswb	%mm0,%mm0
		paddw		%mm4,%mm2
		psrlw		$4,%mm2
		packuswb	%mm2,%mm2
		punpcklbw	%mm2,%mm0
		movq		%mm0,(%edi)
		movq		(%esi,%ebp),%mm2
		movq		8(%esi,%ebp),%mm6
		addl		$16,%esi
		movq		%mm2,%mm0
		punpcklwd	%mm6,%mm2
		punpckhwd	%mm6,%mm0
		movq		%mm2,%mm6
		punpcklwd	%mm0,%mm2
		punpckhwd	%mm0,%mm6
		movq		.L62,%mm4
		movq		%mm2,%mm0
		pand		%mm4,%mm0
		pxor		%mm0,%mm2
		movq		%mm0,%mm5
		psllw		$3,%mm5
		psrlw		$2,%mm0
		por		%mm5,%mm0
		psllw		$11,%mm4
		pand		%mm2,%mm4
		pxor		%mm4,%mm2
		movq		%mm4,%mm5
		psrlw		$8,%mm5
		psrlw		$13,%mm4
		por		%mm5,%mm4
		movq		%mm2,%mm5
		psrlw		$3,%mm5
		psrlw		$9,%mm2
		por		%mm5,%mm2
		psllw		$4,%mm0
		paddw		%mm0,%mm1
		pmulhw		.L45,%mm0
		psllw		$5,%mm2
		pmulhw		.L46,%mm2
		psllw		$4,%mm4
		paddw		%mm4,%mm3
		pmulhw		.L47,%mm4
		paddw		%mm2,%mm0
		paddw		%mm4,%mm0
		movq		.L62,%mm4
		movq		%mm6,%mm2
		pand		%mm4,%mm2
		pxor		%mm2,%mm6
		movq		%mm2,%mm5
		psllw		$3,%mm5
		psrlw		$2,%mm2
		por		%mm5,%mm2
		psllw		$11,%mm4
		pand		%mm6,%mm4
		pxor		%mm4,%mm6
		movq		%mm4,%mm5
		psrlw		$8,%mm5
		psrlw		$13,%mm4
		por		%mm5,%mm4
		movq		%mm6,%mm5
		psrlw		$3,%mm5
		psrlw		$9,%mm6
		por		%mm5,%mm6
		psllw		$4,%mm2
		paddw		%mm2,%mm1
		pmulhw		.L45,%mm2
		psllw		$5,%mm6
		pmulhw		.L46,%mm6
		psllw		$4,%mm4
		paddw		%mm4,%mm3
		pmulhw		.L47,%mm4
		paddw		%mm6,%mm2
		paddw		%mm4,%mm2
		movq		.L52,%mm4
		movq		%mm0,%mm5
		paddw		%mm2,%mm5
		paddw		%mm7,%mm5
		paddw		%mm4,%mm0
		psrlw		$4,%mm0
		packuswb	%mm0,%mm0
		paddw		%mm4,%mm2
		psrlw		$4,%mm2
		packuswb	%mm2,%mm2
		movq		.L49,%mm6
		punpcklbw	%mm2,%mm0
		psrlw		$2,%mm5
		movq		%mm0,(%edi,%edx)
		pmulhw		%mm6,%mm1
		pmulhw		%mm6,%mm3
		psubw		%mm5,%mm1
		pmulhw		.L51,%mm1
		psubw		%mm5,%mm3
		pmulhw		.L50,%mm3
		packsswb	%mm1,%mm3
		pxor		.L53,%mm3
		movd		%mm3,(%eax)
		psrlq		$32,%mm3
		movd		%mm3,(%ebx)
		addl		$8,%edi
		addl		$4,%eax
		addl		$4,%ebx
		subl		$8,%ecx
		jne		.L77
		addl		t99(%esp),%esi
		addl		%ebp,%esi
		movl		t101(%esp),%ecx
		addl		%ecx,%eax
		addl		t100(%esp),%edi
		addl		%edx,%edi
		addl		%ecx,%ebx
		subl		$2,t103(%esp)
		jne		.L78
		leal		24(%esp),%esp
		emms
		popl		%edi
		popl		%esi
		popl		%ebp
		popl		%ebx
		ret

