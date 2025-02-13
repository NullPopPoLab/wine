/*
 * winegstreamer Unix library interface
 *
 * Copyright 2020-2021 Zebediah Figura for CodeWeavers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef __WINE_WINEGSTREAMER_UNIXLIB_H
#define __WINE_WINEGSTREAMER_UNIXLIB_H

#include <stdbool.h>
#include <stdint.h>
#include "windef.h"
#include "winternl.h"
#include "wtypes.h"
#include "mmreg.h"

#include "wine/unixlib.h"

struct wg_format
{
    enum wg_major_type
    {
        WG_MAJOR_TYPE_UNKNOWN,
        WG_MAJOR_TYPE_VIDEO,
        WG_MAJOR_TYPE_AUDIO,
        WG_MAJOR_TYPE_WMA,
    } major_type;

    union
    {
        struct
        {
            enum wg_video_format
            {
                WG_VIDEO_FORMAT_UNKNOWN,

                WG_VIDEO_FORMAT_BGRA,
                WG_VIDEO_FORMAT_BGRx,
                WG_VIDEO_FORMAT_BGR,
                WG_VIDEO_FORMAT_RGB15,
                WG_VIDEO_FORMAT_RGB16,

                WG_VIDEO_FORMAT_AYUV,
                WG_VIDEO_FORMAT_I420,
                WG_VIDEO_FORMAT_NV12,
                WG_VIDEO_FORMAT_UYVY,
                WG_VIDEO_FORMAT_YUY2,
                WG_VIDEO_FORMAT_YV12,
                WG_VIDEO_FORMAT_YVYU,

                WG_VIDEO_FORMAT_CINEPAK,
            } format;
            int32_t width, height;
            uint32_t fps_n, fps_d;
        } video;
        struct
        {
            enum wg_audio_format
            {
                WG_AUDIO_FORMAT_UNKNOWN,

                WG_AUDIO_FORMAT_U8,
                WG_AUDIO_FORMAT_S16LE,
                WG_AUDIO_FORMAT_S24LE,
                WG_AUDIO_FORMAT_S32LE,
                WG_AUDIO_FORMAT_F32LE,
                WG_AUDIO_FORMAT_F64LE,

                WG_AUDIO_FORMAT_MPEG1_LAYER1,
                WG_AUDIO_FORMAT_MPEG1_LAYER2,
                WG_AUDIO_FORMAT_MPEG1_LAYER3,
            } format;

            uint32_t channels;
            uint32_t channel_mask; /* In WinMM format. */
            uint32_t rate;
        } audio;
        struct
        {
            uint32_t version;
            uint32_t bitrate;
            uint32_t rate;
            uint32_t depth;
            uint32_t channels;
            uint32_t block_align;
            uint32_t codec_data_len;
            unsigned char codec_data[64];
        } wma;
    } u;
};

enum wg_parser_event_type
{
    WG_PARSER_EVENT_NONE = 0,
    WG_PARSER_EVENT_BUFFER,
    WG_PARSER_EVENT_EOS,
    WG_PARSER_EVENT_SEGMENT,
};

struct wg_parser_event
{
    enum wg_parser_event_type type;
    union
    {
        struct
        {
            /* pts and duration are in 100-nanosecond units. */
            ULONGLONG pts, duration;
            uint32_t size;
            bool discontinuity, preroll, delta, has_pts, has_duration;
        } buffer;
        struct
        {
            ULONGLONG position, stop;
            DOUBLE rate;
        } segment;
    } u;
};
C_ASSERT(sizeof(struct wg_parser_event) == 40);

enum wg_parser_type
{
    WG_PARSER_DECODEBIN,
    WG_PARSER_AVIDEMUX,
    WG_PARSER_MPEGAUDIOPARSE,
    WG_PARSER_WAVPARSE,
};

struct wg_parser_create_params
{
    struct wg_parser *parser;
    enum wg_parser_type type;
    bool unlimited_buffering;
};

struct wg_parser_connect_params
{
    struct wg_parser *parser;
    UINT64 file_size;
};

struct wg_parser_get_next_read_offset_params
{
    struct wg_parser *parser;
    UINT32 size;
    UINT64 offset;
};

struct wg_parser_push_data_params
{
    struct wg_parser *parser;
    const void *data;
    UINT32 size;
};

struct wg_parser_get_stream_count_params
{
    struct wg_parser *parser;
    UINT32 count;
};

struct wg_parser_get_stream_params
{
    struct wg_parser *parser;
    UINT32 index;
    struct wg_parser_stream *stream;
};

struct wg_parser_stream_get_preferred_format_params
{
    struct wg_parser_stream *stream;
    struct wg_format *format;
};

struct wg_parser_stream_enable_params
{
    struct wg_parser_stream *stream;
    const struct wg_format *format;
};

struct wg_parser_stream_get_event_params
{
    struct wg_parser_stream *stream;
    struct wg_parser_event *event;
};

struct wg_parser_stream_copy_buffer_params
{
    struct wg_parser_stream *stream;
    void *data;
    UINT32 offset;
    UINT32 size;
};

struct wg_parser_stream_notify_qos_params
{
    struct wg_parser_stream *stream;
    bool underflow;
    DOUBLE proportion;
    INT64 diff;
    UINT64 timestamp;
};

struct wg_parser_stream_get_duration_params
{
    struct wg_parser_stream *stream;
    UINT64 duration;
};

struct wg_parser_stream_seek_params
{
    struct wg_parser_stream *stream;
    DOUBLE rate;
    UINT64 start_pos, stop_pos;
    DWORD start_flags, stop_flags;
};

struct wg_transform_create_params
{
    struct wg_transform *transform;
    const struct wg_format *input_format;
    const struct wg_format *output_format;
};

enum unix_funcs
{
    unix_wg_parser_create,
    unix_wg_parser_destroy,

    unix_wg_parser_connect,
    unix_wg_parser_disconnect,

    unix_wg_parser_begin_flush,
    unix_wg_parser_end_flush,

    unix_wg_parser_get_next_read_offset,
    unix_wg_parser_push_data,

    unix_wg_parser_get_stream_count,
    unix_wg_parser_get_stream,

    unix_wg_parser_stream_get_preferred_format,
    unix_wg_parser_stream_enable,
    unix_wg_parser_stream_disable,

    unix_wg_parser_stream_get_event,
    unix_wg_parser_stream_copy_buffer,
    unix_wg_parser_stream_release_buffer,
    unix_wg_parser_stream_notify_qos,

    unix_wg_parser_stream_get_duration,
    unix_wg_parser_stream_seek,

    unix_wg_transform_create,
    unix_wg_transform_destroy,
};

#endif /* __WINE_WINEGSTREAMER_UNIXLIB_H */
