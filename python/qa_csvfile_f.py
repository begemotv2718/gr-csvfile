#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2014 <+YOU OR YOUR COMPANY+>.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import csvfile_swig as csvfile
import os

g_in_file = os.path.join(os.getenv("srcdir"), "test.csv")


class qa_csvfile_f (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_t (self):
        # set up fg
        xpected_result = (1.0,1.1,3.0,4.4)
        csvf = csvfile.csvfile_f(g_in_file,False,1)
        dst = blocks.vector_sink_f()
        self.tb.connect(csvf,dst)
        #run
        self.tb.run ()
        result_data = dst.data()
        # check data
        self.assertFloatTuplesAlmostEqual(xpected_result, result_data, 4) 

    def test_002_t (self):
        # set up fg
        xpected_result_0 = (1.0,1.1,3.0,4.4)
        xpected_result_1 = (1.1,1.0,3.3,4.2)
        csvf = csvfile.csvfile_f(g_in_file,False,2)
        dst_0 = blocks.vector_sink_f()
        dst_1 = blocks.vector_sink_f()
        self.tb.connect((csvf,0),dst_0)
        self.tb.connect((csvf,1),dst_1)
        #run
        self.tb.run ()
        result_data_0 = dst_0.data()
        result_data_1 = dst_1.data()
        # check data
        self.assertFloatTuplesAlmostEqual(xpected_result_0, result_data_0, 4) 
        self.assertFloatTuplesAlmostEqual(xpected_result_1, result_data_1, 4)

    def test_003_t (self):
        # set up fg
        xpected_result_0 = (1.0,1.1,3.0,4.4)
        xpected_result_1 = (1.1,1.0,3.3,4.2)
        xpected_result_2 = (2.0,-2.0,3.0,5.0)
        xpected_result_3 = (0.0,0.0,0.0,0.0)
        csvf = csvfile.csvfile_f(g_in_file,False,4)
        dst_0 = blocks.vector_sink_f()
        dst_1 = blocks.vector_sink_f()
        dst_2 = blocks.vector_sink_f()
        dst_3 = blocks.vector_sink_f()
        self.tb.connect((csvf,0),dst_0)
        self.tb.connect((csvf,1),dst_1)
        self.tb.connect((csvf,2),dst_2)
        self.tb.connect((csvf,3),dst_3)
        #run
        self.tb.run ()
        result_data_0 = dst_0.data()
        result_data_1 = dst_1.data()
        result_data_2 = dst_2.data()
        result_data_3 = dst_3.data()
        # check data
        self.assertFloatTuplesAlmostEqual(xpected_result_0, result_data_0, 4) 
        self.assertFloatTuplesAlmostEqual(xpected_result_1, result_data_1, 4)
        self.assertFloatTuplesAlmostEqual(xpected_result_2, result_data_2, 4)
        self.assertFloatTuplesAlmostEqual(xpected_result_3, result_data_3, 4)

if __name__ == '__main__':
    gr_unittest.run(qa_csvfile_f, "qa_csvfile_f.xml")
