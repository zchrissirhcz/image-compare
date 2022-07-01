// asvl_helper.hpp: header-only library for ASVLOFFSCREEN processing
//      - mainly for create/destoy/read/write/validate
//      - for convert format, see asvl_cvtfmt.hpp
// author: Zhuo Zhang (zz9555@arcsoft.com.cn)
// last update: 2022-06-30 23:30:00

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>

#include "amcomdef.h"
#include "asvloffscreen.h"


//================================================================================
// Public APIs
//================================================================================

#define ASVL_API static

//--------------------------------------------------------------------------------
// 1. Logging
//--------------------------------------------------------------------------------
// Usage:
//  ASVL_LOGD("your_debug_log_formatter\n", ...); // print as you specified
//  ASVL_LOGE("your_error_log_formatter", ...); // print specified and function, file, line
#define ASVL_STDIO 1

#ifdef ASVL_STDIO
#if __ANDROID_API__ >= 8
#include <android/log.h>
#define ASVL_LOGE(fmt, ...) do { \
    fprintf(stderr, (fmt "%s %s:%d\n"), ##__VA_ARGS__, __FUNCTION__, __FILE__, __LINE__); \
    __android_log_print(ANDROID_LOG_WARN, "asvl_helper", (fmt "%s %s:%d\n"), ##__VA_ARGS__, __FUNCTION__, __FILE__, __LINE__); } while(0)
#define ASVL_LOGD(...) do { \
    fprintf(stderr, ##__VA_ARGS__); \
    __android_log_print(ANDROID_LOG_DEBUG, "asvl_helper", ##__VA_ARGS__); } while(0)
#else
#include <stdio.h>
#define ASVL_LOGE(fmt, ...) do { \
    fprintf(stderr, (fmt " in %s(), %s:%d\n"), ##__VA_ARGS__, __FUNCTION__, __FILE__, __LINE__); } while(0)
#define ASVL_LOGD(...) do { \
    fprintf(stderr, ##__VA_ARGS__); } while(0)
#endif
#else
#define ASVL_LOGE(fmt, ...)
#define ASVL_LOGD(...)
#endif

#define ASVL_PAF_UNKNOWN  0x001

namespace asvl {

//--------------------------------------------------------------------------------
// 2. Size 类型
//--------------------------------------------------------------------------------
// usage:
// asvl::MSize msize;
// msize.set_width(1920).set_height(1080);
class MSize
{
public:
    int width;
    int height;
public:
    MSize(): width(0), height(0) {}
    MSize& set_width(int w)
    {
        width = w;
        return *this;
    }

    MSize& set_height(int h)
    {
        height = h;
        return *this;
    }
    bool operator = (const MSize& other) const
    {
        return width == other.width & height == other.height;
    }
    bool operator != (const MSize& other) const
    {
        return !(this->operator=(other));
    }
};

class Plane
{
public:
    int width;
    int height;
    int channels;
    int pitch;
    int elemsize;
    uint8_t* data;
public:
    Plane(): width(0), height(0), channels(0), pitch(0), elemsize(sizeof(uint8_t)), data(nullptr) {}
    Plane& set_width(int _width)
    {
        width = _width;
        return *this;
    }
    Plane& set_height(int _height)
    {
        height = _height;
        return *this;
    }
    Plane& set_channels(int _channels)
    {
        channels = _channels;
        return *this;
    }
    Plane& set_pitch(int _pitch)
    {
        pitch = _pitch;
        return *this;
    }
    Plane& set_data(uint8_t* _data)
    {
        data = _data;
        return *this;
    }
    int bufsize() const
    {
        return height * pitch * sizeof(uint8_t);
    }
};

// meta info
ASVL_API std::unordered_map<MUInt32, std::string> get_fmt_table();
ASVL_API MUInt32 get_fmt(ASVLOFFSCREEN* asvl);
ASVL_API MUInt32 get_fmt_from_ext(const std::string& ext);
ASVL_API std::string get_fmt_str(MUInt32 fmt);
ASVL_API MSize get_size(ASVLOFFSCREEN* asvl);
ASVL_API MSize get_size_from_path(const std::string& image_path);
ASVL_API std::string get_ext(MUInt32 fmt);

ASVL_API Plane get_plane(ASVLOFFSCREEN* asvl, int plane_idx);
ASVL_API void get_expected_plane_states(MUInt32 fmt, int expected_states[4]);

// creating ASVLOFFSCREEN
ASVL_API ASVLOFFSCREEN* create_asvl(MUInt32 fmt, MSize y_size, bool create_plane_buffers = true);
ASVL_API ASVLOFFSCREEN* create_asvl_header(MUInt32 fmt, MSize y_size);
ASVL_API void destroy_asvl(ASVLOFFSCREEN* asvl);

template<int uIdx>
ASVL_API ASVLOFFSCREEN* create_yuv420sp(MSize size);
ASVL_API ASVLOFFSCREEN* create_nv21(MSize size);
ASVL_API ASVLOFFSCREEN* create_nv12(MSize size);

ASVL_API ASVLOFFSCREEN* create_gray(MSize size);

template<int bIdx = 2>
ASVL_API ASVLOFFSCREEN* create_rgb(MSize size);
ASVL_API ASVLOFFSCREEN* create_bgr(MSize size);

template<int bIdx = 2>
ASVL_API ASVLOFFSCREEN* create_rgba(MSize size);
ASVL_API ASVLOFFSCREEN* create_bgra(MSize size);

// loading ASVLOFFSCREEN
ASVL_API ASVLOFFSCREEN* load_asvl(const std::string& image_path, MUInt32 fmt);
ASVL_API ASVLOFFSCREEN* load_asvl(const char* image_path, MUInt32 fmt);

ASVL_API ASVLOFFSCREEN* load_nv21(const std::string& image_path);
ASVL_API ASVLOFFSCREEN* load_nv21(const char* image_path);
ASVL_API ASVLOFFSCREEN* load_nv12(const std::string& image_path);
ASVL_API ASVLOFFSCREEN* load_nv12(const char* image_path);

template<int bIdx = 2>
ASVL_API ASVLOFFSCREEN* load_rgb(const std::string& image_path);
ASVL_API ASVLOFFSCREEN* load_rgb(const char* image_path);
ASVL_API ASVLOFFSCREEN* load_rgb(const std::string& image_path);

template<int bIdx = 2>
ASVL_API ASVLOFFSCREEN* load_rgba(const std::string& image_path);
ASVL_API ASVLOFFSCREEN* load_rgba(const char* image_path);
ASVL_API ASVLOFFSCREEN* load_rgba(const std::string& image_path);

// saving ASVLOFFSCREEN
ASVL_API void save_asvl(const std::string& dir, const std::string& prefix, ASVLOFFSCREEN* asvl);
ASVL_API void save_asvl(const char* dir, const char* prefix, ASVLOFFSCREEN* asvl);

// validating ASVLOFFSCREEN
ASVL_API bool validate_asvl_header(ASVLOFFSCREEN* asvl);
ASVL_API bool validate_asvl(ASVLOFFSCREEN* asvl);

ASVL_API bool are_planes_continous(ASVLOFFSCREEN* asvl);

ASVL_API void dump_meta(ASVLOFFSCREEN* asvl, const char* msg = nullptr);
ASVL_API void dump_meta(ASVLOFFSCREEN* asvl, const std::string& msg);

ASVL_API bool almost_equal(ASVLOFFSCREEN* expected, ASVLOFFSCREEN* actual, double eps = 1e-6, bool check_pitch_equality = false, bool check_planes_memory_continuity = false);

// The proxy/wrapper for ASVLOFFSCREEN
class RichyImage
{
public:
    Plane planes[4];
    ASVLOFFSCREEN* asvl;

public:
    RichyImage(ASVLOFFSCREEN* _asvl):
        asvl(_asvl)
    {
        for (int pi = 0; pi < 4; pi++)
        {
            planes[pi] = get_plane(asvl, pi);
        }
    }
    int bufsize() const
    {
        int sz = 0;
        for (int pi = 0; pi < 4; pi++)
        {
            sz += planes[pi].bufsize();
        }
        return sz;
    }

    void assign_buffer(uint8_t* buf)
    {
        for (int pi = 0; pi < 4; pi++)
        {
            if (planes[pi].bufsize() == 0)
            {
                asvl->ppu8Plane[pi] = NULL;
                planes[pi].set_data(NULL);
                break;
            }
            else
            {
                asvl->ppu8Plane[pi] = buf;
                planes[pi].set_data(buf);
                buf += planes[pi].bufsize();
            }
        }
    }

    void canonicalize_pitch()
    {
        for (int pi = 0; pi < 4; pi++)
        {
            Plane& plane = planes[pi];
            plane.set_pitch(plane.channels * plane.width);
            asvl->pi32Pitch[pi] = plane.channels * plane.width;
        }
    }

    int number_of_planes() const
    {
        int cnt = 0;
        for (int pi = 0; pi < 4; pi++)
        {
            if (planes[pi].bufsize() == 0)
            {
                break;
            }
            cnt++;
        }
        return cnt;
    }
};

} // namespace asvl




//================================================================================
// Implementations
//================================================================================

namespace {

using namespace asvl;

class StringUtil
{
public:
    /// @brief split a string with specified delimeter string
    /// @param str the string to be splited
    /// @param delim the delimeter string
    /// @return the splited result
    static std::vector<std::string> split(const std::string& str, const std::string& delim)
    {
        std::vector<std::string> tokens;
        size_t prev = 0, pos = 0;
        do
        {
            pos = str.find(delim, prev);
            if (pos == std::string::npos) pos = str.length();
            std::string token = str.substr(prev, pos-prev);
            if (!token.empty()) tokens.push_back(token);
            prev = pos + delim.length();
        }
        while (pos < str.length() && prev < str.length());
        return tokens;
    }
};

class PathUtil
{
public:
    static std::string basename(const std::string& path)
    {
        int slash_pos = path.find_last_of('/');
        return path.substr(slash_pos + 1);
    }
    static std::string dirname(const std::string& path)
    {
        int slash_pos = path.find_last_of('/');
        return path.substr(0, slash_pos);
    }
    static std::string sep()
    {
        return "/";
    }
    static std::vector<std::string> split(const std::string& path)
    {
        return StringUtil::split(path, PathUtil::sep());
    }
    static std::string join(const std::string& pathbase, const std::string& pathpart)
    {
        return pathbase + PathUtil::sep() + pathpart;
    }
    static std::string head(const std::string& path)
    {
        std::string basename = PathUtil::basename(path);
        std::vector<std::string> vs = StringUtil::split(basename, ".");
        return vs[0];
    }
    static std::string ext(const std::string& path)
    {
        std::string basename = PathUtil::basename(path);
        std::vector<std::string> vs = StringUtil::split(basename, ".");
        return vs[1];
    }
};

class AsvlImagePathInfo
{
public:
    // format: [dirname][name_prefix_]WxH.ext
    std::string path;
    std::string dirname;
    std::string basename; // [name_prefix_]WxH.ext
    std::string name_head; // [name_prefix_]WxH
    std::string name_prefix; // if empty, then basename is WxH.ext
    std::string ext;
    int width;
    int height;
public:
    AsvlImagePathInfo(const std::string& _path):
        path(_path)
    {
        // TODO: 验证文件路径合法性
        basename = PathUtil::basename(path);
        dirname = PathUtil::dirname(path);
        name_head = PathUtil::head(basename);
        ext = PathUtil::ext(basename);

        // TODO: 验证 split 结果正确性
        std::vector<std::string> vs1 = StringUtil::split(name_head, "_");
        name_prefix = name_head.substr(0, name_head.find_last_of('_'));
        std::vector<std::string> vs2 = StringUtil::split(vs1[vs1.size()-1], "x");
        width = std::stoi(vs2[0]);
        height = std::stoi(vs2[1]);

        ASVL_LOGD("path: %s\n", path.c_str());
        ASVL_LOGD("basename: %s\n", basename.c_str());
        ASVL_LOGD("dirname: %s\n", dirname.c_str());
        ASVL_LOGD("name_head: %s\n", name_head.c_str());
        ASVL_LOGD("name_prefix: %s\n", name_prefix.c_str());
        ASVL_LOGD("ext: %s\n", ext.c_str());
        ASVL_LOGD("width: %d\n", width);
        ASVL_LOGD("height: %d\n", height);
    }
    AsvlImagePathInfo(const std::string& dir, const std::string& _name_prefix, ASVLOFFSCREEN* asvl)
    {
        dirname = dir;
        name_prefix = _name_prefix;
        MSize size = get_size(asvl);
        width = size.width;
        height = size.height;

        // Checking name prefix. Only alphanum or _ is permitted
        bool name_prefix_valid = true;
        for (int i = 0; i < name_prefix.length(); i++)
        {
            if (!(isalnum(name_prefix[i]) || name_prefix[i] == '_'))
            {
                name_prefix_valid = false;
                ASVL_LOGE("invalid name_prefix");
                abort(); // ?
            }
        }

        name_head = "";
        if (name_prefix.length()!=0)
        {
            name_head += name_prefix + "_";
        }
        name_head += std::to_string(width) + "x" + std::to_string(height);

        ext = get_ext(asvl->u32PixelArrayFormat);

        basename = name_head + "." + ext;

        path = PathUtil::join(dirname, basename);
    }
};


} // namespace

// ASVL_PAF_ 宏转字符串
std::unordered_map<MUInt32, std::string> asvl::get_fmt_table()
{
    static std::unordered_map<MUInt32, std::string> fmt_table =
    {
        { ASVL_PAF_RGB16_B5G6R5, "ASVL_PAF_RGB16_B5G6R5" },
        { ASVL_PAF_RGB16_B5G5R5, "ASVL_PAF_RGB16_B5G5R5" },
        { ASVL_PAF_RGB16_B4G4R4, "ASVL_PAF_RGB16_B4G4R4" },
        { ASVL_PAF_RGB16_B5G5R5T, "ASVL_PAF_RGB16_B5G5R5T" },
        { ASVL_PAF_RGB16_R5G6B5, "ASVL_PAF_RGB16_R5G6B5" },
        { ASVL_PAF_RGB16_R5G5B5, "ASVL_PAF_RGB16_R5G5B5" },
        { ASVL_PAF_RGB16_R4G4B4, "ASVL_PAF_RGB16_R4G4B4" },
        { ASVL_PAF_RGB24_B8G8R8, "ASVL_PAF_RGB24_B8G8R8" },
        { ASVL_PAF_RGB24_B6G6R6, "ASVL_PAF_RGB24_B6G6R6" },
        { ASVL_PAF_RGB24_B6G6R6T, "ASVL_PAF_RGB24_B6G6R6T" },
        { ASVL_PAF_RGB24_R8G8B8, "ASVL_PAF_RGB24_R8G8B8" },
        { ASVL_PAF_RGB24_R6G6B6, "ASVL_PAF_RGB24_R6G6B6" },
        { ASVL_PAF_RGB32_B8G8R8, "ASVL_PAF_RGB32_B8G8R8" },
        { ASVL_PAF_RGB32_B8G8R8A8, "ASVL_PAF_RGB32_B8G8R8A8" },
        { ASVL_PAF_RGB32_R8G8B8, "ASVL_PAF_RGB32_R8G8B8" },
        { ASVL_PAF_RGB32_A8R8G8B8, "ASVL_PAF_RGB32_A8R8G8B8" },
        { ASVL_PAF_RGB32_R8G8B8A8, "ASVL_PAF_RGB32_R8G8B8A8" },
        { ASVL_PAF_YUV, "ASVL_PAF_YUV" },
        { ASVL_PAF_YVU, "ASVL_PAF_YVU" },
        { ASVL_PAF_UVY, "ASVL_PAF_UVY" },
        { ASVL_PAF_VUY, "ASVL_PAF_VUY" },
        { ASVL_PAF_YUYV, "ASVL_PAF_YUYV" },
        { ASVL_PAF_YVYU, "ASVL_PAF_YVYU" },
        { ASVL_PAF_UYVY, "ASVL_PAF_UYVY" },
        { ASVL_PAF_VYUY, "ASVL_PAF_VYUY" },
        { ASVL_PAF_YUYV2, "ASVL_PAF_YUYV2" },
        { ASVL_PAF_YVYU2, "ASVL_PAF_YVYU2" },
        { ASVL_PAF_UYVY2, "ASVL_PAF_UYVY2" },
        { ASVL_PAF_VYUY2, "ASVL_PAF_VYUY2" },
        { ASVL_PAF_YYUV, "ASVL_PAF_YYUV" },
        { ASVL_PAF_I420, "ASVL_PAF_I420" },
        { ASVL_PAF_I422V, "ASVL_PAF_I422V" },
        { ASVL_PAF_I422H, "ASVL_PAF_I422H" },
        { ASVL_PAF_I444, "ASVL_PAF_I444" },
        { ASVL_PAF_YV12, "ASVL_PAF_YV12" },
        { ASVL_PAF_YV16V, "ASVL_PAF_YV16V" },
        { ASVL_PAF_YV16H, "ASVL_PAF_YV16H" },
        { ASVL_PAF_YV24, "ASVL_PAF_YV24" },
        { ASVL_PAF_GRAY, "ASVL_PAF_GRAY" },
        { ASVL_PAF_NV12, "ASVL_PAF_NV12" },
        { ASVL_PAF_NV21, "ASVL_PAF_NV21" },
        { ASVL_PAF_LPI422H, "ASVL_PAF_LPI422H" },
        { ASVL_PAF_LPI422H2, "ASVL_PAF_LPI422H2" },
        { ASVL_PAF_NV41, "ASVL_PAF_NV41" },
        { ASVL_PAF_NEG_UYVY, "ASVL_PAF_NEG_UYVY" },
        { ASVL_PAF_NEG_I420, "ASVL_PAF_NEG_I420" },
        { ASVL_PAF_MONO_UYVY, "ASVL_PAF_MONO_UYVY" },
        { ASVL_PAF_MONO_I420, "ASVL_PAF_MONO_I420" },
        { ASVL_PAF_P8_YUYV, "ASVL_PAF_P8_YUYV" },
        { ASVL_PAF_SP16UNIT, "ASVL_PAF_SP16UNIT" },
        { ASVL_PAF_DEPTH_U16, "ASVL_PAF_DEPTH_U16" },
        { ASVL_PAF_DEPTH8_U16_MSB, "ASVL_PAF_DEPTH8_U16_MSB" },
        { ASVL_PAF_DEPTH8_U16_LSB, "ASVL_PAF_DEPTH8_U16_LSB" },
        { ASVL_PAF_DEPTH10_U16_MSB, "ASVL_PAF_DEPTH10_U16_MSB" },
        { ASVL_PAF_DEPTH10_U16_LSB, "ASVL_PAF_DEPTH10_U16_LSB" },
        { ASVL_PAF_DEPTH12_U16_MSB, "ASVL_PAF_DEPTH12_U16_MSB" },
        { ASVL_PAF_DEPTH12_U16_LSB, "ASVL_PAF_DEPTH12_U16_LSB" },
        { ASVL_PAF_DEPTH14_U16_MSB, "ASVL_PAF_DEPTH14_U16_MSB" },
        { ASVL_PAF_DEPTH14_U16_LSB, "ASVL_PAF_DEPTH14_U16_LSB" },
        { ASVL_PAF_DEPTH16_U16, "ASVL_PAF_DEPTH16_U16" },
        { ASVL_PAF_DEPTH9_U16_MSB, "ASVL_PAF_DEPTH9_U16_MSB" },
        { ASVL_PAF_DEPTH9_U16_LSB, "ASVL_PAF_DEPTH9_U16_LSB" },
        { ASVL_PAF_DEPTH11_U16_MSB, "ASVL_PAF_DEPTH11_U16_MSB" },
        { ASVL_PAF_DEPTH11_U16_LSB, "ASVL_PAF_DEPTH11_U16_LSB" },
        { ASVL_PAF_DEPTH13_U16_MSB, "ASVL_PAF_DEPTH13_U16_MSB" },
        { ASVL_PAF_DEPTH13_U16_LSB, "ASVL_PAF_DEPTH13_U16_LSB" },
        { ASVL_PAF_DEPTH15_U16_MSB, "ASVL_PAF_DEPTH15_U16_MSB" },
        { ASVL_PAF_DEPTH15_U16_LSB, "ASVL_PAF_DEPTH15_U16_LSB" },
        { ASVL_PAF_RAW10_RGGB_10B, "ASVL_PAF_RAW10_RGGB_10B" },
        { ASVL_PAF_RAW10_GRBG_10B, "ASVL_PAF_RAW10_GRBG_10B" },
        { ASVL_PAF_RAW10_GBRG_10B, "ASVL_PAF_RAW10_GBRG_10B" },
        { ASVL_PAF_RAW10_BGGR_10B, "ASVL_PAF_RAW10_BGGR_10B" },
        { ASVL_PAF_RAW12_RGGB_12B, "ASVL_PAF_RAW12_RGGB_12B" },
        { ASVL_PAF_RAW12_GRBG_12B, "ASVL_PAF_RAW12_GRBG_12B" },
        { ASVL_PAF_RAW12_GBRG_12B, "ASVL_PAF_RAW12_GBRG_12B" },
        { ASVL_PAF_RAW12_BGGR_12B, "ASVL_PAF_RAW12_BGGR_12B" },
        { ASVL_PAF_RAW10_RGGB_16B, "ASVL_PAF_RAW10_RGGB_16B" },
        { ASVL_PAF_RAW10_GRBG_16B, "ASVL_PAF_RAW10_GRBG_16B" },
        { ASVL_PAF_RAW10_GBRG_16B, "ASVL_PAF_RAW10_GBRG_16B" },
        { ASVL_PAF_RAW10_BGGR_16B, "ASVL_PAF_RAW10_BGGR_16B" },
        { ASVL_PAF_RAW12_RGGB_16B, "ASVL_PAF_RAW12_RGGB_16B" },
        { ASVL_PAF_RAW12_GRBG_16B, "ASVL_PAF_RAW12_GRBG_16B" },
        { ASVL_PAF_RAW12_GBRG_16B, "ASVL_PAF_RAW12_GBRG_16B" },
        { ASVL_PAF_RAW12_BGGR_16B, "ASVL_PAF_RAW12_BGGR_16B" },
        { ASVL_PAF_RAW16_RGGB_16B, "ASVL_PAF_RAW16_RGGB_16B" },
        { ASVL_PAF_RAW16_GRBG_16B, "ASVL_PAF_RAW16_GRBG_16B" },
        { ASVL_PAF_RAW16_GBRG_16B, "ASVL_PAF_RAW16_GBRG_16B" },
        { ASVL_PAF_RAW16_BGGR_16B, "ASVL_PAF_RAW16_BGGR_16B" },
        { ASVL_PAF_RAW14_RGGB_14B, "ASVL_PAF_RAW14_RGGB_14B" },
        { ASVL_PAF_RAW14_GRBG_14B, "ASVL_PAF_RAW14_GRBG_14B" },
        { ASVL_PAF_RAW14_GBRG_14B, "ASVL_PAF_RAW14_GBRG_14B" },
        { ASVL_PAF_RAW14_BGGR_14B, "ASVL_PAF_RAW14_BGGR_14B" },
        { ASVL_PAF_RAW14_RGGB_16B, "ASVL_PAF_RAW14_RGGB_16B" },
        { ASVL_PAF_RAW14_GRBG_16B, "ASVL_PAF_RAW14_GRBG_16B" },
        { ASVL_PAF_RAW14_GBRG_16B, "ASVL_PAF_RAW14_GBRG_16B" },
        { ASVL_PAF_RAW14_BGGR_16B, "ASVL_PAF_RAW14_BGGR_16B" },
        { ASVL_PAF_RAW10_RGGB_16B_MSB, "ASVL_PAF_RAW10_RGGB_16B_MSB" },
        { ASVL_PAF_RAW10_GRBG_16B_MSB, "ASVL_PAF_RAW10_GRBG_16B_MSB" },
        { ASVL_PAF_RAW10_GBRG_16B_MSB, "ASVL_PAF_RAW10_GBRG_16B_MSB" },
        { ASVL_PAF_RAW10_BGGR_16B_MSB, "ASVL_PAF_RAW10_BGGR_16B_MSB" },
        { ASVL_PAF_RAW12_RGGB_16B_MSB, "ASVL_PAF_RAW12_RGGB_16B_MSB" },
        { ASVL_PAF_RAW12_GRBG_16B_MSB, "ASVL_PAF_RAW12_GRBG_16B_MSB" },
        { ASVL_PAF_RAW12_GBRG_16B_MSB, "ASVL_PAF_RAW12_GBRG_16B_MSB" },
        { ASVL_PAF_RAW12_BGGR_16B_MSB, "ASVL_PAF_RAW12_BGGR_16B_MSB" },
        { ASVL_PAF_RAW14_RGGB_16B_MSB, "ASVL_PAF_RAW14_RGGB_16B_MSB" },
        { ASVL_PAF_RAW14_GRBG_16B_MSB, "ASVL_PAF_RAW14_GRBG_16B_MSB" },
        { ASVL_PAF_RAW14_GBRG_16B_MSB, "ASVL_PAF_RAW14_GBRG_16B_MSB" },
        { ASVL_PAF_RAW14_BGGR_16B_MSB, "ASVL_PAF_RAW14_BGGR_16B_MSB" },
        { ASVL_PAF_RAW10_RGGB_16B_LSB, "ASVL_PAF_RAW10_RGGB_16B_LSB" },
        { ASVL_PAF_RAW10_GRBG_16B_LSB, "ASVL_PAF_RAW10_GRBG_16B_LSB" },
        { ASVL_PAF_RAW10_GBRG_16B_LSB, "ASVL_PAF_RAW10_GBRG_16B_LSB" },
        { ASVL_PAF_RAW10_BGGR_16B_LSB, "ASVL_PAF_RAW10_BGGR_16B_LSB" },
        { ASVL_PAF_RAW12_RGGB_16B_LSB, "ASVL_PAF_RAW12_RGGB_16B_LSB" },
        { ASVL_PAF_RAW12_GRBG_16B_LSB, "ASVL_PAF_RAW12_GRBG_16B_LSB" },
        { ASVL_PAF_RAW12_GBRG_16B_LSB, "ASVL_PAF_RAW12_GBRG_16B_LSB" },
        { ASVL_PAF_RAW12_BGGR_16B_LSB, "ASVL_PAF_RAW12_BGGR_16B_LSB" },
        { ASVL_PAF_RAW14_RGGB_16B_LSB, "ASVL_PAF_RAW14_RGGB_16B_LSB" },
        { ASVL_PAF_RAW14_GRBG_16B_LSB, "ASVL_PAF_RAW14_GRBG_16B_LSB" },
        { ASVL_PAF_RAW14_GBRG_16B_LSB, "ASVL_PAF_RAW14_GBRG_16B_LSB" },
        { ASVL_PAF_RAW14_BGGR_16B_LSB, "ASVL_PAF_RAW14_BGGR_16B_LSB" },
        { ASVL_PAF_RAW8_RGGB_8B, "ASVL_PAF_RAW8_RGGB_8B" },
        { ASVL_PAF_RAW8_GRBG_8B, "ASVL_PAF_RAW8_GRBG_8B" },
        { ASVL_PAF_RAW8_GBRG_8B, "ASVL_PAF_RAW8_GBRG_8B" },
        { ASVL_PAF_RAW8_BGGR_8B, "ASVL_PAF_RAW8_BGGR_8B" },
        { ASVL_PAF_RAW8_RGGB_16B_LSB, "ASVL_PAF_RAW8_RGGB_16B_LSB" },
        { ASVL_PAF_RAW8_GRBG_16B_LSB, "ASVL_PAF_RAW8_GRBG_16B_LSB" },
        { ASVL_PAF_RAW8_GBRG_16B_LSB, "ASVL_PAF_RAW8_GBRG_16B_LSB" },
        { ASVL_PAF_RAW8_BGGR_16B_LSB, "ASVL_PAF_RAW8_BGGR_16B_LSB" },
        { ASVL_PAF_RAW8_RGGB_16B_MSB, "ASVL_PAF_RAW8_RGGB_16B_MSB" },
        { ASVL_PAF_RAW8_GRBG_16B_MSB, "ASVL_PAF_RAW8_GRBG_16B_MSB" },
        { ASVL_PAF_RAW8_GBRG_16B_MSB, "ASVL_PAF_RAW8_GBRG_16B_MSB" },
        { ASVL_PAF_RAW8_BGGR_16B_MSB, "ASVL_PAF_RAW8_BGGR_16B_MSB" },
        { ASVL_PAF_RAW10_GRAY_10B, "ASVL_PAF_RAW10_GRAY_10B" },
        { ASVL_PAF_RAW12_GRAY_12B, "ASVL_PAF_RAW12_GRAY_12B" },
        { ASVL_PAF_RAW14_GRAY_14B, "ASVL_PAF_RAW14_GRAY_14B" },
        { ASVL_PAF_RAW16_GRAY_16B, "ASVL_PAF_RAW16_GRAY_16B" },
        { ASVL_PAF_RAW10_GRAY_16B, "ASVL_PAF_RAW10_GRAY_16B" },
        { ASVL_PAF_RAW10_GRAY_16B_MSB, "ASVL_PAF_RAW10_GRAY_16B_MSB" },
        { ASVL_PAF_RAW10_GRAY_16B_LSB, "ASVL_PAF_RAW10_GRAY_16B_LSB" },
        { ASVL_PAF_RAW11_GRAY_16B, "ASVL_PAF_RAW11_GRAY_16B" },
        { ASVL_PAF_RAW11_GRAY_16B_MSB, "ASVL_PAF_RAW11_GRAY_16B_MSB" },
        { ASVL_PAF_RAW11_GRAY_16B_LSB, "ASVL_PAF_RAW11_GRAY_16B_LSB" },
        { ASVL_PAF_RAW12_GRAY_16B, "ASVL_PAF_RAW12_GRAY_16B" },
        { ASVL_PAF_RAW12_GRAY_16B_MSB, "ASVL_PAF_RAW12_GRAY_16B_MSB" },
        { ASVL_PAF_RAW12_GRAY_16B_LSB, "ASVL_PAF_RAW12_GRAY_16B_LSB" },
        { ASVL_PAF_RAW13_GRAY_16B, "ASVL_PAF_RAW13_GRAY_16B" },
        { ASVL_PAF_RAW13_GRAY_16B_MSB, "ASVL_PAF_RAW13_GRAY_16B_MSB" },
        { ASVL_PAF_RAW13_GRAY_16B_LSB, "ASVL_PAF_RAW13_GRAY_16B_LSB" },
        { ASVL_PAF_RAW14_GRAY_16B, "ASVL_PAF_RAW14_GRAY_16B" },
        { ASVL_PAF_RAW14_GRAY_16B_MSB, "ASVL_PAF_RAW14_GRAY_16B_MSB" },
        { ASVL_PAF_RAW14_GRAY_16B_LSB, "ASVL_PAF_RAW14_GRAY_16B_LSB" },
        { ASVL_PAF_RAW15_GRAY_16B, "ASVL_PAF_RAW15_GRAY_16B" },
        { ASVL_PAF_RAW15_GRAY_16B_MSB, "ASVL_PAF_RAW15_GRAY_16B_MSB" },
        { ASVL_PAF_RAW15_GRAY_16B_LSB, "ASVL_PAF_RAW15_GRAY_16B_LSB" },
        { ASVL_PAF_P010_MSB, "ASVL_PAF_P010_MSB" },
        { ASVL_PAF_P010_LSB, "ASVL_PAF_P010_LSB" },
        { ASVL_PAF_P012_MSB, "ASVL_PAF_P012_MSB" },
        { ASVL_PAF_P012_LSB, "ASVL_PAF_P012_LSB" },
        { ASVL_PAF_P014_MSB, "ASVL_PAF_P014_MSB" },
        { ASVL_PAF_P014_LSB, "ASVL_PAF_P014_LSB" },
        { ASVL_PAF_NV21_TP10, "ASVL_PAF_NV21_TP10" },
        { ASVL_PAF_NV12_TP10, "ASVL_PAF_NV12_TP10" },
        { ASVL_PAF_UBWC_TP10, "ASVL_PAF_UBWC_TP10" },
        { ASVL_PAF_UBWC_NV12, "ASVL_PAF_UBWC_NV12" },
        { ASVL_PAF_QUADRAW8_RGGB_8B, "ASVL_PAF_QUADRAW8_RGGB_8B" },
        { ASVL_PAF_QUADRAW8_GRBG_8B, "ASVL_PAF_QUADRAW8_GRBG_8B" },
        { ASVL_PAF_QUADRAW8_GBRG_8B, "ASVL_PAF_QUADRAW8_GBRG_8B" },
        { ASVL_PAF_QUADRAW8_BGGR_8B, "ASVL_PAF_QUADRAW8_BGGR_8B" },
        { ASVL_PAF_QUADRAW8_RGGB_16B_LSB, "ASVL_PAF_QUADRAW8_RGGB_16B_LSB" },
        { ASVL_PAF_QUADRAW8_GRBG_16B_LSB, "ASVL_PAF_QUADRAW8_GRBG_16B_LSB" },
        { ASVL_PAF_QUADRAW8_GBRG_16B_LSB, "ASVL_PAF_QUADRAW8_GBRG_16B_LSB" },
        { ASVL_PAF_QUADRAW8_BGGR_16B_LSB, "ASVL_PAF_QUADRAW8_BGGR_16B_LSB" },
        { ASVL_PAF_QUADRAW8_RGGB_16B_MSB, "ASVL_PAF_QUADRAW8_RGGB_16B_MSB" },
        { ASVL_PAF_QUADRAW8_GRBG_16B_MSB, "ASVL_PAF_QUADRAW8_GRBG_16B_MSB" },
        { ASVL_PAF_QUADRAW8_GBRG_16B_MSB, "ASVL_PAF_QUADRAW8_GBRG_16B_MSB" },
        { ASVL_PAF_QUADRAW8_BGGR_16B_MSB, "ASVL_PAF_QUADRAW8_BGGR_16B_MSB" },
        { ASVL_PAF_QUADRAW10_RGGB_10B, "ASVL_PAF_QUADRAW10_RGGB_10B" },
        { ASVL_PAF_QUADRAW10_GRBG_10B, "ASVL_PAF_QUADRAW10_GRBG_10B" },
        { ASVL_PAF_QUADRAW10_GBRG_10B, "ASVL_PAF_QUADRAW10_GBRG_10B" },
        { ASVL_PAF_QUADRAW10_BGGR_10B, "ASVL_PAF_QUADRAW10_BGGR_10B" },
        { ASVL_PAF_QUADRAW10_RGGB_16B_LSB, "ASVL_PAF_QUADRAW10_RGGB_16B_LSB" },
        { ASVL_PAF_QUADRAW10_GRBG_16B_LSB, "ASVL_PAF_QUADRAW10_GRBG_16B_LSB" },
        { ASVL_PAF_QUADRAW10_GBRG_16B_LSB, "ASVL_PAF_QUADRAW10_GBRG_16B_LSB" },
        { ASVL_PAF_QUADRAW10_BGGR_16B_LSB, "ASVL_PAF_QUADRAW10_BGGR_16B_LSB" },
        { ASVL_PAF_QUADRAW10_RGGB_16B_MSB, "ASVL_PAF_QUADRAW10_RGGB_16B_MSB" },
        { ASVL_PAF_QUADRAW10_GRBG_16B_MSB, "ASVL_PAF_QUADRAW10_GRBG_16B_MSB" },
        { ASVL_PAF_QUADRAW10_GBRG_16B_MSB, "ASVL_PAF_QUADRAW10_GBRG_16B_MSB" },
        { ASVL_PAF_QUADRAW10_BGGR_16B_MSB, "ASVL_PAF_QUADRAW10_BGGR_16B_MSB" },
        { ASVL_PAF_QUADRAW12_RGGB_12B, "ASVL_PAF_QUADRAW12_RGGB_12B" },
        { ASVL_PAF_QUADRAW12_GRBG_12B, "ASVL_PAF_QUADRAW12_GRBG_12B" },
        { ASVL_PAF_QUADRAW12_GBRG_12B, "ASVL_PAF_QUADRAW12_GBRG_12B" },
        { ASVL_PAF_QUADRAW12_BGGR_12B, "ASVL_PAF_QUADRAW12_BGGR_12B" },
        { ASVL_PAF_QUADRAW12_RGGB_16B_LSB, "ASVL_PAF_QUADRAW12_RGGB_16B_LSB" },
        { ASVL_PAF_QUADRAW12_GRBG_16B_LSB, "ASVL_PAF_QUADRAW12_GRBG_16B_LSB" },
        { ASVL_PAF_QUADRAW12_GBRG_16B_LSB, "ASVL_PAF_QUADRAW12_GBRG_16B_LSB" },
        { ASVL_PAF_QUADRAW12_BGGR_16B_LSB, "ASVL_PAF_QUADRAW12_BGGR_16B_LSB" },
        { ASVL_PAF_QUADRAW12_RGGB_16B_MSB, "ASVL_PAF_QUADRAW12_RGGB_16B_MSB" },
        { ASVL_PAF_QUADRAW12_GRBG_16B_MSB, "ASVL_PAF_QUADRAW12_GRBG_16B_MSB" },
        { ASVL_PAF_QUADRAW12_GBRG_16B_MSB, "ASVL_PAF_QUADRAW12_GBRG_16B_MSB" },
        { ASVL_PAF_QUADRAW12_BGGR_16B_MSB, "ASVL_PAF_QUADRAW12_BGGR_16B_MSB" },
        { ASVL_PAF_QUADRAW14_RGGB_14B, "ASVL_PAF_QUADRAW14_RGGB_14B" },
        { ASVL_PAF_QUADRAW14_GRBG_14B, "ASVL_PAF_QUADRAW14_GRBG_14B" },
        { ASVL_PAF_QUADRAW14_GBRG_14B, "ASVL_PAF_QUADRAW14_GBRG_14B" },
        { ASVL_PAF_QUADRAW14_BGGR_14B, "ASVL_PAF_QUADRAW14_BGGR_14B" },
        { ASVL_PAF_QUADRAW14_RGGB_16B_LSB, "ASVL_PAF_QUADRAW14_RGGB_16B_LSB" },
        { ASVL_PAF_QUADRAW14_GRBG_16B_LSB, "ASVL_PAF_QUADRAW14_GRBG_16B_LSB" },
        { ASVL_PAF_QUADRAW14_GBRG_16B_LSB, "ASVL_PAF_QUADRAW14_GBRG_16B_LSB" },
        { ASVL_PAF_QUADRAW14_BGGR_16B_LSB, "ASVL_PAF_QUADRAW14_BGGR_16B_LSB" },
        { ASVL_PAF_QUADRAW14_RGGB_16B_MSB, "ASVL_PAF_QUADRAW14_RGGB_16B_MSB" },
        { ASVL_PAF_QUADRAW14_GRBG_16B_MSB, "ASVL_PAF_QUADRAW14_GRBG_16B_MSB" },
        { ASVL_PAF_QUADRAW14_GBRG_16B_MSB, "ASVL_PAF_QUADRAW14_GBRG_16B_MSB" },
        { ASVL_PAF_QUADRAW14_BGGR_16B_MSB, "ASVL_PAF_QUADRAW14_BGGR_16B_MSB" },
        { ASVL_PAF_QUADRAW16_RGGB_16B, "ASVL_PAF_QUADRAW16_RGGB_16B" },
        { ASVL_PAF_QUADRAW16_GRBG_16B, "ASVL_PAF_QUADRAW16_GRBG_16B" },
        { ASVL_PAF_QUADRAW16_GBRG_16B, "ASVL_PAF_QUADRAW16_GBRG_16B" },
        { ASVL_PAF_QUADRAW16_BGGR_16B, "ASVL_PAF_QUADRAW16_BGGR_16B" },
        { ASVL_PAF_RGB_B8G8R8_48B_LSB, "ASVL_PAF_RGB_B8G8R8_48B_LSB" },
        { ASVL_PAF_RGB_B8G8R8_48B_MSB, "ASVL_PAF_RGB_B8G8R8_48B_MSB" },
        { ASVL_PAF_RGB_B10G10R10_30B, "ASVL_PAF_RGB_B10G10R10_30B" },
        { ASVL_PAF_RGB_B10G10R10_48B_LSB, "ASVL_PAF_RGB_B10G10R10_48B_LSB" },
        { ASVL_PAF_RGB_B10G10R10_48B_MSB, "ASVL_PAF_RGB_B10G10R10_48B_MSB" },
        { ASVL_PAF_RGB_B12G12R12_36B, "ASVL_PAF_RGB_B12G12R12_36B" },
        { ASVL_PAF_RGB_B12G12R12_48B_LSB, "ASVL_PAF_RGB_B12G12R12_48B_LSB" },
        { ASVL_PAF_RGB_B12G12R12_48B_MSB, "ASVL_PAF_RGB_B12G12R12_48B_MSB" },
        { ASVL_PAF_RGB_B14G14R14_42B, "ASVL_PAF_RGB_B14G14R14_42B" },
        { ASVL_PAF_RGB_B14G14R14_48B_LSB, "ASVL_PAF_RGB_B14G14R14_48B_LSB" },
        { ASVL_PAF_RGB_B14G14R14_48B_MSB, "ASVL_PAF_RGB_B14G14R14_48B_MSB" },
        { ASVL_PAF_RGB_B16G16R16_48B, "ASVL_PAF_RGB_B16G16R16_48B" },
        { ASVL_PAF_RGB_R8G8B8_48B_LSB, "ASVL_PAF_RGB_R8G8B8_48B_LSB" },
        { ASVL_PAF_RGB_R8G8B8_48B_MSB, "ASVL_PAF_RGB_R8G8B8_48B_MSB" },
        { ASVL_PAF_RGB_R10G10B10_30B, "ASVL_PAF_RGB_R10G10B10_30B" },
        { ASVL_PAF_RGB_R10G10B10_48B_LSB, "ASVL_PAF_RGB_R10G10B10_48B_LSB" },
        { ASVL_PAF_RGB_R10G10B10_48B_MSB, "ASVL_PAF_RGB_R10G10B10_48B_MSB" },
        { ASVL_PAF_RGB_R12G12B12_36B, "ASVL_PAF_RGB_R12G12B12_36B" },
        { ASVL_PAF_RGB_R12G12B12_48B_LSB, "ASVL_PAF_RGB_R12G12B12_48B_LSB" },
        { ASVL_PAF_RGB_R12G12B12_48B_MSB, "ASVL_PAF_RGB_R12G12B12_48B_MSB" },
        { ASVL_PAF_RGB_R14G14B14_42B, "ASVL_PAF_RGB_R14G14B14_42B" },
        { ASVL_PAF_RGB_R14G14B14_48B_LSB, "ASVL_PAF_RGB_R14G14B14_48B_LSB" },
        { ASVL_PAF_RGB_R14G14B14_48B_MSB, "ASVL_PAF_RGB_R14G14B14_48B_MSB" },
        { ASVL_PAF_RGB_R16G16B16_48B, "ASVL_PAF_RGB_R16G16B16_48B" },
        // { ASVL_PAF_RAW10_MSC3x3_16B_LSB, "ASVL_PAF_RAW10_MSC3x3_16B_LSB" },
        // { ASVL_PAF_RAW10_MSC3x3_16B_MSB, "ASVL_PAF_RAW10_MSC3x3_16B_MSB" },
        // { ASVL_PAF_RAW10_MSC3x3_10B, "ASVL_PAF_RAW10_MSC3x3_10B" },
        // { ASVL_PAF_RAW12_MSC3x3_16B_LSB, "ASVL_PAF_RAW12_MSC3x3_16B_LSB" },
        // { ASVL_PAF_RAW12_MSC3x3_16B_MSB, "ASVL_PAF_RAW12_MSC3x3_16B_MSB" },
        // { ASVL_PAF_RAW12_MSC3x3_12B, "ASVL_PAF_RAW12_MSC3x3_12B" },
        // { ASVL_PAF_RAW14_MSC3x3_16B_LSB, "ASVL_PAF_RAW14_MSC3x3_16B_LSB" },
        // { ASVL_PAF_RAW14_MSC3x3_16B_MSB, "ASVL_PAF_RAW14_MSC3x3_16B_MSB" },
        // { ASVL_PAF_RAW14_MSC3x3_14B, "ASVL_PAF_RAW14_MSC3x3_14B" },
    };
    return fmt_table;
}

std::string asvl::get_fmt_str(MUInt32 fmt)
{
    std::unordered_map<MUInt32, std::string> fmt_table = get_fmt_table();
    if (fmt_table.count(fmt))
    {
        return fmt_table[fmt];
    }
    else
    {
        return "unknown";
    }
}

ASVLOFFSCREEN* asvl::create_asvl(MUInt32 fmt, MSize y_size, bool create_plane_buffers)
{
    auto fmt_table = get_fmt_table();
    if (!fmt_table.count(fmt))
    {
        ASVL_LOGE("not supported fmt: %d", fmt);
        return NULL;
    }

    ASVLOFFSCREEN* asvl = (ASVLOFFSCREEN*)malloc(sizeof(ASVLOFFSCREEN));
    if (asvl == NULL)
    {
        ASVL_LOGE("failed to allocate memory");
        abort();
    }
    asvl->i32Height = y_size.height;
    asvl->i32Width = y_size.width;
    asvl->u32PixelArrayFormat = fmt;
    asvl->pi32Pitch[0] = asvl->pi32Pitch[1] = asvl->pi32Pitch[2] = asvl->pi32Pitch[3] = 0;

    // reset pitch to canonical case
    RichyImage image(asvl);
    image.canonicalize_pitch();

    asvl->ppu8Plane[0] = nullptr;
    asvl->ppu8Plane[1] = nullptr;
    asvl->ppu8Plane[2] = nullptr;
    asvl->ppu8Plane[3] = nullptr;


    // NOTE: create plane buffers rely on plane info, should be put after asvl metadata assigning.
    if (create_plane_buffers)
    {
        uint8_t* buf = (uint8_t*)malloc(image.bufsize());
        asvl->ppu8Plane[0] = buf;
        image.assign_buffer(buf);
    }

    return asvl;
}

ASVLOFFSCREEN* asvl::create_asvl_header(MUInt32 fmt, MSize y_size)
{
    return create_asvl(fmt, y_size, false);
}

template<>
ASVLOFFSCREEN* asvl::create_yuv420sp<0>(MSize size)
{
    return create_asvl(ASVL_PAF_NV12, size);
}

template<>
ASVLOFFSCREEN* asvl::create_yuv420sp<1>(MSize size)
{
    return create_asvl(ASVL_PAF_NV21, size);
}

ASVLOFFSCREEN* asvl::create_nv21(MSize size)
{
    return create_asvl(ASVL_PAF_NV21, size);
}

ASVLOFFSCREEN* asvl::create_nv12(MSize size)
{
    return create_asvl(ASVL_PAF_NV12, size);
}

ASVLOFFSCREEN* asvl::load_nv21(const std::string& image_path)
{
    return load_asvl(image_path, ASVL_PAF_NV21);
}

ASVLOFFSCREEN* asvl::load_nv12(const std::string& image_path)
{
    return load_asvl(image_path, ASVL_PAF_NV12);
}

template<int bIdx>
ASVLOFFSCREEN* asvl::create_rgb(MSize size)
{
    if (bIdx == 0)
    {
        return create_asvl(ASVL_PAF_RGB24_B8G8R8, size);
    }
    else if (bIdx == 2)
    {
        return create_asvl(ASVL_PAF_RGB24_R8G8B8, size);
    }
    else
    {
        ASVL_LOGE("invalid bIdx");
        return nullptr;
    }
}

ASVLOFFSCREEN* asvl::create_bgr(MSize size)
{
    return create_asvl(ASVL_PAF_RGB24_B8G8R8, size);
}

ASVLOFFSCREEN* asvl::create_bgra(MSize size)
{
    const int bIdx = 0;
    return create_rgba<bIdx>(size);
}

template<int bIdx>
ASVLOFFSCREEN* asvl::load_rgb(const std::string& image_path)
{
    if (bIdx == 0)
    {
        return load_asvl(image_path, ASVL_PAF_RGB24_B8G8R8);
    }
    else if (bIdx == 2) {
        return load_asvl(image_path, ASVL_PAF_RGB24_R8G8B8);
    }
    else {
        ASVL_LOGE("bIdx invalid");
        return NULL;
    }
}

template<int bIdx>
ASVLOFFSCREEN* asvl::load_rgba(const std::string& image_path)
{
    if (bIdx == 0)
    {
        return load_asvl(image_path, ASVL_PAF_RGB32_B8G8R8A8);
    }
    else if (bIdx == 2)
    {
        return load_asvl(image_path, ASVL_PAF_RGB32_R8G8B8A8);
    }
    else
    {
        ASVL_LOGE("bIdx invalid");
        return NULL;
    }
}

template<int bIdx>
ASVLOFFSCREEN* asvl::create_rgba(MSize size)
{
    if (bIdx == 0)
    {
        return create_asvl(ASVL_PAF_RGB32_B8G8R8A8, size);
    }
    else if (bIdx == 2)
    {
        return create_asvl(ASVL_PAF_RGB32_R8G8B8A8, size);
    }
    else
    {
        ASVL_LOGE("invalid bIdx");
        return nullptr;
    }
}

ASVLOFFSCREEN* asvl::load_rgb(const std::string& image_path)
{
    return load_asvl(image_path, ASVL_PAF_RGB24_R8G8B8);
}

ASVLOFFSCREEN* asvl::load_rgba(const std::string& image_path)
{
    return load_asvl(image_path, ASVL_PAF_RGB32_R8G8B8A8);
}

ASVLOFFSCREEN* asvl::create_gray(MSize size)
{
    return create_asvl(ASVL_PAF_GRAY, size);
}

void asvl::get_expected_plane_states(MUInt32 fmt, int states[4])
{
    memset(states, 0, sizeof(int)*4);
    switch (fmt)
    {
    case ASVL_PAF_RGB24_R8G8B8:
    case ASVL_PAF_RGB24_B8G8R8:
    case ASVL_PAF_RGB32_B8G8R8A8:
    case ASVL_PAF_RGB32_R8G8B8A8:
    case ASVL_PAF_GRAY:
        states[0] = 1;
        break;
    case ASVL_PAF_NV21:
    case ASVL_PAF_NV12:
        states[0] = 1;
        states[1] = 1;
        break;
    default:
        ASVL_LOGE("un-handled format: %s\n", get_fmt_str(fmt).c_str());
    }
}

bool asvl::validate_asvl_header(ASVLOFFSCREEN* asvl)
{
    // dimension checkings for all types
    if (asvl->i32Height < 0 || asvl->i32Width < 0)
    {
        return false;
    }
    if (asvl->i32Height * asvl->i32Width < 0)
    {
        return false;
    }

    // planes checking
    Plane planes[4] =
    {
        get_plane(asvl, 0),
        get_plane(asvl, 1),
        get_plane(asvl, 2),
        get_plane(asvl, 3)
    };
    int state[4] =
    {
        planes[0].data == nullptr ? 0 : 1,
        planes[1].data == nullptr ? 0 : 1,
        planes[2].data == nullptr ? 0 : 1,
        planes[3].data == nullptr ? 0 : 1
    };

    MUInt32 fmt = asvl->u32PixelArrayFormat;
    int expected_states[4];
    get_expected_plane_states(fmt, expected_states);
    for (int pi = 0; pi < 4; pi++)
    {
        if (expected_states[pi] != state[pi])
        {
            return false;
        }
    }

    // planes contents checking
    for (int pi = 0; pi < 4; pi++)
    {
        Plane plane = get_plane(asvl, pi);
        if (plane.data == nullptr) continue;

        if (plane.pitch < plane.width * plane.channels)
            return false;
    }
    return true;
}

bool asvl::validate_asvl(ASVLOFFSCREEN* asvl)
{
    if (!validate_asvl_header(asvl))
    {
        return false;
    }

    // planes contents checking
    for (int pi = 0; pi < 4; pi++)
    {
        Plane plane = get_plane(asvl, pi);
        if (plane.data == nullptr) continue;

        if (plane.pitch < plane.width * plane.channels)
            return false;

        // check data. If crash then the provided asvl is buggy.
        // TODO: 能否在 C++ 代码的运行时， 判断内存是否合法？ 感觉做不到。。
        double sum = 0;
        for (int i = 0; i < plane.height; i++)
        {
            uint8_t* line = plane.data + i * plane.pitch;
            for (int j = 0; j < plane.width; j++)
            {
                for (int k = 0; k < plane.channels; k++)
                {
                    sum += line[j * plane.channels + k];
                }
            }
        }
        ASVL_LOGD("check data: sum = %lf\n", sum);
    }
    return true;
}

// 打印 ASVLOFFSCREEN 元信息
void asvl::dump_meta(ASVLOFFSCREEN* asvl, const char* msg)
{
    int w = asvl->i32Width;
    int h = asvl->i32Height;

    const char* tag = msg;
    if (msg == nullptr)
    {
        tag = "asvl";
    }

    int fmt = asvl->u32PixelArrayFormat;
    std::string fmt_str = get_fmt_str(fmt);

    ASVL_LOGD("%s: w=%d, h=%d, fmt=%d(0x%x, %s), ", tag, w, h, fmt, fmt, fmt_str.c_str());

    RichyImage rich_image(asvl);

    if (fmt == ASVL_PAF_NV21 || fmt == ASVL_PAF_NV12 || fmt == ASVL_PAF_I420 || fmt == ASVL_PAF_UYVY || fmt == ASVL_PAF_I444)
    {
        const int num_planes = rich_image.number_of_planes();
        for (int pi = 0; pi < num_planes; pi++) {
            ASVL_LOGD("pitch[%d]=%d, ", pi, asvl->pi32Pitch[pi]);
        }
        for (int pi = 0; pi < num_planes; pi++) {
            ASVL_LOGD("plane[%d]=%p, ", pi, asvl->ppu8Plane[pi]);
        }

        if (are_planes_continous(asvl)) {
            ASVL_LOGD("(continous plane buffer: YES)");
        } else {
            ASVL_LOGD("(continous plane buffer: NO)");
        }
        ASVL_LOGD("\n");
    }
    else if (fmt == ASVL_PAF_RGB24_B8G8R8 || fmt == ASVL_PAF_RGB24_R8G8B8 ||
            fmt == ASVL_PAF_RGB32_B8G8R8A8 || fmt == ASVL_PAF_RGB32_R8G8B8A8)
    {
        ASVL_LOGD("pitch[0]=%d\n", asvl->pi32Pitch[0]);
    }
    else {
        ASVL_LOGE("not supported format code: %d\n", fmt);
    }
}

// 释放 asvl::create() 创建的 ASVLOFFSCREEN*
void asvl::destroy_asvl(ASVLOFFSCREEN* asvl)
{
    if (asvl)
    {
        // 内存是否连续的检查， 不连续时的释放
        Plane planes[4];
        for (int i = 0; i < 4; i++)
        {
            planes[i] = get_plane(asvl, i);
        }

        // if (asvl->ppu8Plane[0])
        // {
        //     uint8_t* ptr[4];
        //     int cnt = 0;
        //     if (asvl->ppu8Plane[0])
        //     {
        //         ptr[cnt++] = asvl->ppu8Plane[0];
        //     }
        //     for (int i = 1; i < 4; i++)
        //     {
        //         uint8_t* sp = asvl->ppu8Plane[i];
        //         if (sp)
        //         {
        //             int offset = planes[i - 1].height * planes[i - 1].pitch;
        //             if (ptr[cnt - 1] + offset != sp)
        //             {
        //                 ptr[cnt++] = sp;
        //             }
        //         }
        //     }
        //     for (int i = 0; i < cnt; i++)
        //     {
        //         free(ptr[i]);
        //     }
        // }
        // TODO: 上面一段代码有问题。计划用 plane 获取偏移，重新实现。
        free(asvl->ppu8Plane[0]);

        free(asvl);
    }
}

// 判断 plane 之间是否连续
bool asvl::are_planes_continous(ASVLOFFSCREEN* asvl)
{
    RichyImage image(asvl);
    const int num_planes = image.number_of_planes();
    for (int i = 1; i < num_planes; i++)
    {
        if (image.planes[i].data != image.planes[i-1].data + image.planes[i-1].bufsize())
        {
            return false;
        }
    }
    return true;
}

ASVLOFFSCREEN* asvl::load_asvl(const std::string& image_path, MUInt32 fmt)
{
    AsvlImagePathInfo path_info(image_path);
    MSize size;
    size.set_width(path_info.width)
        .set_height(path_info.height);
    ASVLOFFSCREEN* asvl = create_asvl(fmt, size);

#if 0
    FILE* fin = fopen(image_path.c_str(), "rb");

    const int y_buf_sz = size.width * size.height;
    fread(asvl->ppu8Plane[0], y_buf_sz, 1, fin);

    const int uv_buf_sz = size.width * size.height / 2;
    fread(asvl->ppu8Plane[1], uv_buf_sz, 1, fin);

    fclose(fin);

#else

    std::fstream fin(image_path, std::ios::in | std::ios::binary);
    if (fin.is_open())
    {
        // read binary contents for each plane
        for (int i = 0; i < 4; i++)
        {
            if (asvl->ppu8Plane[i])
            {
                Plane plane = get_plane(asvl, i);
                fin.read(reinterpret_cast<char*>(asvl->ppu8Plane[i]), plane.bufsize());
            }
        }
    }
    else
    {
        ASVL_LOGE("failed to open %s", image_path.c_str());
    }
#endif

    return asvl;
}

ASVLOFFSCREEN* asvl::load_asvl(const char* image_path, MUInt32 fmt)
{
    if (image_path)
        return load_asvl(std::string(image_path), fmt);
    return NULL;
}

asvl::Plane asvl::get_plane(ASVLOFFSCREEN* asvl, int plane_idx)
{
    if (plane_idx < 0 || plane_idx > 3)
    {
        ASVL_LOGE("invalid plane_idx");
        abort();
    }
    // NOTE: 这里不能调用 validate_asvl(), 会产生递归

    Plane info;
    unsigned fmt = asvl->u32PixelArrayFormat;

    if (fmt == ASVL_PAF_RGB24_B8G8R8 || fmt == ASVL_PAF_RGB24_R8G8B8)
    {
        if (plane_idx == 0)
        {
            info.set_width(asvl->i32Width)
                .set_height(asvl->i32Height)
                .set_channels(3)
                .set_pitch(asvl->pi32Pitch[0])
                .set_data(asvl->ppu8Plane[0]);
        }
    }
    else if (fmt == ASVL_PAF_GRAY)
    {
        if (plane_idx == 0)
        {
            info.set_height(asvl->i32Height)
                .set_width(asvl->i32Width)
                .set_channels(1)
                .set_pitch(asvl->pi32Pitch[0])
                .set_data(asvl->ppu8Plane[0]);
        }
    }
    else if (fmt == ASVL_PAF_RGB32_B8G8R8A8 || fmt == ASVL_PAF_RGB32_R8G8B8A8)
    {
        if (plane_idx == 0)
        {
            info.set_height(asvl->i32Height)
                .set_width(asvl->i32Width)
                .set_channels(4)
                .set_pitch(asvl->pi32Pitch[0])
                .set_data(asvl->ppu8Plane[0]);
        }
    }
    else if (fmt == ASVL_PAF_NV21 || fmt == ASVL_PAF_NV12)
    {
        if (plane_idx == 0)
        {
            info.set_height(asvl->i32Height)
                .set_width(asvl->i32Width)
                .set_channels(1)
                .set_pitch(asvl->pi32Pitch[0])
                .set_data(asvl->ppu8Plane[0]);
        }
        else if (plane_idx == 1)
        {
            info.set_height(asvl->i32Height / 2)
                .set_width(asvl->i32Width / 2)
                .set_channels(2)
                .set_pitch(asvl->pi32Pitch[1])
                .set_data(asvl->ppu8Plane[1]);
        }
    }
    else if (fmt == ASVL_PAF_I420)
    {
        if (plane_idx == 0)
        {
            info.set_height(asvl->i32Height)
                .set_width(asvl->i32Width)
                .set_channels(1)
                .set_pitch(asvl->pi32Pitch[0])
                .set_data(asvl->ppu8Plane[0]);
        }
        else if (plane_idx == 1)
        {
            info.set_height(asvl->i32Height / 2)
                .set_width(asvl->i32Width / 2)
                .set_channels(1)
                .set_pitch(asvl->pi32Pitch[1])
                .set_data(asvl->ppu8Plane[1]);
        }
        else if (plane_idx == 2)
        {
            info.set_height(asvl->i32Height / 2)
                .set_width(asvl->i32Width / 2)
                .set_channels(1)
                .set_pitch(asvl->pi32Pitch[2])
                .set_data(asvl->ppu8Plane[2]);
        }
    }
    else if (fmt == ASVL_PAF_UYVY)
    {
        if (plane_idx == 0)
        {
            info.set_height(asvl->i32Height)
                .set_width(asvl->i32Width)
                .set_channels(2)
                .set_pitch(asvl->pi32Pitch[0])
                .set_data(asvl->ppu8Plane[0]);
        }
    }
    else if (fmt == ASVL_PAF_I444)
    {
        if (plane_idx == 0 || plane_idx == 1 || plane_idx == 2)
        {
            info.set_height(asvl->i32Height)
                .set_width(asvl->i32Width)
                .set_channels(1)
                .set_pitch(asvl->pi32Pitch[plane_idx])
                .set_data(asvl->ppu8Plane[plane_idx]);
        }
    }
    else
    {
        ASVL_LOGE("un-handled format: %s", get_fmt_str(fmt).c_str());
    }

    return info;
}

MSize asvl::get_size(ASVLOFFSCREEN* asvl)
{
    MSize size;
    size.set_width(asvl->i32Width).set_height(asvl->i32Height);
    return size;
}

void asvl::save_asvl(const std::string& dir, const std::string& name_prefix, ASVLOFFSCREEN* asvl)
{
    AsvlImagePathInfo path_info(dir, name_prefix, asvl);
    std::string save_path = path_info.path;
    std::fstream fout;
    fout.open(save_path, std::ios::out | std::ios::binary);

    for (int i = 0; i < 4; i++)
    {
        Plane plane = get_plane(asvl, i);
        if (plane.data)
            fout.write(reinterpret_cast<char*>(plane.data), plane.bufsize());
    }
}

void asvl::save_asvl(const char* dir, const char* name_prefix, ASVLOFFSCREEN* asvl)
{
    std::string dir_str;
    if (dir != NULL)
        dir_str = dir;

    std::string name_prefix_str;
    if (name_prefix != NULL)
        name_prefix_str = name_prefix;

    save_asvl(dir_str, name_prefix_str, asvl);
}

ASVL_API std::string asvl::get_ext(MUInt32 fmt)
{
    std::string ext;
    switch (fmt)
    {
    case ASVL_PAF_NV12:
        ext = "NV12"; break;
    case ASVL_PAF_NV21:
        ext = "NV21"; break;
    case ASVL_PAF_I420:
        ext = "I420"; break;
    case ASVL_PAF_UYVY:
        ext = "UYVY"; break;
    case ASVL_PAF_RGB24_B8G8R8:
        ext = "BGR24"; break;
    case ASVL_PAF_RGB24_R8G8B8:
        ext = "RGB24"; break;
    case ASVL_PAF_RGB32_B8G8R8A8:
        ext = "BGRA32"; break;
    case ASVL_PAF_RGB32_R8G8B8A8:
        ext = "RGBA32"; break;
    case ASVL_PAF_I444:
        ext = "I444"; break;
    default:
        ext = "known";
        ASVL_LOGE("un-handled format: %s", get_fmt_str(fmt).c_str());
    }
    return ext;
}

MUInt32 asvl::get_fmt(ASVLOFFSCREEN* asvl)
{
    return asvl->u32PixelArrayFormat;
}

MUInt32 asvl::get_fmt_from_ext(const std::string& ext)
{
    std::unordered_map<std::string, MUInt32> inverse_fmt_table =
    {
        {"NV21", ASVL_PAF_NV21},
        {"NV12", ASVL_PAF_NV12},
        {"RGB24", ASVL_PAF_RGB24_R8G8B8},
        {"BGR24", ASVL_PAF_RGB24_B8G8R8},
        {"RGB32", ASVL_PAF_RGB32_R8G8B8A8},
        {"BGR32", ASVL_PAF_RGB32_B8G8R8A8}
    };
    std::string upper_ext = ext;
    for (int i = 0; i < ext.size(); i++)
    {
        upper_ext[i] = toupper(ext[i]);
    }

    if (inverse_fmt_table.count(upper_ext))
    {
        return inverse_fmt_table[upper_ext];
    }
    else
    {
        ASVL_LOGE("not handled format ext: %s", ext.c_str());
        return ASVL_PAF_UNKNOWN;
    }
}

bool asvl::almost_equal(ASVLOFFSCREEN* expected, ASVLOFFSCREEN* actual, double eps, bool check_pitch_equality, bool check_planes_memory_continuity)
{
    MSize expected_size = get_size(expected);
    MSize actual_size = get_size(actual);
    if (expected_size != actual_size)
    {
        ASVL_LOGD("size not equal");
        return false;
    }
    MUInt32 expected_fmt = get_fmt(expected);
    MUInt32 actual_fmt = get_fmt(actual);
    if (expected_fmt != actual_fmt)
    {
        ASVL_LOGD("format not equal");
        return false;
    }
    // compare the continous memory property
    if (check_planes_memory_continuity)
    {
        bool expected_equality = are_planes_continous(expected);
        bool actual_equality = are_planes_continous(actual);
        if (expected_equality != actual_equality)
        {
            return false;
        }
    }
    for (int pi = 0; pi < 4; pi++)
    {
        Plane expected_plane = get_plane(expected, pi);
        Plane actual_plane = get_plane(actual, pi);
        if (expected_plane.width != actual_plane.width)
        {
            ASVL_LOGD("plane[%d]'s width not equal: %d, %d\n", pi, expected_plane.width, actual_plane.width);
            return false;
        }

        if (expected_plane.height != actual_plane.height)
        {
            ASVL_LOGD("plane[%d]'s height not equal: %d, %d\n", pi, expected_plane.height, actual_plane.height);
            return false;
        }

        if (check_pitch_equality && (expected_plane.pitch != actual_plane.pitch))
        {
            ASVL_LOGD("plane[%d]'s pitch not equal: %d, %d", pi, expected_plane.pitch, actual_plane.pitch);
            return false;
        }

        // compare pixel contents
        const int plane_height = expected_plane.height;
        const int plane_width = expected_plane.width;
        const int plane_channels = expected_plane.channels;
        for (int i = 0; i < plane_height; i++)
        {
            uint8_t* expected_line = expected_plane.data + i * expected_plane.pitch;
            uint8_t* actual_line = actual_plane.data + i * actual_plane.pitch;
            for (int j = 0; j < plane_width; j++)
            {
                for (int k = 0; k < plane_channels; k++)
                {
                    const int idx = j * plane_channels + k;
                    int abs_diff = (int)expected_line[idx] - (int)actual_line[idx];
                    if ( (double)abs_diff > eps )
                    {
                        ASVL_LOGD("not equal in plane%d, (expected: %d, actual: %d): %d, %d (absdiff=%d)\n", pi, i, j, (int)expected_line[idx], (int)actual_line[idx], abs_diff);
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
