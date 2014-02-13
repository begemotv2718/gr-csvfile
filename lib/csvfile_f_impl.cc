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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "csvfile_f_impl.h"


namespace gr {
  namespace csvfile {

    csvfile_f::sptr
    csvfile_f::make(const char *filename, bool repeat, bool skipheader, int n_chans)
    {
      return gnuradio::get_initial_sptr
        (new csvfile_f_impl(filename,repeat));
    }

    /*
     * The private constructor
     */
    csvfile_f_impl::csvfile_f_impl(const char *filename, bool repeat, bool skipheader, int nchans)
      : gr::sync_block("csvfile_f",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, n_chans, sizeof(float))),
      d_fp(NULL),d_repeat(repeat),d_skipheader(skipheader),d_nchans(nchans)
    {
      d_fp=std::ifstream(filename);
      if(!d_fp.is_open()){
        perror(filename);
        throw std::runtime_error("can't open file");
      }

      if(d_skipheader){
        std::getline(d_fp,NULL);
      }

    }

    /*
     * Our virtual destructor.
     */
    csvfile_f_impl::~csvfile_f_impl()
    {
      d_fp.close();
    }

    int
    csvfile_f_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        float **out = (float**) &output_items[0];
        int n_out_chans = output_items.size();
       
        int i;

        for(i=0; i< noutput_items; i++){

          if(d_fp.eof()){
            if(d_repeat){
              d_fp.seekg(0);
            }else{
              return -1;
            }
          }

          std::string line;
          std::getline(d_fp,line);

          std::string cell;
          int chan = 0;
          while(std::getline(line,cell,',') && chan < d_nchans){
            chan++;
            if(chan< n_out_chans){
              out[chan][i]=::atof(cell);
            }
          }
        }




        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace csvfile */
} /* namespace gr */

