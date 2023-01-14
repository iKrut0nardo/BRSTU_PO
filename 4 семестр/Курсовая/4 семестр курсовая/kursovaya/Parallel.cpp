#include <iostream>
#include <string>
#include "mpi.h"
#include "opencv2/opencv.hpp"
#include <time.h>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    unsigned int end_time = clock();
    // the input image
    cv::Mat image;

    // the total size of the image matrix (rows * columns * channels):
    size_t imageTotalSize;

    // partial size (how many bytes will be sent to each process):
    size_t imagePartialSize;

    // how many channels are there in the image?
    int channels;

    // partial buffer, to contain the image.
    // 'uchar' means 'unsigned char', i.e. an 8-bit value, because each pixel in an image is a byte (0..255)
    uchar* partialBuffer;

    // also create the output image, where we will save the results:
    cv::Mat outImage;

    // ------------------------------------

    // start the MPI part
    MPI_Init(&argc, &argv);

    // get the world size and current rank:
    int size;
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    // read the image and its properties in the ROOT process:
    if (rank == 0)
    {
        // read the image
        image = cv::imread("1.bmp", IMREAD_GRAYSCALE);
        resize(image, image, Size(6000, 6000));
        // check if it's empty:
        if (image.empty())
        {
            std::cerr << "Image is empty, terminating!" << std::endl;
            return -1;
        }

        // get the number of channels in the image
        channels = image.channels();

        // get the total size of the image matrix (rows * columns * channels)
        // the explanation can be found here: https://stackoverflow.com/a/26441073/4003714 
        imageTotalSize = image.step[0] * image.rows;

        // check if we can evenly divide the image bytes by the number of processes
        // the image.total() method returns the number of elements, i.e. (rows * cols)
        if (image.total() % size)
        {
            std::cerr << "Cannot evenly divide the image between the processes. Choose a different number of processes!" << std::endl;
            return -2;
        }

        // get partial size (how many bytes are sent to each process):
        imagePartialSize = imageTotalSize / size;

        std::cout << "The image will be divided into blocks of " << imagePartialSize << " bytes each" << std::endl;
    }

    // send the "partial size" from #0 to other processes:
    MPI_Bcast(&imagePartialSize, 1, MPI_UNSIGNED_LONG_LONG, 0, MPI_COMM_WORLD);
    
    // send the number of channels in the image from #0 to other processes:
    MPI_Bcast(&channels, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // synchronize the processes here, to make sure that the sizes are initialized:
    MPI_Barrier(MPI_COMM_WORLD);

    // allocate the partial buffer:
    partialBuffer = new uchar[imagePartialSize];

    // synchronize the processe here, to make sure each process has allocated the buffer:
    MPI_Barrier(MPI_COMM_WORLD);

    // scatter the image between the processes:
    MPI_Scatter(image.data, imagePartialSize, MPI_UNSIGNED_CHAR, partialBuffer, imagePartialSize, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

    // synchronize the image processing:
    MPI_Barrier(MPI_COMM_WORLD);

    // -----------------------------------------------------------------------------------------------------------------------------------------------
    // AND NOW HERE EACH PROCESS HAS ITS OWN PART OF THE IMAGE!

    // THE PARTS ARE DIVIDED ROW-WISE, I.E. THE FIRST PROCESS WILL HAVE THE FIRST COUPLE OF ROWS, THE SECOND PROCESS HAS THE NEXT COUPLE OF ROWS, ETC.

    // IMPORTANT: the matrix `partialBuffer` is 1-dimensional, and contains the image data in the following format:
    // b0 g0 r0   b1 g1 r1   b2 g2 r2   b3 g3 r3 ....... bN-1 gN-1 rN-1
    // so, just a sequence of (B, G, R) values, from beginning to end

    // you can convert it into a 3D matrix here, if you want, or into a 2D-matrix... or just leave it like that. 

    // but anyway, you can now process the image, FOR EXAMPLE:

    // iterate through the image
    
    uchar* out = new uchar[imagePartialSize];
    uchar A, B, C, D;
    for (size_t i = 0; i < 1000 - 1; i += channels)
    {
        for (int j = 0; j < 6000 - 1; j++) {

            A = partialBuffer[i * 6000 + j];
            B = partialBuffer[(i + 1) * 6000 + j];
            C = partialBuffer[i * 6000 + j + 1];
            D = partialBuffer[(i + 1) * 6000 + j + 1];

            out[i * 6000 + j] = abs(A - D) + abs(B - C);
            out[i * 6000 + j] = saturate_cast<uchar>(out[i * 6000 + j] * 2);
        }
    }
    swap(out, partialBuffer);
    // -----------------------------------------------------------------------------------------------------------------------------------------------

    // synchronize the image processing:
    MPI_Barrier(MPI_COMM_WORLD);

    // initialize the output image (only need to do it in the ROOT process)
    if (rank == 0)
    {
        outImage = cv::Mat(image.size(), image.type());
    }

    // and now we finally send the partial buffers back to the ROOT, gathering the complete image:
    MPI_Gather(partialBuffer, imagePartialSize, MPI_UNSIGNED_CHAR, outImage.data, imagePartialSize, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

    // Save and display image, onle in the ROOT process
    if (rank == 0)
    {
        // save the image:
        resize(outImage, outImage, Size(4000, 4000));
        cv::imwrite("out.bmp", outImage);
        cout << "Operation success! Time = " << end_time / 1000.0 << endl;
    }

    delete[]partialBuffer;

    MPI_Finalize();
    
}
