/* -*- c++ -*- */

#define CSVFILE_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "csvfile_swig_doc.i"

%{
#include "csvfile/csvfile_f.h"
%}


%include "csvfile/csvfile_f.h"
GR_SWIG_BLOCK_MAGIC2(csvfile, csvfile_f);
