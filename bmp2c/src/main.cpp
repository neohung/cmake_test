#include <stdio.h>
#include <stdlib.h>
#include <main.h>
#include <tcimg.h>

void usage(char* str)
{
	printf("%s [bmpfilename] [variable] [outfilename]\n",str);
}

void outputfile(char* outfilename, TrueColorImage* pimg, char* pvariable)
{
  FILE * pFile;
  pFile = fopen (outfilename,"w");
  if (pFile!=NULL)
  {
    
    fprintf(pFile,"#include <tcimg.h> \n\n\n");
    fprintf(pFile,"unsigned char %s_ImageData[];\n", pvariable);
    
    fprintf(pFile,"TrueColorImage %s = {  \n", pvariable);
    fprintf(pFile, "%s_ImageData, \n", pvariable);
    fprintf(pFile, "%d, \n", pimg->ImgWidth);
    fprintf(pFile, "%d, \n", pimg->ImgHeight);
    fprintf(pFile, "%d, \n", pimg->ImgByteWidth);
    fprintf(pFile, "%d, \n", pimg->ImgTotalPixels);
    fprintf(pFile, "%d }; \n\n", pimg->ImgTotalBytes);

    fprintf(pFile,"unsigned char %s_ImageData[] = { \n", pvariable);
    int i,j;
    for (j = 0; j < pimg->ImgHeight; ++j){
    	for (i = 0; i < pimg->ImgByteWidth; i+=3){
    		//downup
    		//int offset = (j * img->ImgByteWidth) + i;
    		//updown
    		int offset = ((pimg->ImgHeight-1-j) * pimg->ImgByteWidth) + i;
            fprintf(pFile,"%u, %u, %u, \n",
                   (unsigned int)pimg->ImgData[offset+0],
                   (unsigned int)pimg->ImgData[offset+1],
                   (unsigned int)pimg->ImgData[offset+2]);
    	}
    }

    fprintf(pFile,"};\n\n\n");
    fclose (pFile);
  }else{
  	printf("ERROR to write file %s\n",outfilename);
  	exit(1);
  }
}

int main(int argc, char** argv)
{
	char* filename;
	char* variable;
	char* ofilename;
	if (argc == 4){
		filename = argv[1];
		variable = argv[2];
		ofilename = argv[3];
	}else{
		usage(argv[0]);
		exit(0);
	}
	printf("bmp2c ready to read file [%s]\n", filename);
	TrueColorImage img;
	//int TCIMG_ReadFromFile( TrueColorImage* const img, const char filename[]);
	/*TrueColorImage
    {
      UINT8   *ImgData;
      INT32    ImgWidth;
      INT32    ImgHeight;
      INT32    ImgByteWidth;
      INT32    ImgTotalPixels;
      INT32    ImgTotalBytes;
    }
    */

	int info = TCIMG_ReadFromFile(&img, filename);
	if (info != 0){
		printf("ERROR to read file %s, info=%d\n",filename,info);
	}
	printf("%s information:\n",filename);
	printf("W x H --> (%d,%d)\n",img.ImgWidth, img.ImgHeight);
	printf("ImgTotalBytes --> %d\n",img.ImgTotalBytes);
	printf("ImgByteWidth --> %d\n",img.ImgByteWidth);

	outputfile(ofilename, &img, variable);
  return 0;
}
