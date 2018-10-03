/*
 * writing initialized data to a hdf5 file
 */
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include "hdf5.h"

#define ALLOC(s) calloc((s), sizeof(char))
#define FREE(s) free(s)
#define FILE "tmp/Ising.h5"
#define DATASETNAME "InitArray"
#define RANK 3


static void test_hdf5_null(void **state) {
(void) state;    /* unused */
}

static void test_hdf5_initialize(void **state) {
    size_t nN = N;
    size_t nK = K;
    int i, bw, totalwritten;
    bool *s;
    hid_t file, dataset;        /* file and dataset handles */
    hid_t datatype, dataspace;   /* handles */
    hsize_t dimsf[RANK];           /* dataset dimensions */
    herr_t status;
    file = H5Fcreate(FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);
    dimsf[0] = K;
    dimsf[1] = N;
    dimsf[2] = N;
    dataspace = H5Screate_simple(RANK, dimsf, NULL);

    /*
     * Initialize data
     */
    real_t g = 2.0;
    real_t Texp = 6.0;
    real_t T = floor(pow(10,Texp));

    s = ALLOC ( N*T * sizeof(bool) );
    real_t *J = ALLOC ( K*N*N * sizeof(real_t) );

    ising_initialize_data(g,nN,nK,Texp,J, s);

    /*
     * Define datatype for the data in the file
     * We will store H5T_IEEE_F64LE, 8-bytes float
     * which is little-endian
     */
    datatype = H5Tcopy(H5T_IEEE_F64LE);
    status = H5Tset_order(datatype, H5T_ORDER_LE);

    /*
     * Create a new dataset within the file using defined dataspae and
     * datatype and default dataset creation propertis.
     */
    dataset = H5Dcreate2(file, DATASETNAME, datatype, dataspace,
            H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    /*
     * Write the data to the dataset using default transfer properties
     */
    status = H5Dwrite(dataset, H5T_IEEE_F64LE, H5S_ALL, H5S_ALL, H5P_DEFAULT, J); 

    /*
     * Close/release resources.
     */
    H5Sclose(dataspace);
    H5Tclose(datatype);
    H5Dclose(dataset);
    H5Fclose(file);

    assert_int_equal(0,status);
}
