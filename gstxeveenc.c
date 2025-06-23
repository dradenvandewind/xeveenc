/*
 * Copyright (c) 2025, Le Blond Erwan
 * Contact: erwanleblond@gmail.com
 */

// Add these definitions at the top of gstxeveenc.c
#define PACKAGE "gstxeve"
#define VERSION "1.0.0"

#include "gstxeveenc.h"
#include <string.h>

GST_DEBUG_CATEGORY_STATIC(gst_xeve_enc_debug);
#define GST_CAT_DEFAULT gst_xeve_enc_debug

typedef struct {
  XEVE xeve_handle;
  XEVE_PARAM *xeve_param;      // Pointer instead of direct structure
  XEVE_CDSC *xeve_cdsc;        // Pointer instead of direct structure
  gboolean encoder_initialized;
  GstVideoCodecState *input_state;
} GstXeveEncPrivate;

#define GST_XEVE_ENC_GET_PRIVATE(obj) \
  ((GstXeveEncPrivate *)gst_xeve_enc_get_instance_private(GST_XEVE_ENC(obj)))

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

G_DEFINE_TYPE_WITH_PRIVATE(GstXeveEnc, gst_xeve_enc, GST_TYPE_VIDEO_ENCODER)

static void gst_xeve_enc_set_property(GObject *object, guint prop_id,
                                     const GValue *value, GParamSpec *pspec);
static void gst_xeve_enc_get_property(GObject *object, guint prop_id,
                                     GValue *value, GParamSpec *pspec);
static void gst_xeve_enc_dispose(GObject *object);
static gboolean gst_xeve_enc_start(GstVideoEncoder *encoder);
static gboolean gst_xeve_enc_stop(GstVideoEncoder *encoder);
static gboolean gst_xeve_enc_set_format(GstVideoEncoder *encoder,
                                       GstVideoCodecState *state);
static GstFlowReturn gst_xeve_enc_handle_frame(GstVideoEncoder *encoder,
                                              GstVideoCodecFrame *frame);

static void
gst_xeve_enc_class_init(GstXeveEncClass *klass)
{
  g_print("Private struct size: %zu\n", sizeof(GstXeveEncPrivate));
  GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
  GstVideoEncoderClass *video_encoder_class = GST_VIDEO_ENCODER_CLASS(klass);
  GstElementClass *element_class = GST_ELEMENT_CLASS(klass);

  GST_DEBUG_CATEGORY_INIT(gst_xeve_enc_debug, "xeveenc", 0, "XEVE Encoder");

  gobject_class->set_property = gst_xeve_enc_set_property;
  gobject_class->get_property = gst_xeve_enc_get_property;
  gobject_class->dispose = gst_xeve_enc_dispose;

  g_object_class_install_property(
      gobject_class, PROP_BITRATE,
      g_param_spec_int("bitrate", "Bitrate", "Target bitrate in kbps",
                       1, 200000, 2000, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property(
      gobject_class, PROP_QP,
      g_param_spec_int("qp", "QP", "Quantization Parameter (0 = auto)",
                       0, 51, 0, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  // Add other properties similarly...

  gst_element_class_add_static_pad_template(element_class, &sink_template);
  gst_element_class_add_static_pad_template(element_class, &src_template);

  gst_element_class_set_static_metadata(
      element_class,
      "XEVE Video Encoder",
      "Codec/Encoder/Video",
      "Encode video streams using XEVE",
      "Erwan Le Blond <erwanleblond@gmail.com>");

  video_encoder_class->start = gst_xeve_enc_start;
  video_encoder_class->stop = gst_xeve_enc_stop;
  video_encoder_class->set_format = gst_xeve_enc_set_format;
  video_encoder_class->handle_frame = gst_xeve_enc_handle_frame;
}

static void
gst_xeve_enc_init(GstXeveEnc *self)
{
  GstXeveEncPrivate *priv = GST_XEVE_ENC_GET_PRIVATE(self);

  GST_DEBUG_OBJECT(self, "init called");

  self->width = 0;    
  self->height = 0;    
  self->fps_n = 25;   
  self->fps_d = 1;

  // Default encoder settings
  self->bitrate = 2000;
  self->qp = 0;
  self->profile = 0;
  self->preset = 2;
  self->tune = 0;
  self->closed_gop = FALSE;
  self->keyint_max = 250;
  self->annexb = TRUE;

  // Initialize pointers to NULL before allocation
  priv->xeve_param = NULL;
  priv->xeve_cdsc = NULL;
  priv->xeve_handle = NULL;
  priv->input_state = NULL;
  priv->encoder_initialized = FALSE;

  // Secure allocation  
  priv->xeve_param = g_malloc0(sizeof(XEVE_PARAM));
  priv->xeve_cdsc = g_malloc0(sizeof(XEVE_CDSC));
  
  if (priv->xeve_param) {
    xeve_param_default(priv->xeve_param);
  }

  GST_DEBUG_OBJECT(self, "init completed");
}

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
    // Handle other properties...
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
    // Handle other properties...
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
      break;
  }
}
static void
gst_xeve_enc_dispose(GObject *object)
{
  GstXeveEnc *self = GST_XEVE_ENC(object);
  GstXeveEncPrivate *priv = GST_XEVE_ENC_GET_PRIVATE(self);

  GST_DEBUG_OBJECT(self, "dispose called");

  // Clean the XEVE encoder  
  if (priv->xeve_handle) {
    xeve_delete(priv->xeve_handle);
    priv->xeve_handle = NULL;
  }

  // Release the input state  
  if (priv->input_state) {
    gst_video_codec_state_unref(priv->input_state);
    priv->input_state = NULL;
  }

  // Check that pointers are not NULL before release  
  if (priv->xeve_param) {
    g_free(priv->xeve_param);
    priv->xeve_param = NULL;
  }

  if (priv->xeve_cdsc) {
    g_free(priv->xeve_cdsc);
    priv->xeve_cdsc = NULL;
  }

  priv->encoder_initialized = FALSE;

  G_OBJECT_CLASS(gst_xeve_enc_parent_class)->dispose(object);
}

static gboolean
gst_xeve_enc_start(GstVideoEncoder *encoder)
{
  GstXeveEnc *self = GST_XEVE_ENC(encoder);
  GstXeveEncPrivate *priv = GST_XEVE_ENC_GET_PRIVATE(self);

  GST_DEBUG_OBJECT(self, "start called");

  if (!priv->xeve_param) {
    GST_ERROR_OBJECT(self, "XEVE param not initialized");
    return FALSE;
  }


  // Reset status  
  priv->encoder_initialized = FALSE;
  
  GST_INFO_OBJECT(self, "XEVE encoder started - waiting for format negotiation");
  return TRUE;
}

static gboolean
gst_xeve_enc_stop(GstVideoEncoder *encoder)
{
  GstXeveEnc *self = GST_XEVE_ENC(encoder);
  GstXeveEncPrivate *priv = GST_XEVE_ENC_GET_PRIVATE(self);

  if (priv->xeve_handle) {
    xeve_delete(priv->xeve_handle);
    priv->xeve_handle = NULL;
  }

  if (priv->input_state) {
    gst_video_codec_state_unref(priv->input_state);
    priv->input_state = NULL;
  }

  GST_INFO_OBJECT(self, "Encoder XEVE started");

  return TRUE;
}
static gboolean
gst_xeve_enc_set_format(GstVideoEncoder *encoder, GstVideoCodecState *state)
{
  GstXeveEnc *self = GST_XEVE_ENC(encoder);
  GstXeveEncPrivate *priv = GST_XEVE_ENC_GET_PRIVATE(self);
  GstVideoInfo *info = &state->info;
  int err = 0;

  GST_INFO_OBJECT(self, "set_format called");

  if (!priv->xeve_param || !priv->xeve_cdsc) {
    GST_ERROR_OBJECT(self, "XEVE structures not initialized");
    return FALSE;
  }

  if (priv->input_state)
    gst_video_codec_state_unref(priv->input_state);

  priv->input_state = gst_video_codec_state_ref(state);

  // Correctly extract information from GstVideoInfo  
  gint width = GST_VIDEO_INFO_WIDTH(info);
  gint height = GST_VIDEO_INFO_HEIGHT(info);
  gint fps_n = GST_VIDEO_INFO_FPS_N(info);
  gint fps_d = GST_VIDEO_INFO_FPS_D(info);

  GST_INFO_OBJECT(self, "Extracted from caps: %dx%d @ %d/%d fps", 
                  width, height, fps_n, fps_d);

  // Check that the dimensions are valid  
  if (width <= 0 || height <= 0) {
    GST_ERROR_OBJECT(self, "Invalid dimensions extracted: %dx%d", width, height);
    return FALSE;
  }

  // Assign to instance variables  
  self->width = width;
  self->height = height;
  self->fps_n = fps_n;
  self->fps_d = fps_d;

  // Configure XEVE settings
  priv->xeve_param->w = width;
  priv->xeve_param->h = height;
  priv->xeve_param->fps.num = fps_n;
  priv->xeve_param->fps.den = fps_d;

  // Color format configuration
  switch (GST_VIDEO_INFO_FORMAT(info)) {
    case GST_VIDEO_FORMAT_I420:
    case GST_VIDEO_FORMAT_NV12:
    case GST_VIDEO_FORMAT_YV12:
      priv->xeve_param->cs = XEVE_CS_YCBCR420;
      break;
    default:
      GST_ERROR_OBJECT(self, "Unsupported input format: %s", 
                       gst_video_format_to_string(GST_VIDEO_INFO_FORMAT(info)));
      return FALSE;
  }

  // Clean the existing encoder
  if (priv->xeve_handle) {
    xeve_delete(priv->xeve_handle);
    priv->xeve_handle = NULL;
  }

  // Configure all encoder settings
  priv->xeve_param->profile = self->profile;
  priv->xeve_param->bitrate = self->bitrate;
  priv->xeve_param->qp = self->qp;
  priv->xeve_param->closed_gop = self->closed_gop;
  priv->xeve_param->keyint = self->keyint_max;
  priv->xeve_param->use_annexb = self->annexb;

  // Apply presets
  xeve_param_ppt(priv->xeve_param, self->profile, self->preset, self->tune);

  #ifdef DEBUG 
    g_print("File: %s | Function: %s | Line: %d\n", __FILE__, __func__, __LINE__);
    g_print("width %d \n", priv->xeve_param->w);
    g_print("height %d \n", priv->xeve_param->h);
    g_print("fps num %d \n", priv->xeve_param->fps.num);
    g_print("fps_den %d \n", priv->xeve_param->fps.den);
    g_print("chromat format %d \n", priv->xeve_param->cs);
    g_print("File: %s | Function: %s | Line: %d\n", __FILE__, __func__, __LINE__);
  #endif 

// Create the XEVE encoder - CORRECTION: pass xeve_param, not xeve_cdsc  
  //priv->xeve_handle = xeve_create(priv->xeve_param, &err);
    priv->xeve_handle = xeve_create(priv->xeve_cdsc, &err);

  if (!priv->xeve_handle || err != XEVE_OK) {
    GST_ERROR_OBJECT(self, "Failed to initialize XEVE encoder (err=%d)", err);
    return FALSE;
  }

  priv->encoder_initialized = TRUE;
  GST_INFO_OBJECT(self, "XEVE encoder initialized successfully: %dx%d", width, height);

  // Set the output caps  
  GstVideoCodecState *output_state;
  GstCaps *output_caps;
  
  output_caps = gst_caps_new_simple("video/x-xeve",
                                   "width", G_TYPE_INT, width,
                                   "height", G_TYPE_INT, height,
                                   "framerate", GST_TYPE_FRACTION, fps_n, fps_d,
                                   "stream-format", G_TYPE_STRING, "byte-stream",
                                   "alignment", G_TYPE_STRING, "au",
                                   NULL);
  
  output_state = gst_video_encoder_set_output_state(encoder, output_caps, state);
  gst_video_codec_state_unref(output_state);

  return TRUE;
}

static GstFlowReturn
gst_xeve_enc_handle_frame(GstVideoEncoder *encoder, GstVideoCodecFrame *frame)
{
  GstXeveEnc *self = GST_XEVE_ENC(encoder);
  GstXeveEncPrivate *priv = GST_XEVE_ENC_GET_PRIVATE(self);
  GstVideoInfo *info = &priv->input_state->info;
  XEVE_IMGB img_buf = {0};
  XEVE_BITB bit_buf = {0};
  XEVE_STAT enc_stat;
  GstMapInfo in_map, out_map;
  GstBuffer *out_buf;
  GstFlowReturn ret = GST_FLOW_ERROR;
  int err;

  if (!priv->xeve_param) {
    GST_ERROR_OBJECT(self, "XEVE param not initialized");
    goto done;
  }

  if (!gst_buffer_map(frame->input_buffer, &in_map, GST_MAP_READ)) {
    GST_ERROR_OBJECT(self, "Failed to map input buffer");
    goto done;
  }

  img_buf.cs = priv->xeve_param->cs;
  img_buf.w[0] = GST_VIDEO_INFO_WIDTH(info);
  img_buf.h[0] = GST_VIDEO_INFO_HEIGHT(info);
  img_buf.a[0] = in_map.data;

  err = xeve_push(priv->xeve_handle, &img_buf);
  if (err != XEVE_OK) {
    GST_ERROR_OBJECT(self, "Failed to push frame (err=%d)", err);
    goto unmap_input;
  }

  out_buf = gst_buffer_new_and_alloc(priv->xeve_param->w * priv->xeve_param->h * 3 / 2);
  if (!out_buf) {
    GST_ERROR_OBJECT(self, "Failed to allocate output buffer");
    goto unmap_input;
  }

  if (!gst_buffer_map(out_buf, &out_map, GST_MAP_WRITE)) {
    GST_ERROR_OBJECT(self, "Failed to map output buffer");
    gst_buffer_unref(out_buf);
    goto unmap_input;
  }

  bit_buf.addr = out_map.data;
  bit_buf.bsize = out_map.size;
  err = xeve_encode(priv->xeve_handle, &bit_buf, &enc_stat);
  
  gst_buffer_unmap(out_buf, &out_map);
  
  if (err != XEVE_OK || bit_buf.ssize == 0) {
    GST_ERROR_OBJECT(self, "Failed to encode frame (err=%d)", err);
    gst_buffer_unref(out_buf);
    goto unmap_input;
  }

  gst_buffer_resize(out_buf, 0, bit_buf.ssize);
  frame->output_buffer = out_buf;
  ret = gst_video_encoder_finish_frame(encoder, frame);

unmap_input:
  gst_buffer_unmap(frame->input_buffer, &in_map);
done:
  return ret;
}

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