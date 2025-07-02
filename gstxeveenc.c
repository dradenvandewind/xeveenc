/*
 * Copyright (c) 2025, Le Blond Erwan
 * Contact: erwanleblond@gmail.com
 */

// Add these definitions at the top of gstxeveenc.c
#define PACKAGE "gstxeve"
#define VERSION "1.0.0"

#include "gstxeveenc.h"
#include <string.h>

#include <stdio.h>
#ifdef DEBUG

void print_xeve_param(const XEVE_PARAM *param) {
  if (param == NULL) {
    printf("Error: NULL parameter passed to print_xeve_param\n");
    return;
  }

  printf("XEVE_PARAM Structure Values:\n");
  printf("===========================\n");

  /* Basic parameters */
  printf("Profile: %d\n", param->profile);
  printf("Threads: %d\n", param->threads);
  printf("Width: %d\n", param->w);
  printf("Height: %d\n", param->h);
  printf("FPS: %d/%d\n", param->fps.num, param->fps.den);
  printf("Keyint: %d\n", param->keyint);
  printf("Color space: %d\n", param->cs);
  printf("RC type: %d\n", param->rc_type);
  printf("QP: %d\n", param->qp);
  printf("QP CB offset: %d\n", param->qp_cb_offset);
  printf("QP CR offset: %d\n", param->qp_cr_offset);
  printf("Bitrate: %d kbps\n", param->bitrate);
  printf("VBV bufsize: %d kbits\n", param->vbv_bufsize);
  printf("CRF: %d\n", param->crf);
  printf("B-frames: %d\n", param->bframes);
  printf("AQ mode: %d\n", param->aq_mode);
  printf("Lookahead: %d\n", param->lookahead);
  printf("Closed GOP: %d\n", param->closed_gop);
  printf("Use Annex-B: %d\n", param->use_annexb);
  printf("Use filler: %d\n", param->use_filler);

  /* Chroma QP table */
  printf("Chroma QP table present: %d\n", param->chroma_qp_table_present_flag);
  // Note: The arrays are too large to print completely - you might want to
  // print just a few elements

  /* Coding tools */
  printf("Disable HGOP: %d\n", param->disable_hgop);
  printf("Ref pic gap length: %d\n", param->ref_pic_gap_length);
  printf("Codec bit depth: %d\n", param->codec_bit_depth);
  printf("Level IDC: %d\n", param->level_idc);
  printf("Cutree: %d\n", param->cutree);
  printf("Constrained intra pred: %d\n", param->constrained_intra_pred);
  printf("Use deblock: %d\n", param->use_deblock);
  printf("Inter slice type: %d\n", param->inter_slice_type);

  /* Picture cropping */
  printf("Picture cropping flag: %d\n", param->picture_cropping_flag);
  if (param->picture_cropping_flag) {
    printf("  Crop left: %d\n", param->picture_crop_left_offset);
    printf("  Crop right: %d\n", param->picture_crop_right_offset);
    printf("  Crop top: %d\n", param->picture_crop_top_offset);
    printf("  Crop bottom: %d\n", param->picture_crop_bottom_offset);
  }

  /* More parameters */
  printf("RDO DBK switch: %d\n", param->rdo_dbk_switch);
  printf("QP increase frame: %d\n", param->qp_incread_frame);
  printf("SEI CMD info: %d\n", param->sei_cmd_info);
  printf("Use pic sign: %d\n", param->use_pic_sign);
  printf("F I-frame: %d\n", param->f_ifrm);
  printf("QP max: %d\n", param->qp_max);
  printf("QP min: %d\n", param->qp_min);
  printf("GOP size: %d\n", param->gop_size);
  printf("Force output: %d\n", param->force_output);
  printf("Use FCST: %d\n", param->use_fcst);
  printf("Chroma format IDC: %d\n", param->chroma_format_idc);
  printf("CS width shift: %d\n", param->cs_w_shift);
  printf("CS height shift: %d\n", param->cs_h_shift);

  /* CU settings */
  printf("Max CU intra: %d\n", param->max_cu_intra);
  printf("Min CU intra: %d\n", param->min_cu_intra);
  printf("Max CU inter: %d\n", param->max_cu_inter);
  printf("Min CU inter: %d\n", param->min_cu_inter);

  /* Motion estimation */
  printf("Ref frames: %d\n", param->ref);
  printf("ME ref num: %d\n", param->me_ref_num);
  printf("ME algorithm: %d\n", param->me_algo);
  printf("ME range: %d\n", param->me_range);
  printf("ME sub: %d\n", param->me_sub);
  printf("ME sub pos: %d\n", param->me_sub_pos);
  printf("ME sub range: %d\n", param->me_sub_range);
  printf("Skip threshold: %f\n", param->skip_th);
  printf("Merge num: %d\n", param->merge_num);
  printf("RDOQ: %d\n", param->rdoq);
  printf("CABAC refine: %d\n", param->cabac_refine);

  /* Main Profile Parameters */
  printf("IBC flag: %d\n", param->ibc_flag);
  printf("IBC search range X: %d\n", param->ibc_search_range_x);
  printf("IBC search range Y: %d\n", param->ibc_search_range_y);
  printf("IBC hash search flag: %d\n", param->ibc_hash_search_flag);
  printf("IBC hash search max cand: %d\n", param->ibc_hash_search_max_cand);
  printf("IBC hash search range for small blocks: %d\n",
         param->ibc_hash_search_range_4smallblk);
  printf("IBC fast method: %d\n", param->ibc_fast_method);

  /* Toolset and framework */
  printf("Toolset IDC H: %d\n", param->toolset_idc_h);
  printf("Toolset IDC L: %d\n", param->toolset_idc_l);
  printf("BTT: %d\n", param->btt);
  printf("SUCO: %d\n", param->suco);

  /* VUI parameters */
  printf("SAR: %d\n", param->sar);
  printf("SAR width: %d, SAR height: %d\n", param->sar_width,
         param->sar_height);
  printf("Video format: %d\n", param->videoformat);
  printf("Range: %d\n", param->range);
  printf("Color primaries: %d\n", param->colorprim);
  printf("Transfer characteristics: %d\n", param->transfer);
  printf("Matrix coefficients: %d\n", param->matrix_coefficients);

  /* SEI options */
  printf("Master display: %d\n", param->master_display);
  printf("Max CLL: %d\n", param->max_cll);
  printf("Max FALL: %d\n", param->max_fall);

  printf("===========================\n");
}
#endif

GST_DEBUG_CATEGORY_STATIC(gst_xeve_enc_debug);
#define GST_CAT_DEFAULT gst_xeve_enc_debug

typedef struct {
  XEVE xeve_handle;
  XEVE_CDSC *xeve_cdsc; // Pointer instead of direct structure
  gboolean encoder_initialized;
  GstVideoCodecState *input_state;
  gint frame_number;
  unsigned char *bs_buf;
  XEVE_BITB bitb;

} GstXeveEncPrivate;

#define GST_XEVE_ENC_GET_PRIVATE(obj)                                          \
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
    "sink", GST_PAD_SINK, GST_PAD_ALWAYS,
    GST_STATIC_CAPS("video/x-raw, "
                    "format = (string) { I420, NV12, YV12 }, "
                    "width = (int) [ 16, 8192 ], "
                    "height = (int) [ 16, 4320 ], "
                    "framerate = (fraction) [ 0/1, 300/1 ]"));

static GstStaticPadTemplate src_template = GST_STATIC_PAD_TEMPLATE(
    "src", GST_PAD_SRC, GST_PAD_ALWAYS,
    GST_STATIC_CAPS("video/x-xeve, "
                    "width = (int) [ 16, 8192 ], "
                    "height = (int) [ 16, 4320 ], "
                    "framerate = (fraction) [ 0/1, 300/1 ], "
                    "stream-format = (string) byte-stream, "
                    "alignment = (string) au"));

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

static void gst_xeve_enc_class_init(GstXeveEncClass *klass) {
  GObjectClass *gobject_class = G_OBJECT_CLASS(klass);
  GstVideoEncoderClass *video_encoder_class = GST_VIDEO_ENCODER_CLASS(klass);
  GstElementClass *element_class = GST_ELEMENT_CLASS(klass);

  GST_DEBUG_CATEGORY_INIT(gst_xeve_enc_debug, "xeveenc", 0, "XEVE Encoder");

  gobject_class->set_property = gst_xeve_enc_set_property;
  gobject_class->get_property = gst_xeve_enc_get_property;
  gobject_class->dispose = gst_xeve_enc_dispose;

  g_object_class_install_property(
      gobject_class, PROP_BITRATE,
      g_param_spec_int("bitrate", "Bitrate", "Target bitrate in kbps", 1,
                       200000, 2000,
                       G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  g_object_class_install_property(
      gobject_class, PROP_QP,
      g_param_spec_int("qp", "QP", "Quantization Parameter (0 = auto)", 0, 51,
                       0, G_PARAM_READWRITE | G_PARAM_STATIC_STRINGS));

  // Add other properties similarly...

  gst_element_class_add_static_pad_template(element_class, &sink_template);
  gst_element_class_add_static_pad_template(element_class, &src_template);

  gst_element_class_set_static_metadata(
      element_class, "XEVE Video Encoder", "Codec/Encoder/Video",
      "Encode video streams using XEVE",
      "Erwan Le Blond <erwanleblond@gmail.com>");

  video_encoder_class->start = gst_xeve_enc_start;
  video_encoder_class->stop = gst_xeve_enc_stop;
  video_encoder_class->set_format = gst_xeve_enc_set_format;
  video_encoder_class->handle_frame = gst_xeve_enc_handle_frame;
}

static void gst_xeve_enc_init(GstXeveEnc *self) {
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
  priv->xeve_cdsc = NULL;
  priv->xeve_handle = NULL;
  priv->input_state = NULL;
  priv->encoder_initialized = FALSE;
  priv->frame_number = 0;
  priv->bs_buf = NULL;

  // Secure allocation
  // priv->xeve_cdsc = g_malloc0(sizeof(XEVE_CDSC));
  // memset(priv->xeve_cdsc, 0, sizeof(XEVE_CDSC));
  priv->xeve_cdsc = g_malloc(sizeof(XEVE_CDSC)); // Allocate but don't zero
  memset(priv->xeve_cdsc, 0, sizeof(XEVE_CDSC)); // Now safe to memset

  if (priv->xeve_cdsc == NULL) {
    GST_ERROR_OBJECT(self,
                     "Failed to allocate XEVE_CDSC structure, Pointer is NULL");
    return;
  } else {
    priv->xeve_cdsc->max_bs_buf_size = MAX_BS_BUF;
  }

  // priv->xeve_cdsc->max_bs_buf_size = MAX_BS_BUF; // MAX_BITSTREAM_SIZE;
  //  priv->bs_buf = g_malloc0(MAX_BITSTREAM_SIZE);
  priv->bs_buf = (unsigned char *)malloc(MAX_BS_BUF);

  if (!priv->bs_buf) {
    GST_ERROR_OBJECT(self, "Failed to allocate bitstream buffer");
    return;
  }
  // Initialize bitstream buffer
  if (priv->bs_buf) {
    priv->bitb.bsize = MAX_BS_BUF;
    // priv->xeve_cdsc->max_bs_buf_size;
    priv->bitb.addr = priv->bs_buf;
  }

#if 0
  g_print("priv->xeve_cdsc %x \n", priv->xeve_cdsc);
  g_print("priv->xeve_cdsc->max_bs_buf_size %d \n", priv->xeve_cdsc->max_bs_buf_size);
#endif

  if (priv->xeve_cdsc) {
    /* get default parameters */
    xeve_param_default(&priv->xeve_cdsc->param);
  }

  GST_DEBUG_OBJECT(self, "init completed");
}

static void gst_xeve_enc_set_property(GObject *object, guint prop_id,
                                      const GValue *value, GParamSpec *pspec) {
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

static void gst_xeve_enc_get_property(GObject *object, guint prop_id,
                                      GValue *value, GParamSpec *pspec) {
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
static void gst_xeve_enc_dispose(GObject *object) {
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

  if (priv->xeve_cdsc) {
    g_free(priv->xeve_cdsc);
    priv->xeve_cdsc = NULL;
  }

  if (self->imgb_rec) {
    imgb_free(self->imgb_rec);
    self->imgb_rec = NULL;
  }

  if (priv->bs_buf) {
    g_free(priv->bs_buf);
    priv->bs_buf = NULL;
  }

  // Close any open files
  if (self->fp) {
    fclose(self->fp);
    self->fp = NULL;
  }
  if (self->fp_Y) {
    fclose(self->fp_Y);
    self->fp_Y = NULL;
  }
  if (self->fp_U) {
    fclose(self->fp_U);
    self->fp_U = NULL;
  }
  if (self->fp_V) {
    fclose(self->fp_V);
    self->fp_V = NULL;
  }

  if (self->fp_bitstream) {
    fclose(self->fp_bitstream);
    self->fp_bitstream = NULL;
  }

  priv->encoder_initialized = FALSE;

  G_OBJECT_CLASS(gst_xeve_enc_parent_class)->dispose(object);
}

static gboolean gst_xeve_enc_start(GstVideoEncoder *encoder) {
  GstXeveEnc *self = GST_XEVE_ENC(encoder);
  GstXeveEncPrivate *priv = GST_XEVE_ENC_GET_PRIVATE(self);

  GST_DEBUG_OBJECT(self, "start called");

  if (!priv->xeve_cdsc) {
    GST_ERROR_OBJECT(self, "XEVE  not initialized");
    return FALSE;
  }

  // Reset status
  priv->encoder_initialized = FALSE;

  GST_INFO_OBJECT(self,
                  "XEVE encoder started - waiting for format negotiation");
  return TRUE;
}

static gboolean gst_xeve_enc_stop(GstVideoEncoder *encoder) {
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

static int set_extra_config(XEVE id, XEVE_PARAM *param) {
  int ret, size;
  // todo to be configure from plugin param
  // embed SEI messages identifying encoder parameters
  int info = 1;
  // embed picture signature (HASH) for conformance checking in decoding"
  int hash = 0;
  // 1;

  size = 4;
  ret = xeve_config(id, XEVE_CFG_SET_SEI_CMD, &info, &size);
  if (XEVE_FAILED(ret)) {
    g_print("failed to set config for sei command info messages\n");
    // GST_ERROR_OBJECT(self, "failed to set config for sei command info
    // messages");
    return -1;
  }

  if (hash) {
    size = 4;
    ret = xeve_config(id, XEVE_CFG_SET_USE_PIC_SIGNATURE, &hash, &size);
    if (XEVE_FAILED(ret)) {
      // GST_ERROR_OBJECT(self, "failed to set config for picture signature\n");
      g_print("failed to set config for picture signature\n");

      return -1;
    }
  }

  return 0;
}

static gboolean gst_xeve_enc_set_format(GstVideoEncoder *encoder,
                                        GstVideoCodecState *state) {
  GstXeveEnc *self = GST_XEVE_ENC(encoder);
  GstXeveEncPrivate *priv = GST_XEVE_ENC_GET_PRIVATE(self);
  GstVideoInfo *info = &state->info;
  int err = 0;
  int ret = 0;

  GST_INFO_OBJECT(self, "set_format called");

  if (!priv->xeve_cdsc) {
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
  /*
  GST_VIDEO_INFO_CHROMA_SITE(info);


  */

  GST_INFO_OBJECT(self, "Extracted from caps: %dx%d @ %d/%d fps", width, height,
                  fps_n, fps_d);

  // Check that the dimensions are valid
  if (width <= 0 || height <= 0) {
    GST_ERROR_OBJECT(self, "Invalid dimensions extracted: %dx%d", width,
                     height);
    return FALSE;
  }

  // Assign to instance variables
  self->width = width;
  self->height = height;
  self->fps_n = fps_n;
  self->fps_d = fps_d;

  // Configure XEVE settings

  priv->xeve_cdsc->param.w = width;
  priv->xeve_cdsc->param.h = height;
  priv->xeve_cdsc->param.fps.num = fps_n;
  priv->xeve_cdsc->param.fps.den = fps_d;
  priv->xeve_cdsc->param.keyint = 1; // 0: only one I-frame at the first time;
                                     // 1: every frame is coded in I-frame
  priv->xeve_cdsc->param.bframes =
      0; // No B-frames for now to investigate todo conf from input plugin

  priv->xeve_cdsc->param.rc_type = XEVE_RC_CQP;
  priv->xeve_cdsc->param.bitrate = 5; // in kbps

  // Only proceed if xeve_cdsc and its params are valid
  if (priv->xeve_cdsc && priv->xeve_cdsc->param.fps.num != 0) {
    if (priv->xeve_cdsc->param.rc_type == XEVE_RC_ABR ||
        priv->xeve_cdsc->param.rc_type == XEVE_RC_CRF) {
      // ABR/CRF: VBV = (bitrate / fps) × buffer_duration (floating-point math)
      float buffer_duration_in_seconds =
          2.0f; // Adjust as needed (1-4 sec typical)
      priv->xeve_cdsc->param.vbv_bufsize =
          (int)(buffer_duration_in_seconds *
                (priv->xeve_cdsc->param.bitrate /
                 (float)priv->xeve_cdsc->param.fps.num));
    } else if (priv->xeve_cdsc->param.rc_type == XEVE_RC_CQP) {
      // CQP: Fixed bitrate (5kbps example) and 2x buffer
      priv->xeve_cdsc->param.bitrate =
          5; // Default bitrate for CQP (adjust if needed)
      priv->xeve_cdsc->param.vbv_bufsize = priv->xeve_cdsc->param.bitrate * 2;
    }
  } else {
    // Fallback: Handle invalid config (log error + safe defaults)
    fprintf(stderr, "ERROR: Invalid xeve_cdsc or zero fps.num!\n");
    GST_ERROR_OBJECT(self, "ERROR: Invalid xeve_cdsc or zero fps.num");

    if (priv->xeve_cdsc) {
      priv->xeve_cdsc->param.vbv_bufsize = priv->xeve_cdsc->param.bitrate * 2;
    }
  }

  priv->xeve_cdsc->param.bitrate = 5; // in kbps

  priv->xeve_cdsc->param.vbv_bufsize =
      2 * priv->xeve_cdsc->param.bitrate; // 12 kbits
                                          //

#if 0
  // Color format configuration
  switch (GST_VIDEO_INFO_FORMAT(info)) {
    case GST_VIDEO_FORMAT_I420:
    case GST_VIDEO_FORMAT_NV12:
    case GST_VIDEO_FORMAT_YV12:
      priv->xeve_cdsc->param.cs = XEVE_CS_SET(XEVE_CS_YCBCR420, priv->xeve_cdsc->param.codec_bit_depth, 0);

      break;
    default:
      GST_ERROR_OBJECT(self, "Unsupported input format: %s", 
                       gst_video_format_to_string(GST_VIDEO_INFO_FORMAT(info)));
      return FALSE;
  }
#else
  // Color format configuration
  switch (GST_VIDEO_INFO_FORMAT(info)) {
  case GST_VIDEO_FORMAT_I420:
    self->bit_depth = 8;
    // priv->xeve_cdsc->param.cs =
    //     XEVE_CS_SET(XEVE_CF_YCBCR420, self->bit_depth, 0);
    priv->xeve_cdsc->param.cs =
        XEVE_CS_YCBCR420; /// test
                          // XEVE_CS_SET(XEVE_CF_YCBCR420,
                          // priv->xeve_cdsc->param.codec_bit_depth, 0);
    priv->xeve_cdsc->param.cs =
        XEVE_CS_SET(XEVE_CF_YCBCR420, self->bit_depth, 0);
    ;

    self->bit_depth = 8;
    break;
  case GST_VIDEO_FORMAT_Y42B:
    priv->xeve_cdsc->param.cs = XEVE_CS_SET(
        XEVE_CF_YCBCR422, priv->xeve_cdsc->param.codec_bit_depth, 0);
    self->bit_depth = 8;
    break;
  case GST_VIDEO_FORMAT_Y444:
    priv->xeve_cdsc->param.cs = XEVE_CS_SET(
        XEVE_CF_YCBCR444, priv->xeve_cdsc->param.codec_bit_depth, 0);
    self->bit_depth = 8;
    break;
  case GST_VIDEO_FORMAT_I420_10LE:
    priv->xeve_cdsc->param.cs = XEVE_CS_SET(
        XEVE_CF_YCBCR420, priv->xeve_cdsc->param.codec_bit_depth, 0);
    self->bit_depth = 10;
    break;
  case GST_VIDEO_FORMAT_I422_10LE:
    priv->xeve_cdsc->param.cs = XEVE_CS_SET(
        XEVE_CF_YCBCR422, priv->xeve_cdsc->param.codec_bit_depth, 0);
    self->bit_depth = 10;
    break;
  case GST_VIDEO_FORMAT_Y444_10LE:
    priv->xeve_cdsc->param.cs = XEVE_CS_SET(
        XEVE_CF_YCBCR444, priv->xeve_cdsc->param.codec_bit_depth, 0);
    self->bit_depth = 10;
    break;
  default:
    GST_ERROR_OBJECT(self, "Unsupported input format: %s",
                     gst_video_format_to_string(GST_VIDEO_INFO_FORMAT(info)));
    return FALSE;
  }

#if 0
  // Set default parameters according to xeve_app 
  priv->xeve_cdsc->param.rdo_dbk_switch = 0;
  priv->xeve_cdsc->param.me_range = 64;
  priv->xeve_cdsc->param.me_sub = 2;
  priv->xeve_cdsc->param.me_sub_range = 1;
#endif

#endif
#if 1
  // width = (width + 7) & 0xFFF8;
  // height = (height + 7) & 0xFFF8;

  self->imgb_rec = imgb_alloc(width, height, priv->xeve_cdsc->param.cs);
  // self->imgb_rec = imgb_alloc(width, height, 2059);

  if (!self->imgb_rec) {
    imgb_free(self->imgb_rec);
    self->imgb_rec = NULL;
  }
#endif
  self->fp = fopen("dumpbuf.yuv", "ab");
  if (self->fp == NULL) {
    GST_ERROR_OBJECT(self, "Failed to open dump file");
    return FALSE;
  } else {
    GST_INFO_OBJECT(self, "Dump file opened successfully");
  }
  self->fp_Y = fopen("dumpbuf_Y.yuv", "ab");
  if (self->fp_Y == NULL) {
    GST_ERROR_OBJECT(self, "Failed to open Y dump file");
    return FALSE;
  } else {
    GST_INFO_OBJECT(self, "Y dump file opened successfully");
  }
  self->fp_U = fopen("dumpbuf_U.yuv", "ab");
  if (self->fp_U == NULL) {
    GST_ERROR_OBJECT(self, "Failed to open U dump file");
    return FALSE;
  } else {
    GST_INFO_OBJECT(self, "U dump file opened successfully");
  }
  self->fp_V = fopen("dumpbuf_V.yuv", "ab");
  if (self->fp_V == NULL) {
    GST_ERROR_OBJECT(self, "Failed to open V dump file");
    return FALSE;
  } else {
    GST_INFO_OBJECT(self, "V dump file opened successfully");
  }

  self->fp_bitstream = fopen("fp_bitstream.evc", "ab");
  if (self->fp_bitstream == NULL) {
    GST_ERROR_OBJECT(self, "Failed to open bitstream dump file");
    return FALSE;
  } else {
    GST_INFO_OBJECT(self, "bitream dump file opened successfully");
  }

  // Clean the existing encoder
  if (priv->xeve_handle) {
    xeve_delete(priv->xeve_handle);
    priv->xeve_handle = NULL;
  }
  /*

    priv->xeve_cdsc->param.profile = self->profile;
    priv->xeve_cdsc->param.bitrate = self->bitrate;
    priv->xeve_cdsc->param.qp = self->qp;
    priv->xeve_cdsc->param.closed_gop = self->closed_gop;
    priv->xeve_cdsc->param.keyint = self->keyint_max;
    priv->xeve_cdsc->param.use_annexb = self->annexb;
  */
  priv->xeve_cdsc->param.threads = (int)sysconf(_SC_NPROCESSORS_ONLN); // 8;

  // Apply presets

  ret = xeve_param_ppt(&priv->xeve_cdsc->param, XEVE_PROFILE_BASELINE,
                       XEVE_PRESET_DEFAULT, XEVE_TUNE_NONE);
  if (XEVE_FAILED(ret)) {
    GST_ERROR_OBJECT(self, "cannot set profile, preset, tune to parameter: %d",
                     ret);

    ret = -1;
    // goto ERR;
  }

  priv->xeve_cdsc->param.rc_type = XEVE_RC_CQP;
  // XEVE_RC_ABR;

  g_print("File: %s | Function: %s | Line: %d\n", __FILE__, __func__, __LINE__);

// Create the XEVE encoder - CORRECTION: pass xeve_param, not xeve_cdsc
// priv->xeve_handle = xeve_create(priv->xeve_param, &err);
#ifdef DEBUG

  g_print("priv->xeve_cdsc %x \n", priv->xeve_cdsc);
  g_print("priv->xeve_cdsc->max_bs_buf_size %d \n",
          priv->xeve_cdsc->max_bs_buf_size);
  print_xeve_param(&priv->xeve_cdsc->param);

#endif

  if (ret = xeve_param_check(&priv->xeve_cdsc->param)) {

    GST_ERROR_OBJECT(self, "invalid configuration: %d", ret);
    ret = -1;
    // goto ERR;
  }

  // XEVE               id = NULL;

  priv->xeve_handle = xeve_create(priv->xeve_cdsc, &err);
  if (!priv->xeve_handle) {
    GST_ERROR_OBJECT(self, "cannot create XEVE encoder: %d", err);
  }
#ifdef false
  /* create encoder */
  // id = xeve_create(priv->xeve_cdsc, NULL);
  if (id == NULL) {
    g_print("cannot create XEVE encoder\n");
    // ret = -1; goto ERR;
  }
#endif

  if (!priv->xeve_handle || err != XEVE_OK) {
    GST_ERROR_OBJECT(self, "Failed to initialize XEVE encoder (err=%d)", err);
    return FALSE;
  }
  ret = set_extra_config(priv->xeve_handle, &priv->xeve_cdsc->param);
  if (ret) {
    GST_ERROR_OBJECT(self, "cannot set extra configurations (ret=%d)", ret);
    // ret = -1; goto ERR;
  }

  priv->encoder_initialized = TRUE;
  GST_INFO_OBJECT(self, "XEVE encoder initialized successfully: %dx%d", width,
                  height);

  // Set the output caps
  GstVideoCodecState *output_state;
  GstCaps *output_caps;

  output_caps = gst_caps_new_simple(
      "video/x-xeve", "width", G_TYPE_INT, width, "height", G_TYPE_INT, height,
      "framerate", GST_TYPE_FRACTION, fps_n, fps_d, "stream-format",
      G_TYPE_STRING, "byte-stream", "alignment", G_TYPE_STRING, "au", NULL);

  output_state =
      gst_video_encoder_set_output_state(encoder, output_caps, state);
  gst_video_codec_state_unref(output_state);

  return TRUE;
}
#if 0
static int buffertoimgb(GstBuffer *buffer, XEVE_IMGB *img, int width, int height)
{
    int f_w, f_h;
    int y_size, u_size, v_size;
    unsigned char *p8;
    GstMapInfo map_info;
    unsigned char *buffer_data;
    size_t buffer_size;
    size_t offset = 0;

    /* Map the GstBuffer to access its data */
    if (!gst_buffer_map(buffer, &map_info, GST_MAP_READ)) {
        logerr("Failed to map GstBuffer\n");
        return -1;
    }

    buffer_data = map_info.data;
    buffer_size = map_info.size;

    

    /* reading YUV format */
    int chroma_format = XEVE_CS_GET_FORMAT(img->cs);
    int bit_depth = XEVE_CS_GET_BIT_DEPTH(img->cs);
    int w_shift = (chroma_format == XEVE_CF_YCBCR420) || (chroma_format == XEVE_CF_YCBCR422) ? 1 : 0;
    int h_shift = chroma_format == XEVE_CF_YCBCR420 ? 1 : 0;

    if (bit_depth == 8) {
        f_w = width;
        f_h = height;
    } else if (bit_depth >= 10 && bit_depth <= 14) {
        f_w = width * sizeof(short);
        f_h = height;
    } else {
        logerr("not supported color space\n");
        gst_buffer_unmap(buffer, &map_info);
        return -1;
    }

    /* Read Y component */
    p8 = (unsigned char*)img->a[0];
    for (int j = 0; j < f_h; j++) {
        if (offset + f_w > buffer_size) {
            gst_buffer_unmap(buffer, &map_info);
            return -1;
        }
        
        memcpy(p8, buffer_data + offset, f_w);
        offset += f_w;
        p8 += img->s[0];
    }

    /* Read U and V components if not grayscale */
    if (chroma_format != XEVE_CF_YCBCR400) {
        f_w = f_w >> w_shift;
        f_h = f_h >> h_shift;

        /* Read U component */
        p8 = (unsigned char*)img->a[1];
        for (int j = 0; j < f_h; j++) {
            if (offset + f_w > buffer_size) {
                gst_buffer_unmap(buffer, &map_info);
                return -1;
            }
            
            memcpy(p8, buffer_data + offset, f_w);
            offset += f_w;
            p8 += img->s[1];
        }

        /* Read V component */
        p8 = (unsigned char*)img->a[2];
        for (int j = 0; j < f_h; j++) {
            if (offset + f_w > buffer_size) {
                gst_buffer_unmap(buffer, &map_info);
                return -1;
            }
            
            memcpy(p8, buffer_data + offset, f_w);
            offset += f_w;
            p8 += img->s[2];
        }
    }

    /* Unmap the buffer */
    gst_buffer_unmap(buffer, &map_info);
    return 0;
}
#endif
#if 1

typedef struct {
  GstBuffer *y_buffer;
  GstBuffer *u_buffer;
  GstBuffer *v_buffer;
} I420Planes;

I420Planes extract_i420_planes(GstBuffer *buffer, GstVideoInfo *info) {
  I420Planes planes = {NULL, NULL, NULL};
  GstMapInfo map;

  // Verify format is I420
  if (GST_VIDEO_INFO_FORMAT(info) != GST_VIDEO_FORMAT_I420) {
    GST_ERROR("Buffer is not in I420 format");
    return planes;
  }

  // Map the source buffer
  if (!gst_buffer_map(buffer, &map, GST_MAP_READ)) {
    GST_ERROR("Failed to map source buffer");
    return planes;
  }

  // Get video dimensions
  const guint width = GST_VIDEO_INFO_WIDTH(info);
  const guint height = GST_VIDEO_INFO_HEIGHT(info);

  // Calculate plane sizes (I420 has 2x2 chroma subsampling)
  const gsize y_size = width * height;
  const gsize uv_size = (width / 2) * (height / 2);

  // Get strides
  const gsize y_stride = GST_VIDEO_INFO_PLANE_STRIDE(info, 0);
  const gsize u_stride = GST_VIDEO_INFO_PLANE_STRIDE(info, 1);
  const gsize v_stride = GST_VIDEO_INFO_PLANE_STRIDE(info, 2);

  // Get plane offsets (more reliable than assuming layout)
  const gsize y_offset = GST_VIDEO_INFO_PLANE_OFFSET(info, 0);
  const gsize u_offset = GST_VIDEO_INFO_PLANE_OFFSET(info, 1);
  const gsize v_offset = GST_VIDEO_INFO_PLANE_OFFSET(info, 2);

  // Get plane pointers
  guint8 *y_src = map.data + y_offset;
  guint8 *u_src = map.data + u_offset;
  guint8 *v_src = map.data + v_offset;

  // Create destination buffers
  planes.y_buffer = gst_buffer_new_allocate(NULL, y_size, NULL);
  planes.u_buffer = gst_buffer_new_allocate(NULL, uv_size, NULL);
  planes.v_buffer = gst_buffer_new_allocate(NULL, uv_size, NULL);

  // Map destination buffers
  GstMapInfo y_map, u_map, v_map;
  if (gst_buffer_map(planes.y_buffer, &y_map, GST_MAP_WRITE) &&
      gst_buffer_map(planes.u_buffer, &u_map, GST_MAP_WRITE) &&
      gst_buffer_map(planes.v_buffer, &v_map, GST_MAP_WRITE)) {

    // Copy Y plane (handle stride if needed)
    for (guint i = 0; i < height; i++) {
      memcpy(y_map.data + i * width, y_src + i * y_stride, width);
    }

    // Copy U plane (chroma is subsampled)
    for (guint i = 0; i < height / 2; i++) {
      memcpy(u_map.data + i * (width / 2), u_src + i * u_stride, width / 2);
    }

    // Copy V plane (chroma is subsampled)
    for (guint i = 0; i < height / 2; i++) {
      memcpy(v_map.data + i * (width / 2), v_src + i * v_stride, width / 2);
    }

    // Unmap destination buffers
    gst_buffer_unmap(planes.u_buffer, &u_map);
    gst_buffer_unmap(planes.v_buffer, &v_map);
    gst_buffer_unmap(planes.y_buffer, &y_map);
  } else {
    // Cleanup if mapping failed
    GST_ERROR("Failed to map destination buffers");
    gst_buffer_unref(planes.y_buffer);
    gst_buffer_unref(planes.u_buffer);
    gst_buffer_unref(planes.v_buffer);
    planes.y_buffer = planes.u_buffer = planes.v_buffer = NULL;
  }

  // Unmap source buffer
  gst_buffer_unmap(buffer, &map);

  return planes;
}

#endif

void display_XEVE_Img(XEVE_IMGB *img) {
  if (!img) {
    g_print("XEVE_IMGB is NULL\n");
    return;
  }

  g_print("XEVE_IMGB details:\n");
  g_print("Number of planes: %d\n", img->np);
  g_print("Color space: %d\n", img->cs);
  for (int i = 0; i < img->np; i++) {
    g_print("Plane %d: width=%d, height=%d, stride=%d\n", i, img->w[i],
            img->h[i], img->s[i]);
    g_print("Plane %d: x=%d, y=%d, e=%d\n", i, img->x[i], img->y[i], img->e[i]);

    g_print("Plane %d: aw=%d, ah=%d \n", i, img->aw[i], img->aw[i]);
    g_print("Plane %d: padl=%d, padr=%d padu=%d, padb=%d \n", i, img->padl[i],
            img->padl[i], img->padu[i], img->padb[i]);
    g_print("Plane %d:  actual allocated buffer size  bsize=%d\n", i,
            img->bsize[i]);
    /* time-stamps */
    // XEVE_MTIME          ts[XEVE_TS_NUM];
    /*
    XEVE_IMGB details:
  Number of planes: 3
  Color space: 2571
  Plane 0: width=352, height=288, stride=352
  Plane 0: x=0, y=0, e=288
  Plane 0: aw=352, ah=352
  Plane 0: padl=0, padr=0 padu=0, padb=0
  Plane 0:  actual allocated buffer size  bsize=202752
  Plane 1: width=176, height=144, stride=176
  Plane 1: x=0, y=0, e=144
  Plane 1: aw=176, ah=176
  Plane 1: padl=0, padr=0 padu=0, padb=0
  Plane 1:  actual allocated buffer size  bsize=50688
  Plane 2: width=176, height=144, stride=176
  Plane 2: x=0, y=0, e=144
  Plane 2: aw=176, ah=176
  Plane 2: padl=0, padr=0 padu=0, padb=0
  Plane 2:  actual allocated buffer size  bsize=50688

    */
  }
}

#if 1
// Fixed gstbuffer_to_xeve_imgb function
int gstbuffer_to_xeve_imgb_new(FILE *file, FILE *fileY, FILE *fileU,
                               FILE *fileV, GstBuffer *gst_buffer,
                               GstVideoInfo *video_info, XEVE_IMGB *imgb,
                               gint in_chroma_format, gint in_bit_depth) {
  GstMapInfo map, map_Y, map_U, map_V;

  guint8 *src_data;
  gint width, height;
  gint y_stride, u_stride, v_stride;
  gsize y_offset, u_offset, v_offset;
  gint bytes_per_pixel;

  GstBuffer *tmp_gst_buffer;

  tmp_gst_buffer = gst_buffer_copy_region(gst_buffer, GST_BUFFER_COPY_ALL,
                                          0, // offset
                                          gst_buffer_get_size(gst_buffer));

  if (!gst_buffer || !video_info || !imgb) {
    return -1;
  }

  // Map the GStreamer buffer for reading
  if (!gst_buffer_map(gst_buffer, &map, GST_MAP_READ)) {
    GST_ERROR("Failed to map input buffer");
    return -1;
  }

  I420Planes planes = extract_i420_planes(tmp_gst_buffer, video_info);

  if (planes.y_buffer && planes.u_buffer && planes.v_buffer) {
    // Use the separated planes...

    // Map the GStreamer buffer for reading
    if (!gst_buffer_map(planes.y_buffer, &map_Y, GST_MAP_READ)) {
      GST_ERROR("Failed to map input buffer");
      return -1;
    }

    // Map the GStreamer buffer for reading
    if (!gst_buffer_map(planes.u_buffer, &map_U, GST_MAP_READ)) {
      GST_ERROR("Failed to map input buffer");
      return -1;
    }

    // Map the GStreamer buffer for reading
    if (!gst_buffer_map(planes.v_buffer, &map_V, GST_MAP_READ)) {
      GST_ERROR("Failed to map input buffer");
      return -1;
    }

    if (file) {
      fwrite(map_Y.data, map_Y.size, 1, fileY);
    }

    if (file) {
      fwrite(map_U.data, map_U.size, 1, fileU);
    }

    if (file) {
      fwrite(map_V.data, map_V.size, 1, fileV);
    }

    // Remember to unref when done
    gst_buffer_unref(planes.y_buffer);
    gst_buffer_unref(planes.u_buffer);
    gst_buffer_unref(planes.v_buffer);
  }

  width = GST_VIDEO_INFO_WIDTH(video_info);
  height = GST_VIDEO_INFO_HEIGHT(video_info);
  src_data = map.data;

  if (file) {
    fwrite(map.data, map.size, 1, file);
  }

  bytes_per_pixel = 1;

  // Get plane information from GStreamer
  y_stride = GST_VIDEO_INFO_PLANE_STRIDE(video_info, 0);
  y_offset = GST_VIDEO_INFO_PLANE_OFFSET(video_info, 0);

  // Configure imgb based on format
  switch (GST_VIDEO_INFO_FORMAT(video_info)) {
  case GST_VIDEO_FORMAT_I420:
  case GST_VIDEO_FORMAT_YV12:
    imgb->np = 3;
    imgb->cs = in_chroma_format;

    // Y plane
    imgb->w[0] = width;
    imgb->h[0] = height;
    imgb->s[0] = ALIGN_VAL(width, 16); // XEVE alignment requirement

    // U and V planes
    imgb->w[1] = imgb->w[2] = width / 2;
    imgb->h[1] = imgb->h[2] = height / 2;
    imgb->s[1] = imgb->s[2] = ALIGN_VAL((width / 2), 16);

    u_stride = GST_VIDEO_INFO_PLANE_STRIDE(video_info, 1);
    v_stride = GST_VIDEO_INFO_PLANE_STRIDE(video_info, 2);
    u_offset = GST_VIDEO_INFO_PLANE_OFFSET(video_info, 1);
    v_offset = GST_VIDEO_INFO_PLANE_OFFSET(video_info, 2);
    break;

  case GST_VIDEO_FORMAT_NV12:
    imgb->np = 2;
    imgb->cs = in_chroma_format;

    // Y plane
    imgb->w[0] = width;
    imgb->h[0] = height;
    imgb->s[0] = ALIGN_VAL(width, 16);

    // UV plane
    imgb->w[1] = width;
    imgb->h[1] = height / 2;
    imgb->s[1] = ALIGN_VAL(width, 16);

    u_stride = GST_VIDEO_INFO_PLANE_STRIDE(video_info, 1);
    u_offset = GST_VIDEO_INFO_PLANE_OFFSET(video_info, 1);
    break;

  default:
    GST_ERROR("Unsupported format");
    gst_buffer_unmap(gst_buffer, &map);
    return -2;
  }

  // Copie du plan Y
  memcpy(imgb->a[0], map_Y.data, map_Y.size);

  // Copie du plan U
  memcpy(imgb->a[1], map_U.data, map_U.size);

  // Copie du plan V
  memcpy(imgb->a[2], map_V.data, map_V.size);

  // Set timestamps
  if (GST_BUFFER_PTS_IS_VALID(gst_buffer)) {
    imgb->ts[0] = GST_BUFFER_PTS(gst_buffer);
  }
  if (GST_BUFFER_DTS_IS_VALID(gst_buffer)) {
    imgb->ts[1] = GST_BUFFER_DTS(gst_buffer);
  }

  imgb->refcnt = 1;

  // Unmap the buffer now that we've copied the data
  gst_buffer_unmap(gst_buffer, &map);

  return 0;
}
#else
int gstbuffer_to_xeve_imgb_new(GstBuffer *gst_buffer, GstVideoInfo *video_info,
                               XEVE_IMGB *imgb, gint in_chroma_format,
                               gint in_bit_depth) {
  GstMapInfo map;
  guint8 *src_data;
  gint width, height;
  gint y_stride, u_stride, v_stride;
  gsize y_offset, u_offset, v_offset;
  gint bytes_per_pixel;

  if (!gst_buffer || !video_info || !imgb) {
    return -1;
  }

  // Map the GStreamer buffer for reading
  if (!gst_buffer_map(gst_buffer, &map, GST_MAP_READ)) {
    GST_ERROR("Failed to map input buffer");
    return -1;
  }

  width = GST_VIDEO_INFO_WIDTH(video_info);
  height = GST_VIDEO_INFO_HEIGHT(video_info);
  src_data = map.data;

  // Pour les formats YUV standard, bytes_per_pixel = 1
  // Le in_bit_depth est pour la configuration XEVE, pas pour la copie GStreamer
  bytes_per_pixel = 1;

  GST_DEBUG("Buffer size: %zu bytes", map.size);

  // Get plane information from GStreamer
  y_stride = GST_VIDEO_INFO_PLANE_STRIDE(video_info, 0);
  y_offset = GST_VIDEO_INFO_PLANE_OFFSET(video_info, 0);

  // Debug: afficher les informations du format
  GST_DEBUG("Format: %s, Width: %d, Height: %d",
            gst_video_format_to_string(GST_VIDEO_INFO_FORMAT(video_info)),
            width, height);
  GST_DEBUG("Y: stride=%d, offset=%zu", y_stride, y_offset);

  // Configure imgb based on format
  switch (GST_VIDEO_INFO_FORMAT(video_info)) {
  case GST_VIDEO_FORMAT_I420:
  case GST_VIDEO_FORMAT_YV12:
    imgb->np = 3;
    imgb->cs = in_chroma_format;

    // Y plane
    imgb->w[0] = width;
    imgb->h[0] = height;
    imgb->s[0] = ALIGN_VAL(width, 16); // XEVE alignment requirement

    // U and V planes
    imgb->w[1] = imgb->w[2] = width / 2;
    imgb->h[1] = imgb->h[2] = height / 2;
    imgb->s[1] = imgb->s[2] = ALIGN_VAL(width / 2, 16);

    // Utiliser les offsets et strides de GStreamer
    u_stride = GST_VIDEO_INFO_PLANE_STRIDE(video_info, 1);
    v_stride = GST_VIDEO_INFO_PLANE_STRIDE(video_info, 2);
    u_offset = GST_VIDEO_INFO_PLANE_OFFSET(video_info, 1);
    v_offset = GST_VIDEO_INFO_PLANE_OFFSET(video_info, 2);

    // Mais aussi calculer manuellement pour comparaison
    gsize calculated_u_offset = y_stride * height;
    gsize calculated_v_offset = calculated_u_offset + (u_stride * height / 2);

    GST_DEBUG("I420/YV12 - GStreamer offsets: U=%zu, V=%zu", u_offset,
              v_offset);
    GST_DEBUG("I420/YV12 - Calculated offsets: U=%zu, V=%zu",
              calculated_u_offset, calculated_v_offset);

    // Utiliser les offsets calculés si ceux de GStreamer semblent incorrects
    if (u_offset < y_stride * height ||
        v_offset < u_offset + (width / 2) * (height / 2)) {
      GST_WARNING("GStreamer offsets seem incorrect, using calculated ones");
      u_offset = calculated_u_offset;
      v_offset = calculated_v_offset;
    }

    GST_DEBUG("Final - U: stride=%d, offset=%zu, V: stride=%d, offset=%zu",
              u_stride, u_offset, v_stride, v_offset);
    break;

  case GST_VIDEO_FORMAT_NV12:
    imgb->np = 2;
    imgb->cs = in_chroma_format;

    // Y plane
    imgb->w[0] = width;
    imgb->h[0] = height;
    imgb->s[0] = ALIGN_VAL(width, 16);

    // UV plane (entrelacé)
    imgb->w[1] = width;
    imgb->h[1] = height / 2;
    imgb->s[1] = ALIGN_VAL(width, 16);

    u_stride = GST_VIDEO_INFO_PLANE_STRIDE(video_info, 1);
    u_offset = GST_VIDEO_INFO_PLANE_OFFSET(video_info, 1);

    GST_DEBUG("NV12 - UV: stride=%d, offset=%zu", u_stride, u_offset);
    break;

  default:
    GST_ERROR("Unsupported format");
    gst_buffer_unmap(gst_buffer, &map);
    return -2;
  }

  // Copy data plane by plane with proper stride handling
  for (int i = 0; i < imgb->np; i++) {
    gint src_stride, dst_stride, copy_width;
    guint8 *src_plane, *dst_plane;

    // Get source plane info
    switch (i) {
    case 0: // Y plane
      src_stride = y_stride;
      src_plane = src_data + y_offset;
      copy_width = width;
      // Vérification pour éviter le débordement
      if (copy_width > src_stride) {
        copy_width = src_stride;
      }
      GST_DEBUG("Plane %d (Y): src_plane offset=%zu, copy_width=%d", i,
                y_offset, copy_width);
      break;
    case 1: // U plane (ou UV pour NV12)
      src_stride = u_stride;
      src_plane = src_data + u_offset;
      if (GST_VIDEO_INFO_FORMAT(video_info) == GST_VIDEO_FORMAT_NV12) {
        copy_width = width; // UV entrelacé
      } else {
        copy_width = width / 2; // Plans U séparés
      }
      GST_DEBUG("Plane %d (U/UV): src_plane offset=%zu, copy_width=%d", i,
                u_offset, copy_width);
      break;
    case 2: // V plane (seulement pour I420/YV12)
      src_stride = v_stride;
      src_plane = src_data + v_offset;
      copy_width = width / 2;
      GST_DEBUG("Plane %d (V): src_plane offset=%zu, copy_width=%d", i,
                v_offset, copy_width);
      break;
    }

    dst_plane = imgb->a[i];
    dst_stride = imgb->s[i];

    // Vérification de sécurité
    if (!src_plane || !dst_plane) {
      GST_ERROR("Invalid plane pointer for plane %d", i);
      gst_buffer_unmap(gst_buffer, &map);
      return -3;
    }

    // Copy line by line to handle stride differences
    for (int y = 0; y < imgb->h[i]; y++) {
      // Vérification des limites pour éviter le débordement
      if ((src_plane + y * src_stride + copy_width) > (src_data + map.size)) {
        GST_ERROR("Copy would exceed buffer bounds for plane %d, line %d", i,
                  y);
        gst_buffer_unmap(gst_buffer, &map);
        return -4;
      }

      memcpy(dst_plane + y * dst_stride, src_plane + y * src_stride,
             copy_width);
    }

    // Set other imgb fields
    imgb->x[i] = imgb->y[i] = 0;
    imgb->aw[i] = imgb->w[i];
    imgb->ah[i] = imgb->h[i];
    imgb->padl[i] = imgb->padr[i] = imgb->padu[i] = imgb->padb[i] = 0;
    imgb->baddr[i] = imgb->a[i];
    imgb->bsize[i] = imgb->s[i] * imgb->h[i];
  }

  // Set timestamps
  if (GST_BUFFER_PTS_IS_VALID(gst_buffer)) {
    imgb->ts[0] = GST_BUFFER_PTS(gst_buffer);
  }
  if (GST_BUFFER_DTS_IS_VALID(gst_buffer)) {
    imgb->ts[1] = GST_BUFFER_DTS(gst_buffer);
  }

  imgb->refcnt = 1;

  // Unmap the buffer now that we've copied the data
  gst_buffer_unmap(gst_buffer, &map);

  return 0;
}
#endif

#if 0
int gstbuffer_to_xeve_imgb(GstBuffer *gst_buffer, GstVideoInfo *video_info, XEVE_IMGB *imgb)
{
    GstMapInfo map_info;
    
    if (!gst_buffer || !video_info || !imgb) {
        return -1;
    }
   // Map the GStreamer buffer
if (!gst_buffer_map(gst_buffer, &map_info, GST_MAP_READ)) {
    g_print("we can't map buffer\n");
    return -1;
}

// Initialize the XEVE_IMGB structure
memset(imgb, 0, sizeof(XEVE_IMGB));

// Set the color space according to the GStreamer format
switch (GST_VIDEO_INFO_FORMAT(video_info)) {
    case GST_VIDEO_FORMAT_I420:
    case GST_VIDEO_FORMAT_YV12:
        imgb->cs = 0; // YUV420 (value to be adjusted according to XEVE)
        imgb->np = 3; // Y, U, V planes
        break;
    case GST_VIDEO_FORMAT_NV12:
        imgb->cs = 1; // NV12 (value to be adjusted according to XEVE)
        imgb->np = 2; // Y, UV planes
        break;
    case GST_VIDEO_FORMAT_RGB:
    case GST_VIDEO_FORMAT_BGR:
        imgb->cs = 2; // RGB (value to be adjusted according to XEVE)
        imgb->np = 1; // Single plane
        break;
    default:
        gst_buffer_unmap(gst_buffer, &map_info);
        return -2; // Unsupported format
}

// Fill in the information for each plane
guint8 *data = map_info.data;
// gsize offset = 0;

for (int i = 0; i < imgb->np; i++) {
    // Compute the dimensions of the plane according to the format
    if (i == 0) { // Y plane or RGB
        imgb->w[i] = GST_VIDEO_INFO_WIDTH(video_info);
        imgb->h[i] = GST_VIDEO_INFO_HEIGHT(video_info);
    } else { // U/V planes for YUV formats
        switch (GST_VIDEO_INFO_FORMAT(video_info)) {
            case GST_VIDEO_FORMAT_I420:
            case GST_VIDEO_FORMAT_YV12:
                imgb->w[i] = GST_VIDEO_INFO_WIDTH(video_info) / 2;
                imgb->h[i] = GST_VIDEO_INFO_HEIGHT(video_info) / 2;
                break;
            case GST_VIDEO_FORMAT_NV12:
                if (i == 1) { // UV plane
                    imgb->w[i] = GST_VIDEO_INFO_WIDTH(video_info);
                    imgb->h[i] = GST_VIDEO_INFO_HEIGHT(video_info) / 2;
                }
                break;
            default:
                break;
        }
    }

    // Position (usually 0,0 for the full frame)
    imgb->x[i] = 0;
    imgb->y[i] = 0;

    // Compute the stride
    imgb->s[i] = GST_VIDEO_INFO_PLANE_STRIDE(video_info, i);

    // Data address of the plane with offset
    imgb->a[i] = data + GST_VIDEO_INFO_PLANE_OFFSET(video_info, i);

    // Aligned dimensions (often identical to normal dimensions)
    imgb->aw[i] = imgb->w[i];
    imgb->ah[i] = imgb->h[i];

    // Padding (usually 0 if no specific padding)
    imgb->padl[i] = 0;
    imgb->padr[i] = 0;
    imgb->padu[i] = 0;
    imgb->padb[i] = 0;

    // Buffer address and size
    imgb->baddr[i] = imgb->a[i];
    imgb->bsize[i] = imgb->s[i] * imgb->h[i];
}
 
    // Timestamps
    if (GST_BUFFER_PTS_IS_VALID(gst_buffer)) {
        imgb->ts[0] = GST_BUFFER_PTS(gst_buffer);
    }
    if (GST_BUFFER_DTS_IS_VALID(gst_buffer)) {
        imgb->ts[1] = GST_BUFFER_DTS(gst_buffer);
    }
    
    // Gestion du cycle de vie
    imgb->refcnt = 1;
    
    // Note: Ne pas unmapper le buffer ici car XEVE_IMGB pointe vers ses données
    // Le unmap devra être fait après utilisation de imgb
    
    return 0;
}
#else

int gstbuffer_to_xeve_imgb(GstBuffer *gst_buffer, GstVideoInfo *video_info,
                           XEVE_IMGB *imgb, gint in_chromat_format,
                           gint in_bit_depth) {
  GstMapInfo map;
  guint8 *data;

  gint y_stride, u_stride, v_stride;
  gsize y_offset, u_offset, v_offset;
  gsize y_size;
  gsize u_size;
  gsize v_size;
  gint width;
  gint height;

  guint8 *src_data, *dst_data;

  gint chroma_format = XEVE_CS_GET_FORMAT(in_chromat_format);
  gint bit_depth = in_bit_depth;
  // XEVE_CS_GET_BIT_DEPTH(in_chromat_format);
  gint w_shift =
      (chroma_format == XEVE_CF_YCBCR420) || (chroma_format == XEVE_CF_YCBCR422)
          ? 1
          : 0;
  gint h_shift = chroma_format == XEVE_CF_YCBCR420 ? 1 : 0;

  if (!gst_buffer || !video_info || !imgb) {
    return -1;
  }
  // Map the GStreamer buffer
  if (!gst_buffer_map(gst_buffer, &map, GST_MAP_READ)) {
    g_print("we can't map buffer\n");
    return -1;
  }

  width = GST_VIDEO_INFO_WIDTH(video_info);
  height = GST_VIDEO_INFO_HEIGHT(video_info);

  // Get strides and offsets for each plane
  y_stride = GST_VIDEO_INFO_PLANE_STRIDE(video_info, 0);
  u_stride = GST_VIDEO_INFO_PLANE_STRIDE(video_info, 1);
  v_stride = GST_VIDEO_INFO_PLANE_STRIDE(video_info, 2);

  y_offset = GST_VIDEO_INFO_PLANE_OFFSET(video_info, 0);
  u_offset = GST_VIDEO_INFO_PLANE_OFFSET(video_info, 1);
  v_offset = GST_VIDEO_INFO_PLANE_OFFSET(video_info, 2);

#if DEBUG

  g_print("chroma_format %d bit_depth %d w_shift %d h_shift %d n",
          chroma_format, bit_depth, w_shift, h_shift);

#endif

  // Initialize the XEVE_IMGB structure
  // memset(imgb, 0, sizeof(XEVE_IMGB));

#if 0
// Set the color space according to the GStreamer format
switch (GST_VIDEO_INFO_FORMAT(video_info)) {
    case GST_VIDEO_FORMAT_I420:
    case GST_VIDEO_FORMAT_YV12:
        imgb->cs = 0; // YUV420 (value to be adjusted according to XEVE)
        imgb->np = 3; // Y, U, V planes
        break;
    case GST_VIDEO_FORMAT_NV12:
        imgb->cs = 1; // NV12 (value to be adjusted according to XEVE)
        imgb->np = 2; // Y, UV planes
        break;
    case GST_VIDEO_FORMAT_RGB:
    case GST_VIDEO_FORMAT_BGR:
        imgb->cs = 2; // RGB (value to be adjusted according to XEVE)
        imgb->np = 1; // Single plane
        break;
    default:
        gst_buffer_unmap(gst_buffer, &map_info);
        return -2; // Unsupported format
}
#else

  // Set the color space according to the GStreamer format
  switch (GST_VIDEO_INFO_FORMAT(video_info)) {
  case GST_VIDEO_FORMAT_I420:
  case GST_VIDEO_FORMAT_YV12:
    imgb->cs = 0; // YUV420 (value to be adjusted according to XEVE)
    imgb->np = 3; // Y, U, V planes
    break;
  case GST_VIDEO_FORMAT_NV12:
    imgb->cs = 1; // NV12 (value to be adjusted according to XEVE)
    imgb->np = 2; // Y, UV planes
    break;
  default:
    gst_buffer_unmap(gst_buffer, &map);
    return -2; // Unsupported format
  }

#if 1
  // Calculate plane sizes
  switch (GST_VIDEO_INFO_FORMAT(video_info)) {
  case GST_VIDEO_FORMAT_I420:
  case GST_VIDEO_FORMAT_YV12:
    y_size = height * y_stride;
    u_size = (height / 2) * u_stride;
    v_size = (height / 2) * v_stride;
    imgb->cs = 0; // YUV420 (value to be adjusted according to XEVE)
    imgb->np = 3; // Y, U, V planes
    break;
  case GST_VIDEO_FORMAT_Y42B:
    y_size = height * y_stride;
    u_size = height * u_stride;
    v_size = height * v_stride;
    break;
  case GST_VIDEO_FORMAT_Y444:
    y_size = height * y_stride;
    u_size = height * u_stride;
    v_size = height * v_stride;
    break;
  default:
    g_warning("Unsupported YUV format");
    gst_buffer_unmap(gst_buffer, &map);
    return FALSE;
  }
#else

  // Calculate actual data sizes (without padding)
  switch (GST_VIDEO_INFO_FORMAT(video_info)) {
  case GST_VIDEO_FORMAT_I420:
  case GST_VIDEO_FORMAT_YV12:
    y_size = height * width;
    u_size = (height / 2) * (width / 2);
    v_size = (height / 2) * (width / 2);
    break;
  case GST_VIDEO_FORMAT_Y42B:
    y_size = height * width;
    u_size = height * (width / 2);
    v_size = height * (width / 2);
    break;
  case GST_VIDEO_FORMAT_Y444:
    y_size = height * width;
    u_size = height * width;
    v_size = height * width;
    break;
  default:
    g_warning("Unsupported YUV format");
    gst_buffer_unmap(gst_buffer, &map);
    return FALSE;
  }

#endif

#endif

  // Fill in the information for each plane
  data = map.data;
  // gsize offset = 0;

  for (int i = 0; i < imgb->np; i++) {
    // Compute the dimensions of the plane according to the format
    if (i == 0) { // Y plane or RGB
      imgb->w[i] = GST_VIDEO_INFO_WIDTH(video_info);
      imgb->h[i] = GST_VIDEO_INFO_HEIGHT(video_info);
    } else { // U/V planes for YUV formats
      switch (GST_VIDEO_INFO_FORMAT(video_info)) {
      case GST_VIDEO_FORMAT_I420:
      case GST_VIDEO_FORMAT_YV12:
        imgb->w[i] = GST_VIDEO_INFO_WIDTH(video_info) / 2;
        imgb->h[i] = GST_VIDEO_INFO_HEIGHT(video_info) / 2;
        break;
      case GST_VIDEO_FORMAT_NV12:
        if (i == 1) { // UV plane
          imgb->w[i] = GST_VIDEO_INFO_WIDTH(video_info);
          imgb->h[i] = GST_VIDEO_INFO_HEIGHT(video_info) / 2;
        }
        break;
      default:
        break;
      }
    }
#if 1

    // Copies entire planes including any padding bytes. This is faster but may
    // include stride padding.
    //  Copy Y plane
    memcpy(imgb->a[0], data + y_offset, y_size);

    // Copy U plane
    memcpy(imgb->a[1], data + u_offset, u_size);

    // Copy V plane
    memcpy(imgb->a[2], data + v_offset, v_size);
#else

    // Copy Y plane line by line (handle stride properly)
    dst_data = imgb->a[0];
    for (i = 0; i < height; i++) {
      memcpy(imgb->a[0], data + y_offset + (i * y_stride), width);
      imgb->a[0] += width;
    }
    // Copy U plane line by line
    gint u_height =
        (GST_VIDEO_INFO_FORMAT(video_info) == GST_VIDEO_FORMAT_I420 ||
         GST_VIDEO_INFO_FORMAT(video_info) == GST_VIDEO_FORMAT_YV12)
            ? height / 2
            : height;
    gint u_width = (GST_VIDEO_INFO_FORMAT(video_info) == GST_VIDEO_FORMAT_Y444)
                       ? width
                       : width / 2;
    dst_data = imgb->a[1];
    for (i = 0; i < u_height; i++) {
      memcpy(imgb->a[1], data + u_offset + (i * u_stride), u_width);
      imgb->a[1] += u_width;
    }
    // Copy V plane line by line

    gint v_height =
        (GST_VIDEO_INFO_FORMAT(video_info) == GST_VIDEO_FORMAT_I420 ||
         GST_VIDEO_INFO_FORMAT(video_info) == GST_VIDEO_FORMAT_YV12)
            ? height / 2
            : height;
    gint v_width = (GST_VIDEO_INFO_FORMAT(video_info) == GST_VIDEO_FORMAT_Y444)
                       ? width
                       : width / 2;
    dst_data = imgb->a[2];
    for (i = 0; i < v_height; i++) {
      memcpy(imgb->a[2], data + v_offset + (i * v_stride), v_width);
      imgb->a[2] += v_width;
    }

#endif

    // Position (usually 0,0 for the full frame)
    imgb->x[i] = 0;
    imgb->y[i] = 0;

    // Compute the stride
    imgb->s[i] = GST_VIDEO_INFO_PLANE_STRIDE(video_info, i);

    // Data address of the plane with offset
    imgb->a[i] = data + GST_VIDEO_INFO_PLANE_OFFSET(video_info, i);

    // Aligned dimensions (often identical to normal dimensions)
    imgb->aw[i] = imgb->w[i];
    imgb->ah[i] = imgb->h[i];

    // Padding (usually 0 if no specific padding)
    imgb->padl[i] = 0;
    imgb->padr[i] = 0;
    imgb->padu[i] = 0;
    imgb->padb[i] = 0;

    // Buffer address and size
    imgb->baddr[i] = imgb->a[i];
    imgb->bsize[i] = imgb->s[i] * imgb->h[i];
  }

  // Timestamps
  if (GST_BUFFER_PTS_IS_VALID(gst_buffer)) {
    imgb->ts[0] = GST_BUFFER_PTS(gst_buffer);
  }
  if (GST_BUFFER_DTS_IS_VALID(gst_buffer)) {
    imgb->ts[1] = GST_BUFFER_DTS(gst_buffer);
  }

  // Gestion du cycle de vie
  imgb->refcnt = 1;

  // Note: Ne pas unmapper le buffer ici car XEVE_IMGB pointe vers ses données
  // Le unmap devra être fait après utilisation de imgb

  return 0;
}

#endif

#if 0
typedef struct {
    XEVE_IMGB img_buf;
    GstMapInfo map_info;  // Store the mapping info
} XEVE_IMGB_Wrapper;

int gstbuffer_to_xeve_imgb(GstBuffer *gst_buffer, GstVideoInfo *video_info, XEVE_IMGB_Wrapper *wrapper)
{
    if (!gst_buffer || !video_info || !wrapper) {
        return -1;
    }
    
    memset(&wrapper->img_buf, 0, sizeof(XEVE_IMGB));
    memset(&wrapper->map_info, 0, sizeof(GstMapInfo));
    
    if (!gst_buffer_map(gst_buffer, &wrapper->map_info, GST_MAP_READ)) {
        GST_ERROR("Failed to map input buffer");
        return -1;
    }
    
    // Rest of the conversion code as before, but operating on wrapper->img_buf
    // ...
    
    return 0;
}
#endif
static int imgb_read_from_gstbuffer(GstBuffer *input_buffer,
                                    GstVideoInfo *video_info, XEVE_IMGB *imgb,
                                    int chromat) {
  unsigned char *p8;
  int i, j, bd;
  int cs_w_off, cs_h_off;
  GstMapInfo map_info;
  int chroma_format = XEVE_CS_GET_FORMAT(chromat);
  int bit_depth = XEVE_CS_GET_BIT_DEPTH(chromat);
  int plane_width, plane_height;
  gsize plane_offset;

  GST_DEBUG("bit_depth %d bytes", bit_depth);

  bit_depth = 8;

  // Mapper le buffer GStreamer pour lecture
  if (!gst_buffer_map(input_buffer, &map_info, GST_MAP_READ)) {
    GST_ERROR("Failed to map GstBuffer for reading");
    return -1;
  }

  // Déterminer les paramètres selon la profondeur de bits
  if (bit_depth == 8) {
    bd = 1;
  } else if (bit_depth >= 10 && bit_depth <= 14) {
    bd = 2;
  } else {
    GST_ERROR("Unsupported bit depth: %d", bit_depth);
    gst_buffer_unmap(input_buffer, &map_info);
    return -1;
  }

  // Vérifier la taille totale du buffer
  GST_DEBUG("Buffer size: %zu bytes, expected for format: %zu bytes",
            map_info.size, GST_VIDEO_INFO_SIZE(video_info));

  // Copier les données depuis le buffer vers chaque plan de l'image XEVE
  for (i = 0; i < imgb->np && i < GST_VIDEO_INFO_N_PLANES(video_info); i++) {
    // Utiliser les informations du GstVideoInfo pour les dimensions et offsets
    plane_width = GST_VIDEO_INFO_COMP_WIDTH(video_info, i);
    plane_height = GST_VIDEO_INFO_COMP_HEIGHT(video_info, i);
    plane_offset = GST_VIDEO_INFO_PLANE_OFFSET(video_info, i);

    GST_DEBUG("Plane %d: width=%d, height=%d, offset=%zu, stride=%d", i,
              plane_width, plane_height, plane_offset,
              GST_VIDEO_INFO_PLANE_STRIDE(video_info, i));

    // Vérifier que l'offset ne dépasse pas la taille du buffer
    if (plane_offset >= map_info.size) {
      GST_ERROR("Plane %d offset %zu exceeds buffer size %zu", i, plane_offset,
                map_info.size);
      gst_buffer_unmap(input_buffer, &map_info);
      return -1;
    }

    // Pointer vers le début du plan dans l'image XEVE
    p8 = (unsigned char *)imgb->a[i] + (imgb->s[i] * imgb->y[i]) +
         (imgb->x[i] * bd);
    // p8 = (unsigned char *)imgb->a[i];

    // adresse_base + (ligne * largeur_ligne) + (colonne * taille_pixel)

    GST_DEBUG("Plane %d: imgb->s[i]=%d, imgb->y[i]=%d, imgb->x[i]=%d", i,
              imgb->s[i], imgb->y[i], imgb->x[i]);

    // Copier ligne par ligne depuis le buffer GStreamer
    unsigned char *src_line = map_info.data + plane_offset;
    int src_stride = GST_VIDEO_INFO_PLANE_STRIDE(video_info, i);
    int copy_width = MIN(plane_width * bd, src_stride);

    for (j = 0; j < plane_height; j++) {
      // Vérifier que nous ne dépassons pas la fin du buffer
      if (src_line + copy_width > map_info.data + map_info.size) {
        GST_ERROR("Would read beyond buffer end at line %d of plane %d", j, i);
        gst_buffer_unmap(input_buffer, &map_info);
        return -1;
      }

      memcpy(p8, src_line, copy_width);
      src_line +=
          src_stride;   // Passer à la ligne suivante dans le buffer source
      p8 += imgb->s[i]; // Passer à la ligne suivante dans l'image XEVE
    }
  }

  // Démapper le buffer
  gst_buffer_unmap(input_buffer, &map_info);

  return 0;
}

// Version alternative qui utilise gst_video_frame pour une gestion plus simple
static int imgb_read_from_gstbuffer_frame(GstBuffer *input_buffer,
                                          GstVideoInfo *video_info,
                                          XEVE_IMGB *imgb, int chroma) {
  GstVideoFrame video_frame;
  unsigned char *p8;
  int i, j, bd;
  int bit_depth = XEVE_CS_GET_BIT_DEPTH(chroma);

  // Mapper le buffer comme un frame vidéo
  if (!gst_video_frame_map(&video_frame, video_info, input_buffer,
                           GST_MAP_READ)) {
    GST_ERROR("Failed to map video frame");
    return -1;
  }

  // Déterminer la taille des échantillons
  bd = (bit_depth <= 8) ? 1 : 2;

  // Copier chaque plan
  for (i = 0; i < imgb->np && i < GST_VIDEO_FRAME_N_PLANES(&video_frame); i++) {
    int plane_width = GST_VIDEO_FRAME_COMP_WIDTH(&video_frame, i);
    int plane_height = GST_VIDEO_FRAME_COMP_HEIGHT(&video_frame, i);
    int src_stride = GST_VIDEO_FRAME_PLANE_STRIDE(&video_frame, i);
    unsigned char *src_data = GST_VIDEO_FRAME_PLANE_DATA(&video_frame, i);

    // Pointer vers le plan de destination
    p8 = (unsigned char *)imgb->a[i] + (imgb->s[i] * imgb->y[i]) +
         (imgb->x[i] * bd);

    GST_DEBUG("Copying plane %d: %dx%d, src_stride=%d, dst_stride=%d", i,
              plane_width, plane_height, src_stride, imgb->s[i]);

    // Copier ligne par ligne
    for (j = 0; j < plane_height; j++) {
      memcpy(p8, src_data + j * src_stride, plane_width * bd);
      p8 += imgb->s[i];
    }
  }

  gst_video_frame_unmap(&video_frame);
  return 0;
}

#if 0
static GstFlowReturn gst_xeve_enc_handle_frame(GstVideoEncoder *encoder,
                                               GstVideoCodecFrame *frame) {
  GstXeveEnc *self = GST_XEVE_ENC(encoder);
  GstXeveEncPrivate *priv = GST_XEVE_ENC_GET_PRIVATE(self);
  GstVideoInfo *info = &priv->input_state->info;
  XEVE_IMGB img_buf = {0};
  XEVE_STAT stat; /* encoding status */

  XEVE_BITB bit_buf = {0};
  GstBuffer *out_buf = NULL;
  GstFlowReturn ret = GST_FLOW_OK;
  gint encoder_return;

  int err;
  GstMapInfo in_map, out_map;

  bit_buf.bsize = priv->xeve_cdsc->max_bs_buf_size;
  bit_buf.addr = priv->bs_buf;

#if 0    
    // Convert GstBuffer to XEVE_IMGB using the helper function
    if (gstbuffer_to_xeve_imgb(frame->input_buffer, info, self->imgb_rec, priv->xeve_cdsc->param.cs, self->bit_depth) != 0) {
        GST_ERROR_OBJECT(self, "Failed to convert GstBuffer to XEVE_IMGB");
        goto done;
    }
#else

  if (gstbuffer_to_xeve_imgb_new(self->fp, self->fp_Y, self->fp_U, self->fp_V,
                                 frame->input_buffer, info, self->imgb_rec,
                                 priv->xeve_cdsc->param.cs,
                                 self->bit_depth) != 0) {
    GST_ERROR_OBJECT(self, "Failed to convert GstBuffer to XEVE_IMGB");
    return GST_FLOW_ERROR;
  }

  imgb_write("outdump.yuv", self->imgb_rec, priv->xeve_cdsc->param.w,
             priv->xeve_cdsc->param.h);

  /*
      if( buffertoimgb(frame->input_buffer, self->imgb_rec, self->width,
     self->height) != 0) { GST_ERROR_OBJECT(self, "Failed to convert GstBuffer
     to XEVE_IMGB");
          //return GST_FLOW_ERROR;
      }
          */

#endif

  // Push frame to encoder
  err = xeve_push(priv->xeve_handle, self->imgb_rec);
  if (XEVE_FAILED(err)) {
    GST_ERROR_OBJECT(
        self, "xeve_push() Failed to push frame to encoder (err=%d)", err);
    ret = -1;
  }

  // Allocate output buffer - use the configured max bitstream size
  /*
  out_buf = gst_buffer_new_and_alloc(priv->xeve_cdsc->max_bs_buf_size);
  if (!out_buf) {
    GST_ERROR_OBJECT(self, "Failed to allocate output buffer");
    goto unmap_input;
  }


  // Map output buffer for writing
  if (!gst_buffer_map(out_buf, &out_map, GST_MAP_WRITE)) {
    GST_ERROR_OBJECT(self, "Failed to map output buffer");
    gst_buffer_unref(out_buf);
    goto unmap_input;
  }
  */

  GST_ERROR_OBJECT(self, "  bit_buf.bsize %ld out_map.size %ld \n",
                   bit_buf.bsize, out_map.size);

  // Set up bitstream buffer
  // bit_buf.addr = out_map.data;
  // bit_buf.bsize = out_map.size;

  // Encode the frame

  encoder_return = xeve_encode(priv->xeve_handle, &bit_buf, &stat);
  if (XEVE_FAILED(encoder_return)) {
    GST_ERROR_OBJECT(self, "Failed to encode frame (ret=%d)", encoder_return);
    ret = -1;
  }

  GST_ERROR_OBJECT(self, "  bit_buf.bsize %zu stat.write %d \n",
                   (size_t)bit_buf.bsize, stat.write);

  if (stat.write > 0 && stat.write < MAX_BITSTREAM_SIZE) {
    g_print("File: %s | Function: %s | Line: %d\n", __FILE__, __func__,
            __LINE__);

    out_buf = gst_buffer_new_allocate(NULL, stat.write, NULL);
    g_print("File: %s | Function: %s | Line: %d\n", __FILE__, __func__,
            __LINE__);

    gst_buffer_fill(out_buf, 0, bit_buf.addr, stat.write);
    g_print("File: %s | Function: %s | Line: %d\n", __FILE__, __func__,
            __LINE__);

    frame->output_buffer = out_buf;
    g_print("File: %s | Function: %s | Line: %d\n", __FILE__, __func__,
            __LINE__);

    gst_buffer_unref(out_buf);
    // Unmap output buffer immediately after encoding
    g_print("File: %s | Function: %s | Line: %d\n", __FILE__, __func__,
            __LINE__);

    // gst_buffer_unmap(out_buf, &out_map);
  }

  // Set up bitstream buffer
  // out_map.data = bit_buf.addr;
  // out_map.size = bit_buf.bsize;

  // Unmap output buffer immediately after encoding
  // gst_buffer_unmap(out_buf, &out_map);

  if (encoder_return == XEVE_OK_OUT_NOT_AVAILABLE) {

    // GST_INFO_OBJECT(self, "XEVE_OK_OUT_NOT_AVAILABLE (ret=%d)", ret);
    GST_DEBUG_OBJECT(
        self,
        "progress success, but output is not available temporarily (ret=%d)",
        ret);
    // We can't write this frame in output bitstream

    ret = 0;
    // continue;
  } else if (encoder_return == XEVE_OK) {

    // GST_INFO_OBJECT(self, "XEVE_OK (ret=%d)", ret);
    GST_INFO_OBJECT(self, "actual encoded size (size=%d)", stat.write);

    if (stat.write > 0) {
      // Resize buffer to actual encoded size
      // gst_buffer_resize(out_buf, 0, stat.write);

      // Set output buffer and finish frame processing
      // frame->output_buffer = out_buf;

      frame->pts = GST_BUFFER_PTS(frame->input_buffer);
      frame->duration = GST_BUFFER_DURATION(frame->input_buffer);
      

      ret = gst_video_encoder_finish_frame(encoder, frame);
      if (ret != GST_FLOW_OK) {
    GST_WARNING_OBJECT(encoder, "finish_frame() returned: %s", gst_flow_get_name(ret));
}

      priv->frame_number++;
      GST_DEBUG_OBJECT(self, " frame inc to bitstream %d)", priv->frame_number);
    }

  } else if (encoder_return == XEVE_OK_NO_MORE_FRM) {
    // break;
  } else {
    GST_INFO_OBJECT(self, "XEVE_OK (err=%d)", ret);
  }

  return ret;

unmap_input:
  // Unmap the input buffer if it was mapped by gstbuffer_to_xeve_imgb()
  if (img_buf.a[0]) { // Check if any plane was mapped
    gst_buffer_unmap(
        frame->input_buffer,
        (GstMapInfo *)img_buf.a[0]); // Need to store map_info properly
  }

done:
  return ret;
}
#else
static GstFlowReturn gst_xeve_enc_handle_frame(GstVideoEncoder *encoder,
                                               GstVideoCodecFrame *frame) {
  GstXeveEnc *self = GST_XEVE_ENC(encoder);
  GstXeveEncPrivate *priv = GST_XEVE_ENC_GET_PRIVATE(self);
  GstVideoInfo *info = &priv->input_state->info;
  XEVE_IMGB img_buf = {0};
  XEVE_STAT stat; /* encoding status */
  XEVE_BITB bit_buf = {0};
  GstBuffer *out_buf = NULL;
  GstFlowReturn ret = GST_FLOW_OK;
  gint encoder_return;
  int err;
  XEVE_CLK clk_beg, clk_end, clk_tot;
  clk_tot = 0;
  GstMapInfo map;
  char *type_I_P_B = NULL;

  // Initialize bitstream buffer
  // bit_buf.bsize = priv->xeve_cdsc->max_bs_buf_size;
  // bit_buf.addr = priv->bs_buf;

  // Convert GstBuffer to XEVE_IMGB
#if 1
  // priv->xeve_cdsc->param.cs = 2059;
  if (gstbuffer_to_xeve_imgb_new(self->fp, self->fp_Y, self->fp_U, self->fp_V,
                                 frame->input_buffer, info, self->imgb_rec,
                                 priv->xeve_cdsc->param.cs,
                                 self->bit_depth) != 0) {
    GST_ERROR_OBJECT(self, "Failed to convert GstBuffer to XEVE_IMGB");
    return GST_FLOW_ERROR;
  }
  display_XEVE_Img(self->imgb_rec);

#else
  // GstBuffer *input_buffer, GstVideoInfo *video_info, XEVE_IMGB *imgb, int
  // chroma

  imgb_read_from_gstbuffer(frame->input_buffer, info, self->imgb_rec,
                           priv->xeve_cdsc->param.cs);

#endif

  // Debug: write frame to file (remove in production)
  imgb_write("outdump.yuv", self->imgb_rec, priv->xeve_cdsc->param.w,
             priv->xeve_cdsc->param.h);

  // Push frame to encoder
  err = xeve_push(priv->xeve_handle, self->imgb_rec);
  if (XEVE_FAILED(err)) {
    GST_ERROR_OBJECT(
        self, "xeve_push() failed to push frame to encoder (err=%d)", err);
    return GST_FLOW_ERROR;
  }
  /* encoding */
  clk_beg = xeve_clk_get();

  // Encode the frame
  encoder_return = xeve_encode(priv->xeve_handle, &priv->bitb, &stat);
  if (XEVE_FAILED(encoder_return)) {
    GST_ERROR_OBJECT(self, "Failed to encode frame (ret=%d)", encoder_return);
    return GST_FLOW_ERROR;
  }

  clk_end = xeve_clk_from(clk_beg);
  clk_tot += clk_end;

  if (self->fp_bitstream && stat.write > 0) {
    // Write bitstream to file
    // fwrite(bit_buf.addr, 1, stat.write, self->fp_bitstream);
    // if(write_data("test.evc", priv->bs_buf, stat.write))
    if (write_data("test.evc", priv->bitb.addr, stat.write)) {
      GST_ERROR_OBJECT(self, "Failed to write bitstream to file");
      return GST_FLOW_ERROR;
    }
  }

  // GST_DEBUG_OBJECT(self, "Bitstream buffer size: %zu, bytes written: %d",
  //                  (size_t)bit_buf.bsize, stat.write);

  GST_DEBUG_OBJECT(self, "Bitstream buffer size: %zu, bytes written: %d",
                   (size_t)priv->bitb.bsize, stat.write);

  // Handle encoder return status
  if (encoder_return == XEVE_OK_OUT_NOT_AVAILABLE) {
    GST_DEBUG_OBJECT(
        self, "Encoding successful, but output not available temporarily");
    // No output available for this frame - this is normal for some frames
    // gst_video_encoder_finish_frame(encoder, frame);
    return GST_FLOW_OK;

  } else if (encoder_return == XEVE_OK) {
    GST_DEBUG_OBJECT(self, "Encoding successful, output size: %d bytes",
                     stat.write);
    priv->frame_number++;
    switch (stat.stype) {
    case XEVE_ST_I:
      type_I_P_B = "I";
      break;
    case XEVE_ST_P:
      type_I_P_B = "P";
      break;
    case XEVE_ST_B:
      type_I_P_B = "B";
      break;
    default:
      GST_DEBUG_OBJECT(self, "Frame type: Unknown");
      type_I_P_B = "Unknown";
      break;
    }

    GST_DEBUG_OBJECT(self,
                     "Frame type: %s / Frame number %d encoded successfully",
                     type_I_P_B, priv->frame_number);

    if (stat.write > 0 && stat.write < MAX_BITSTREAM_SIZE) {
      // Create output buffer with exact size needed
      out_buf = gst_buffer_new_allocate(NULL, stat.write, NULL);
      if (!out_buf) {
        GST_ERROR_OBJECT(self, "Failed to allocate output buffer");
        return GST_FLOW_ERROR;
      }

      if (gst_buffer_map(out_buf, &map, GST_MAP_WRITE)) {
        // Copy encoded data to output buffer
        memcpy(map.data, priv->bitb.addr, stat.write);
        gst_buffer_unmap(out_buf, &map);
      } else {
        GST_ERROR_OBJECT(self, "Failed to map output buffer");
        gst_buffer_unref(out_buf);
        return GST_FLOW_ERROR;
      }

      // Set timestamps
      GST_BUFFER_PTS(out_buf) = GST_BUFFER_PTS(frame->input_buffer);
      GST_BUFFER_DTS(out_buf) = GST_BUFFER_DTS(frame->input_buffer);
      GST_BUFFER_DURATION(out_buf) = GST_BUFFER_DURATION(frame->input_buffer);

      // Assign output buffer to frame
      frame->output_buffer = out_buf;

      // Finish frame processing
      ret = gst_video_encoder_finish_frame(encoder, frame);
      if (ret != GST_FLOW_OK) {
        GST_WARNING_OBJECT(encoder, "finish_frame() returned: %s",
                           gst_flow_get_name(ret));
        return ret;
      }

    } else {
      GST_WARNING_OBJECT(self, "Invalid output size: %d", stat.write);
      gst_video_encoder_finish_frame(encoder, frame);
    }

  } else if (encoder_return == XEVE_OK_NO_MORE_FRM) {
    GST_DEBUG_OBJECT(self, "No more frames to encode");
    gst_video_encoder_finish_frame(encoder, frame);

  } else {
    GST_ERROR_OBJECT(self, "Unexpected encoder return value: %d",
                     encoder_return);
    return GST_FLOW_ERROR;
  }

  return GST_FLOW_OK;
}

#endif
static gboolean plugin_init(GstPlugin *plugin) {
  return gst_element_register(plugin, "xeveenc", GST_RANK_PRIMARY,
                              GST_TYPE_XEVE_ENC);
}

GST_PLUGIN_DEFINE(GST_VERSION_MAJOR, GST_VERSION_MINOR, xeveenc,
                  "XEVE Video Encoder", plugin_init, VERSION, "LGPL",
                  "GStreamer", "https://example.com")