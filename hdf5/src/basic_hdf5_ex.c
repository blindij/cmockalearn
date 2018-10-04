/*
 *  File: basic_hdf5_ex.c
 */

 /*
  * Example taken from: 
  * https://support.hdfgroup.org/HDF5/doc1.6/UG/10_Datasets.html
  *
  * Basic procedure to write to a dataset
  * - Open the dataset
  * - Set dataset dataspace for write
  * - Write data
  * - Close the datatype, dataspace and property list
  * - Close the dataset
  *
  */
  #include <stdio.h>
  #include <hdf5.h>

  int main(int argc, char *argv[]) {
    hid_t file_id, dataset_id;
    herr_t status;
    int i,j, dset_data[4][6];

    /* Initialize the dataset. */
    for (i = 0; i < 4; i++)
        for (j = 0; j < 6; j++)
            dset_data[i][j] = i * 6 + j +1;

    /* Open an existing file. */
    file_id = H5Fopen("tmp/dset.h5", H5F_ACC_RDWR, H5P_DEFAULT);

    /* Open an existing dataset. */
    dataset_id = H5Dopen2(file_id, "/dset", H5P_DEFAULT);

    /* 
     * Write the entire dataset, using 'dset_data':
     * memory type is 'native int'
     * write the entire dataspace to the entire dataspce
     * no transfer properties,
     */ 

    status = H5Dwrite(dataset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dset_data);

    status = H5Dclose(dataset_id);
    return 0;
  }
