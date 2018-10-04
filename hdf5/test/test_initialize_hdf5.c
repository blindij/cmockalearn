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
#define RANK 2


static void test_hdf5_null(void **state) {
(void) state;    /* unused */
}

static void test_hdf5_initialize(void **state) {
    size_t nN = N;
    size_t nK = K;
    int i, bw, totalwritten;
    hid_t file, dataset;        /* file and dataset handles */
    hid_t datatype, dataspace;   /* handles */
    hid_t plist,grp;
    hsize_t cdimsf[RANK];
    hsize_t dimsf[RANK];           /* dataset dimensions */
    herr_t status;

    /*
     * Initialize data
     */
    real_t g = 2.0;
    real_t Texp = 6.0;
    real_t T = floor(pow(10,Texp));

    bool *s = ALLOC ( N*T * sizeof(bool) );
    real_t *J = ALLOC ( K*N*N * sizeof(real_t) );

    ising_initialize_data(g,nN,nK,Texp,J, s);
    /*
     * Create a file
     */
    file = H5Fcreate(FILE, H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    /*
     * Create a group
     */
    grp = H5Gcreate2(file,"/Data", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    /*
     * Create dataset "Compressed Data" in the group using absolute
     * name. Dataset creation property list is modified to use
     * GZIP compression with the compression effort set to 6.
     * Note that compression can be used only when dataset is chunked.
     */
    dimsf[0] = N;
    dimsf[1] = T;
    cdimsf[0] = 20;
    cdimsf[1] = 20;
    dataspace = H5Screate_simple(RANK, dimsf, NULL);
//    plist =  H5Pcreate(H5P_DATASET_CREATE);
//    H5Pset_chunk(plist,2,cdimsf);
//    H5Pset_deflate(plist,6);
//    dataset = H5Dcreate2(file, "Data/Compressed_Data", H5T_NATIVE_HBOOL, dataspace, H5P_DEFAULT, plist, H5P_DEFAULT);
    dataset = H5Dcreate2(file, "Data/Boolean_Data", H5T_NATIVE_HBOOL, dataspace, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    /*
     * Write the s data to the first dataset using default transfer properties
     */
    status = H5Dwrite(dataset, H5T_NATIVE_HBOOL, H5S_ALL, H5S_ALL, H5P_DEFAULT, s); 

    /*
     * Close the first dataset
     */
    H5Sclose(dataspace);
    H5Dclose(dataset);

    /*
     * Create the second dataset
     */
    dimsf[0] = K;
    dimsf[1] = N*N;
    dataspace = H5Screate_simple(RANK, dimsf, NULL);
    dataset = H5Dcreate2(file, "/Data/Float_Data", H5T_NATIVE_FLOAT,
                dataspace, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    /*
     * Write the s data to the first dataset using default transfer properties
     */
    status = H5Dwrite(dataset, H5T_NATIVE_FLOAT, H5S_ALL, H5S_ALL, H5P_DEFAULT, J); 

    /*
     * Close the second dataset and 
     */
    H5Sclose(dataspace);
    H5Dclose(dataset);
    H5Pclose(plist);
    H5Gclose(grp);
    H5Fclose(file);


    /*
     * Define datatype for the data in the file
     * We will store H5T_IEEE_F64LE, 8-bytes float
     * which is little-endian
     */
 //   datatype = H5Tcopy(H5T_IEEE_F64LE);
//    status = H5Tset_order(datatype, H5T_ORDER_LE);

    /*
     * Create a new dataset within the file using defined dataspae and
     * datatype and default dataset creation propertis.
     */
//    dataset = H5Dcreate2(file, DATASETNAME, datatype, dataspace, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    /*
     * Close/release resources.
     */
//    H5Sclose(dataspace);
//    H5Tclose(datatype);
//    H5Dclose(dataset);
//    H5Fclose(file);

    assert_int_equal(0,status);
}
