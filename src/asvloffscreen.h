/*******************************************************************************
Copyright(c) ArcSoft, All right reserved.

This file is ArcSoft's property. It contains ArcSoft's trade secret, proprietary 
and confidential information. 

The information and code contained in this file is only for authorized ArcSoft 
employees to design, create, modify, or review.

DO NOT DISTRIBUTE, DO NOT DUPLICATE OR TRANSMIT IN ANY FORM WITHOUT PROPER 
AUTHORIZATION.

If you are not an intended recipient of this file, you must not copy, 
distribute, modify, or take any action in reliance on it. 

If you have received this file in error, please immediately notify ArcSoft and 
permanently delete the original and any copy of any file and any printout 
thereof.
*******************************************************************************/
#ifndef __ASVL_OFFSCREEN_H__
#define __ASVL_OFFSCREEN_H__

#include "amcomdef.h"

#ifdef __cplusplus
extern "C" {
#endif


/*31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00 */


/* R  R  R  R  R  G  G  G  G  G  G  B  B  B  B  B */
#define		ASVL_PAF_RGB16_B5G6R5		0x101
/* X  R  R  R  R  R  G  G  G  G  G  B  B  B  B  B */
#define		ASVL_PAF_RGB16_B5G5R5		0x102
/* X  X  X  X  R  R  R  R  G  G  G  G  B  B  B  B */
#define		ASVL_PAF_RGB16_B4G4R4		0x103
/* T  R  R  R  R  R  G  G  G  G  G  B  B  B  B  B */ 
#define		ASVL_PAF_RGB16_B5G5R5T		0x104
/* B  B  B  B  B  G  G  G  G  G  G  R  R  R  R  R */ 
#define		ASVL_PAF_RGB16_R5G6B5		0x105
/* X  B  B  B  B  B  G  G  G  G  G  R  R  R  R  R */  
#define		ASVL_PAF_RGB16_R5G5B5		0x106
/* X  X  X  X  B  B  B  B  G  G  G  G  R  R  R  R */ 
#define		ASVL_PAF_RGB16_R4G4B4		0x107


/* R	R  R  R	 R	R  R  R  G  G  G  G  G  G  G  G  B  B  B  B  B  B  B  B */
#define		ASVL_PAF_RGB24_B8G8R8		0x201
/* X	X  X  X	 X	X  R  R  R  R  R  R  G  G  G  G  G  G  B  B  B  B  B  B */ 
#define		ASVL_PAF_RGB24_B6G6R6		0x202
/* X	X  X  X	 X	T  R  R  R  R  R  R  G  G  G  G  G  G  B  B  B  B  B  B */ 
#define		ASVL_PAF_RGB24_B6G6R6T		0x203
/* B  B  B  B  B  B  B  B  G  G  G  G  G  G  G  G  R	R  R  R	 R	R  R  R */
#define		ASVL_PAF_RGB24_R8G8B8		0x204
/* X	X  X  X	 X	X  B  B  B  B  B  B  G  G  G  G  G  G  R  R  R  R  R  R */
#define		ASVL_PAF_RGB24_R6G6B6		0x205

/* X	X  X  X	 X	X  X  X	 R	R  R  R	 R	R  R  R  G  G  G  G  G  G  G  G  B  B  B  B  B  B  B  B */ 
#define		ASVL_PAF_RGB32_B8G8R8		0x301
/* A	A  A  A	 A	A  A  A	 R	R  R  R	 R	R  R  R  G  G  G  G  G  G  G  G  B  B  B  B  B  B  B  B */ 
#define		ASVL_PAF_RGB32_B8G8R8A8		0x302
/* X	X  X  X	 X	X  X  X	 B  B  B  B  B  B  B  B  G  G  G  G  G  G  G  G  R	R  R  R	 R	R  R  R */ 
#define		ASVL_PAF_RGB32_R8G8B8		0x303
/* B    B  B  B  B  B  B  B  G  G  G  G  G  G  G  G  R  R  R  R  R  R  R  R  A	A  A  A  A	A  A  A */
#define		ASVL_PAF_RGB32_A8R8G8B8		0x304
/* A    A  A  A  A  A  A  A  B  B  B  B  B  B  B  B  G  G  G  G  G  G  G  G  R  R  R  R  R	R  R  R */
#define		ASVL_PAF_RGB32_R8G8B8A8		0x305

/*Y0, U0, V0*/																				
#define		ASVL_PAF_YUV				0x401
/*Y0, V0, U0*/																				
#define		ASVL_PAF_YVU				0x402
/*U0, V0, Y0*/																				
#define		ASVL_PAF_UVY				0x403
/*V0, U0, Y0*/																				
#define		ASVL_PAF_VUY				0x404

/*Y0, U0, Y1, V0*/																			
#define		ASVL_PAF_YUYV				0x501
/*Y0, V0, Y1, U0*/																			
#define		ASVL_PAF_YVYU				0x502
/*U0, Y0, V0, Y1*/																			
#define		ASVL_PAF_UYVY				0x503
/*V0, Y0, U0, Y1*/																			
#define		ASVL_PAF_VYUY				0x504
/*Y1, U0, Y0, V0*/																			
#define		ASVL_PAF_YUYV2				0x505
/*Y1, V0, Y0, U0*/																		
#define		ASVL_PAF_YVYU2				0x506
/*U0, Y1, V0, Y0*/																			
#define		ASVL_PAF_UYVY2				0x507
/*V0, Y1, U0, Y0*/																			
#define		ASVL_PAF_VYUY2				0x508
/*Y0, Y1, U0, V0*/																			
#define		ASVL_PAF_YYUV				  0x509

/*8 bit Y plane followed by 8 bit 2x2 subsampled U and V planes*/
#define		ASVL_PAF_I420				0x601
/*8 bit Y plane followed by 8 bit 1x2 subsampled U and V planes*/
#define		ASVL_PAF_I422V				0x602
/*8 bit Y plane followed by 8 bit 2x1 subsampled U and V planes*/
#define		ASVL_PAF_I422H				0x603
/*8 bit Y plane followed by 8 bit U and V planes*/
#define		ASVL_PAF_I444				0x604
/*8 bit Y plane followed by 8 bit 2x2 subsampled V and U planes*/
#define		ASVL_PAF_YV12				0x605
/*8 bit Y plane followed by 8 bit 1x2 subsampled V and U planes*/	
#define		ASVL_PAF_YV16V				0x606
/*8 bit Y plane followed by 8 bit 2x1 subsampled V and U planes*/
#define		ASVL_PAF_YV16H				0x607
/*8 bit Y plane followed by 8 bit V and U planes*/
#define		ASVL_PAF_YV24				0x608
/*8 bit Y plane only*/
#define		ASVL_PAF_GRAY				0x701


/*8 bit Y plane followed by 8 bit 2x2 subsampled UV planes*/
#define		ASVL_PAF_NV12				0x801
/*8 bit Y plane followed by 8 bit 2x2 subsampled VU planes*/
#define		ASVL_PAF_NV21				0x802
/*8 bit Y plane followed by 8 bit 2x1 subsampled UV planes*/
#define		ASVL_PAF_LPI422H			0x803
/*8 bit Y plane followed by 8 bit 2x1 subsampled VU planes*/
#define		ASVL_PAF_LPI422H2			0x804

/*8 bit Y plane followed by 8 bit 4x4 subsampled VU planes*/
#define		ASVL_PAF_NV41				0x805

/*Negative UYVY, U0, Y0, V0, Y1*/																			
#define		ASVL_PAF_NEG_UYVY			0x901
/*Negative I420, 8 bit Y plane followed by 8 bit 2x2 subsampled U and V planes*/
#define		ASVL_PAF_NEG_I420			0x902


/*Mono UYVY, UV values are fixed, gray image in U0, Y0, V0, Y1*/
#define		ASVL_PAF_MONO_UYVY			0xa01
/*Mono I420, UV values are fixed, 8 bit Y plane followed by 8 bit 2x2 subsampled U and V planes*/
#define		ASVL_PAF_MONO_I420			0xa02

/*P8_YUYV, 8 pixels a group, Y0Y1Y2Y3Y4Y5Y6Y7U0U1U2U3V0V1V2V3*/
#define		ASVL_PAF_P8_YUYV			0xb03

/*P16_YUYV, 16*16 pixels a group, Y0Y1Y2Y3...U0U1...V0V1...*/
#define		ASVL_PAF_SP16UNIT			0xc01

#define		ASVL_PAF_DEPTH_U16			0xc02


/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  0  0  0  0  0  0  D  D  D  D  D  D  D  D , 
*/
#define		ASVL_PAF_DEPTH8_U16_MSB	0xc10

/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  0  0  0  0  0  0  0  0 , 
*/
#define		ASVL_PAF_DEPTH8_U16_LSB	0xc11

/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  0  0  0  0  D  D  D  D  D  D  D  D  D  D , 
*/
#define		ASVL_PAF_DEPTH10_U16_MSB	0xc12

/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  D  0  0  0  0  0  0 , 
*/
#define		ASVL_PAF_DEPTH10_U16_LSB	0xc13

/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  0  0  D  D  D  D  D  D  D  D  D  D  D  D , 
*/
#define		ASVL_PAF_DEPTH12_U16_MSB	0xc14

/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  D  D  D  0  0  0  0 , 
*/
#define		ASVL_PAF_DEPTH12_U16_LSB	0xc15


/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  D  D  D  D  D  D  D  D  D  D  D  D  D  D , 
*/
#define		ASVL_PAF_DEPTH14_U16_MSB	0xc16

/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  D  D  D  D  D  0  0 , 
*/
#define		ASVL_PAF_DEPTH14_U16_LSB	0xc17


/* 
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  D  D  D  D  D  D  D , 
*/
#define		ASVL_PAF_DEPTH16_U16	0xc18



/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  0  0  0  0  0  D  D  D  D  D  D  D  D  D , 
*/
#define		ASVL_PAF_DEPTH9_U16_MSB	  0xc19

/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  0  0  0  0  0  0  0 , 
*/
#define		ASVL_PAF_DEPTH9_U16_LSB	   0xc1a


/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  0  0  0  D  D  D  D  D  D  D  D  D  D  D , 
*/
#define		ASVL_PAF_DEPTH11_U16_MSB	  0xc1b

/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  D  D  0  0  0  0  0 , 
*/
#define		ASVL_PAF_DEPTH11_U16_LSB	   0xc1c

/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  0  D  D  D  D  D  D  D  D  D  D  D  D  D , 
*/
#define		ASVL_PAF_DEPTH13_U16_MSB	  0xc1d

/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  D  D  D  D  0  0  0 , 
*/
#define		ASVL_PAF_DEPTH13_U16_LSB	   0xc1e

/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  D  D  D  D  D  D  D  D  D  D  D  D  D  D  D , 
*/
#define		ASVL_PAF_DEPTH15_U16_MSB	  0xc1f

/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  D  D  D  D  D  D  0 , 
*/
#define		ASVL_PAF_DEPTH15_U16_LSB	   0xc20

/*10 bits Bayer raw data, each pixel use 10 bits memory size*/
#define     ASVL_PAF_RAW10_RGGB_10B       		   0xd01
#define     ASVL_PAF_RAW10_GRBG_10B                0xd02
#define     ASVL_PAF_RAW10_GBRG_10B                0xd03
#define     ASVL_PAF_RAW10_BGGR_10B                0xd04

/*12 bits Bayer raw data, each pixel use 12 bits memory size*/
#define     ASVL_PAF_RAW12_RGGB_12B       		   0xd05
#define     ASVL_PAF_RAW12_GRBG_12B                0xd06
#define     ASVL_PAF_RAW12_GBRG_12B                0xd07
#define     ASVL_PAF_RAW12_BGGR_12B                0xd08

/*10 bits Bayer raw data, each pixel use 2 bytes(16bits) memory size*/
#define     ASVL_PAF_RAW10_RGGB_16B        		   0xd09
#define     ASVL_PAF_RAW10_GRBG_16B                0xd0A
#define     ASVL_PAF_RAW10_GBRG_16B                0xd0B
#define     ASVL_PAF_RAW10_BGGR_16B                0xd0C

/*12 bits Bayer raw data, each pixel use 2 bytes(16bits) memory size*/
#define		ASVL_PAF_RAW12_RGGB_16B		           0xd11
#define		ASVL_PAF_RAW12_GRBG_16B		           0xd12
#define		ASVL_PAF_RAW12_GBRG_16B		           0xd13
#define		ASVL_PAF_RAW12_BGGR_16B		           0xd14

/*16 bits Bayer raw data, each pixel use 2 bytes(16bits) memory size*/
#define		ASVL_PAF_RAW16_RGGB_16B		           0xd21
#define		ASVL_PAF_RAW16_GRBG_16B		           0xd22
#define		ASVL_PAF_RAW16_GBRG_16B		           0xd23
#define		ASVL_PAF_RAW16_BGGR_16B		           0xd24

/*14 bits Bayer raw data, each pixel use 14 bits memory size*/
#define     ASVL_PAF_RAW14_RGGB_14B       		   0xd35
#define     ASVL_PAF_RAW14_GRBG_14B                0xd36
#define     ASVL_PAF_RAW14_GBRG_14B                0xd37
#define     ASVL_PAF_RAW14_BGGR_14B                0xd38

/*14 bits Bayer raw data, each pixel use 2 bytes(16bits) memory size*/
#define		ASVL_PAF_RAW14_RGGB_16B		           0xd41
#define		ASVL_PAF_RAW14_GRBG_16B		           0xd42
#define		ASVL_PAF_RAW14_GBRG_16B		           0xd43
#define		ASVL_PAF_RAW14_BGGR_16B		           0xd44

/*10 bits Bayer raw data, each pixel use 2 bytes(16bits) memory size*/
/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  0  0  0  0  D  D  D  D  D  D  D  D  D  D , 
*/
#define     ASVL_PAF_RAW10_RGGB_16B_MSB       	   0xd51
#define     ASVL_PAF_RAW10_GRBG_16B_MSB            0xd52
#define     ASVL_PAF_RAW10_GBRG_16B_MSB            0xd53
#define     ASVL_PAF_RAW10_BGGR_16B_MSB            0xd54

/*12 bits Bayer raw data, each pixel use 2 bytes(16bits) memory size*/
/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  0  0  D  D  D  D  D  D  D  D  D  D  D  D , 
*/
#define		ASVL_PAF_RAW12_RGGB_16B_MSB	           0xd56
#define		ASVL_PAF_RAW12_GRBG_16B_MSB	           0xd57
#define		ASVL_PAF_RAW12_GBRG_16B_MSB	           0xd58
#define		ASVL_PAF_RAW12_BGGR_16B_MSB	           0xd59

/*14 bits Bayer raw data, each pixel use 2 bytes(16bits) memory size*/
/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  D  D  D  D  D  D  D  D  D  D  D  D  D  D , 
*/
#define		ASVL_PAF_RAW14_RGGB_16B_MSB	           0xd5a
#define		ASVL_PAF_RAW14_GRBG_16B_MSB	           0xd5b
#define		ASVL_PAF_RAW14_GBRG_16B_MSB	           0xd5c
#define		ASVL_PAF_RAW14_BGGR_16B_MSB	           0xd5d

/*10 bits Bayer raw data, each pixel use 2 bytes(16bits) memory size*/
/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  D  0  0  0  0  0  0 , 
*/
#define     ASVL_PAF_RAW10_RGGB_16B_LSB       	   0xd61
#define     ASVL_PAF_RAW10_GRBG_16B_LSB            0xd62
#define     ASVL_PAF_RAW10_GBRG_16B_LSB            0xd63
#define     ASVL_PAF_RAW10_BGGR_16B_LSB            0xd64

/*12 bits Bayer raw data, each pixel use 2 bytes(16bits) memory size*/
/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  D  D  D  0  0  0  0 , 
*/
#define		ASVL_PAF_RAW12_RGGB_16B_LSB	           0xd66
#define		ASVL_PAF_RAW12_GRBG_16B_LSB	           0xd67
#define		ASVL_PAF_RAW12_GBRG_16B_LSB	           0xd68
#define		ASVL_PAF_RAW12_BGGR_16B_LSB	           0xd69

/*14 bits Bayer raw data, each pixel use 2 bytes(16bits) memory size*/
/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  D  D  D  D  D  0  0 , 
*/
#define		ASVL_PAF_RAW14_RGGB_16B_LSB	           0xd6a
#define		ASVL_PAF_RAW14_GRBG_16B_LSB	           0xd6b
#define		ASVL_PAF_RAW14_GBRG_16B_LSB	           0xd6c
#define		ASVL_PAF_RAW14_BGGR_16B_LSB	           0xd6d


/*8 bits Bayer raw data, each pixel use 1 bytes(8bits) memory size*/
/* 
  00 01 02 03 04 05 06 07
  D  D  D  D  D  D  D  D , 
*/
#define		ASVL_PAF_RAW8_RGGB_8B	           0xd71
#define		ASVL_PAF_RAW8_GRBG_8B	           0xd72
#define		ASVL_PAF_RAW8_GBRG_8B	           0xd73
#define		ASVL_PAF_RAW8_BGGR_8B	           0xd74

/*8 bits Bayer raw data, each pixel use 2 bytes(16bits) memory size*/
/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  0  0  0  0  0  0  0 , 
*/
#define		ASVL_PAF_RAW8_RGGB_16B_LSB 	           0xd75
#define		ASVL_PAF_RAW8_GRBG_16B_LSB 	           0xd76
#define		ASVL_PAF_RAW8_GBRG_16B_LSB 	           0xd77
#define		ASVL_PAF_RAW8_BGGR_16B_LSB 	           0xd78

/*8 bits Bayer raw data, each pixel use 2 bytes(16bits) memory size*/
/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  0  0  0  0  0  0  D  D  D  D  D  D  D  D , 
*/
#define		ASVL_PAF_RAW8_RGGB_16B_MSB 	           0xd79
#define		ASVL_PAF_RAW8_GRBG_16B_MSB 	           0xd7a
#define		ASVL_PAF_RAW8_GBRG_16B_MSB 	           0xd7b
#define		ASVL_PAF_RAW8_BGGR_16B_MSB 	           0xd7c


/*10 bits gray raw data, each pixel use 10 bits memory size*/
#define     ASVL_PAF_RAW10_GRAY_10B       		   0xe01

/*12 bits gray raw data, each pixel use 12 bits memory size*/
#define     ASVL_PAF_RAW12_GRAY_12B       		   0xe11

/*14 bits gray raw data, each pixel use 14 bits memory size*/
#define     ASVL_PAF_RAW14_GRAY_14B       		   0xe21

/*16 bits gray raw data, each pixel use 2 bytes(16bits) memory size*/
#define     ASVL_PAF_RAW16_GRAY_16B       		   0xe31

/*10 bits gray raw data, each pixel use 2 bytes(16bits) memory size*/
#define     ASVL_PAF_RAW10_GRAY_16B        		   0xe81

/*10 bits gray raw data, each pixel use 2 bytes(16bits) memory size*/
/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  0  0  0  0  D  D  D  D  D  D  D  D  D  D , 
*/
#define     ASVL_PAF_RAW10_GRAY_16B_MSB        		   0xe82

/*10 bits gray raw data, each pixel use 2 bytes(16bits) memory size*/
/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  D  0  0  0  0  0  0 , 
*/
#define     ASVL_PAF_RAW10_GRAY_16B_LSB        		   0xe83


/*11 bits gray raw data, each pixel use 2 bytes(16bits) memory size*/
#define     ASVL_PAF_RAW11_GRAY_16B        		   0xe88

/*11 bits gray raw data, each pixel use 2 bytes(16bits) memory size*/
/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  0  0  0  D  D  D  D  D  D  D  D  D  D  D , 
*/
#define     ASVL_PAF_RAW11_GRAY_16B_MSB        		   0xe89

/*11 bits gray raw data, each pixel use 2 bytes(16bits) memory size*/
/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  D  D  0  0  0  0  0 , 
*/
#define     ASVL_PAF_RAW11_GRAY_16B_LSB        		   0xe8a


/*12 bits gray raw data, each pixel use 2 bytes(16bits) memory size*/
#define     ASVL_PAF_RAW12_GRAY_16B        		   0xe91

/*12 bits gray raw data, each pixel use 2 bytes(16bits) memory size*/
/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  0  0  D  D  D  D  D  D  D  D  D  D  D  D , 
*/
#define     ASVL_PAF_RAW12_GRAY_16B_MSB    		   0xe92

/*12 bits gray raw data, each pixel use 2 bytes(16bits) memory size*/
/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  D  D  D  0  0  0  0 , 
*/
#define     ASVL_PAF_RAW12_GRAY_16B_LSB   		   0xe93



/*13 bits gray raw data, each pixel use 2 bytes(16bits) memory size*/
#define     ASVL_PAF_RAW13_GRAY_16B        		   0xe98

/*13 bits gray raw data, each pixel use 2 bytes(16bits) memory size*/
/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  0  D  D  D  D  D  D  D  D  D  D  D  D  D , 
*/
#define     ASVL_PAF_RAW13_GRAY_16B_MSB    		   0xe99

/*13 bits gray raw data, each pixel use 2 bytes(16bits) memory size*/
/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  D  D  D  D  0  0  0 , 
*/
#define     ASVL_PAF_RAW13_GRAY_16B_LSB   		   0xe9a

/*14 bits gray raw data, each pixel use 2 bytes(16bits) memory size*/
#define     ASVL_PAF_RAW14_GRAY_16B        		   0xea1

/*14 bits gray raw data, each pixel use 2 bytes(16bits) memory size*/
/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  D  D  D  D  D  D  D  D  D  D  D  D  D  D , 
*/
#define     ASVL_PAF_RAW14_GRAY_16B_MSB        	   0xea2

/*14 bits gray raw data, each pixel use 2 bytes(16bits) memory size*/
/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  D  D  D  D  D  0  0 , 
*/
#define     ASVL_PAF_RAW14_GRAY_16B_LSB            0xea3


/*15 bits gray raw data, each pixel use 2 bytes(16bits) memory size*/
#define     ASVL_PAF_RAW15_GRAY_16B        		   0xea8

/*15 bits gray raw data, each pixel use 2 bytes(16bits) memory size*/
/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  D  D  D  D  D  D  D  D  D  D  D  D  D  D  D , 
*/
#define     ASVL_PAF_RAW15_GRAY_16B_MSB        	   0xea9

/*15 bits gray raw data, each pixel use 2 bytes(16bits) memory size*/
/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  D  D  D  D  D  D  0 , 
*/
#define     ASVL_PAF_RAW15_GRAY_16B_LSB            0xeaa


/*10 bit Y plane followed by 10 bit 2x2 subsampled UV planes*/
/* 
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  0  0  0  0  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y , 
  ....
  0  0  0  0  0  0  U  U  U  U  U  U  U  U  U  U , 
  0  0  0  0  0  0  V  V  V  V  V  V  V  V  V  V ,
  ....
*/
#define		ASVL_PAF_P010_MSB			0xf01

/*10 bit Y plane followed by 10 bit 2x2 subsampled UV planes*/
/* 
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  0  0  0  0  0  0 , 
  ....
  U  U  U  U  U  U  U  U  U  U  0  0  0  0  0  0 , 
  V  V  V  V  V  V  V  V  V  V  0  0  0  0  0  0 ,
  ....
*/
#define		ASVL_PAF_P010_LSB			0xf02


/*12 bit Y plane followed by 12 bit 2x2 subsampled UV planes*/
/* 
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  0  0  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y , 
  ....
  0  0  0  0  U  U  U  U  U  U  U  U  U  U  U  U , 
  0  0  0  0  V  V  V  V  V  V  V  V  V  V  V  V ,
  ....
*/
#define		ASVL_PAF_P012_MSB			0xf03

/*12 bit Y plane followed by 12 bit 2x2 subsampled UV planes*/
/* 
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  0  0  0  0 , 
  ....
  U  U  U  U  U  U  U  U  U  U  U  U  0  0  0  0 , 
  V  V  V  V  V  V  V  V  V  V  V  V  0  0  0  0 ,
  ....
*/
#define		ASVL_PAF_P012_LSB			0xf04

/*14 bit Y plane followed by 14 bit 2x2 subsampled UV planes*/
/* 
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y , 
  ....
  0  0  U  U  U  U  U  U  U  U  U  U  U  U  U  U , 
  0  0  V  V  V  V  V  V  V  V  V  V  V  V  V  V ,
  ....
*/
#define		ASVL_PAF_P014_MSB			0xf05

/*14 bit Y plane followed by 14 bit 2x2 subsampled UV planes*/
/* 
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  Y  0  0 , 
  ....
  U  U  U  U  U  U  U  U  U  U  U  U  U  U  0  0 , 
  V  V  V  V  V  V  V  V  V  V  V  V  V  V  0  0 ,
  ....
*/
#define		ASVL_PAF_P014_LSB			0xf06

/* Define from QC: 
   	pi32Pitch[0] is 64 alignment of (i32Width+2)/3)*4;
	pi32Pitch[1] is 64 alignment of (i32Width+2)/3)*4;
	ppu8Plane[0] size is pi32Pitch[0] * (((i32Height+3)/4)*4); 
	ppu8Plane[1] size is pi32Pitch[1] * (((i32Height>>1+3)/4)*4); 
   */
#define		ASVL_PAF_NV21_TP10			    0x1001
#define		ASVL_PAF_NV12_TP10			    0x1002


/* 2 planes, and pitch is equal to the length of plane by byte. 4kB alignment. */
#define		ASVL_PAF_UBWC_TP10			    0x1010

/* Todo for detail. 4kB alignment. */
#define		ASVL_PAF_UBWC_NV12			    0x1020


/*8 bits QuadBayer raw data, each pixel use 1 bytes(8bits) memory size*/
/* 
  00 01 02 03 04 05 06 07
  D  D  D  D  D  D  D  D , 
*/
#define		ASVL_PAF_QUADRAW8_RGGB_8B	               0x1101
#define		ASVL_PAF_QUADRAW8_GRBG_8B	               0x1102
#define		ASVL_PAF_QUADRAW8_GBRG_8B	               0x1103
#define		ASVL_PAF_QUADRAW8_BGGR_8B	               0x1104

/*8 bits QuadBayer raw data, each pixel use 2 bytes(16bits) memory size*/
/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  0  0  0  0  0  0  0 , 
*/
#define		ASVL_PAF_QUADRAW8_RGGB_16B_LSB 	           0x1105
#define		ASVL_PAF_QUADRAW8_GRBG_16B_LSB 	           0x1106
#define		ASVL_PAF_QUADRAW8_GBRG_16B_LSB 	           0x1107
#define		ASVL_PAF_QUADRAW8_BGGR_16B_LSB 	           0x1108

/*8 bits QuadBayer raw data, each pixel use 2 bytes(16bits) memory size*/
/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  0  0  0  0  0  0  D  D  D  D  D  D  D  D , 
*/
#define		ASVL_PAF_QUADRAW8_RGGB_16B_MSB 	           0x1109
#define		ASVL_PAF_QUADRAW8_GRBG_16B_MSB 	           0x110a
#define		ASVL_PAF_QUADRAW8_GBRG_16B_MSB 	           0x110b
#define		ASVL_PAF_QUADRAW8_BGGR_16B_MSB 	           0x110c

/*10 bits QuadBayer raw data, each pixel use 10 bits memory size*/
#define     ASVL_PAF_QUADRAW10_RGGB_10B       		   0x1111
#define     ASVL_PAF_QUADRAW10_GRBG_10B                0x1112
#define     ASVL_PAF_QUADRAW10_GBRG_10B                0x1113
#define     ASVL_PAF_QUADRAW10_BGGR_10B                0x1114

/*10 bits QuadBayer raw data, each pixel use 2 bytes(16bits) memory size*/
/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  D  0  0  0  0  0  0 , 
*/
#define     ASVL_PAF_QUADRAW10_RGGB_16B_LSB       	   0x1115
#define     ASVL_PAF_QUADRAW10_GRBG_16B_LSB            0x1116
#define     ASVL_PAF_QUADRAW10_GBRG_16B_LSB            0x1117
#define     ASVL_PAF_QUADRAW10_BGGR_16B_LSB            0x1118

/*10 bits QuadBayer raw data, each pixel use 2 bytes(16bits) memory size*/
/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  0  0  0  0  D  D  D  D  D  D  D  D  D  D , 
*/
#define     ASVL_PAF_QUADRAW10_RGGB_16B_MSB       	   0x1119
#define     ASVL_PAF_QUADRAW10_GRBG_16B_MSB            0x111a
#define     ASVL_PAF_QUADRAW10_GBRG_16B_MSB            0x111b
#define     ASVL_PAF_QUADRAW10_BGGR_16B_MSB            0x111c

/*12 bits QuadBayer raw data, each pixel use 12 bits memory size*/
#define     ASVL_PAF_QUADRAW12_RGGB_12B       		   0x1121
#define     ASVL_PAF_QUADRAW12_GRBG_12B                0x1122
#define     ASVL_PAF_QUADRAW12_GBRG_12B                0x1123
#define     ASVL_PAF_QUADRAW12_BGGR_12B                0x1124

/*12 bits QuadBayer raw data, each pixel use 2 bytes(16bits) memory size*/
/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  D  D  D  0  0  0  0 , 
*/
#define		ASVL_PAF_QUADRAW12_RGGB_16B_LSB	       0x1125
#define		ASVL_PAF_QUADRAW12_GRBG_16B_LSB	       0x1126
#define		ASVL_PAF_QUADRAW12_GBRG_16B_LSB	       0x1127
#define		ASVL_PAF_QUADRAW12_BGGR_16B_LSB	       0x1128

/*12 bits QuadBayer raw data, each pixel use 2 bytes(16bits) memory size*/
/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  0  0  D  D  D  D  D  D  D  D  D  D  D  D , 
*/
#define		ASVL_PAF_QUADRAW12_RGGB_16B_MSB	       0x1129
#define		ASVL_PAF_QUADRAW12_GRBG_16B_MSB	       0x112a
#define		ASVL_PAF_QUADRAW12_GBRG_16B_MSB	       0x112b
#define		ASVL_PAF_QUADRAW12_BGGR_16B_MSB	       0x112c

/*14 bits QuadBayer raw data, each pixel use 14 bits memory size*/
#define     ASVL_PAF_QUADRAW14_RGGB_14B       		   0x1131
#define     ASVL_PAF_QUADRAW14_GRBG_14B                0x1132
#define     ASVL_PAF_QUADRAW14_GBRG_14B                0x1133
#define     ASVL_PAF_QUADRAW14_BGGR_14B                0x1134

/*14 bits QuadBayer raw data, each pixel use 2 bytes(16bits) memory size*/
/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  D  D  D  D  D  0  0 , 
*/
#define		ASVL_PAF_QUADRAW14_RGGB_16B_LSB	           0x1135
#define		ASVL_PAF_QUADRAW14_GRBG_16B_LSB	           0x1136
#define		ASVL_PAF_QUADRAW14_GBRG_16B_LSB	           0x1137
#define		ASVL_PAF_QUADRAW14_BGGR_16B_LSB	           0x1138

/*14 bits QuadBayer raw data, each pixel use 2 bytes(16bits) memory size*/
/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  D  D  D  D  D  D  D  D  D  D  D  D  D  D , 
*/
#define		ASVL_PAF_QUADRAW14_RGGB_16B_MSB	           0x1139
#define		ASVL_PAF_QUADRAW14_GRBG_16B_MSB	           0x113a
#define		ASVL_PAF_QUADRAW14_GBRG_16B_MSB	           0x113b
#define		ASVL_PAF_QUADRAW14_BGGR_16B_MSB	           0x113c

/*16 bits QuadBayer raw data, each pixel use 2 bytes(16bits) memory size*/
#define		ASVL_PAF_QUADRAW16_RGGB_16B		           0x1141
#define		ASVL_PAF_QUADRAW16_GRBG_16B		           0x1142
#define		ASVL_PAF_QUADRAW16_GBRG_16B		           0x1143
#define		ASVL_PAF_QUADRAW16_BGGR_16B		           0x1144


/*31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00 */

/* LSB
   0000 0000 R R ... R 0000 0000 G G ... G 0000 0000 B B ... B 
*/
#define		ASVL_PAF_RGB_B8G8R8_48B_LSB		                      0x1201
/* MSB   
   R R ... R 0000 0000 G G ... G 0000 0000 B B ... B 0000 0000 
*/
#define		ASVL_PAF_RGB_B8G8R8_48B_MSB		                      0x1202

/* R R ... R G G ... G B B ... B */
#define		ASVL_PAF_RGB_B10G10R10_30B		                      0x1203
/* LSB
   0000 00 R R ... R 0000 00 G G ... G 0000 00 B B ... B 
*/
#define		ASVL_PAF_RGB_B10G10R10_48B_LSB		                  0x1204
/* MSB                                                            
   R R ... R 00 0000 G G ... G 00 0000 B B ... B 00 0000                   
*/                                                                
#define		ASVL_PAF_RGB_B10G10R10_48B_MSB		                  0x1205
                                                                  
/* R R ... R G G ... G B B ... B */                               
#define		ASVL_PAF_RGB_B12G12R12_36B		                      0x1206
/* LSB                                                            
   0000 R R ... R 0000 G G ... G 0000 B B ... B                   
*/                                                                
#define		ASVL_PAF_RGB_B12G12R12_48B_LSB		                  0x1207
/* MSB                                                            
   R R ... R 0000 G G ... G 0000 B B ... B 0000                   
*/                                                                
#define		ASVL_PAF_RGB_B12G12R12_48B_MSB		                  0x1208

/* R R ... R G G ... G B B ... B */                               
#define		ASVL_PAF_RGB_B14G14R14_42B		                      0x1209
/* LSB                                                            
   00 R R ... R 00 G G ... G 00 B B ... B                   
*/                                                                
#define		ASVL_PAF_RGB_B14G14R14_48B_LSB		                  0x120a
/* MSB                                                            
   R R ... R 00 G G ... G 00 B B ... B 00                   
*/                                                                
#define		ASVL_PAF_RGB_B14G14R14_48B_MSB		                  0x120b

/* R R ... R G G ... G B B ... B */                               
#define		ASVL_PAF_RGB_B16G16R16_48B		                      0x120c


/* LSB
   0000 0000 B B ... B 0000 0000 G G ... G 0000 0000 R R ... R
*/
#define		ASVL_PAF_RGB_R8G8B8_48B_LSB		                      0x1211
/* MSB   
   B B ... B 0000 0000 G G ... G 0000 0000 R R ... R 0000 0000  
*/
#define		ASVL_PAF_RGB_R8G8B8_48B_MSB		                      0x1212

/* B B ... B G G ... G R R ... R */
#define		ASVL_PAF_RGB_R10G10B10_30B		                      0x1213
/* LSB
   0000 00 B B ... B 0000 00 G G ... G 0000 00 R R ... R 
*/
#define		ASVL_PAF_RGB_R10G10B10_48B_LSB		                  0x1214
/* MSB                                                            
   B B ... B 00 0000 G G ... G 00 0000 R R ... R 00 0000                     
*/                                                                
#define		ASVL_PAF_RGB_R10G10B10_48B_MSB		                  0x1215
                                                                  
/* B B ... B G G ... G R R ... R */                               
#define		ASVL_PAF_RGB_R12G12B12_36B		                      0x1216
/* LSB                                                            
   0000 B B ... B 0000 G G ... G 0000 R R ... R                   
*/                                                                
#define		ASVL_PAF_RGB_R12G12B12_48B_LSB		                  0x1217
/* MSB                                                            
   B B ... B 0000 G G ... G 0000 R R ... R 0000                    
*/                                                                
#define		ASVL_PAF_RGB_R12G12B12_48B_MSB		                  0x1218

/* B B ... B G G ... G R R ... R */                               
#define		ASVL_PAF_RGB_R14G14B14_42B		                      0x1219
/* LSB                                                            
   00 B B ... B 00 G G ... G 00 R R ... R                   
*/                                                                
#define		ASVL_PAF_RGB_R14G14B14_48B_LSB		                  0x121a
/* MSB                                                            
   B B ... B 00 G G ... G 00 R R ... R 00                    
*/                                                                
#define		ASVL_PAF_RGB_R14G14B14_48B_MSB		                  0x121b

/* B B ... B G G ... G R R ... R */                               
#define		ASVL_PAF_RGB_R16G16B16_48B		                      0x121c



/*10 bits Raw data for MSC, each pixel use 2 bytes(16bits) memory size*/
/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  D  0  0  0  0  0  0 , 
*/
#define		ASVL_PAF_RAW10_MSC3x3_16B_LSB	           0x1601

/*10 bits Raw data for MSC, each pixel use 2 bytes(16bits) memory size*/
/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  0  0  0  0  D  D  D  D  D  D  D  D  D  D , 
*/
#define		ASVL_PAF_RAW10_MSC3x3_16B_MSB	           0x1602

/*10 bits Raw data for MSC, each pixel use 10 bits memory size*/
#define		ASVL_PAF_RAW10_MSC3x3_10B	               0x1603


/*12 bits Raw data for MSC, each pixel use 2 bytes(16bits) memory size*/
/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  D  D  D  0  0  0  0 , 
*/
#define		ASVL_PAF_RAW12_MSC3x3_16B_LSB	           0x1605

/*12 bits Raw data for MSC, each pixel use 2 bytes(16bits) memory size*/
/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  0  0  D  D  D  D  D  D  D  D  D  D  D  D , 
*/
#define		ASVL_PAF_RAW12_MSC3x3_16B_MSB	           0x1606

/*12 bits Raw data for MSC, each pixel use 12 bits memory size*/
#define		ASVL_PAF_RAW12_MSC3x3_12B	               0x1607

/*14 bits Raw data for MSC, each pixel use 2 bytes(16bits) memory size*/
/* LSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  D  D  D  D  D  D  D  D  D  D  D  D  D  D  0  0 , 
*/
#define		ASVL_PAF_RAW14_MSC3x3_16B_LSB	           0x1609

/*14 bits Raw data for MSC, each pixel use 2 bytes(16bits) memory size*/
/* MSB
  00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15
  0  0  D  D  D  D  D  D  D  D  D  D  D  D  D  D , 
*/
#define		ASVL_PAF_RAW14_MSC3x3_16B_MSB	           0x160a

/*14 bits Raw data for MSC, each pixel use 14 bits memory size*/
#define		ASVL_PAF_RAW14_MSC3x3_14B	               0x160b


/*Define the image format space*/		
typedef struct __tag_ASVL_OFFSCREEN
{
	MUInt32	u32PixelArrayFormat;
	MInt32	i32Width;
	MInt32	i32Height;
	MUInt8*	ppu8Plane[4];
	MInt32	pi32Pitch[4];
}ASVLOFFSCREEN, *LPASVLOFFSCREEN;

/*Define the SDK Version infos. This is the template!!!*/		
typedef struct __tag_ASVL_VERSION
{
	    MLong lCodebase;             	// Codebase version number 
	    MLong lMajor;                		// major version number 
	    MLong lMinor;                		// minor version number
	    MLong lBuild;                		// Build version number, increasable only
	    const MChar *Version;        	// version in string form
	    const MChar *BuildDate;      	// latest build Date
	    const MChar *CopyRight;      	// copyright 
}ASVL_VERSION;
const ASVL_VERSION *ASVL_GetVersion();

#ifdef __cplusplus
}
#endif

#endif /*__ASVL_OFFSCREEN_H__*/
