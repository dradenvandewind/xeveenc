/*
 * Copyright (c) 2023, Your Name
 * Contact: your-email@example.com
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef __GST_XEVE_ENC_H__
#define __GST_XEVE_ENC_H__

#include <gst/gst.h>
#include <gst/video/video.h>
#include <gst/video/gstvideoencoder.h>
#include <xeve.h>

G_BEGIN_DECLS

#define GST_TYPE_XEVE_ENC            (gst_xeve_enc_get_type())
#define GST_XEVE_ENC(obj)            (G_TYPE_CHECK_INSTANCE_CAST((obj), GST_TYPE_XEVE_ENC, GstXeveEnc))
#define GST_XEVE_ENC_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST((klass), GST_TYPE_XEVE_ENC, GstXeveEncClass))
#define GST_IS_XEVE_ENC(obj)         (G_TYPE_CHECK_INSTANCE_TYPE((obj), GST_TYPE_XEVE_ENC))
#define GST_IS_XEVE_ENC_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), GST_TYPE_XEVE_ENC))
#define GST_XEVE_ENC_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS((obj), GST_TYPE_XEVE_ENC, GstXeveEncClass))

typedef struct _GstXeveEnc GstXeveEnc;
typedef struct _GstXeveEncClass GstXeveEncClass;

/**
 * GstXeveEnc:
 * @parent: Parent GstVideoEncoder object
 * @xeve_handle: XEVE encoder instance handle
 * @xeve_param: XEVE encoding parameters
 * @xeve_cdsc: XEVE encoder description
 * @bitrate: Target bitrate in kbps
 * @qp: Quantization Parameter (0 = auto)
 * @profile: Encoding profile (0=baseline, 1=main)
 * @preset: Encoding preset (0=default, 1=fast, 2=medium, 3=slow, 4=placebo)
 * @tune: Tuning mode (0=none, 1=zerolatency, 2=psnr)
 * @closed_gop: Use closed GOP structure
 * @keyint_max: Maximum GOP size
 * @annexb: Use Annex-B format
 * 
 * XEVE video encoder element.
 */
struct _GstXeveEnc {
  GstVideoEncoder parent;
  
  /*< private >*/
  XEVE xeve_handle;
  XEVE_PARAM xeve_param;
  XEVE_CDSC xeve_cdsc;

  /* Properties */
  gint bitrate;
  gint qp;
  gint profile;
  gint preset;
  gint tune;
  gboolean closed_gop;
  gint keyint_max;
  gboolean annexb;

  /* Internal state */
  gboolean encoder_initialized;
  GstVideoCodecState *input_state;
};

struct _GstXeveEncClass {
  GstVideoEncoderClass parent_class;
};

GType gst_xeve_enc_get_type(void);

G_END_DECLS

#endif /* __GST_XEVE_ENC_H__ */