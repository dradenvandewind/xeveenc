#ifndef __GST_XEVE_ENC_H__
#define __GST_XEVE_ENC_H__

#include <gst/gst.h>
#include <gst/video/video.h>
#include <gst/video/gstvideoencoder.h>
#include <xeve.h>
#define DEBUG TRUE
G_BEGIN_DECLS

#define GST_TYPE_XEVE_ENC            (gst_xeve_enc_get_type())
G_DECLARE_FINAL_TYPE(GstXeveEnc, gst_xeve_enc, GST, XEVE_ENC, GstVideoEncoder)

struct _GstXeveEnc {
  GstVideoEncoder parent;
  
  /* Properties */

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

  /*< private >*/
  gpointer priv;
};

G_END_DECLS

#endif /* __GST_XEVE_ENC_H__ */