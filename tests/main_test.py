import binomial
import scipy.stats
import numpy as np
import unittest
import logging
import sys
from timeit import timeit

class TestBinomial(unittest.TestCase):
    PRECISION = 5
    def test_simple_entry(self):
        self.assertEqual(binomial.binomialpmf(1,20,0.1,),scipy.stats.binom.pmf(1,20,0.1))

    def test_list_k(self):
        args = ([1,2,3,4,5],20,0.1)
        l1=list(np.around(binomial.binomialpmf(*args),self.PRECISION))
        l2=list(np.around(scipy.stats.binom.pmf(*args),self.PRECISION))
        self.assertListEqual(l1,l2)

    def test_list_p(self):
        args = (1,20,list(np.linspace(0,1,20)))
        l1=list(np.around(binomial.binomialpmf(*args),self.PRECISION))
        l2=list(np.around(scipy.stats.binom.pmf(*args),self.PRECISION))
        self.assertListEqual(l1,l2)

    def test_timeit(self):
        global args
        args = (1,20,list(np.linspace(0,1,20)))
        log= logging.getLogger("TestBinomial.test_timeit")
        log.debug(f'Binomial {timeit("binomial.binomialpmf(*args)",number=100,globals=globals()):.6f}s')
        log.debug(f'SciPy {timeit("scipy.stats.binom.pmf(*args)",number=100,globals=globals()):.6f}s')

        
if __name__ == '__main__':
    logging.basicConfig(stream=sys.stdout)
    logging.getLogger("TestBinomial.test_timeit").setLevel(logging.DEBUG)
    unittest.main()
