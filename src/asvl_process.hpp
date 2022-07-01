// asvl_cvtfmt.hpp: header-only library for ASVLOFFSCREEN processing
//  - 颜色格式转换
//  - resize, crop, rotate, warpAffine, draw/paint
// author: Zhuo Zhang (zz9555@arcsoft.com.cn)
// last update: 2022-06-30 11:05:24

#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <iostream>
#include <string>

#include "asvl_helper.hpp"
#include "asvloffscreen.h"

#define USE_OPENCV 1

#ifdef USE_OPENCV
#include <opencv2/opencv.hpp>
#endif

//================================================================================
// Public APIs
//================================================================================

namespace asvl {


// rgb_from_*
//  rgb_from_nv21()
//  rgb_from_nv12()
//  rgb_from_nv61()
//  ...
// 
// rgb_to_*
//  rgb_to_nv21()
//  rgb_to_nv12()
//  rgb_to_i420()
//  ...

ASVL_API ASVLOFFSCREEN* rgb_to_nv21(ASVLOFFSCREEN* asvl_rgb);
ASVL_API ASVLOFFSCREEN* rgb_from_nv21(ASVLOFFSCREEN* asvl_nv21);

ASVL_API ASVLOFFSCREEN* rgb_to_nv12(ASVLOFFSCREEN* asvl_rgb);
ASVL_API ASVLOFFSCREEN* rgb_from_nv12(ASVLOFFSCREEN* asvl_nv12);

ASVL_API ASVLOFFSCREEN* rgb_to_i420(ASVLOFFSCREEN* asvl_rgb);
ASVL_API ASVLOFFSCREEN* rgb_from_i420(ASVLOFFSCREEN* asvl_i420);

ASVL_API ASVLOFFSCREEN* rgb_to_uyvy(ASVLOFFSCREEN* asvl_rgb);
ASVL_API ASVLOFFSCREEN* rgb_from_uyvy(ASVLOFFSCREEN* asvl_uyvy);

ASVL_API ASVLOFFSCREEN* rgb_to_i444(ASVLOFFSCREEN* asvl_rgb);
ASVL_API ASVLOFFSCREEN* rgb_from_i444(ASVLOFFSCREEN* asvl_i444);


ASVL_API ASVLOFFSCREEN* i420_to_uyvy(ASVLOFFSCREEN* asvl_i420);
ASVL_API ASVLOFFSCREEN* i444_to_nv21(ASVLOFFSCREEN* asvl_i444);

// drawing
ASVL_API void draw_point(ASVLOFFSCREEN* pimg, MPOINTF pnt, int radius, int r_val, int g_val, int b_val);


} // namespace asvl

namespace {
// https://stackoverflow.com/questions/17892346/how-to-convert-rgb-yuv-rgb-both-ways

inline void YUVfromRGB(double& Y, double& U, double& V, const double R, const double G, const double B)
{
    Y =  0.257 * R + 0.504 * G + 0.098 * B +  16;
    U = -0.148 * R - 0.291 * G + 0.439 * B + 128;
    V =  0.439 * R - 0.368 * G - 0.071 * B + 128;
}

inline void RGBfromYUV(double& R, double& G, double& B, double Y, double U, double V)
{
    Y -= 16;
    U -= 128;
    V -= 128;
    R = 1.164 * Y             + 1.596 * V;
    G = 1.164 * Y - 0.392 * U - 0.813 * V;
    B = 1.164 * Y + 2.017 * U;
}

inline void RGBfromYUV_u8(uint8_t& R, uint8_t& G, uint8_t& B, uint8_t y, uint8_t u, uint8_t v)
{
    double dR, dG, dB;
    
    double dY = y;
    double dU = u;
    double dV = v;

    RGBfromYUV(dR, dG, dB, dY, dU, dV);

    R = dR;
    G = dG;
    B = dB;
}

inline void YUVfromRGB_u8(uint8_t& Y, uint8_t& U, uint8_t& V, const uint8_t R, const uint8_t G, const uint8_t B)
{
    double dY, dU, dV;

    double dR = R;
    double dG = G;
    double dB = B;

    YUVfromRGB(dY, dU, dV, dR, dG, dB);

    // Y = dY;
    // U = dU;
    // V = dV;
    Y = std::max(0.0, std::min(dY, 255.0));
    U = std::max(0.0, std::min(dU, 255.0));
    V = std::max(0.0, std::min(dV, 255.0));
}


// behave same as opencv(exclude carotene)
void RGBfromYUV_BT601_u8(uint8_t& R, uint8_t& G, uint8_t& B, uint8_t Y, uint8_t U, uint8_t V)
{
    // double dR, dG, dB;
    // double dY = Y;
    // double dU = U;
    // double dV = V;
    // RGBfromYUV_BT601(dR, dG, dB, dY, dU, dV);

    // R = dR;
    // G = dG;
    // B = dB;

    static const int ITUR_BT_601_CY = 1220542;
    static const int ITUR_BT_601_CUB = 2116026;
    static const int ITUR_BT_601_CUG = -409993;
    static const int ITUR_BT_601_CVG = -852492;
    static const int ITUR_BT_601_CVR = 1673527;
    static const int ITUR_BT_601_SHIFT = 20;


    #define CLIP_TO_UCHAR(x) ((x) < 0 ? 0 : ((x) > 255 ? 255 : (x)))

    int u = U - 128;///
    int v = V - 128;///

    int shift = 1 << (ITUR_BT_601_SHIFT - 1);
    int ruv = shift + ITUR_BT_601_CVR * v;
    int guv = shift + ITUR_BT_601_CVG * v + ITUR_BT_601_CUG * u;
    int buv = shift + ITUR_BT_601_CUB * u;


    int y00 = std::max(0, Y-16) * ITUR_BT_601_CY;
    R = CLIP_TO_UCHAR( (y00 + ruv) >> ITUR_BT_601_SHIFT );
    G = CLIP_TO_UCHAR( (y00 + guv) >> ITUR_BT_601_SHIFT );
    B = CLIP_TO_UCHAR( (y00 + buv) >> ITUR_BT_601_SHIFT );

    #undef CLIP_TO_UCHAR
}

//ref: https://blog.csdn.net/denisyq/article/details/52625692
void bgr_to_nv21(unsigned char *imgSrc, int width, int height, unsigned char *imgDst)
{
    int w, h;
    int shift = 14, offset1 = 8192, offset2 = 2105344;
    int C0 = 1868, C1 = 9617, C2 = 4899, C3 = 11682, C4 = 9241;

    int r1, r2, g1, g2, b1, b2;

    unsigned char * pRGB1 = imgSrc;
    unsigned char * pRGB2 = imgSrc + width * 3;

    unsigned char * pDY1 = imgDst;
    unsigned char * pDY2 = imgDst + width;
    unsigned char * pDUV = imgDst + width * height;

    for (h = 0; h < height; h += 2)
    {
        for (w = 0; w < width; w += 2)
        {
            b1 = *pRGB1++;
            g1 = *pRGB1++;
            r1 = *pRGB1++;
            *pDY1 = (b1 * C0 + g1 * C1 + r1 * C2 + offset1) >> shift;
            *pDUV++ = ((r1 - *pDY1) * C3 + offset2) >> shift;
            *pDUV++ = ((b1 - *pDY1) * C4 + offset2) >> shift;
            pDY1++;

            b1 = *pRGB1++;
            g1 = *pRGB1++;
            r1 = *pRGB1++;
            *pDY1 = (b1 * C0 + g1 * C1 + r1 * C2 + offset1) >> shift;
            pDY1++;

            b2 = *pRGB2++;
            g2 = *pRGB2++;
            r2 = *pRGB2++;
            *pDY2 = (b2 * C0 + g2 * C1 + r2 * C2 + offset1) >> shift;
            pDY2++;

            b2 = *pRGB2++;
            g2 = *pRGB2++;
            r2 = *pRGB2++;
            *pDY2 = (b2 * C0 + g2 * C1 + r2 * C2 + offset1) >> shift;
            pDY2++;
        }
        pRGB1 += 3 * width;
        pRGB2 += 3 * width;
        pDY1 += width;
        pDY2 += width;

    }
}

#ifndef MAX
#define MAX(a ,b) ((a > b) ? a : b)
#endif

#ifndef MIN
#define MIN(a ,b) ((a < b) ? a : b)
#endif

#define CLAMP(a) (MAX((MIN(a, 0xff)), 0x00)) 

void nv21_to_bgr(unsigned char *imgY, int width, int height, unsigned char *imgDst)
{
    int w, h;
    int shift = 14, offset = 8192;
    int C0 = 22987, C1 = -11698, C2 = -5636, C3 = 29049;

    int y1, y2, u1, v1;

    unsigned char * pY1 = imgY;
    unsigned char * pY2 = imgY + width;
    unsigned char * pUV = imgY + width * height;

    unsigned char * pD1 = imgDst;
    unsigned char * pD2 = imgDst + width * 3;

    for (h = 0; h < height; h += 2)
    {
        for (w = 0; w < width; w += 2)
        {
            v1 = *pUV - 128;
            pUV++;
            u1 = *pUV - 128;
            pUV++;




            y1 = *pY1;
            y2 = *pY2;

            *pD1++ = CLAMP(y1 + ((u1 * C3 + offset) >> shift));
            *pD1++ = CLAMP(y1 + ((u1 * C2 + v1 * C1 + offset) >> shift));
            *pD1++ = CLAMP(y1 + ((v1 * C0 + offset) >> shift));
            *pD2++ = CLAMP(y2 + ((u1 * C3 + offset) >> shift));
            *pD2++ = CLAMP(y2 + ((u1 * C2 + v1 * C1 + offset) >> shift));
            *pD2++ = CLAMP(y2 + ((v1 * C0 + offset) >> shift));

            pY1++;
            pY2++;




            y1 = *pY1;
            y2 = *pY2;

            *pD1++ = CLAMP(y1 + ((u1 * C3 + offset) >> shift));
            *pD1++ = CLAMP(y1 + ((u1 * C2 + v1 * C1 + offset) >> shift));
            *pD1++ = CLAMP(y1 + ((v1 * C0 + offset) >> shift));
            *pD2++ = CLAMP(y2 + ((u1 * C3 + offset) >> shift));
            *pD2++ = CLAMP(y2 + ((u1 * C2 + v1 * C1 + offset) >> shift));
            *pD2++ = CLAMP(y2 + ((v1 * C0 + offset) >> shift));

            pY1++;
            pY2++;

        }
        pY1 += width;
        pY2 += width;
        pD1 += 3 * width;
        pD2 += 3 * width;

    }
}



template<int u_idx, int b_idx>
void yuv420sp_to_rgb_opencv(
    uchar* y_plane, int width, int height, int y_linebytes,
    uchar* uv_plane, int uv_linebytes,
    uchar* rgb, int rgb_linebytes
)
{

    /// param checking
    if (y_plane==NULL || uv_plane==NULL || rgb==NULL) {
        fprintf(stderr, "invalid input\n");
        return;
    }
    
    /// neon-specific param checking
    if (width<2 || height<2) {
        fprintf(stderr, "invalid input dims\n");
        return;
    }

    /// declare variables
    int w = width;
    int h = height;

    // Coefficients for YUV420p to RGB conversion
    static const int ITUR_BT_601_CY = 1220542;
    static const int ITUR_BT_601_CUB = 2116026;
    static const int ITUR_BT_601_CUG = -409993;
    static const int ITUR_BT_601_CVG = -852492;
    static const int ITUR_BT_601_CVR = 1673527;
    static const int ITUR_BT_601_SHIFT = 20;

    // Coefficients for RGB to YUV420p conversion
    //static const int ITUR_BT_601_CRY =  269484;
    //static const int ITUR_BT_601_CGY =  528482;
    //static const int ITUR_BT_601_CBY =  102760;
    //static const int ITUR_BT_601_CRU = -155188;
    //static const int ITUR_BT_601_CGU = -305135;
    //static const int ITUR_BT_601_CBU =  460324;
    //static const int ITUR_BT_601_CGV = -385875;
    //static const int ITUR_BT_601_CBV = -74448;

    //R = 1.164(Y - 16) + 1.596(V - 128)
    //G = 1.164(Y - 16) - 0.813(V - 128) - 0.391(U - 128)
    //B = 1.164(Y - 16)                  + 2.018(U - 128)

    //R = (1220542(Y - 16) + 1673527(V - 128)                  + (1 << 19)) >> 20
    //G = (1220542(Y - 16) - 852492(V - 128) - 409993(U - 128) + (1 << 19)) >> 20
    //B = (1220542(Y - 16)                  + 2116026(U - 128) + (1 << 19)) >> 20


#if TV_NEON
    int shift = 1 << (ITUR_BT_601_SHIFT - 1);
    int32x4_t v_shift = vdupq_n_s32(shift);
    int16x8_t v_0 = vdupq_n_s16(0);
    int16x8_t v_16 = vdupq_n_s16(16);
    uint8x8_t v_128 = vdup_n_u8(128);
#endif // TV_NEON

    for (int y=0; y<=h-2; y+=2)
    {
        unsigned char* y_ptr0 = y_plane;
        unsigned char* y_ptr1 = y_ptr0 + y_linebytes;
        y_plane = y_ptr1 + y_linebytes;

        unsigned char* rgb0 = rgb;
        unsigned char* rgb1 = rgb0+ rgb_linebytes;
        rgb = rgb1 + rgb_linebytes;

        unsigned char* uv_ptr = uv_plane;
        uv_plane = uv_ptr + uv_linebytes;

#if TV_NEON
        int nn = w >> 3;
        int remain = w - (nn << 3);
#else
        int remain = w;
#endif // TV_NEON

#if TV_NEON
        for (; nn > 0; nn--)
        {
            // y0 = y_ptr0[0] << 6
            //int16x8_t v_y0 = vreinterpretq_s16_u16(vshll_n_u8(vld1_u8(y_ptr0), 6));
            // y1 = y_ptr1[0] << 6
            //int16x8_t v_y1 = vreinterpretq_s16_u16(vshll_n_u8(vld1_u8(y_ptr1), 6));
            int16x8_t v_y0 = vreinterpretq_s16_u16(vmovl_u8(vld1_u8(y_ptr0)));
            int16x8_t v_y1 = vreinterpretq_s16_u16(vmovl_u8(vld1_u8(y_ptr1)));

            // y0 = std::max(0, y0 - 16)
            v_y0 = vmaxq_s16(v_0, vsubq_s16(v_y0, v_16));
            v_y1 = vmaxq_s16(v_0, vsubq_s16(v_y1, v_16));

            int8x8_t v_uv = vreinterpret_s8_u8(vsub_u8(vld1_u8(uv_ptr), v_128));
            int8x8x2_t v_uvtmp = vtrn_s8(v_uv, v_uv);
            int8x8_t v_u = v_uvtmp.val[u_idx];
            int8x8_t v_v = v_uvtmp.val[1-u_idx];

            int16x8_t v_s16_u = vmovl_s8(v_u);
            int32x4_t v_u0 = vmovl_s16(vget_low_s16(v_s16_u));
            int32x4_t v_u1 = vmovl_s16(vget_high_s16(v_s16_u));
            
            int16x8_t v_s16_v = vmovl_s8(v_v);
            int32x4_t v_v0 = vmovl_s16(vget_low_s16(v_s16_v));
            int32x4_t v_v1 = vmovl_s16(vget_high_s16(v_s16_v));

            // int shift = 1 << (ITUR_BT_601_SHIFT - 1);
            // int ruv = shift + ITUR_BT_601_CVR * v;
            // int guv = shift + ITUR_BT_601_CVG * v + ITUR_BT_601_CUG * u;
            // int buv = shift + ITUR_BT_601_CUB * u;
            /// rgb, 00
            int32x4_t v_r00 = vmlaq_n_s32(v_shift, v_v0, ITUR_BT_601_CVR);
            int32x4_t v_g00 = vaddq_s32(v_shift,
                vmlaq_n_s32(
                    vmulq_n_s32(v_v0, ITUR_BT_601_CVG),
                    v_u0, ITUR_BT_601_CUG
                )
            );
            int32x4_t v_b00 = vmlaq_n_s32(v_shift, v_u0, ITUR_BT_601_CUB);

            // load Y, first line
            int32x4_t v_y00 = vmulq_n_s32(vmovl_s16(vget_low_s16(v_y0)), ITUR_BT_601_CY);
            int32x4_t v_y01 = vmulq_n_s32(vmovl_s16(vget_high_s16(v_y0)), ITUR_BT_601_CY);

            /// rgb, 01
            int32x4_t v_r01 = vmlaq_n_s32(v_shift, v_v1, ITUR_BT_601_CVR);
            int32x4_t v_g01 = vaddq_s32(v_shift,
                vmlaq_n_s32(
                    vmulq_n_s32(v_v1, ITUR_BT_601_CVG),
                    v_u1, ITUR_BT_601_CUG
                )
            );
            int32x4_t v_b01 = vmlaq_n_s32(v_shift, v_u1, ITUR_BT_601_CUB);
            

            // load Y, second line
            int32x4_t v_y10 = vmulq_n_s32(vmovl_s16(vget_low_s16(v_y1)), ITUR_BT_601_CY);
            int32x4_t v_y11 = vmulq_n_s32(vmovl_s16(vget_high_s16(v_y1)), ITUR_BT_601_CY);
            

            uint8x8x3_t v_rgb0;
            // ITUR_BT_601_SHIFT is 20, out of range [1, 16], have to do shift right **twice** (16+4)
            v_rgb0.val[2-b_idx] = vqmovn_u16( vshrq_n_u16(
                vcombine_u16( // uint16x8_t
                    vqshrun_n_s32(vaddq_s32(v_r00, v_y00), 16), // uint16x4_t
                    vqshrun_n_s32(vaddq_s32(v_r01, v_y01), 16)  // uint16x4_t
                ),
                4 //ITUR_BT_601_SHIFT - 16
            ));
            v_rgb0.val[1] = vqmovn_u16( vshrq_n_u16(
                vcombine_u16( // uint16x8_t
                    vqshrun_n_s32(vaddq_s32(v_g00, v_y00), 16), // uint16x4_t
                    vqshrun_n_s32(vaddq_s32(v_g01, v_y01), 16)  // uint16x4_t
                ),
                4 // ITUR_BT_601_SHIFT - 16
            ));
            v_rgb0.val[b_idx] = vqmovn_u16( vshrq_n_u16(
                vcombine_u16( // uint16x8_t
                    vqshrun_n_s32(vaddq_s32(v_b00, v_y00), 16), // uint16x4_t
                    vqshrun_n_s32(vaddq_s32(v_b01, v_y01), 16)  // uint16x4_t
                ),
                4 // ITUR_BT_601_SHIFT - 16
            ));
            vst3_u8(rgb0, v_rgb0);


            // rgb, 10
            int32x4_t v_r10 = vmlaq_n_s32(v_shift, v_v0, ITUR_BT_601_CVR);
            int32x4_t v_g10 = vaddq_s32(v_shift,
                vmlaq_n_s32(
                    vmulq_n_s32(v_v0, ITUR_BT_601_CVG),
                    v_u0, ITUR_BT_601_CUG
                )
            );
            int32x4_t v_b10 = vmlaq_n_s32(v_shift, v_u0, ITUR_BT_601_CUB);

            // rgb, 11
            int32x4_t v_r11 = vmlaq_n_s32(v_shift, v_v1, ITUR_BT_601_CVR);
            int32x4_t v_g11 = vaddq_s32(v_shift,
                vmlaq_n_s32(
                    vmulq_n_s32(v_v1, ITUR_BT_601_CVG),
                    v_u1, ITUR_BT_601_CUG
                )
            );
            int32x4_t v_b11 = vmlaq_n_s32(v_shift, v_u1, ITUR_BT_601_CUB);


            uint8x8x3_t v_rgb1;
            // ITUR_BT_601_SHIFT is 20, out of range [1, 16], have to do shift right **twice** (16+4)
            v_rgb1.val[2-b_idx] = vqmovn_u16( vshrq_n_u16(
                vcombine_u16( // uint16x8_t
                    vqshrun_n_s32(vaddq_s32(v_r10, v_y10), 16), // uint16x4_t
                    vqshrun_n_s32(vaddq_s32(v_r11, v_y11), 16)  // uint16x4_t
                ),
                4 // ITUR_BT_601_SHIFT - 16
            ));
            v_rgb1.val[1] = vqmovn_u16( vshrq_n_u16(
                vcombine_u16( // uint16x8_t
                    vqshrun_n_s32(vaddq_s32(v_g10, v_y10), 16), // uint16x4_t
                    vqshrun_n_s32(vaddq_s32(v_g11, v_y11), 16)  // uint16x4_t
                ),
                4 // ITUR_BT_601_SHIFT - 16
            ));
            v_rgb1.val[b_idx] = vqmovn_u16( vshrq_n_u16(
                vcombine_u16( // uint16x8_t
                    vqshrun_n_s32(vaddq_s32(v_b10, v_y10), 16), // uint16x4_t
                    vqshrun_n_s32(vaddq_s32(v_b11, v_y11), 16)  // uint16x4_t
                ),
                4 // ITUR_BT_601_SHIFT - 16
            ));
            vst3_u8(rgb1, v_rgb1);

            y_ptr0 += 8;
            y_ptr1 += 8;
            uv_ptr += 8;
            rgb0 += 24;
            rgb1 += 24;
        }
#endif // TV_NEON

#define CLIP_TO_UCHAR(x) ((x) < 0 ? 0 : ((x) > 255 ? 255 : (x)))
        for (; remain>0; remain-=2)
        {
            int u = uv_ptr[u_idx] - 128;///
            int v = uv_ptr[1-u_idx] - 128;///

            // int ruv = 90 * v;
            // int guv = -46 * v - 22 * u;
            // int buv = 113 * u;
            int shift = 1 << (ITUR_BT_601_SHIFT - 1);
            int ruv = shift + ITUR_BT_601_CVR * v;
            int guv = shift + ITUR_BT_601_CVG * v + ITUR_BT_601_CUG * u;
            int buv = shift + ITUR_BT_601_CUB * u;
            
            /// y00
            // int y00 = y_ptr0[0] << 6;
            // rgb0[2-b_idx] = CLIP_TO_UCHAR((y00 + ruv) >> 6);
            // rgb0[1] = CLIP_TO_UCHAR((y00 + guv) >> 6);
            // rgb0[b_idx] = CLIP_TO_UCHAR((y00 + buv) >> 6);
            ///////////////
            /*
            static const int ITUR_BT_601_CY = 1220542;
            static const int ITUR_BT_601_CUB = 2116026;
            static const int ITUR_BT_601_CUG = -409993;
            static const int ITUR_BT_601_CVG = -852492;
            static const int ITUR_BT_601_CVR = 1673527;
            static const int ITUR_BT_601_SHIFT = 20;

            r = uchar_clip( ( max(0, y-16)*ITUR_BT_601_CY + (1 << (20 - 1) ) + ITUR_BT_601_CVR * v ) >> 20 );
            g = uchar_clip( ( max(0, y-16)*ITUR_BT_601_CY + (1 << (20 - 1) ) + ITUR_BT_601_CVG * v + ITUR_BT_601_CUG * u ) >> 20 );
            b = uchar_clip( ( max(0, y-16)*ITUR_BT_601_CY + (1 << (20 - 1) ) + ITUR_BT_601_CUB * u ) >> 20 );

            r = uchar_clip( ( max(0, y-16)*ITUR_BT_601_CY + (1 << (20 - 1) ) + ITUR_BT_601_CVR * v ) >> 20 );
            g = uchar_clip( ( max(0, y-16)*ITUR_BT_601_CY + (1 << (20 - 1) ) + ITUR_BT_601_CVG * v + ITUR_BT_601_CUG * u ) >> 20 );
            b = uchar_clip( ( max(0, y-16)*ITUR_BT_601_CY + (1 << (20 - 1) ) + ITUR_BT_601_CUB * u ) >> 20 );

            r = ( y * ITUR_BT_601_CY + 2^19 + ITUR_BT_601_CVR * v ) / 2^20;
            g = ( y * ITUR_BT_601_CY + 2^19 + ITUR_BT_601_CVG * v + ITUR_BT_601_CUG * u ) / 2^20;
            b = ( y * ITUR_BT_601_CY + 2^19 + ITUR_BT_601_CUB * u ) / 2^20;

            r = (ITUR_BT_601_CY/2^20) * y + (ITUR_BT_601_CVR/2^20) * v;
            g = (ITUR_BT_601_CY/2^20) * y + (ITUR_BT_601_CVG/2^20) * v + (ITUR_BT_601_CUG/2^20) * v;
            b = (ITUR_BT_601_CY/2^20) * y + (ITUR_BT_601_CUB/2^20) * u;

            r = 1.1639 * y + 1.5959 * v;
            g = 1.1639 * y - 0.8129 * v - 0.3909 * u;
            b = 1.1639 * y + 2.0179 * u;

            // 1.164 = 255 / 219 = 255 / (235-16),    [16, 235] is range, [0, 255] is range
            R = 1.164(Y - 16) + 1.596(V - 128)
            G = 1.164(Y - 16) - 0.813(V - 128) - 0.391(U - 128)
            B = 1.164(Y - 16)                  + 2.018(U - 128)

            R = (1220542(Y - 16) + 1673527(V - 128)                  + (1 << 19)) >> 20
            G = (1220542(Y - 16) - 852492(V - 128) - 409993(U - 128) + (1 << 19)) >> 20
            B = (1220542(Y - 16)                  + 2116026(U - 128) + (1 << 19)) >> 20
            */
            ///////////////
            int y00 = std::max(0, y_ptr0[0]-16) * ITUR_BT_601_CY;
            rgb0[2-b_idx] = CLIP_TO_UCHAR( (y00 + ruv) >> ITUR_BT_601_SHIFT );
            rgb0[1] = CLIP_TO_UCHAR( (y00 + guv) >> ITUR_BT_601_SHIFT );
            rgb0[b_idx] = CLIP_TO_UCHAR( (y00 + buv) >> ITUR_BT_601_SHIFT );
            rgb0 += 3;

            // int y01 = y_ptr0[1] << 6;
            // rgb0[2-b_idx] = CLIP_TO_UCHAR((y01 + ruv) >> 6);
            // rgb0[1] = CLIP_TO_UCHAR((y01 + guv) >> 6);
            // rgb0[b_idx] = CLIP_TO_UCHAR((y01 + buv) >> 6);
            int y01 = std::max(0, y_ptr0[1]-16) * ITUR_BT_601_CY;
            rgb0[2-b_idx] = CLIP_TO_UCHAR( (y01 + ruv) >> ITUR_BT_601_SHIFT );
            rgb0[1] = CLIP_TO_UCHAR( (y01 + guv) >> ITUR_BT_601_SHIFT );
            rgb0[b_idx] = CLIP_TO_UCHAR( (y01 + buv) >> ITUR_BT_601_SHIFT );
            rgb0 += 3;

            // int y10 = y_ptr1[0] << 6;
            // rgb1[2-b_idx] = CLIP_TO_UCHAR((y10 + ruv) >> 6);
            // rgb1[1] = CLIP_TO_UCHAR((y10 + guv) >> 6);
            // rgb1[b_idx] = CLIP_TO_UCHAR((y10 + buv) >> 6);
            int y10 = std::max(0, y_ptr1[0]-16) * ITUR_BT_601_CY;
            rgb1[2-b_idx] = CLIP_TO_UCHAR( (y10 + ruv) >> ITUR_BT_601_SHIFT );
            rgb1[1] = CLIP_TO_UCHAR( (y10 + guv) >> ITUR_BT_601_SHIFT );
            rgb1[b_idx] = CLIP_TO_UCHAR( (y10 + buv) >> ITUR_BT_601_SHIFT );
            rgb1 += 3;

            // int y11 = y_ptr1[1] << 6;
            // rgb1[2-b_idx] = CLIP_TO_UCHAR((y11 + ruv) >> 6);
            // rgb1[1] = CLIP_TO_UCHAR((y11 + guv) >> 6);
            // rgb1[b_idx] = CLIP_TO_UCHAR((y11 + buv) >> 6);
            int y11 = std::max(0, y_ptr1[1]-16) * ITUR_BT_601_CY;
            rgb1[2-b_idx] = CLIP_TO_UCHAR( (y11 + ruv) >> ITUR_BT_601_SHIFT );
            rgb1[1] = CLIP_TO_UCHAR( (y11 + guv) >> ITUR_BT_601_SHIFT );
            rgb1[b_idx] = CLIP_TO_UCHAR( (y11 + buv) >> ITUR_BT_601_SHIFT );
            rgb1 += 3;

            y_ptr0 += 2;
            y_ptr1 += 2;
            uv_ptr += 2;///
        }
#undef CLIP_TO_UCHAR
    }
}


} // namespace

namespace asvl {

enum class InterpMethod
{
    NN,
    LINEAR,
    BICUBIC
};



ASVL_API ASVLOFFSCREEN* convert_from(ASVLOFFSCREEN* src, MUInt32 dst_fmt);

// 张卓，我这边想从NV21转成YUV444P，且包含缩放，有没有一个函数解决的
// 我现在的做法是将Y,U,V都单独提取出来再用mobilecv分别缩放，感觉有些浪费，mobilecv没有这样的实现
// ，不知道toy有没有 （by 张文豪）

// 包含： 格式转换的 warp affine
// 解决常见需求： resize， crop resize， 旋转， 格式转换， 以及它们的组合
ASVL_API void warp_affine(ASVLOFFSCREEN* src, ASVLOFFSCREEN* dst, float* tm);

} // namespace asvl


//================================================================================
// Implementations
//================================================================================

namespace {

template<int uIdx>
ASVLOFFSCREEN* rgb_to_yuv420sp(ASVLOFFSCREEN* asvl_rgb)
{
    asvl::MSize ysize = asvl::get_size(asvl_rgb);
    ASVLOFFSCREEN* asvl_yuv420sp = asvl::create_yuv420sp<uIdx>(ysize);

    const int srcPitch = asvl_rgb->pi32Pitch[0];
    const int dstPitchY = asvl_yuv420sp->pi32Pitch[0];
    const int dstPitchUV = asvl_yuv420sp->pi32Pitch[1];

    for (int i = 0; i < ysize.height; i += 2)
    {
        const uint8_t* rgb0 = asvl_rgb->ppu8Plane[0] + i * srcPitch;
        const uint8_t* rgb1 = rgb0 + srcPitch;
        uint8_t* y0 = asvl_yuv420sp->ppu8Plane[0] + i * dstPitchY;
        uint8_t* y1 = y0 + dstPitchY;
        uint8_t* uv = asvl_yuv420sp->ppu8Plane[1] + (i / 2) * dstPitchUV;
        for (int j = 0; j < ysize.width; j += 2)
        {
            uint8_t y, u, v, r, g, b;

            r = *rgb0++;
            g = *rgb0++;
            b = *rgb0++;
            YUVfromRGB_u8(y, u, v, r, g, b);
            *y0++ = y;
            uv[1-uIdx] = v;
            uv[uIdx] = u;
            uv += 2;

            r = *rgb0++;
            g = *rgb0++;
            b = *rgb0++;
            YUVfromRGB_u8(y, u, v, r, g, b);
            *y0++ = y;

            r = *rgb1++;
            g = *rgb1++;
            b = *rgb1++;
            YUVfromRGB_u8(y, u, v, r, g, b);
            *y1++ = y;

            r = *rgb1++;
            g = *rgb1++;
            b = *rgb1++;
            YUVfromRGB_u8(y, u, v, r, g, b);
            *y1++ = y;
        }
    }
    return asvl_yuv420sp;
}


template<int uIdx>
ASVLOFFSCREEN* rgb_from_yuv420sp(ASVLOFFSCREEN* asvl_yuv420sp)
{
    asvl::MSize ysize = asvl::get_size(asvl_yuv420sp);
    ASVLOFFSCREEN* asvl_rgb = asvl::create_rgb(ysize);

    int srcPitchY = asvl_yuv420sp->pi32Pitch[0];
    int srcPitchUV = asvl_yuv420sp->pi32Pitch[1];
    int dstPitch = asvl_rgb->pi32Pitch[0];

#if 0
    //void nv21_to_bgr(unsigned char *imgY, int width, int height, unsigned char *imgDst)
    nv21_to_bgr(asvl_yuv420sp->ppu8Plane[0], ysize.width, ysize.height, asvl_rgb->ppu8Plane[0]);
    return asvl_rgb;

#elif 0
    cv::Size ssize;
    ssize.width = ysize.width;
    ssize.height = ysize.height;
    
    cv::Mat src(ysize.height * 3 / 2, ysize.width, CV_8UC1, asvl_yuv420sp->ppu8Plane[0]);
    cv::Mat dst(ysize.height, ysize.width, CV_8UC3, asvl_rgb->ppu8Plane[0]);
    cv::cvtColor(src, dst, cv::COLOR_YUV2BGR_NV21);
    return asvl_rgb;
#elif 0

    uint8_t* y_plane = asvl_yuv420sp->ppu8Plane[0];
    int width = ysize.width;
    int height = ysize.height;
    int y_linebytes = asvl_yuv420sp->pi32Pitch[0];
    uint8_t* uv_plane = asvl_yuv420sp->ppu8Plane[1];
    int uv_linebytes = asvl_yuv420sp->pi32Pitch[1];
    uint8_t* rgb = asvl_rgb->ppu8Plane[0];
    int rgb_linebytes = asvl_rgb->pi32Pitch[0];
    yuv420sp_to_rgb_opencv<uIdx, 2>(
        y_plane, width, height, y_linebytes,
        uv_plane, uv_linebytes,
        rgb, rgb_linebytes
    );
    return asvl_rgb;

#endif

    for (int i = 0; i < ysize.height; i += 2)
    {
        uint8_t* y0 = asvl_yuv420sp->ppu8Plane[0] + i * srcPitchY;
        uint8_t* y1 = y0 + srcPitchY;
        uint8_t* uv = asvl_yuv420sp->ppu8Plane[1] + (i / 2) * srcPitchUV;

        uint8_t* rgb0 = asvl_rgb->ppu8Plane[0] + i * dstPitch;
        uint8_t* rgb1 = rgb0 + dstPitch;
        for (int j = 0; j < ysize.width; j+=2)
        {
            uint8_t u, v;
            uint8_t y;
            uint8_t r, g, b;

            v = uv[1-uIdx];
            u = uv[uIdx];
            uv += 2;

            y = *y0++;
            RGBfromYUV_BT601_u8(r, g, b, y, u, v);
            *rgb0++ = r;
            *rgb0++ = g;
            *rgb0++ = b;

            y = *y0++;
            RGBfromYUV_BT601_u8(r, g, b, y, u, v);
            *rgb0++ = r;
            *rgb0++ = g;
            *rgb0++ = b;


            y = *y1++;
            RGBfromYUV_BT601_u8(r, g, b, y, u, v);
            *rgb1++ = r;
            *rgb1++ = g;
            *rgb1++ = b;

            y = *y1++;
            RGBfromYUV_BT601_u8(r, g, b, y, u, v);
            *rgb1++ = r;
            *rgb1++ = g;
            *rgb1++ = b;
        }
    }
    return asvl_rgb;
}

} // namespace

ASVLOFFSCREEN* asvl::convert_from(ASVLOFFSCREEN* src, MUInt32 dst_fmt)
{
    MSize size = get_size(src);
    ASVLOFFSCREEN* dst = create_asvl(dst_fmt, size);
    MUInt32 src_fmt = src->u32PixelArrayFormat;

    if ((src_fmt == ASVL_PAF_NV21 && dst_fmt == ASVL_PAF_NV12)
        || (src_fmt == ASVL_PAF_NV12 && dst_fmt == ASVL_PAF_NV21)
        )
    {
        Plane src_y_plane = get_plane(src, 0);
        Plane dst_y_plane = get_plane(dst, 0);
        memcpy(dst_y_plane.data, src_y_plane.data, dst_y_plane.bufsize());

        Plane src_uv_plane = get_plane(src, 1);
        Plane dst_uv_plane = get_plane(dst, 1);
        for (int i = 0; i < dst_uv_plane.height; i++)
        {
            uint8_t* src_line = src_uv_plane.data + i * src_uv_plane.pitch;
            uint8_t* dst_line = dst_uv_plane.data + i * dst_uv_plane.pitch;
            for (int j = 0; j < dst_uv_plane.pitch; j+=2)
            {
                uint8_t buf[2];
                buf[0] = src_line[j];
                buf[1] = src_line[j + 1];
                dst_line[j] = buf[1];
                dst_line[j + 1] = buf[0];
            }
        }
    }
    else if ((src_fmt == ASVL_PAF_RGB24_B8G8R8 && dst_fmt == ASVL_PAF_RGB24_R8G8B8)
        || (src_fmt == ASVL_PAF_RGB24_R8G8B8 && dst_fmt == ASVL_PAF_RGB24_B8G8R8)
        )
    {
        Plane src_plane = get_plane(src, 0);
        Plane dst_plane = get_plane(dst, 0);
        for (int i = 0; i < src_plane.height; i++)
        {
            uint8_t* src_line = src_plane.data + i * src_plane.pitch;
            uint8_t* dst_line = dst_plane.data + i * dst_plane.pitch;
            for (int j = 0; j < dst_plane.pitch; j+= 3)
            {
                uint8_t buf[3];
                buf[0] = src_line[j];
                buf[1] = src_line[j + 1];
                buf[2] = src_line[j + 2];
                dst_line[0] = buf[2];
                dst_line[1] = buf[1];
                dst_line[2] = buf[0];
            }
        }
    }
    else if ((src_fmt == ASVL_PAF_RGB32_B8G8R8A8 && dst_fmt == ASVL_PAF_RGB32_R8G8B8A8)
        || (src_fmt == ASVL_PAF_RGB32_R8G8B8A8 && dst_fmt == ASVL_PAF_RGB32_B8G8R8A8)
        )
    {
        Plane src_plane = get_plane(src, 0);
        Plane dst_plane = get_plane(dst, 0);
        for (int i = 0; i < src_plane.height; i++)
        {
            uint8_t* src_line = src_plane.data + i * src_plane.pitch;
            uint8_t* dst_line = dst_plane.data + i * dst_plane.pitch;
            for (int j = 0; j < dst_plane.pitch; j+= 3)
            {
                uint8_t buf[4];
                buf[0] = src_line[j];
                buf[1] = src_line[j + 1];
                buf[2] = src_line[j + 2];
                buf[3] = src_line[j + 3];
                dst_line[0] = buf[2];
                dst_line[1] = buf[1];
                dst_line[2] = buf[0];
                dst_line[3] = buf[3];
            }
        }
    }
    else
    {
        ASVL_LOGE("not supported convert format mapping: %s -> %s",
            get_fmt_str(src_fmt).c_str(),
            get_fmt_str(dst_fmt).c_str()
        );
    }
    return dst;
}


// drawing
void asvl::draw_point(ASVLOFFSCREEN* pimg, MPOINTF pnt, int radius, int r_val, int g_val, int b_val)
{
    MUInt32 fmt = pimg->u32PixelArrayFormat;
    int uIdx = -233;
    if (fmt == ASVL_PAF_NV21)
    {
        uIdx = 1;
    }
    else if (fmt == ASVL_PAF_NV12)
    {
        uIdx = 0;
    }
    else
    {
        ASVL_LOGE("only support NV21/NV12");
        return;
    }

    double Y, U, V;
    YUVfromRGB(Y, U, V, r_val, g_val, b_val);

    int y_val, u_val, v_val;
    y_val = Y;
    u_val = U;
    v_val = V;

    y_val = std::max(0, std::min(y_val, 255));
    u_val = std::max(0, std::min(u_val, 255));
    v_val = std::max(0, std::min(v_val, 255));

    for (int i = -radius; i < radius + 1; i++)
    {
        int endj = floor(sqrt(radius * radius - i * i));
        for (int j = -endj; j < endj + 1; j++)
        {
            int newx = pnt.x + j;
            int newy = pnt.y + i;
            if (newx < 1 || newx > pimg->i32Width - 2 || newy < 1 || newy > pimg->i32Height - 2)
            {
                continue;
            }
            MUInt8* pdata = pimg->ppu8Plane[0] + pimg->pi32Pitch[0] * newy + newx;
            *pdata = y_val;

            newx = (newx - newx%2)/2;
            newy = (newy - newy%2)/2;

            pdata = pimg->ppu8Plane[1] + pimg->pi32Pitch[1] * newy + newx * 2;

            pdata[uIdx] = u_val;
            pdata[1 - uIdx] = v_val;
            pdata += 2;
        }
    }
}

ASVLOFFSCREEN* asvl::rgb_to_nv21(ASVLOFFSCREEN* asvl_rgb)
{
    return rgb_to_yuv420sp<1>(asvl_rgb);
}

ASVLOFFSCREEN* asvl::rgb_to_nv12(ASVLOFFSCREEN* asvl_rgb)
{
    return rgb_to_yuv420sp<0>(asvl_rgb);
}

ASVLOFFSCREEN* asvl::rgb_from_nv21(ASVLOFFSCREEN* asvl_nv21)
{
    return rgb_from_yuv420sp<1>(asvl_nv21);
}

ASVLOFFSCREEN* asvl::rgb_from_nv12(ASVLOFFSCREEN* asvl_nv12)
{
    return rgb_from_yuv420sp<0>(asvl_nv12);
}

ASVLOFFSCREEN* asvl::rgb_to_i420(ASVLOFFSCREEN* asvl_rgb)
{
    asvl::MSize ysize = asvl::get_size(asvl_rgb);
    ASVLOFFSCREEN* asvl_i420 = asvl::create_asvl(ASVL_PAF_I420, ysize);

    const int srcPitch = asvl_rgb->pi32Pitch[0];
    const int dstPitchY = asvl_i420->pi32Pitch[0];
    const int dstPitchU = asvl_i420->pi32Pitch[1];
    const int dstPitchV = asvl_i420->pi32Pitch[2];

    asvl::dump_meta(asvl_rgb, "!rgb");
    asvl::dump_meta(asvl_i420, "!i420");

    for (int i = 0; i < ysize.height; i += 2)
    {
        const uint8_t* rgb0 = asvl_rgb->ppu8Plane[0] + i * srcPitch;
        const uint8_t* rgb1 = rgb0 +  srcPitch;
        uint8_t* y0 = asvl_i420->ppu8Plane[0] + i * dstPitchY;
        uint8_t* y1 = y0 + dstPitchY;
        uint8_t* pU = asvl_i420->ppu8Plane[1] + (i / 2) * dstPitchU;
        uint8_t* pV = asvl_i420->ppu8Plane[2] + (i / 2) * dstPitchV;
        for (int j = 0; j < ysize.width; j += 2)
        {
            uint8_t y, u, v, r, g, b;

            r = *rgb0++;
            g = *rgb0++;
            b = *rgb0++;
            YUVfromRGB_u8(y, u, v, r, g, b);
            *y0++ = y;
            *pV++ = v;
            *pU++ = u;

            r = *rgb0++;
            g = *rgb0++;
            b = *rgb0++;
            YUVfromRGB_u8(y, u, v, r, g, b);
            *y0++ = y;

            r = *rgb1++;
            g = *rgb1++;
            b = *rgb1++;
            YUVfromRGB_u8(y, u, v, r, g, b);
            *y1++ = y;

            r = *rgb1++;
            g = *rgb1++;
            b = *rgb1++;
            YUVfromRGB_u8(y, u, v, r, g, b);
            *y1++ = y;
        }
    }

    return asvl_i420;
}


ASVLOFFSCREEN* asvl::rgb_from_i420(ASVLOFFSCREEN* asvl_i420)
{
    asvl::MSize ysize = asvl::get_size(asvl_i420);
    ASVLOFFSCREEN* asvl_rgb = asvl::create_rgb(ysize);

    const int srcPitchY = asvl_i420->pi32Pitch[0];
    const int srcPitchU = asvl_i420->pi32Pitch[1];
    const int srcPitchV = asvl_i420->pi32Pitch[2];
    const int dstPitch = asvl_rgb->pi32Pitch[0];

    for (int i = 0; i < ysize.height; i += 2)
    {
        uint8_t* y0 = asvl_i420->ppu8Plane[0] + i * srcPitchY;
        uint8_t* y1 = y0 + srcPitchY;
        uint8_t* pU = asvl_i420->ppu8Plane[1] + (i / 2) * srcPitchU;
        uint8_t* pV = asvl_i420->ppu8Plane[2] + (i / 2) * srcPitchV;

        uint8_t* rgb0 = asvl_rgb->ppu8Plane[0] + i * dstPitch;
        uint8_t* rgb1 = rgb0 + dstPitch;
        for (int j = 0; j < ysize.width; j+=2)
        {
            uint8_t u, v;
            uint8_t y;
            uint8_t r, g, b;

            v = *pV++;
            u = *pU++;

            y = *y0++;
            RGBfromYUV_BT601_u8(r, g, b, y, u, v);
            *rgb0++ = r;
            *rgb0++ = g;
            *rgb0++ = b;

            y = *y0++;
            RGBfromYUV_BT601_u8(r, g, b, y, u, v);
            *rgb0++ = r;
            *rgb0++ = g;
            *rgb0++ = b;


            y = *y1++;
            RGBfromYUV_BT601_u8(r, g, b, y, u, v);
            *rgb1++ = r;
            *rgb1++ = g;
            *rgb1++ = b;

            y = *y1++;
            RGBfromYUV_BT601_u8(r, g, b, y, u, v);
            *rgb1++ = r;
            *rgb1++ = g;
            *rgb1++ = b;
        }
    }
    return asvl_rgb;
}

// U0 Y0 V0 Y1      U1 Y2 V1 Y3
ASVLOFFSCREEN* asvl::rgb_to_uyvy(ASVLOFFSCREEN* asvl_rgb)
{
    asvl::MSize ysize = asvl::get_size(asvl_rgb);
    ASVLOFFSCREEN* asvl_uyvy = asvl::create_asvl(ASVL_PAF_UYVY, ysize);

    const int srcPitch = asvl_rgb->pi32Pitch[0];
    const int dstPitch = asvl_uyvy->pi32Pitch[0];

    for (int i = 0; i < ysize.height; i += 2)
    {
        const uint8_t* rgb0 = asvl_rgb->ppu8Plane[0] + i * srcPitch;
        const uint8_t* rgb1 = rgb0 + srcPitch;
        uint8_t* pDst0 = asvl_uyvy->ppu8Plane[0] + i * dstPitch;
        uint8_t* pDst1 = pDst0 + dstPitch;

        for (int j = 0; j < ysize.width; j += 2)
        {
            uint8_t y0, y1, r, g, b, u, v;
            uint8_t u0, v0;

            r = *rgb0++;
            g = *rgb0++;
            b = *rgb0++;
            YUVfromRGB_u8(y0, u, v, r, g, b);
            u0 = u;
            v0 = v;
            
            r = *rgb0++;
            g = *rgb0++;
            b = *rgb0++;
            YUVfromRGB_u8(y1, u, v, r, g, b);

            *pDst0++ = u0;
            *pDst0++ = y0;
            *pDst0++ = v0;
            *pDst0++ = y1;


            
            r = *rgb1++;
            g = *rgb1++;
            b = *rgb1++;
            YUVfromRGB_u8(y0, u, v, r, g, b);
            
            r = *rgb1++;
            g = *rgb1++;
            b = *rgb1++;
            YUVfromRGB_u8(y1, u, v, r, g, b);

            *pDst1++ = u0;
            *pDst1++ = y0;
            *pDst1++ = v0;
            *pDst1++ = y1;
        }
    }
    return asvl_uyvy;
}

ASVLOFFSCREEN* asvl::i444_to_nv21(ASVLOFFSCREEN* asvl_i444)
{
    asvl::MSize ysize = asvl::get_size(asvl_i444);
    ASVLOFFSCREEN* asvl_nv21 = asvl::create_asvl(ASVL_PAF_NV21, ysize);

    const int dstPitchY = asvl_nv21->pi32Pitch[0];
    const int dstPitchUV = asvl_nv21->pi32Pitch[1];

    const int srcPitchY = asvl_i444->pi32Pitch[0];
    const int srcPitchU = asvl_i444->pi32Pitch[1];
    const int srcPitchV = asvl_i444->pi32Pitch[2];

    // asvl::dump_meta(asvl_i444, "!i444");
    // asvl::dump_meta(asvl_nv21, "!nv21");
    
    for (int i = 0; i < ysize.height; i += 2)
    {
        uint8_t* ydst0 = asvl_nv21->ppu8Plane[0] + i * dstPitchY;
        uint8_t* ydst1 = ydst0 + dstPitchY;
        uint8_t* vudst = asvl_nv21->ppu8Plane[1] + (i / 2) * dstPitchUV;

        const uint8_t* pSrcY0 = asvl_i444->ppu8Plane[0] + i * srcPitchY;
        const uint8_t* pSrcY1 = pSrcY0 + srcPitchY;
        const uint8_t* pSrcU = asvl_i444->ppu8Plane[1] + i * srcPitchU;
        const uint8_t* pSrcV = asvl_i444->ppu8Plane[2] + i * srcPitchV;
        for (int j = 0; j < ysize.width; j += 2)
        {
            *ydst0++ = *pSrcY0++;
            *ydst0++ = *pSrcY0++;
            *ydst1++ = *pSrcY1++;
            *ydst1++ = *pSrcY1++;
            *vudst++ = *pSrcV++;
            pSrcV++; //!
            *vudst++ = *pSrcU++;
            pSrcU++; //!
        }
    }

    return asvl_nv21;
}

ASVLOFFSCREEN* asvl::i420_to_uyvy(ASVLOFFSCREEN* asvl_i420)
{
    asvl::MSize ysize = asvl::get_size(asvl_i420);
    ASVLOFFSCREEN* asvl_uyvy = asvl::create_asvl(ASVL_PAF_UYVY, ysize);
    const int srcPitchY = asvl_i420->pi32Pitch[0];
    const int srcPitchU = asvl_i420->pi32Pitch[1];
    const int srcPitchV = asvl_i420->pi32Pitch[2];
    const int dstPitch = asvl_uyvy->pi32Pitch[0];

    for (int i = 0; i < ysize.height; i += 2)
    {
        const uint8_t* pSrcY0 = asvl_i420->ppu8Plane[0] + i * srcPitchY;
        const uint8_t* pSrcY1 = pSrcY0 + srcPitchY;
        const uint8_t* pSrcU = asvl_i420->ppu8Plane[1] + (i / 2) * srcPitchU;
        const uint8_t* pSrcV = asvl_i420->ppu8Plane[2] + (i / 2) * srcPitchV;

        uint8_t* pDst0 = asvl_uyvy->ppu8Plane[0] + i * dstPitch;
        uint8_t* pDst1 = pDst0 + dstPitch;
        for (int j = 0; j < ysize.width; j += 2)
        {
            uint8_t nU = *pSrcU++;
            uint8_t nV = *pSrcV++;

            *pDst0++ = nU;
            *pDst0++ = *pSrcY0++;
            *pDst0++ = nV;
            *pDst0++ = *pSrcY0++;

            *pDst1++ = nU;
            *pDst1++ = *pSrcY1++;
            *pDst1++ = nV;
            *pDst1++ = *pSrcY1++;
        }
    }
    return asvl_uyvy;
}


ASVLOFFSCREEN* asvl::rgb_from_uyvy(ASVLOFFSCREEN* asvl_uyvy)
{
    asvl::MSize ysize = asvl::get_size(asvl_uyvy);
    ASVLOFFSCREEN* asvl_rgb = asvl::create_rgb(ysize);

    const int srcPitch = asvl_uyvy->pi32Pitch[0];
    const int dstPitch = asvl_rgb->pi32Pitch[0];

    asvl::dump_meta(asvl_uyvy, "!uyvy");
    asvl::dump_meta(asvl_rgb, "!asvl_rgb");
    for (int i = 0; i < ysize.height; i += 2)
    {
        const uint8_t* pSrc0 = asvl_uyvy->ppu8Plane[0] + i * srcPitch;
        const uint8_t* pSrc1 = pSrc0 + srcPitch;
        uint8_t* rgb0 = asvl_rgb->ppu8Plane[0] + i * dstPitch;
        uint8_t* rgb1 = rgb0 + dstPitch;

        for (int j = 0; j < ysize.width; j += 2)
        {
            uint8_t y0, y1, u0, v0;
            uint8_t r, g, b;

            u0 = pSrc0[0];
            y0 = pSrc0[1];
            v0 = pSrc0[2];
            y1 = pSrc0[3];
            pSrc0 += 4;

            RGBfromYUV_BT601_u8(r, g, b, y0, u0, v0);
            *rgb0++ = r;
            *rgb0++ = g;
            *rgb0++ = b;

            RGBfromYUV_BT601_u8(r, g, b, y1, u0, v0);
            *rgb0++ = r;
            *rgb0++ = g;
            *rgb0++ = b;


            //u0 = pSrc1[0];
            y0 = pSrc1[1];
            //v0 = pSrc1[2];
            y1 = pSrc1[3];
            pSrc1 += 4;

            RGBfromYUV_BT601_u8(r, g, b, y0, u0, v0);
            *rgb1++ = r;
            *rgb1++ = g;
            *rgb1++ = b;

            RGBfromYUV_BT601_u8(r, g, b, y1, u0, v0);
            *rgb1++ = r;
            *rgb1++ = g;
            *rgb1++ = b;
        }
    }

    return asvl_rgb;
}


// Y Y Y Y           R G B    R G B   R G B
// Y Y Y Y
// Y Y Y Y           R G B    R G B   R G B
// Y Y Y Y           
//                   
// U U U U
// U U U U
// U U U U      =>   ...
// U U U U
//
// V V V V
// V V V V
// V V V V
// V V V V          R G B    R G B   R G B
ASVLOFFSCREEN* asvl::rgb_from_i444(ASVLOFFSCREEN* asvl_i444)
{
    asvl::MSize ysize = asvl::get_size(asvl_i444);
    ASVLOFFSCREEN* asvl_rgb = asvl::create_rgb(ysize);

    const int srcPitchY = asvl_i444->pi32Pitch[0];
    const int srcPitchU = asvl_i444->pi32Pitch[1];
    const int srcPitchV = asvl_i444->pi32Pitch[2];

    const int dstPitch = asvl_rgb->pi32Pitch[0];
    for (int i = 0; i < ysize.height; i++)
    {
        const uint8_t* pY = asvl_i444->ppu8Plane[0] + i * srcPitchY;
        const uint8_t* pU = asvl_i444->ppu8Plane[1] + i * srcPitchU;
        const uint8_t* pV = asvl_i444->ppu8Plane[2] + i * srcPitchV;
        uint8_t* rgb = asvl_rgb->ppu8Plane[0] + i * dstPitch;
        for (int j = 0; j < ysize.width; j++)
        {
            uint8_t y, u, v, r, g, b;
            y = *pY++;
            u = *pU++;
            v = *pV++;
            RGBfromYUV_BT601_u8(r, g, b, y, u, v);
            *rgb++ = r;
            *rgb++ = g;
            *rgb++ = b;
        }
    }

    return asvl_rgb;
}

#ifdef USE_OPENCV

static
void my_test_convert_color()
{
    std::string im_name = "boy.png";

    cv::Mat src = cv::imread(im_name);

    //int width = src.cols;
    //int height = src.rows;
    //width = (width / 4) * 4;
    //height = (height / 4) * 4;
    //cv::Rect rect(0, 0, width, height);
    //cv::Mat dst = src(rect);
    //cv::imwrite("boy_aligned.png", dst);

    size_t buf_size = src.cols * src.rows * 3 / 2;
    uchar* nv21 = (uchar*)malloc(buf_size);
    memset(nv21, 0, buf_size);
    //bgr888_to_yuv420sp(src.data, src.cols, src.rows, nv21);
    bgr_to_nv21(src.data, src.cols, src.rows, nv21);

    buf_size = 3 * src.cols * src.rows;
    uchar* bgr = (uchar*)malloc(buf_size);
    memset(bgr, 0, buf_size);
    nv21_to_bgr(nv21, src.cols, src.rows, bgr);

    src.data = bgr;
    cv::imwrite("boy_res_zznew.png", src);

}
#endif
