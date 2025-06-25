project('gst-xeve-encoder', 'c',
  version : '1.0.0',
  license : 'LGPL',
  meson_version : '>= 0.53.0',
  default_options : ['c_std=gnu11'])

# Initialisation du compilateur
cc = meson.get_compiler('c')

# Dependencies
gst_dep = dependency('gstreamer-1.0', version : '>=1.18.0')
gstvideo_dep = dependency('gstreamer-video-1.0')

# Chemins de recherche standard
xeve_lib_dirs = [
  '/usr/local/lib',
  '/usr/lib/x86_64-linux-gnu', 
  '/usr/lib',
  # Ajoutez d'autres chemins standard si nécessaire
]

xeve_inc_dirs = [
  '/usr/local/include',
  '/usr/include',
  '/usr/local/include/xeve'

]

# Recherche de la bibliothèque XEVE
xeve_dep = cc.find_library('xeve',
  required : true,
  dirs : xeve_lib_dirs)

# Configuration des includes
xeve_inc = include_directories(xeve_inc_dirs)

mathlib = cc.find_library('m', required: true)

# Vérification du header
if not cc.has_header('xeve.h')
  error('xeve.h header not found. Please install libxeve-dev or check installation path')
endif

# Plugin config
plugin_sources = [
  'gstxeveenc.c',
]

c_args = [
  '-DHAVE_CONFIG_H',
  '-DGST_USE_UNSTABLE_API',
  '-DG_LOG_DOMAIN="GST-XEVE"'
]

shared_library('gstxeveenc',
  plugin_sources,
  c_args : c_args,
  dependencies : [gst_dep, gstvideo_dep, xeve_dep, mathlib],
  include_directories : xeve_inc,
  install : true,
  install_dir : join_paths(get_option('libdir'), 'gstreamer-1.0'),
  name_prefix : '',
)