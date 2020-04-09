/*
 *  Zapping (TV viewer for the Gnome Desktop)
 *  SWAR color conversion routines
 *
 *  Copyright (C) 2001 Michael H. Schimek <mschimek@users.sf.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/* Generated file - do not edit */

#ifndef _GEN_CONV_H__
#define _GEN_CONV_H__

extern void mmx_rgb565_yuyv(unsigned char *d, unsigned char *s, int w, int h, int d_stride, int s_stride);
extern void mmx_rgb565_yuv420(unsigned char *d, unsigned char *d_u, unsigned char *d_v, unsigned char *s, int w, int h, int d_stride, int d_uv_stride, int s_stride);

#endif /* _GEN_CONV_H__ */
