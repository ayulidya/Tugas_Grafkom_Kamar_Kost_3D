#include <windows.h>
#include <stdio.h>
#include <GL\glut.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <sys/timeb.h>


GLuint texture[5];
GLUquadricObj *qobj;
GLint slices = 16;
GLint stacks = 16;
static float ypos = 0, zpos = 0, xpos = 0,a = -9, b = -5,c = -30;


int z=0;


struct Image {
	unsigned long sizeX;
	unsigned long sizeY;
	char *data;
};
typedef struct Image Image; //struktur data untuk

//ukuran image #bisa di set sesuai kebutuhan
#define checkImageWidth 164
#define checkImageHeight 164

GLubyte checkImage[checkImageWidth][checkImageHeight][3];

//mengambil gambar BMP
int ImageLoad(char *filename, Image *image) {
	FILE *file;
	unsigned long size; // ukuran image dalam bytes
	unsigned long i; // standard counter.
	unsigned short int plane; // number of planes in image

	unsigned short int bpp; // jumlah bits per pixel
	char temp; // temporary color storage for var warna sementara untuk memastikan filenya ada


	if ((file = fopen(filename, "rb")) == NULL) {
		printf("File Not Found : %s\n", filename);
		return 0;
	}
	// mencari file header bmp
	fseek(file, 18, SEEK_CUR);
	// read the width
	if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
		printf("Error reading width from %s.\n", filename);
		return 0;
	}
	//printf("Width of %s: %lu\n", filename, image->sizeX);
	// membaca nilai height
	if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
		printf("Error reading height from %s.\n", filename);
		return 0;
	}
	//printf("Height of %s: %lu\n", filename, image->sizeY);
	//menghitung ukuran image(asumsi 24 bits or 3 bytes per pixel).

	size = image->sizeX * image->sizeY * 3;
	// read the planes
	if ((fread(&plane, 2, 1, file)) != 1) {
		printf("Error reading planes from %s.\n", filename);
		return 0;
	}
	if (plane != 1) {
		printf("Planes from %s is not 1: %u\n", filename, plane);
		return 0;
	}
	// read the bitsperpixel
	if ((i = fread(&bpp, 2, 1, file)) != 1) {
		printf("Error reading bpp from %s.\n", filename);

		return 0;
	}
	if (bpp != 24) {
		printf("Bpp from %s is not 24: %u\n", filename, bpp);
		return 0;
	}
	// seek past the rest of the bitmap header.
	fseek(file, 24, SEEK_CUR);
	// read the data.
	image->data = (char *) malloc(size);
	if (image->data == NULL) {
		printf("Error allocating memory for color-corrected image data");
		return 0;
	}
	if ((i = fread(image->data, size, 1, file)) != 1) {
		printf("Error reading image data from %s.\n", filename);
		return 0;
	}
	for (i = 0; i < size; i += 3) { // membalikan semuan nilai warna (gbr - > rgb)
		temp = image->data[i];
		image->data[i] = image->data[i + 2];
		image->data[i + 2] = temp;
	}
	// we're done.
	return 1;
}

//mengambil tekstur
Image * loadTexture1() {
	Image *image1;
	
	// alokasi memmory untuk tekstur
	image1 = (Image *) malloc(sizeof(Image));
	if (image1 == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}
	//pic.bmp is a 64x64 picture
	if (!ImageLoad("img.bmp", image1)) {
		exit(1);
	}
	return image1;
}

Image * loadTexture2() {
	Image *image2;
	// alokasi memmory untuk tekstur
	image2 = (Image *) malloc(sizeof(Image));
	if (image2 == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}
	//pic.bmp is a 64x64 picture
	if (!ImageLoad("tembok.bmp", image2)) {
		exit(1);
	}
	return image2;
}

Image * loadTexture3() {
	Image *image3;
	// alokasi memmory untuk tekstur
	image3 = (Image *) malloc(sizeof(Image));
	if (image3 == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}
	//pic.bmp is a 64x64 picture
	if (!ImageLoad("km.bmp", image3)) {
		exit(1);
	}
	return image3;
}

Image * loadTexture4() {
	Image *image4;
	// alokasi memmory untuk tekstur
	image4 = (Image *) malloc(sizeof(Image));
	if (image4 == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}
	if (!ImageLoad("wall.bmp", image4)) {
		exit(1);
	}
	return image4;
}
Image * loadTexture5() {
	Image *image5;
	// alokasi memmory untuk tekstur
	image5 = (Image *) malloc(sizeof(Image));
	if (image5 == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}
	if (!ImageLoad("texture.bmp", image5)) {
		exit(1);
	}
	return image5;
}
Image * loadTexture6() {
	Image *image6;
	// alokasi memmory untuk tekstur
	image6 = (Image *) malloc(sizeof(Image));
	if (image6 == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}
	if (!ImageLoad("dwi1.bmp", image6)) {
		exit(1);
	}
	return image6;
} 
Image * loadTexture7() {
	Image *image7;
	// alokasi memmory untuk tekstur
	image7 = (Image *) malloc(sizeof(Image));
	if (image7 == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}
	if (!ImageLoad("jdl.bmp", image7)) {
		exit(1);
	}
	return image7;
} 
Image * loadTexture8() {
	Image *image8;
	// alokasi memmory untuk tekstur
	image8 = (Image *) malloc(sizeof(Image));
	if (image8 == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}
	if (!ImageLoad("jamdinding.bmp", image8)) {
		exit(1);
	}
	return image8;
} 
Image * loadTexture9() {
	Image *image9;
	// alokasi memmory untuk tekstur
	image9 = (Image *) malloc(sizeof(Image));
	if (image9 == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}
	if (!ImageLoad("wood.bmp", image9)) {
		exit(1);
	}
	return image9;
} 
Image * loadTexture10() {
	Image *image10;
	// alokasi memmory untuk tekstur
	image10 = (Image *) malloc(sizeof(Image));
	if (image10 == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}
	if (!ImageLoad("lcd1.bmp", image10)) {
		exit(1);
	}
	return image10;
} 

Image * loadTexture11() {
	Image *image11;
	// alokasi memmory untuk tekstur
	image11 = (Image *) malloc(sizeof(Image));
	if (image11 == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}
	if (!ImageLoad("karpetos.bmp", image11)) {
		exit(1);
	}
	return image11;
} 
Image * loadTexture12() {
	Image *image12;
	// alokasi memmory untuk tekstur
	image12 = (Image *) malloc(sizeof(Image));
	if (image12 == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}
	if (!ImageLoad("hijau.bmp", image12)) {
		exit(1);
	}
	return image12;
} 
Image * loadTexture13() {
	Image *image13;
	// alokasi memmory untuk tekstur
	image13 = (Image *) malloc(sizeof(Image));
	if (image13 == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}
	if (!ImageLoad("dwi7.bmp", image13)) {
		exit(1);
	}
	return image13;
} 
Image * loadTexture14() {
	Image *image14;
	// alokasi memmory untuk tekstur
	image14 = (Image *) malloc(sizeof(Image));
	if (image14 == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}
	if (!ImageLoad("texture.bmp", image14)) {
		exit(1);
	}
	return image14;
} 
Image * loadTexture15() {
	Image *image15;
	// alokasi memmory untuk tekstur
	image15 = (Image *) malloc(sizeof(Image));
	if (image15 == NULL) {
		printf("Error allocating space for image");
		exit(0);
	}
	if (!ImageLoad("walpaper.bmp", image15)) {
		exit(1);
	}
	return image15;
} 


void myinit(void)
{
     
    glClearColor(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	


    Image *image1 = loadTexture1();
	Image *image2 = loadTexture2();
	Image *image3 = loadTexture3();
    Image *image4 = loadTexture4();
    Image *image5 = loadTexture5();
    Image *image6 = loadTexture6();
    Image *image7 = loadTexture7();
    Image *image8 = loadTexture8();
    Image *image9 = loadTexture9();
    Image *image10 = loadTexture10();
    Image *image11 = loadTexture11();
    Image *image12 = loadTexture12();
    Image *image13 = loadTexture13();
    Image *image14 = loadTexture14();
    Image *image15 = loadTexture15();
 
	if (image1 == NULL) {
		printf("Image was not returned from loadTexture\n");
		exit(0);
	}
	if (image2 == NULL) {
		printf("Image was not returned from loadTexture\n");
		exit(0);
	}
	if (image3 == NULL) {
		printf("Image was not returned from loadTexture\n");
		exit(0);
	}
 	if (image4 == NULL) {
		printf("Image was not returned from loadTexture\n");
		exit(0);
	}  
	if (image5 == NULL) {
		printf("Image was not returned from loadTexture\n");
		exit(0);
	}  
		if (image6 == NULL) {
		printf("Image was not returned from loadTexture\n");
		exit(0);
	}  
	if (image7 == NULL) {
		printf("Image was not returned from loadTexture\n");
		exit(0);
	}
    if (image8 == NULL) {
		printf("Image was not returned from loadTexture\n");
		exit(0);
	}  
	if (image9 == NULL) {
		printf("Image was not returned from loadTexture\n");
		exit(0);
	}  
    if (image10 == NULL) {
		printf("Image was not returned from loadTexture\n");
		exit(0);
	}
    if (image11 == NULL) {
		printf("Image was not returned from loadTexture\n");
		exit(0);
	}
	 if (image12 == NULL) {
		printf("Image was not returned from loadTexture\n");
		exit(0);
	}
	if (image13 == NULL) {
		printf("Image was not returned from loadTexture\n");
		exit(0);
	}
	if (image14 == NULL) {
		printf("Image was not returned from loadTexture\n");
		exit(0);
	}
	if (image15 == NULL) {
		printf("Image was not returned from loadTexture\n");
		exit(0);
	}
  
  

	// Generate texture/ membuat texture
	
	glGenTextures(15,texture);
    
    //tekstur kayu lemari
	//binding texture untuk membuat texture 2D
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	//menyesuaikan ukuran textur ketika image lebih besar dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//menyesuaikan ukuran textur ketika image lebih kecil dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image1->data);

	//tekstur dinding
	//binding texture untuk membuat texture 2D
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	//menyesuaikan ukuran textur ketika image lebih besar dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //
	//menyesuaikan ukuran textur ketika image lebih kecil dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image2->sizeX, image2->sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image2->data);

	//tekstur selimut
	//binding texture untuk membuat texture 2D
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	//menyesuaikan ukuran textur ketika image lebih besar dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //
	//menyesuaikan ukuran textur ketika image lebih kecil dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image3->sizeX, image3->sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image3->data);

	//tekstur spray
	//binding texture untuk membuat texture 2D
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	//menyesuaikan ukuran textur ketika image lebih besar dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //
	//menyesuaikan ukuran textur ketika image lebih kecil dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image4->sizeX, image4->sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image4->data);
			
	//tekstur 5
	//binding texture untuk membuat texture 2D
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	//menyesuaikan ukuran textur ketika image lebih besar dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //
	//menyesuaikan ukuran textur ketika image lebih kecil dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image5->sizeX, image5->sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image5->data);
			
	//tekstur lukisan belakang
	//binding texture untuk membuat texture 2D
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	//menyesuaikan ukuran textur ketika image lebih besar dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //
	//menyesuaikan ukuran textur ketika image lebih kecil dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image6->sizeX, image6->sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image6->data);

    //tekstur jendela
	//binding texture untuk membuat texture 2D
	glBindTexture(GL_TEXTURE_2D, texture[7]);
	//menyesuaikan ukuran textur ketika image lebih besar dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //
	//menyesuaikan ukuran textur ketika image lebih kecil dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image7->sizeX, image7->sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image7->data);

    //tekstur jam dinding
	//binding texture untuk membuat texture 2D
	glBindTexture(GL_TEXTURE_2D, texture[8]);
	//menyesuaikan ukuran textur ketika image lebih besar dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //
	//menyesuaikan ukuran textur ketika image lebih kecil dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image8->sizeX, image8->sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image8->data);
    //tekstur kayu meja
	//binding texture untuk membuat texture 2D
	glBindTexture(GL_TEXTURE_2D, texture[9]);
	//menyesuaikan ukuran textur ketika image lebih besar dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //
	//menyesuaikan ukuran textur ketika image lebih kecil dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image9->sizeX, image9->sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image9->data);

    //tekstur televisi
	//binding texture untuk membuat texture 2D
	glBindTexture(GL_TEXTURE_2D, texture[10]);
	//menyesuaikan ukuran textur ketika image lebih besar dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //
	//menyesuaikan ukuran textur ketika image lebih kecil dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image10->sizeX, image10->sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image10->data);

    //tekstur karpet
	//binding texture untuk membuat texture 2D
	glBindTexture(GL_TEXTURE_2D, texture[11]);
	//menyesuaikan ukuran textur ketika image lebih besar dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //
	//menyesuaikan ukuran textur ketika image lebih kecil dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image11->sizeX, image11->sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image11->data);
			
     	//tekstur tempat sampah
	//binding texture untuk membuat texture 2D
	glBindTexture(GL_TEXTURE_2D, texture[12]);
	//menyesuaikan ukuran textur ketika image lebih besar dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //
	//menyesuaikan ukuran textur ketika image lebih kecil dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image12->sizeX, image12->sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image12->data);
            
            //texture lukisan
	glBindTexture(GL_TEXTURE_2D, texture[13]);
	//menyesuaikan ukuran textur ketika image lebih besar dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //
	//menyesuaikan ukuran textur ketika image lebih kecil dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image13->sizeX, image13->sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image13->data);		

//texture sofa dan komputer
	glBindTexture(GL_TEXTURE_2D, texture[14]);
	//menyesuaikan ukuran textur ketika image lebih besar dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //
	//menyesuaikan ukuran textur ketika image lebih kecil dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image14->sizeX, image14->sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image14->data);	
			//texture layar
	glBindTexture(GL_TEXTURE_2D, texture[15]);
	//menyesuaikan ukuran textur ketika image lebih besar dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //
	//menyesuaikan ukuran textur ketika image lebih kecil dari texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //
	glTexImage2D(GL_TEXTURE_2D, 0, 3, image15->sizeX, image15->sizeY, 0, GL_RGB,
			GL_UNSIGNED_BYTE, image15->data);

	glEnable(GL_TEXTURE_2D);	
	glShadeModel(GL_FLAT);
}
//void pilar silinder
void pilar(){
    qobj = gluNewQuadric();	
    gluQuadricDrawStyle(qobj,GLU_FILL);	
    gluCylinder(qobj,0.5,0.5,10,45,2);
}





//fungsi kotak kosong, belum diisi koordinat. diisi di display()
void kamar(float x1,float y1,float z1,float x2,float y2,float z2)
{
	//depan
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x1,y1,z1);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x2,y1,z1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x2,y2,z1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x1,y2,z1);
	//atas
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x1,y2,z1);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x2,y2,z1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x2,y2,z2);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x1,y2,z2);
	//belakang
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x1,y2,z2);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x2,y2,z2);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x2,y1,z2);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x1,y1,z2);
	//bawah
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x1,y1,z2);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x2,y1,z2);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x2,y1,z1);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x1,y1,z1);
	//samping kiri
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x1,y1,z1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x1,y2,z1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x1,y2,z2);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x1,y1,z2);
	//samping kanan
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x2,y1,z1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x2,y2,z1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x2,y2,z2);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x2,y1,z2);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		//putar arah jarum jam (menambah derajat putaran)
		case 'z':
		ypos=ypos+5;
		if (ypos>360) ypos=0;
		glutPostRedisplay();
		break;
		//putar berlawanan arah jarum jam (mengurangi derajat putaran)
		case 'x':
		ypos=ypos-5;
		if (ypos>360) ypos=0;
		glutPostRedisplay();
		break;
		//putar arah jarum jam (menambah derajat putaran)
		case '1':
		xpos=xpos+5;
		if (xpos>360) xpos=0;
		glutPostRedisplay();
		break;
		//putar berlawanan arah jarum jam (mengurangi derajat putaran)
		case '2':
		xpos=xpos-5;
		if (xpos>360) xpos=0;
		glutPostRedisplay();
		break;
		//vertikal bawah (menambah koordinat y)
		case 's':
		b = b + 1;
		if (b>-2) b=-2;
		glutPostRedisplay();
		break;
		//vertikal atas (mengurangi koordinat y)
		case 'w':
		b = b - 1;
		if (b<-30) b=-30;
		glutPostRedisplay();
		break;
		//horisontal kiri (mengurangi koordinat x)
		case 'a':
		a = a + 1;
		if (a>25) a=25;
		glutPostRedisplay();
		break;
		//horisontal kanan (menambah koordinat x)
		case 'd':
		a = a - 1;
		if (a<-80) a=80;
		glutPostRedisplay();
		break;
		//memperbesar objek (menambah koordinat z)
		case 'q':
		c = c + 1;
		if (c>15) c=15;
		glutPostRedisplay();
		break;
		//memperkecil abjek(mengurangi koordinat z)
		case 'e':
		c = c - 1;
		glutPostRedisplay();
		break;
	}
}


void display()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity ();
	glEnable(GL_DEPTH_TEST);
	//perpindahan
	glTranslatef(a,b,c);
	//putaran
	glRotatef(xpos,1,0,0);
	glRotatef(ypos,0,1,0);
	glRotatef(zpos,0,0,1);


 
	
	//tembok kiri
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		    glColor3f(1.0f,1.0f,1.0f);
			kamar(-24,-0.5,0,-23.5,15,-24);
			//
			kamar(20,-0.5,0,22,15,-24);
		glEnd();
	glPopMatrix();
	
	//tempat sampah
	
	glPushMatrix();
    glScaled(3,0.5 ,3.5);
    glTranslatef(-6, 9.4,-0.7);
    //glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glBindTexture(GL_TEXTURE_2D, texture[12]);
    //glColor3f(1.0f,1.0f,1.0f);
    glRotatef(90, 90, 0, 0);
    pilar();
    glPopMatrix();
    
    
  


    
		//tembok belakang
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		    glColor3f(1.0f,1.0f,1.0f);
   kamar(-24,0.5,-23,20,15,-24);
   			glEnd();
	glPopMatrix();
	
	//lukisan belakang2
    glPushMatrix();
  		glBindTexture(GL_TEXTURE_2D, texture[6]);
		glBegin(GL_QUADS);
		    glColor3f(1.1f,1.1f,1.1f);
			kamar(-19.5,11.3,-23.6,-3.5,2.7,-22.8);
		glEnd();
	glPopMatrix();
	

	

	
	//kasur
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[4]);
		glBegin(GL_QUADS);
		glColor3f(1.1f,1.1f,1.1f);
			kamar(-22,0.7,-10,1,1.7,-22);

        glEnd();
	glPopMatrix();
	
		//bantal
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[3]);
		glBegin(GL_QUADS);
		glColor3f(1.1f,1.1f,1.1f);
			kamar(-22,0.7,-12,-17,2.5,-20);

        glEnd();
	glPopMatrix();
	 
	
		//lukisan kiri
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[8]);
		glBegin(GL_QUADS);
		    glColor3f(1.0f,1.0f,1.0f);
			kamar(-23.1,6.5,-21.5,-23.2,10.5,-18);
		glEnd();
	glPopMatrix();
	
	//lukisan kiri
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[13]);
		glBegin(GL_QUADS);
		    glColor3f(1.0f,1.0f,1.0f);
			kamar(-23.1,5.5,-15.5,-23.1,11.5,-9.5);
		glEnd();
	glPopMatrix();
	
	//lukisan kiri3
    glPushMatrix();
            glBindTexture(GL_TEXTURE_2D, texture[7]);
		glBegin(GL_QUADS);
		   glColor3f(1.0f,1.0f,1.0f);
			kamar(-23.4,4,-8.1,-23.5,12.9,-2.54);
		glEnd();
	glPopMatrix();
 
	
		//lemari
   glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[1]);
		glBegin(GL_QUADS);
		    glColor3f(1.0f,1.0f,1.0f);
			kamar(16.5,0,-22,20,10,-13);
		glEnd();
	glPopMatrix();
	
	//meja
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[9]);
		glBegin(GL_QUADS);
		    glColor3f(1.0f,1.0f,1.0f);
			kamar(-6.6,2.5,-5,0,3,-0.5);
            kamar(-6.6,0,-5,-6,3,-0.5);
            kamar(-0.6,0,-5,0,3,-0.5);
				glEnd();
	glPopMatrix();
	



//komputer
	glPushMatrix();
            glBindTexture(GL_TEXTURE_2D, texture[14]);
		glBegin(GL_QUADS);
		   glColor3f(1.0f,1.0f,1.0f);
			kamar(-5,3.3,-1,-0.5,6,-0.8);			
			kamar(-2,3,-1,-3.5,3.5,-0.8);
		glEnd();
	glPopMatrix();
	
   //layar komputer
	glPushMatrix();
            glBindTexture(GL_TEXTURE_2D, texture[15]);
		glBegin(GL_QUADS);
		   glColor3f(1.0f,1.0f,1.0f);
			kamar(-4.8,3.5,-1.1,-0.7,5.8,-1);			
		glEnd();
	glPopMatrix(); 

//keyboard

    glPushMatrix();
            glBindTexture(GL_TEXTURE_2D, texture[14]);
		glBegin(GL_QUADS);
		   glColor3f(1.0f,1.0f,1.0f);
			kamar(-4.5,3,-2,-1,3.1,-3.5);			
		glEnd();
	glPopMatrix(); 
    //tv
    glPushMatrix();
    
            glBindTexture(GL_TEXTURE_2D, texture[10]);
		glBegin(GL_QUADS);
		   glColor3f(1.0f,1.0f,1.0f);
			kamar(19.5,3,-11,20,10.5,-3.4);
		glEnd();
	glPopMatrix();
	
	
	
	//kramik
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[11]);
		glBegin(GL_QUADS);
		    glColor3f(1.0f,1.0f,1.0f);
			kamar(-23.5,0.5,-23,20,-0.5,0);		
        glEnd();
	glPopMatrix();
	
//selimut
	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, texture[3]);
		glBegin(GL_QUADS);
		glColor3f(1.0f,1.0f,1.0f);
		kamar(-12,1.0,-9.0,1.5,2.0,-22);
	
		glEnd();
	glPopMatrix();

//lantai teras
         glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[11]);
		glBegin(GL_QUADS);
		    glColor3f(1.0f,1.0f,1.0f);
			kamar(25,0.5,-23,50,-0.5,0);		
        glEnd();
	glPopMatrix();
//kursi teras

glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[14]);
		glBegin(GL_QUADS);
		    glColor3f(1.0f,1.0f,1.0f);
			kamar(30,2,-23,35,3,-18);	
            kamar(30,0,-23,35,6,-21);
            kamar(29,0,-23,30,4,-18);
            kamar(35,0,-23,36,4,-18);	
        glEnd();
	glPopMatrix();
	//kursi teras 2
glBindTexture(GL_TEXTURE_2D, texture[14]);
		glBegin(GL_QUADS);
		    glColor3f(1.0f,1.0f,1.0f);
			kamar(36.5,2,-12,42,3,-5);
            kamar(40,-0.5,-12,42,6,-5);	
           	kamar(36,-0.5,-4,42,4,-4.5);
           	kamar(36,-0.5,-12.5,42,4,-13);
        glEnd();
	glPopMatrix();
	//meja teras
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[9]);
		glBegin(GL_QUADS);
		    glColor3f(1.0f,1.0f,1.0f);
			kamar(30,2.5,-12,35,3,-5);
            kamar(30,0,-12,35,3,-5);
            
				glEnd();
	glPopMatrix();
	
	

//tiang
       glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
		    glColor3f(1.0f,1.0f,1.0f);
			kamar(40,-0.5,0,42,15,-2);
			kamar(25,-0.5,0,27,15,-2);
			kamar(25,-0.5,-21,27,15,-23);
			kamar(40,-0.5,-21,42,15,-23);
		glEnd();
	glPopMatrix();
//tanah
 glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture[9]);
		glBegin(GL_QUADS);
		    glColor3f(1.0f,1.0f,1.0f);
			kamar(-30,0,-23,51,-0.5,2);		
        glEnd();
	glPopMatrix();

glPushMatrix();
glScalef(0.35, 0.65, 1);
glTranslatef(3.5,3.5,-3);
glColor3f(0,0,0);
glutSolidCube(5.0);
glPopMatrix();


	glFlush();
     
     
}
void reshape (int w, int h)
{
     glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, 1.0 * (GLfloat) w / (GLfloat) h, 1.0, 40.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, 0.0);
	gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (1024, 600);
    glutInitWindowPosition (20, 75);
    glutCreateWindow ("kamar");
    myinit ();
    glutDisplayFunc(display); 
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
return 0;
}


