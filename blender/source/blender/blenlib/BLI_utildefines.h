/*
 * $Id$
 *
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The Original Code is Copyright (C) 2001-2002 by NaN Holding BV.
 * All rights reserved.
 *
 * The Original Code is: all of this file.
 *
 * Contributor(s): none yet.
 *
 * ***** END GPL LICENSE BLOCK *****
*/

#ifndef BLI_UTILDEFINES_H
#define BLI_UTILDEFINES_H

/** \file BLI_utildefines.h
 *  \ingroup bli
 */

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif


#define ELEM(a, b, c)           ( (a)==(b) || (a)==(c) )
#define ELEM3(a, b, c, d)       ( ELEM(a, b, c) || (a)==(d) )
#define ELEM4(a, b, c, d, e)    ( ELEM(a, b, c) || ELEM(a, d, e) )
#define ELEM5(a, b, c, d, e, f) ( ELEM(a, b, c) || ELEM3(a, d, e, f) )
#define ELEM6(a, b, c, d, e, f, g)      ( ELEM(a, b, c) || ELEM4(a, d, e, f, g) )
#define ELEM7(a, b, c, d, e, f, g, h)   ( ELEM3(a, b, c, d) || ELEM4(a, e, f, g, h) )
#define ELEM8(a, b, c, d, e, f, g, h, i)        ( ELEM4(a, b, c, d, e) || ELEM4(a, f, g, h, i) )
#define ELEM9(a, b, c, d, e, f, g, h, i, j)        ( ELEM4(a, b, c, d, e) || ELEM5(a, f, g, h, i, j) )
#define ELEM10(a, b, c, d, e, f, g, h, i, j, k)        ( ELEM4(a, b, c, d, e) || ELEM6(a, f, g, h, i, j, k) )
#define ELEM11(a, b, c, d, e, f, g, h, i, j, k, l)        ( ELEM4(a, b, c, d, e) || ELEM7(a, f, g, h, i, j, k, l) )

/* shift around elements */
#define SHIFT3(type, a, b, c) { type tmp; tmp = a; a = c; c = b; b = tmp; }
#define SHIFT4(type, a, b, c, d) { type tmp; tmp = a; a = d; d = c; c = b; b = tmp; }

/* min/max */
#define MIN2(x,y)               ( (x)<(y) ? (x) : (y) )
#define MIN3(x,y,z)             MIN2( MIN2((x),(y)) , (z) )
#define MIN4(x,y,z,a)           MIN2( MIN2((x),(y)) , MIN2((z),(a)) )

#define MAX2(x,y)               ( (x)>(y) ? (x) : (y) )
#define MAX3(x,y,z)             MAX2( MAX2((x),(y)) , (z) )
#define MAX4(x,y,z,a)           MAX2( MAX2((x),(y)) , MAX2((z),(a)) )

#define INIT_MINMAX(min, max) { (min)[0]= (min)[1]= (min)[2]= 1.0e30f; (max)[0]= (max)[1]= (max)[2]= -1.0e30f; }

#define INIT_MINMAX2(min, max) { (min)[0]= (min)[1]= 1.0e30f; (max)[0]= (max)[1]= -1.0e30f; }

#define DO_MIN(vec, min) { if( (min)[0]>(vec)[0] ) (min)[0]= (vec)[0];      \
							  if( (min)[1]>(vec)[1] ) (min)[1]= (vec)[1];   \
							  if( (min)[2]>(vec)[2] ) (min)[2]= (vec)[2]; } \

#define DO_MAX(vec, max) { if( (max)[0]<(vec)[0] ) (max)[0]= (vec)[0];		\
							  if( (max)[1]<(vec)[1] ) (max)[1]= (vec)[1];	\
							  if( (max)[2]<(vec)[2] ) (max)[2]= (vec)[2]; } \

#define DO_MINMAX(vec, min, max) { if( (min)[0]>(vec)[0] ) (min)[0]= (vec)[0]; \
							  if( (min)[1]>(vec)[1] ) (min)[1]= (vec)[1]; \
							  if( (min)[2]>(vec)[2] ) (min)[2]= (vec)[2]; \
							  if( (max)[0]<(vec)[0] ) (max)[0]= (vec)[0]; \
							  if( (max)[1]<(vec)[1] ) (max)[1]= (vec)[1]; \
							  if( (max)[2]<(vec)[2] ) (max)[2]= (vec)[2]; } \

#define DO_MINMAX2(vec, min, max) { if( (min)[0]>(vec)[0] ) (min)[0]= (vec)[0]; \
							  if( (min)[1]>(vec)[1] ) (min)[1]= (vec)[1]; \
							  if( (max)[0]<(vec)[0] ) (max)[0]= (vec)[0]; \
							  if( (max)[1]<(vec)[1] ) (max)[1]= (vec)[1]; }

/* some math and copy defines */

#ifndef SWAP
#define SWAP(type, a, b)        { type sw_ap; sw_ap=(a); (a)=(b); (b)=sw_ap; }
#endif

#define ABS(a)					( (a)<0 ? (-(a)) : (a) )

#define AVG2(x, y)		( 0.5 * ((x) + (y)) )

#define FTOCHAR(val) ((val)<=0.0f)? 0 : (((val)>(1.0f-0.5f/255.0f))? 255 : (char)((255.0f*(val))+0.5f))
#define FTOUSHORT(val) ((val >= 1.0f-0.5f/65535)? 65535: (val <= 0.0f)? 0: (unsigned short)(val*65535.0f + 0.5f))
#define F3TOCHAR3(v2,v1) (v1)[0]=FTOCHAR((v2[0])); (v1)[1]=FTOCHAR((v2[1])); (v1)[2]=FTOCHAR((v2[2]))
#define F3TOCHAR4(v2,v1) { (v1)[0]=FTOCHAR((v2[0])); (v1)[1]=FTOCHAR((v2[1])); (v1)[2]=FTOCHAR((v2[2])); \
						(v1)[3]=FTOCHAR((v2[3])); (v1)[3] = 255; }
#define F4TOCHAR4(v2,v1) { (v1)[0]=FTOCHAR((v2[0])); (v1)[1]=FTOCHAR((v2[1])); (v1)[2]=FTOCHAR((v2[2])); \
						(v1)[3]=FTOCHAR((v2[3])); (v1)[3]=FTOCHAR((v2[3])); }


#define VECCOPY(v1,v2)          {*(v1)= *(v2); *(v1+1)= *(v2+1); *(v1+2)= *(v2+2);}
#define VECCOPY2D(v1,v2)          {*(v1)= *(v2); *(v1+1)= *(v2+1);}
#define QUATCOPY(v1,v2)         {*(v1)= *(v2); *(v1+1)= *(v2+1); *(v1+2)= *(v2+2); *(v1+3)= *(v2+3);}
#define LONGCOPY(a, b, c)	{int lcpc=c, *lcpa=(int *)a, *lcpb=(int *)b; while(lcpc-->0) *(lcpa++)= *(lcpb++);}


#define VECADD(v1,v2,v3) 	{*(v1)= *(v2) + *(v3); *(v1+1)= *(v2+1) + *(v3+1); *(v1+2)= *(v2+2) + *(v3+2);}
#define VECSUB(v1,v2,v3) 	{*(v1)= *(v2) - *(v3); *(v1+1)= *(v2+1) - *(v3+1); *(v1+2)= *(v2+2) - *(v3+2);}
#define VECSUB2D(v1,v2,v3) 	{*(v1)= *(v2) - *(v3); *(v1+1)= *(v2+1) - *(v3+1);}
#define VECADDFAC(v1,v2,v3,fac) {*(v1)= *(v2) + *(v3)*(fac); *(v1+1)= *(v2+1) + *(v3+1)*(fac); *(v1+2)= *(v2+2) + *(v3+2)*(fac);}
#define VECSUBFAC(v1,v2,v3,fac) {*(v1)= *(v2) - *(v3)*(fac); *(v1+1)= *(v2+1) - *(v3+1)*(fac); *(v1+2)= *(v2+2) - *(v3+2)*(fac);}
#define QUATADDFAC(v1,v2,v3,fac) {*(v1)= *(v2) + *(v3)*(fac); *(v1+1)= *(v2+1) + *(v3+1)*(fac); *(v1+2)= *(v2+2) + *(v3+2)*(fac); *(v1+3)= *(v2+3) + *(v3+3)*(fac);}

#define INPR(v1, v2)		( (v1)[0]*(v2)[0] + (v1)[1]*(v2)[1] + (v1)[2]*(v2)[2] )

/* some misc stuff.... */
#define CLAMP(a, b, c)		if((a)<(b)) (a)=(b); else if((a)>(c)) (a)=(c)
#define CLAMPIS(a, b, c) ((a)<(b) ? (b) : (a)>(c) ? (c) : (a))
#define CLAMPTEST(a, b, c)	if((b)<(c)) {CLAMP(a, b, c);} else {CLAMP(a, c, b);}

#define IS_EQ(a,b) ((fabs((double)(a)-(b)) >= (double) FLT_EPSILON) ? 0 : 1)
#define IS_EQF(a,b) ((fabsf((float)(a)-(b)) >= (float) FLT_EPSILON) ? 0 : 1)

#define IS_EQT(a, b, c) ((a > b)? (((a-b) <= c)? 1:0) : ((((b-a) <= c)? 1:0)))
#define IN_RANGE(a, b, c) ((b < c)? ((b<a && a<c)? 1:0) : ((c<a && a<b)? 1:0))
#define IN_RANGE_INCL(a, b, c) ((b < c)? ((b<=a && a<=c)? 1:0) : ((c<=a && a<=b)? 1:0))

/* array helpers */
#define ARRAY_LAST_ITEM(arr_start, arr_dtype, elem_size, tot) 		(arr_dtype *)((char*)arr_start + (elem_size*(tot - 1)))
#define ARRAY_HAS_ITEM(item, arr_start, arr_dtype, elem_size, tot) 	((item >= arr_start) && (item <= ARRAY_LAST_ITEM(arr_start, arr_dtype, elem_size, tot)))

/* This one rotates the bytes in an int64, int (32) and short (16) */
#define SWITCH_INT64(a) { \
	char s_i, *p_i; \
	p_i= (char *)&(a); \
	s_i=p_i[0]; p_i[0]=p_i[7]; p_i[7]=s_i; \
	s_i=p_i[1]; p_i[1]=p_i[6]; p_i[6]=s_i; \
	s_i=p_i[2]; p_i[2]=p_i[5]; p_i[5]=s_i; \
	s_i=p_i[3]; p_i[3]=p_i[4]; p_i[4]=s_i; }

		#define SWITCH_INT(a) { \
	char s_i, *p_i; \
	p_i= (char *)&(a); \
	s_i=p_i[0]; p_i[0]=p_i[3]; p_i[3]=s_i; \
	s_i=p_i[1]; p_i[1]=p_i[2]; p_i[2]=s_i; }

#define SWITCH_SHORT(a)	{ \
	char s_i, *p_i; \
	p_i= (char *)&(a); \
	s_i=p_i[0]; p_i[0]=p_i[1]; p_i[1]=s_i; }


/* Warning-free macros for storing ints in pointers. Use these _only_
 * for storing an int in a pointer, not a pointer in an int (64bit)! */
#define SET_INT_IN_POINTER(i) ((void*)(intptr_t)(i))
#define GET_INT_FROM_POINTER(i) ((int)(intptr_t)(i))

/* Macro to convert a value to string in the preprocessor
 * STRINGIFY_ARG: gives the defined name in the string
 * STRINGIFY: gives the defined value. */
#define STRINGIFY_ARG(x) #x
#define STRINGIFY(x) STRINGIFY_ARG(x)

/* useful for debugging */
#define AT __FILE__ ":" STRINGIFY(__LINE__)

/* UNUSED macro, for function argument */
#ifdef __GNUC__
#  define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))
#else
#  define UNUSED(x) UNUSED_ ## x
#endif

#ifdef __GNUC__
#  define UNUSED_FUNCTION(x) __attribute__((__unused__)) UNUSED_ ## x
#else
#  define UNUSED_FUNCTION(x) UNUSED_ ## x
#endif

#ifdef __GNUC__
#  define WARN_UNUSED  __attribute__((warn_unused_result))
#else
#  define WARN_UNUSED
#endif

/*little macro so inline keyword works*/
#if defined(_MSC_VER)
#  define BM_INLINE static __forceinline
#elif defined(__GNUC__)
#  define BM_INLINE static inline __attribute((always_inline))
#else
/* #warning "MSC/GNUC defines not found, inline non-functional" */
#  define BM_INLINE static
#endif


/* BLI_assert(), default only to print
 * for aborting need to define WITH_ASSERT_ABORT
 */
#if !defined NDEBUG
#  ifdef WITH_ASSERT_ABORT
#    define _dummy_abort abort
#  else
#    define _dummy_abort() (void)0
#  endif
#  ifdef __GNUC__ /* just want to check if __func__ is available */
#    define BLI_assert(a) \
do { \
	if (!(a)) { \
		fprintf(stderr, \
			"BLI_assert failed: %s, %s(), %d at \'%s\'\n", \
			__FILE__, __func__, __LINE__, STRINGIFY(a)); \
		_dummy_abort(); \
	} \
} while (0)
#  else
#    define BLI_assert(a) \
do { \
	if (0 == (a)) { \
		fprintf(stderr, \
			"BLI_assert failed: %s, %d at \'%s\'\n", \
			__FILE__, __LINE__, STRINGIFY(a)); \
		_dummy_abort(); \
	} \
} while (0)
#  endif
#else
#  define BLI_assert(a) (void)0
#endif

#endif // BLI_UTILDEFINES_H
