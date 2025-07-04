#ifndef __GST_XEVE_ENC_H__
#define __GST_XEVE_ENC_H__

#include <gst/gst.h>
#include <gst/video/gstvideoencoder.h>
#include <gst/video/video.h>
#include <unistd.h> // for sysconf
#include <xeve.h>
#include <xeve_app_util.h>

#define DEBUG TRUE
#define DUMP_YUV_INPUT_BUFFER FALSE
#define MAX_BITSTREAM_SIZE (10 * 1000 * 1000)
#define MAX_BS_BUF (16 * 1024 * 1024)

#define ALIGN_VAL(val, align) ((((val) + (align) - 1) / (align)) * (align))
#define CEIL_RSHIFT(a, b) (((a) + (1 << (b)) - 1) >> (b))

static const char *const xeve_sar_names[] = {
    "unknown", "1:1",    "12:11", "10:11", "16:11", "40:33",
    "24:11",   "20:11",  "32:11", "80:33", "18:11", "15:11",
    "64:33",   "160:99", "4:3",   "3:2",   "2:1",   0};
static const char *const xeve_video_format_names[] = {
    "component", "pal", "ntsc", "secam", "mac", "unknown", 0};
static const char *const xeve_fullrange_names[] = {"limited", "full", 0};
static const char *const xeve_colorprim_names[] = {
    "reserved", "bt709",     "unknown",   "reserved", "bt470m",
    "bt470bg",  "smpte170m", "smpte240m", "film",     "bt2020",
    "smpte428", "smpte431",  "smpte432",  0};
static const char *const xeve_transfer_names[] = {
    "reserved",  "bt709",        "unknown",   "reserved",     "bt470m",
    "bt470bg",   "smpte170m",    "smpte240m", "linear",       "log100",
    "log316",    "iec61966-2-4", "bt1361e",   "iec61966-2-1", "bt2020-10",
    "bt2020-12", "smpte2084",    "smpte428",  "arib-std-b67", 0};
static const char *const xeve_colmatrix_names[] = {"gbr",
                                                   "bt709",
                                                   "unknown",
                                                   "",
                                                   "fcc",
                                                   "bt470bg",
                                                   "smpte170m",
                                                   "smpte240m",
                                                   "ycgco",
                                                   "bt2020nc",
                                                   "bt2020c",
                                                   "smpte2085",
                                                   "chroma-derived-nc",
                                                   "chroma-derived-c",
                                                   "ictcp",
                                                   0};

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