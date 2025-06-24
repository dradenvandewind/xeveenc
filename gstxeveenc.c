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
    // Note: The arrays are too large to print completely - you might want to print just a few elements
    
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
    printf("IBC hash search range for small blocks: %d\n", param->ibc_hash_search_range_4smallblk);
    printf("IBC fast method: %d\n", param->ibc_fast_method);
    
    /* Toolset and framework */
    printf("Toolset IDC H: %d\n", param->toolset_idc_h);
    printf("Toolset IDC L: %d\n", param->toolset_idc_l);
    printf("BTT: %d\n", param->btt);
    printf("SUCO: %d\n", param->suco);
    
    /* VUI parameters */
    printf("SAR: %d\n", param->sar);
    printf("SAR width: %d, SAR height: %d\n", param->sar_width, param->sar_height);
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
  priv->xeve_cdsc = NULL;
  priv->xeve_handle = NULL;
  priv->input_state = NULL;
  priv->encoder_initialized = FALSE;

  // Secure allocation  
  priv->xeve_cdsc = g_malloc0(sizeof(XEVE_CDSC));
  priv->xeve_cdsc->max_bs_buf_size = MAX_BITSTREAM_SIZE;
#if 0
  g_print("priv->xeve_cdsc %x \n", priv->xeve_cdsc);
  g_print("priv->xeve_cdsc->max_bs_buf_size %d \n", priv->xeve_cdsc->max_bs_buf_size);
#endif 

  if(priv->xeve_cdsc)
  {
    /* get default parameters */
    xeve_param_default(&priv->xeve_cdsc->param);

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

  if (!priv->xeve_cdsc) {
    GST_ERROR_OBJECT(self, "XEVE  not initialized");
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

  priv->xeve_cdsc->param.w = width;
  priv->xeve_cdsc->param.h = height;
  priv->xeve_cdsc->param.fps.num = fps_n;
  priv->xeve_cdsc->param.fps.den = fps_d;



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
priv->xeve_cdsc->param.threads = 8;


  // Apply presets

  ret = xeve_param_ppt(&priv->xeve_cdsc->param, XEVE_PROFILE_BASELINE, XEVE_PRESET_SLOW, XEVE_TUNE_NONE);
  if (XEVE_FAILED(ret))
    {
        GST_ERROR_OBJECT(self, "cannot set profile, preset, tune to parameter: %d", 
                       ret);

        ret = -1;
        // goto ERR;
    }

    g_print("File: %s | Function: %s | Line: %d\n", __FILE__, __func__, __LINE__);


// Create the XEVE encoder - CORRECTION: pass xeve_param, not xeve_cdsc  
  //priv->xeve_handle = xeve_create(priv->xeve_param, &err);
#ifdef DEBUG

    g_print("priv->xeve_cdsc %x \n", priv->xeve_cdsc);
    g_print("priv->xeve_cdsc->max_bs_buf_size %d \n", priv->xeve_cdsc->max_bs_buf_size);
    print_xeve_param(&priv->xeve_cdsc->param);

#endif

  if (ret = xeve_param_check(&priv->xeve_cdsc->param))
    {
        
        GST_ERROR_OBJECT(self, "invalid configuration: %d", 
                       ret);
        ret = -1; 
        //goto ERR;
    }

//XEVE               id = NULL;

   


    priv->xeve_handle = xeve_create(priv->xeve_cdsc, &err);
    if (!priv->xeve_handle)
    {
      GST_ERROR_OBJECT(self, "cannot create XEVE encoder: %d", 
                       err);
    }
 #ifdef false   
    /* create encoder */
    //id = xeve_create(priv->xeve_cdsc, NULL);
    if (id == NULL)
    {
        g_print("cannot create XEVE encoder\n");
        //ret = -1; goto ERR;
    }
#endif




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


static GstFlowReturn
gst_xeve_enc_handle_frame(GstVideoEncoder *encoder, GstVideoCodecFrame *frame)
{
    GstXeveEnc *self = GST_XEVE_ENC(encoder);
    GstXeveEncPrivate *priv = GST_XEVE_ENC_GET_PRIVATE(self);
    GstVideoInfo *info = &priv->input_state->info;
    XEVE_IMGB img_buf = {0};
    XEVE_STAT stat; /* encoding status */

    XEVE_BITB bit_buf = {0};
    GstBuffer *out_buf;
    GstFlowReturn ret = GST_FLOW_ERROR;
    //XEVE_CLK           clk_beg, clk_end, clk_tot;

    int err;
    GstMapInfo in_map, out_map;
    // Convert GstBuffer to XEVE_IMGB using the helper function
    if (gstbuffer_to_xeve_imgb(frame->input_buffer, info, &img_buf) != 0) {
        GST_ERROR_OBJECT(self, "Failed to convert GstBuffer to XEVE_IMGB");
        goto done;
    }

    // Push frame to encoder
    err = xeve_push(priv->xeve_handle, &img_buf);
    if(XEVE_FAILED(err))
    {
      GST_ERROR_OBJECT(self, "xeve_push() Failed to push frame to encoder (err=%d)", err);
      ret = -1;
      //goto ERR;
    }

       // Allocate output buffer - use the configured max bitstream size
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

    // Set up bitstream buffer
    bit_buf.addr = out_map.data;
    bit_buf.bsize = out_map.size;

    // Encode the frame
    //clk_beg = xeve_clk_get();

    ret = xeve_encode(priv->xeve_handle, &bit_buf, &stat);
    
    // Unmap output buffer immediately after encoding
    gst_buffer_unmap(out_buf, &out_map);

    if(XEVE_FAILED(ret))
    {
      GST_ERROR_OBJECT(self, "Failed to encode frame (ret=%d)", ret);
      ret = -1;
      //goto ERR;
    }

    if(ret == XEVE_OK_OUT_NOT_AVAILABLE)
    {
      
      GST_INFO_OBJECT(self, "XEVE_OK_OUT_NOT_AVAILABLE (ret=%d)", ret);
      GST_INFO_OBJECT(self, "progress success, but output is not available temporarily (ret=%d)", ret);
      ret = -1;
      //continue;
    }
    else if(ret == XEVE_OK)
    {
      GST_INFO_OBJECT(self, "XEVE_OK (ret=%d)", ret);
      GST_INFO_OBJECT(self, "actual encoded size (size=%d)", stat.write);

      if(stat.write > 0)
      {
        // Resize buffer to actual encoded size
        gst_buffer_resize(out_buf, 0, stat.write);

        // Set output buffer and finish frame processing
        frame->output_buffer = out_buf;

        frame->pts = GST_BUFFER_PTS (frame->input_buffer);
        frame->duration = GST_BUFFER_DURATION (frame->input_buffer);
        ret = gst_video_encoder_finish_frame(encoder, frame);
        GST_INFO_OBJECT(self, "gst_video_encoder_finish_frame (ret=%d)", ret);
      }

    }
    else if (ret == XEVE_OK_NO_MORE_FRM)
    {
      //break;
    }
    else
    {      
      GST_INFO_OBJECT(self, "XEVE_OK (err=%d)", ret);
    }

    return ret;

    

unmap_input:
    // Unmap the input buffer if it was mapped by gstbuffer_to_xeve_imgb()
    if (img_buf.a[0]) {  // Check if any plane was mapped
        gst_buffer_unmap(frame->input_buffer, 
                        (GstMapInfo *)img_buf.a[0]);  // Need to store map_info properly
    }
    
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