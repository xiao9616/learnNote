import unittest
import faiss
import numpy as np
import time
np.random.seed(1234)
feature_dim = 1024
database_size = 80000
num_range = 65536
n_list = 1000


class MyTestCase(unittest.TestCase):

    def test_base_search(self):
        self.index.add(self.database)
        D, I = self.index.search(self.wait_find, 1)
        print(D, I)

    def test_faster_search(self):
        self.index = faiss.IndexIVFFlat(self.index, feature_dim, n_list)
        self.index.train(self.database)
        self.index.add(self.database)
        D, I = self.index.search(self.wait_find, 1)
        print(D, I)

    def setUp(self) -> None:
        self.database = np.random.random((database_size, feature_dim)).astype('float32')
        self.wait_find = np.random.random((1, feature_dim)).astype('float32')
        self.index = faiss.IndexFlatL2(feature_dim)

    def tearDown(self) -> None:
        super().tearDown()


class testFaissDemo(unittest.TestCase):
    def test_base(self):
        d = 1024  # dimension
        nb = 240000  # database size
        nq = 10000  # nb of queries
        np.random.seed(1234)  # make reproducible
        xb = np.random.random((nb, d)).astype('float32')
        xb[:, 0] += np.arange(nb) / 1000.
        xq = np.random.random((nq, d)).astype('float32')
        xq[:, 0] += np.arange(nq) / 1000.

        index = faiss.IndexFlatL2(d)  # build the index
        print(index.is_trained)
        index.add(xb)  # add vectors to the index
        print(index.ntotal)

        k = 4  # we want to see 4 nearest neighbors
        start_time=time.time()
        D, I = index.search(xb, 1)  # sanity check
        end_time = time.time()
        print(end_time-start_time)
        print(I)
        print(D)


    def test_faster(self):
        d = 1024  # dimension
        nb = 100000  # database size
        nq = 10000  # nb of queries
        np.random.seed(1234)  # make reproducible
        xb = np.random.random((nb, d)).astype('float32')
        xb[:, 0] += np.arange(nb) / 1000.
        xq = np.random.random((nq, d)).astype('float32')
        xq[:, 0] += np.arange(nq) / 1000.

        nlist = 100
        k = 4
        quantizer = faiss.IndexFlatL2(d)  # the other index
        index = faiss.IndexIVFFlat(quantizer, d, nlist, faiss.METRIC_L2)
        # here we specify METRIC_L2, by default it performs inner-product search

        assert not index.is_trained
        index.train(xb)
        assert index.is_trained

        index.add(xb)  # add may be a bit slower as well
        start_time=time.time()
        D, I = index.search(xq, k)  # actual search # sanity check
        end_time = time.time()
        print(end_time-start_time)

        print(I[-5:])  # neighbors of the 5 last queries
        index.nprobe = 10  # default nprobe is 1, try a few more

        start_time=time.time()
        D, I = index.search(xq, k)
        end_time = time.time()
        print(end_time-start_time)
        print(I[-5:])  # neighbors of the 5 last queries

    def test_faster_PQ(self):
        d = 1024  # dimension
        nb = 100000  # database size
        nq = 10000  # nb of queries
        np.random.seed(1234)  # make reproducible
        xb = np.random.random((nb, d)).astype('float32')
        xb[:, 0] += np.arange(nb) / 1000.
        xq = np.random.random((nq, d)).astype('float32')
        xq[:, 0] += np.arange(nq) / 1000.
        nlist = 100
        m = 8
        k = 4
        quantizer = faiss.IndexFlatL2(d)  # this remains the same
        index = faiss.IndexIVFPQ(quantizer, d, nlist, m, 8)
        # 8 specifies that each sub-vector is encoded as 8 bits
        index.train(xb)
        index.add(xb)
        start_time=time.time()
        D, I = index.search(xb[:5], k)   # sanity check
        end_time = time.time()
        print(end_time-start_time)
         # sanity check
        print(I)
        print(D)
        index.nprobe = 10  # make comparable with experiment above
        D, I = index.search(xq, k)  # search
        print(I[-5:])

    def test_gpu(self):
        d = 64  # dimension
        nb = 100000  # database size
        nq = 10000  # nb of queries
        np.random.seed(1234)  # make reproducible
        xb = np.random.random((nb, d)).astype('float32')
        xb[:, 0] += np.arange(nb) / 1000.
        xq = np.random.random((nq, d)).astype('float32')
        xq[:, 0] += np.arange(nq) / 1000.

        import faiss  # make faiss available

        ngpus = faiss.get_num_gpus()

        print("number of GPUs:", ngpus)

        cpu_index = faiss.IndexFlatL2(d)

        gpu_index = faiss.index_cpu_to_all_gpus(  # build the index
            cpu_index
        )

        gpu_index.add(xb)  # add vectors to the index
        print(gpu_index.ntotal)

        k = 4  # we want to see 4 nearest neighbors
        start_time=time.time()
        D, I = gpu_index.search(xq, k)  # actual search
        end_time=time.time()
        print(end_time-start_time)
        print(I[:5])  # neighbors of the 5 first queries
        print(I[-5:])  # neighbors of the 5 last queries

    def setUp(self) -> None:
        super().setUp()

    def tearDown(self) -> None:
        super().tearDown()


if __name__ == '__main__':
    # MyTestCase().run()
    testFaissDemo.run()
