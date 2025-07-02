#ifndef __GST_XEVE_ENC_H__
#define __GST_XEVE_ENC_H__

#include <gst/gst.h>
#include <gst/video/gstvideoencoder.h>
#include <gst/video/video.h>
#include <unistd.h> // for sysconf
#include <xeve.h>
#include <xeve_app_util.h>

#define ALIGN_VAL(val, align) ((((val) + (align) - 1) / (align)) * (align))

#define DEBUG TRUE
#define MAX_BITSTREAM_SIZE (10 * 1000 * 1000)
#define MAX_BS_BUF (16 * 1024 * 1024)

G_BEGIN_DECLS

#define GST_TYPE_XEVE_ENC (gst_xeve_enc_get_type())
G_DECLARE_FINAL_TYPE(GstXeveEnc, gst_xeve_enc, GST, XEVE_ENC, GstVideoEncoder)

struct _GstXeveEnc {
  GstVideoEncoder parent;

  /* Properties */
  gint bit_depth;
  gint width;
  gint height;
  gint fps_n;
  gint fps_d;

  gint bitrate;
  gint qp;
  gint profile;
  gint preset;
  gint tune;
  gboolean closed_gop;
  gint keyint_max;
  gboolean annexb;
  XEVE_IMGB *imgb_rec;
  FILE *fp, *fp_Y, *fp_U, *fp_V, *fp_bitstream;

  /*< private >*/
  gpointer priv;
};

G_END_DECLS

#endif /* __GST_XEVE_ENC_H__ */