#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#pragma pack(push, 1)

typedef struct tagBITMAPFILEHEADER
{
    short bfType;  //specifies the file type
    int bfSize;  //specifies the size in bytes of the bitmap file
    short bfReserved1;  //reserved; must be 0
    short bfReserved2;  //reserved; must be 0
    int bfOffBits;  //species the offset in bytes from the bitmapfileheader to the bitmap bits
}BITMAPFILEHEADER;

#pragma pack(pop)

#pragma pack(push, 1)

typedef struct tagBITMAPINFOHEADER
{
    int biSize;  //specifies the number of bytes required by the struct
    long biWidth;  //specifies width in pixels
    long biHeight;  //species height in pixels
    short biPlanes; //specifies the number of color planes, must be 1
    short biBitCount; //specifies the number of bit per pixel
    int biCompression;//spcifies the type of compression
    int biSizeImage;  //size of image in bytes
    long biXPelsPerMeter;  //number of pixels per meter in x axis
    long biYPelsPerMeter;  //number of pixels per meter in y axis
    int biClrUsed;  //number of colors used by th ebitmap
    int biClrImportant;  //number of colors that are important
}BITMAPINFOHEADER;

#pragma pack(pop)



void laserOn();
void laserOff();
void startRoutine();
void setPower(int power);
void setSpeed(int speed);
void move(float x,float y);
void moveFast(float x,float y);



int line(float x1, float y1, float x2, float y2);
int circle(float x1, float y1, float r);
int arcDegtoDeg(float x1, float y1, float r, float d1, float d2,int direction);


unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);

//MAIN PARAMS
int laserPower=0;
int laserSpeed=500;
FILE* f;


int main()
{
    remove("xplotter.g");
    f = fopen("xplotter.g","a+");

    //demarrage
   startRoutine();

//COEUR DU PROGRAMME

    BITMAPINFOHEADER bitmapInfoHeader;
    unsigned char *bitmapData;
    bitmapData = LoadBitmapFile("panda.bmp",&bitmapInfoHeader);

    setSpeed(800);

    for(int j=0;j<bitmapInfoHeader.biHeight;j++){
        for(int i=0;i<bitmapInfoHeader.biWidth;i++)
        {
            setPower(255-bitmapData[i+j*bitmapInfoHeader.biWidth]);
            line(i*0.3,j*0.3,i*0.3+0.1,j*0.3);
        }
    }

    for(float x=0 ; x<300 ; x+=5){
        line(x,0,x,250);
    }
    for(float y=0 ; y<250 ; y+=5){
        line(0,y,300,y);
    }


/*
    circle(20,20,20);
    circle(20,20,15);
    line(0,0,40,0);
    line(40,0,40,40);
    line(40,40,0,40);
    line(0,40,0,0);
    arcDegtoDeg(20,20,10,0,90,1);
    arcDegtoDeg(20,20,6,0,90,-1);*/

// LA AU DESSUS!!!
    fclose(f);
    return 0;
}


void startRoutine(){
    fprintf(f,"G21\nG90\nG28\nG4 S1\nG92 X0 Y0\n");
}

void laserOn()
{
    fprintf(f,"M3 S%i\n",laserPower);

}

void laserOff()
{
    fprintf(f,"M5\n");
}


void setPower(int power){
    if(power==-1){  //try to calculate a perfect value for power

//TODO

    }else{

    if(power<0)power=0;
    if(power>255)power=255;
    laserPower = power;

    }
    fprintf(f,"M3 S%i\n",laserPower);
}

void setSpeed(int speed){
    if(speed<100)speed=100;
    if(speed>15000)speed=15000;
    laserSpeed = speed;
}


int line(float x1, float y1, float x2, float y2){
    laserOff();
    moveFast(x1,y1);
    laserOn();
    move(x2,y2);
    laserOff();
    return 0;
}


int circle(float x1, float y1, float r)
{
    laserOff();
    moveFast(x1+r,y1);
    laserOn();
    fprintf(f,"G2 X%.2f Y%.2f I%.2f J%.2f F%i\n",x1-r,y1,-r,0.0,laserSpeed);
    fprintf(f,"G2 X%.2f Y%.2f I%.2f J%.2f F%i\n",x1+r,y1,r,0.0,laserSpeed);
    laserOff();
    return 0;
}


int arcDegtoDeg(float x1, float y1, float r, float d1, float d2,int direction){
    laserOff();
    moveFast(x1+r*cos(d1),y1+r*sin(d1));
    laserOn();
    //direction is -1/1 according to... math
    if(direction>=0){
        fprintf(f,"G2 X%.2f Y%.2f I%.2f J%.2f F%i\n",x1+r*cos(d2),y1+r*sin(d2),-r*cos(d1),-r*sin(d1),laserSpeed);
    }else{
        fprintf(f,"G3 X%.2f Y%.2f I%.2f J%.2f F%i\n",x1+r*cos(d2),y1+r*sin(d2),-r*cos(d1),-r*sin(d1),laserSpeed);
    }
    laserOff();

    return 0;
}

void move(float x,float y){
    //x = MIN(MAX(0,x),3000);
    //y = MIN(MAX(0,x),2450);

    fprintf(f,"G0 X%.2f Y%.2f F%i\n",x,y,laserSpeed);
}

void moveFast(float x,float y){
    //x = MIN(MAX(0,x),3000);
    //y = MIN(MAX(0,x),2450);
    float oldspeed = laserSpeed;
    setSpeed(10000);
    fprintf(f,"G0 X%.2f Y%.2f F%i\n",x,y,laserSpeed);
    setSpeed(oldspeed);
}




unsigned char *LoadBitmapFile(char *filename, BITMAPINFOHEADER *bitmapInfoHeader)
{
    FILE *filePtr; //our file pointer
    BITMAPFILEHEADER bitmapFileHeader; //our bitmap file header
    unsigned char *bitmapImage;  //store image data
    int imageIdx=0;  //image index counter
    unsigned char tempRGB;  //our swap variable

    //open filename in read binary mode
    filePtr = fopen(filename,"rb");
    if (filePtr == NULL)
        return NULL;

    //read the bitmap file header
    fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER),1,filePtr);

    //verify that this is a bmp file by check bitmap id
    if (bitmapFileHeader.bfType !=0x4D42)
    {
        fclose(filePtr);
        return NULL;
    }

    //read the bitmap info header
    fread(bitmapInfoHeader, sizeof(BITMAPINFOHEADER),1,filePtr); // small edit. forgot to add the closing bracket at sizeof

    //move file point to the begging of bitmap data
    fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

    //allocate enough memory for the bitmap image data
    bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);

    //verify memory allocation
    if (!bitmapImage)
    {
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }

    //read in the bitmap image data
    fread(bitmapImage,sizeof(char),bitmapInfoHeader->biSizeImage,filePtr);

    //make sure bitmap image data was read
    if (bitmapImage == NULL)
    {
        fclose(filePtr);
        return NULL;
    }

    //swap the r and b values to get RGB (bitmap is BGR)
    for (imageIdx = 0;imageIdx < bitmapInfoHeader->biSizeImage;imageIdx+=3) // fixed semicolon
    {
        tempRGB = bitmapImage[imageIdx];
        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
        bitmapImage[imageIdx + 2] = tempRGB;
    }

    //close file and return bitmap iamge data
    fclose(filePtr);
    return bitmapImage;
}
