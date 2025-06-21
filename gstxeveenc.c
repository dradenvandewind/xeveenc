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
#define PACKAGE "gstxeve"
#define VERSION "1.0.0"

// #ifdef HAVE_CONFIG_H
// #include "config.h"
// #endif

#include "gstxeveenc.h"
#include <string.h>

GST_DEBUG_CATEGORY_STATIC(gst_xeve_enc_debug);
#define GST_CAT_DEFAULT gst_xeve_enc_debug

/* Properties */
enum {
  PROP_0,
  PROP_BITRATE,
  PROP_QP,
  PROP_PROFILE,
  PROP_PRESET,
  PROP_TUNE,
  PROP_CLOSED_GOP,
  PROP_KEYINT_MAX,
  PROP_ANNEXB,
};

/* Capabilities */
static GstStaticPadTemplate sink_template = GST_STATIC_PAD_TEMPLATE(
    "sink",
    GST_PAD_SINK,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS(
        "video/x-raw, "
        "format = (string) { I420, NV12, YV12 }, "
        "width = (int) [ 16, 8192 ], "
        "height = (int) [ 16, 4320 ], "
        "framerate = (fraction) [ 0/1, 300/1 ]"
    )
);

static GstStaticPadTemplate src_template = GST_STATIC_PAD_TEMPLATE(
    "src",
    GST_PAD_SRC,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS(
        "video/x-xeve, "
        "width = (int) [ 16, 8192 ], "
        "height = (int) [ 16, 4320 ], "
        "framerate = (fraction) [ 0/1, 300/1 ], "
        "stream-format = (string) byte-stream, "
        "alignment = (string) au"
    )
);

/* Class initialization */
G_DEFINE_TYPE(GstXeveEnc, gst_xeve_enc, GST_TYPE_VIDEO_ENCODER);

static void gst_xeve_enc_set_property(GObject *object, guint prop_id,
                                     const GValue *value, GParamSpec *pspec);
static void gst_xeve_enc_get_property(GObject *object, guint prop_id,
                                     GValue *value, GParamSpec *pspec);
static gboolean gst_xeve_enc_start(GstVideoEncoder *encoder);
static gboolean gst_xeve_enc_stop(GstVideoEncoder *encoder);
static gboolean gst_xeve_enc_set_format(GstVideoEncoder *encoder,
                                       GstVideoCodecState *state);
static GstFlowReturn gst_xeve_enc_handle_frame(GstVideoEncoder *encoder,
                                              GstVideoCodecFrame *frame);

/* Initialize the plugin's class */
static void
gst_xeve_enc_class_init(GstXeveEncClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
  GstVideoEncoderClass *video_encoder_class = GST_VIDEO_ENCODER_CLASS(klass);
  GstElementClass *element_class = GST_ELEMENT_CLASS(klass);

  GST_DEBUG_CATEGORY_INIT(gst_xeve_enc_debug, "xeveenc", 0, "XEVE Encoder");

  gobject_class->set_property = gst_xeve_enc_set_property;
  gobject_class->get_property = gst_xeve_enc_get_property;

  /* Register properties */
  g_object_class_install_property(
      gobject_class, PROP_BITRATE,
      g_param_spec_int("bitrate", "Bitrate", "Target bitrate in kbps",
                       1, 200000, 2000, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property(
      gobject_class, PROP_QP,
      g_param_spec_int("qp", "QP", "Quantization Parameter (0 = auto)",
                       0, 51, 0, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property(
      gobject_class, PROP_PROFILE,
      g_param_spec_int("profile", "Profile", "Encoding profile (0=baseline, 1=main)",
                       0, 1, 0, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property(
      gobject_class, PROP_PRESET,
      g_param_spec_int("preset", "Preset", "Encoding speed/quality trade-off",
                       0, 4, 2, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property(
      gobject_class, PROP_TUNE,
      g_param_spec_int("tune", "Tune", "Special tuning (0=none, 1=zerolatency, 2=psnr)",
                       0, 2, 0, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property(
      gobject_class, PROP_CLOSED_GOP,
      g_param_spec_boolean("closed-gop", "Closed GOP", "Use closed GOP structure",
                           FALSE, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property(
      gobject_class, PROP_KEYINT_MAX,
      g_param_spec_int("keyint-max", "Keyframe Interval", "Maximum GOP size",
                       0, 1000, 250, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property(
      gobject_class, PROP_ANNEXB,
      g_param_spec_boolean("annexb", "Annex-B", "Use Annex-B format",
                           TRUE, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  /* Set pad templates */
  gst_element_class_add_static_pad_template(element_class, &sink_template);
  gst_element_class_add_static_pad_template(element_class, &src_template);

  gst_element_class_set_static_metadata(
      element_class,
      "XEVE Video Encoder",
      "Codec/Encoder/Video",
      "Encode video streams using XEVE",
      "Your Name <your-email@example.com>");

  /* VideoEncoder callbacks */
  video_encoder_class->start = gst_xeve_enc_start;
  video_encoder_class->stop = gst_xeve_enc_stop;
  video_encoder_class->set_format = gst_xeve_enc_set_format;
  video_encoder_class->handle_frame = gst_xeve_enc_handle_frame;
}

/* Initialize the new element */
static void
gst_xeve_enc_init(GstXeveEnc *self)
{
  /* Default values */
  self->bitrate = 2000;
  self->qp = 0;
  self->profile = XEVE_PROFILE_BASELINE;
  self->preset = XEVE_PRESET_MEDIUM;
  self->tune = XEVE_TUNE_NONE;
  self->closed_gop = FALSE;
  self->keyint_max = 250;
  self->annexb = TRUE;
  self->xeve_handle = NULL;

  /* Initialize XEVE params */
  xeve_param_default(&self->xeve_param);
}

/* Property setters/getters */
static void
gst_xeve_enc_set_property(GObject *object, guint prop_id,
                          const GValue *value, GParamSpec *pspec)
{
  GstXeveEnc *self = GST_XEVE_ENC(object);

  switch (prop_id) {
    case PROP_BITRATE:
      self->bitrate = g_value_get_int(value);
      break;
    case PROP_QP:
      self->qp = g_value_get_int(value);
      break;
    case PROP_PROFILE:
      self->profile = g_value_get_int(value);
      break;
    case PROP_PRESET:
      self->preset = g_value_get_int(value);
      break;
    case PROP_TUNE:
      self->tune = g_value_get_int(value);
      break;
    case PROP_CLOSED_GOP:
      self->closed_gop = g_value_get_boolean(value);
      break;
    case PROP_KEYINT_MAX:
      self->keyint_max = g_value_get_int(value);
      break;
    case PROP_ANNEXB:
      self->annexb = g_value_get_boolean(value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
      break;
  }
}

static void
gst_xeve_enc_get_property(GObject *object, guint prop_id,
                          GValue *value, GParamSpec *pspec)
{
  GstXeveEnc *self = GST_XEVE_ENC(object);

  switch (prop_id) {
    case PROP_BITRATE:
      g_value_set_int(value, self->bitrate);
      break;
    case PROP_QP:
      g_value_set_int(value, self->qp);
      break;
    case PROP_PROFILE:
      g_value_set_int(value, self->profile);
      break;
    case PROP_PRESET:
      g_value_set_int(value, self->preset);
      break;
    case PROP_TUNE:
      g_value_set_int(value, self->tune);
      break;
    case PROP_CLOSED_GOP:
      g_value_set_boolean(value, self->closed_gop);
      break;
    case PROP_KEYINT_MAX:
      g_value_set_int(value, self->keyint_max);
      break;
    case PROP_ANNEXB:
      g_value_set_boolean(value, self->annexb);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
      break;
  }
}

/* Start the encoder */
static gboolean
gst_xeve_enc_start(GstVideoEncoder *encoder)
{
  GstXeveEnc *self = GST_XEVE_ENC(encoder);
  int err = 0;

  /* Apply encoder settings */
  self->xeve_param.profile = self->profile;
  self->xeve_param.bitrate = self->bitrate;
  self->xeve_param.qp = self->qp;
  self->xeve_param.closed_gop = self->closed_gop;
  self->xeve_param.keyint = self->keyint_max;
  self->xeve_param.use_annexb = self->annexb;

  /* Set preset/tune */
  xeve_param_ppt(&self->xeve_param, self->profile, self->preset, self->tune);

  /* Initialize XEVE encoder */
  self->xeve_handle = xeve_create(&self->xeve_cdsc, &err);
  if (!self->xeve_handle || err != XEVE_OK) {
    GST_ERROR_OBJECT(self, "Failed to initialize XEVE encoder (err=%d)", err);
    return FALSE;
  }

  return TRUE;
}

/* Stop the encoder */
static gboolean
gst_xeve_enc_stop(GstVideoEncoder *encoder)
{
  GstXeveEnc *self = GST_XEVE_ENC(encoder);

  if (self->xeve_handle) {
    xeve_delete(self->xeve_handle);
    self->xeve_handle = NULL;
  }

  return TRUE;
}

/* Set input format and configure encoder */
static gboolean
gst_xeve_enc_set_format(GstVideoEncoder *encoder, GstVideoCodecState *state)
{
  GstXeveEnc *self = GST_XEVE_ENC(encoder);
  GstVideoInfo *info = &state->info;

  /* Configure XEVE for the input format */
  self->xeve_param.w = GST_VIDEO_INFO_WIDTH(info);
  self->xeve_param.h = GST_VIDEO_INFO_HEIGHT(info);
  self->xeve_param.fps.num = GST_VIDEO_INFO_FPS_N(info);
  self->xeve_param.fps.den = GST_VIDEO_INFO_FPS_D(info);

  /* Map GStreamer format to XEVE color space */
  switch (GST_VIDEO_INFO_FORMAT(info)) {
    case GST_VIDEO_FORMAT_I420:
      self->xeve_param.cs = XEVE_CS_YCBCR420;
      break;
    case GST_VIDEO_FORMAT_NV12:
      self->xeve_param.cs = XEVE_CS_YCBCR420;
      break;
    case GST_VIDEO_FORMAT_YV12:
      self->xeve_param.cs = XEVE_CS_YCBCR420;
      break;
    default:
      GST_ERROR_OBJECT(self, "Unsupported input format");
      return FALSE;
  }

  return TRUE;
}

/* Process a video frame */
/* Process a video frame */
static GstFlowReturn
gst_xeve_enc_handle_frame(GstVideoEncoder *encoder, GstVideoCodecFrame *frame)
{
  GstXeveEnc *self = GST_XEVE_ENC(encoder);
//   GstVideoCodecState *input_state = gst_video_codec_frame_get_input_state(frame);
//   GstVideoInfo *info = &input_state->info;
  GstVideoCodecState *input_state = frame->input_state;
  GstVideoInfo *info = &input_state->info;

  XEVE_IMGB img_buf = {0};
  XEVE_BITB bit_buf = {0};
  XEVE_STAT enc_stat;
  GstMapInfo in_map, out_map;
  GstBuffer *out_buf;
  GstFlowReturn ret = GST_FLOW_ERROR;
  int err;

  /* Map input buffer */
  if (!gst_buffer_map(frame->input_buffer, &in_map, GST_MAP_READ)) {
    GST_ERROR_OBJECT(self, "Failed to map input buffer");
    goto done;
  }

  /* Fill XEVE_IMGB structure */
  img_buf.cs = self->xeve_param.cs;
  img_buf.w[0] = GST_VIDEO_INFO_WIDTH(info);
  img_buf.h[0] = GST_VIDEO_INFO_HEIGHT(info);
  img_buf.a[0] = in_map.data;

  /* Push frame to XEVE */
  err = xeve_push(self->xeve_handle, &img_buf);
  if (err != XEVE_OK) {
    GST_ERROR_OBJECT(self, "Failed to push frame (err=%d)", err);
    goto unmap_input;
  }

  /* Allocate output buffer */
  out_buf = gst_buffer_new_and_alloc(self->xeve_param.w * self->xeve_param.h * 3 / 2);
  if (!out_buf) {
    GST_ERROR_OBJECT(self, "Failed to allocate output buffer");
    goto unmap_input;
  }

  /* Map output buffer for writing */
  if (!gst_buffer_map(out_buf, &out_map, GST_MAP_WRITE)) {
    GST_ERROR_OBJECT(self, "Failed to map output buffer");
    gst_buffer_unref(out_buf);
    goto unmap_input;
  }

  /* Encode frame */
  bit_buf.addr = out_map.data;
  bit_buf.bsize = out_map.size;
  err = xeve_encode(self->xeve_handle, &bit_buf, &enc_stat);
  
  /* Always unmap output buffer */
  gst_buffer_unmap(out_buf, &out_map);
  
  if (err != XEVE_OK || bit_buf.ssize == 0) {
    GST_ERROR_OBJECT(self, "Failed to encode frame (err=%d)", err);
    gst_buffer_unref(out_buf);
    goto unmap_input;
  }

  /* Set output buffer size */
  gst_buffer_resize(out_buf, 0, bit_buf.ssize);

  /* Set output frame properties */
  frame->output_buffer = out_buf;
  frame->pts = frame->pts;
  frame->dts = frame->dts;
  frame->duration = frame->duration;

  /* Push encoded frame */
  ret = gst_video_encoder_finish_frame(encoder, frame);

unmap_input:
  gst_buffer_unmap(frame->input_buffer, &in_map);
done:
  return ret;
}
/* Plugin entry point */
static gboolean
plugin_init(GstPlugin *plugin)
{
  return gst_element_register(plugin, "xeveenc", GST_RANK_PRIMARY, GST_TYPE_XEVE_ENC);
}

GST_PLUGIN_DEFINE(
    GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    xeveenc,
    "XEVE Video Encoder",
    plugin_init,
    VERSION,
    "LGPL",
    "GStreamer",
    "https://example.com"
)