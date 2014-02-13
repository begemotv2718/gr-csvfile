/* -*- c++ -*- */
/* 
 * Copyright 2014 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_CSVFILE_CSVFILE_F_IMPL_H
#define INCLUDED_CSVFILE_CSVFILE_F_IMPL_H

#include <csvfile/csvfile_f.h>
#include <fstream>
#include <string>

namespace gr {
  namespace csvfile {

    class csvfile_f_impl : public csvfile_f
    {
     private:
      std::ifstream d_fp;
      bool d_repeat;
      bool d_skipheader;
      int d_nchans;
      unsigned int d_sample_rate;
      
     public:
      csvfile_f_impl(const char *filename, bool repeat, bool skipheader, int nchans);
      ~csvfile_f_impl();

      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } // namespace csvfile
} // namespace gr

#endif /* INCLUDED_CSVFILE_CSVFILE_F_IMPL_H */

