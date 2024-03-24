
#include <GL\glew.h> // A cross-platform open-source C/C++ extension loading library
#include <GL\freeglut.h>
#include<cmath>
#include<iostream>

using namespace std;

#define PI 3.14159



GLfloat twicePi; int triangleAmount;
GLfloat radius;
GLfloat radiusmouthH = -.1f;
GLfloat x1;  GLfloat y; int i1;

GLfloat position2 = 21.0f;
GLfloat speed2 = 0.008f;

GLfloat position3 = 0.0f;
GLfloat speed3 = 2.5f;

float  w = 500, h = 500, newWidth, newHeight;
float specialtranslateX = 0, specialtranslateY = 0.5, specialtranslateZ = 1.5;
float transVal;
float transValx;
float transValy;
float scaleExp;
float angle;
int now;
int spinVal;
float scaleVal;
float transValcar;
float pointSize;
float allScale;
float thun;
int stopSpin;
int x;
int i;
int j;
int tt;
int CarMoveReverse = 0;
GLfloat col[] = {0.8, 0.2, 0.1};



int sw;
float transValybl;
float transValyrock;
GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat light_specular[] = { 1, 1, 1, 1.0 };
GLfloat light_position[] = { 2.0, 1.5, -2.0, 1.0 };
GLfloat mat_specular[] = { 1, 1, 1, 1.0 }; //{0.1, 0.1, 0.1, 0.1};
GLfloat mat_amb_diff[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat mat_amb[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat mat_diff[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat shininess[] = { 128 };//{128};  // (range: dull 0 – very shiny128)

GLuint myTexture1;

char image1Path[] = "C:/Users/albat/Desktop/fam.bmp";

GLuint myTexture2;

char image2Path[] = "C:/Users/albat/Desktop/fam2.bmp";

GLuint myTexture3;

char image3Path[] = "C:/Users/albat/Desktop/fam3.bmp";

GLuint myTexture4;

char image4Path[] = "C:/Users/albat/Desktop/fam4.bmp";

GLuint myTexture5;

char image5Path[] = "C:/Users/albat/Desktop/end.bmp";



GLuint LoadTexture(const char* filename, int width, int height)
{
	GLuint texture;
	unsigned char* data;
	FILE* file;

	//The following code will read in our RAW file
	file = fopen(filename, "rb");

	if (file == NULL)
	{
		cout << "Unable to open the image file" << endl << "Program will exit :(" << endl;
		exit(0);
		return 0;
	}

	data = (unsigned char*)malloc(width * height * 3);
	fread(data, width * height * 3, 1, file);

	fclose(file);


	// reorder the image colors to RGB not BGR
	for (int i = 0; i < width * height; ++i)
	{
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;

	}


	/////////////////////////////////////////
	// All Exercises TODO: load another texture image
	//////
	glGenTextures(1, &texture);            //generate the texture with the loaded data
	glBindTexture(GL_TEXTURE_2D, texture); //bind the texture to it's array

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); //set texture environment parameters

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	/////////////////////////////////////////

	free(data); //free the texture array

	if (glGetError() != GL_NO_ERROR)
		printf("GLError in genTexture()\n");

	return texture; //return whether it was successfull  
}
void init() {
	glClearColor(0.223, 0.360, 0.225, 1.0f);
	//glClearColor(0.8f, 0.2f, 0.3f, 1.0f); //TOBIAS
	//glClearColor(0.86f, 0.90f, 0.75f, 1.0f); // Set background color to orangeeee
	glMatrixMode(GL_PROJECTION); // set the projection parameters
	glLoadIdentity();
	glOrtho(-3.2, 3.2, -3.2, 3.2, -3.2, 3.2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(1.5, 1.5, -1.5, 0, 1, -1, 0, 1, 0);

	myTexture1 = LoadTexture(image1Path, 1024, 1024);

	if (myTexture1 == -1)
	{
		cout << "Error in loading the texture" << endl;
	}
	else
		cout << "The texture value is: " << myTexture1 << endl;

	myTexture2 = LoadTexture(image2Path, 1024, 1024);

	if (myTexture2 == -1)
	{
		cout << "Error in loading the texture" << endl;
	}
	else
		cout << "The texture value is: " << myTexture2 << endl;

	myTexture3 = LoadTexture(image3Path, 1024, 1024);

	if (myTexture3 == -1)
	{
		cout << "Error in loading the texture" << endl;
	}
	else
		cout << "The texture value is: " << myTexture3 << endl;

	myTexture4 = LoadTexture(image4Path, 1024, 1024);

	if (myTexture4 == -1)
	{
		cout << "Error in loading the texture" << endl;
	}
	else
		cout << "The texture value is: " << myTexture4 << endl;

	myTexture5 = LoadTexture(image5Path, 512, 512);

	if (myTexture5 == -1)
	{
		cout << "Error in loading the texture" << endl;
	}
	else
		cout << "The texture value is: " << myTexture5 << endl;
}
void reshape(int w, int h) {
	/*
	const float ratio = (float)w / h;
	float sx = ratio > 1.0f ? ratio : 1.0f;
	float sy = ratio > 1.0f ? 1 : 1.0f/ratio;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-sx, sx, -sy, sy, 0, 1);
	glViewport(0, 0, w, h);*/
	glViewport(0, 0, w, h);

	newWidth = w;

	newHeight = h;


}

void draw_pixel(GLint cx, GLint cy)
{
	glBegin(GL_POINTS);
	glVertex2i(cx, cy);
	glEnd();
}
void plotpixels(GLint h, GLint k, GLint x, GLint y)
{
	draw_pixel(x + h, y + k);
	draw_pixel(-x + h, y + k);
	draw_pixel(x + h, -y + k);
	draw_pixel(-x + h, -y + k);
	draw_pixel(y + h, x + k);
	draw_pixel(-y + h, x + k);
	draw_pixel(y + h, -x + k);
	draw_pixel(-y + h, -x + k);
}
void draw_circle(GLint h, GLint k, GLint r)
{
	GLint d = 1 - r, x = 0, y = r;
	while (y > x)
	{
		plotpixels(h, k, x, y);
		if (d < 0) d += 2 * x + 3;
		else
		{
			d += 2 * (x - y) + 5;
			--y;
		}
		++x;
	}
	plotpixels(h, k, x, y);
}
void square() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, myTexture1);
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);

	glTexCoord2f(1, 0);
	glVertex3f(3.2, -3.2, 0);


	glTexCoord2f(1, 1);
	glVertex3f(3.2, 3.2, 0);

	glTexCoord2f(0, 1);
	glVertex3f(-3.2, 3.2, 0);

	glTexCoord2f(0, 0);
	glVertex3f(-3.2, -3.2, 0);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}
void square2() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, myTexture2);
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);

	glTexCoord2f(1, 0);
	glVertex3f(3.2, -3.2, 0);


	glTexCoord2f(1, 1);
	glVertex3f(3.2, 3.2, 0);

	glTexCoord2f(0, 1);
	glVertex3f(-3.2, 3.2, 0);

	glTexCoord2f(0, 0);
	glVertex3f(-3.2, -3.2, 0);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}
void square3() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, myTexture3);
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);

	glTexCoord2f(1, 0);
	glVertex3f(3.2, -3.2, 0);


	glTexCoord2f(1, 1);
	glVertex3f(3.2, 3.2, 0);

	glTexCoord2f(0, 1);
	glVertex3f(-3.2, 3.2, 0);

	glTexCoord2f(0, 0);
	glVertex3f(-3.2, -3.2, 0);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}
void square4() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, myTexture4);
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);

	glTexCoord2f(1, 0);
	glVertex3f(3.2, -3.2, 0);


	glTexCoord2f(1, 1);
	glVertex3f(3.2, 3.2, 0);

	glTexCoord2f(0, 1);
	glVertex3f(-3.2, 3.2, 0);

	glTexCoord2f(0, 0);
	glVertex3f(-3.2, -3.2, 0);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}
void square5() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, myTexture5);
	glColor3f(0, 0, 0);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);

	glTexCoord2f(1, 0);
	glVertex3f(3.2, -3.2, 0);


	glTexCoord2f(1, 1);
	glVertex3f(3.2, 3.2, 0);

	glTexCoord2f(0, 1);
	glVertex3f(-3.2, 3.2, 0);

	glTexCoord2f(0, 0);
	glVertex3f(-3.2, -3.2, 0);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}
void clk() {
	glColor3f(0.6, 0.6, 0.6);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.3, 0);
	glVertex3f(0.0, 0, 0);
	glVertex3f(0.0, 0.3, 0);
	glVertex3f(0.0, 0, 0);
	glEnd();
}
void foodSmoke() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(1.0f, 1.0f, 1.0f, 0.4f);
	glPointSize(1);
	glBegin(GL_POLYGON);

	for (double i = 0; i < 2 * 3.14; i += 3.14 / 20) //<-- Change this Value
		glVertex3f(cos(i) * 0.3 + 0.3, sin(i) * 0.3 + 0.3, 0.0);

	for (double i = 0; i < 2 * 3.14; i += 3.14 / 20) //<-- Change this Value
		glVertex3f(cos(i) * 0.2 + 0.4, sin(i) * 0.2 + 0.5, 0.0);

	for (double i = 0; i < 2 * 3.14; i += 3.14 / 20) //<-- Change this Value
		glVertex3f(cos(i) * 0.22 + 0.15, sin(i) * 0.22 + 0.2, 0.0);

	for (double i = 0; i < 2 * 3.14; i += 3.14 / 20) //<-- Change this Value
		glVertex3f(cos(i) * 0.1 + 0.6, sin(i) * 0.1 + 0.1, 0.0);

	glEnd();
	glDisable(GL_BLEND);
}
void explosion() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(0.650, 0.446, 0.319f, 0.4f);
	glPointSize(1);
	glBegin(GL_POLYGON);

	for (double i = 0; i < 2 * 3.14; i += 3.14 / 20) //<-- Change this Value
		glVertex3f(cos(i) * 0.3 + 0.3, sin(i) * 0.3 + 0.3, 0.0);

	for (double i = 0; i < 2 * 3.14; i += 3.14 / 20) //<-- Change this Value
		glVertex3f(cos(i) * 0.2 + 0.4, sin(i) * 0.2 + 0.5, 0.0);

	for (double i = 0; i < 2 * 3.14; i += 3.14 / 20) //<-- Change this Value
		glVertex3f(cos(i) * 0.22 + 0.15, sin(i) * 0.22 + 0.2, 0.0);

	for (double i = 0; i < 2 * 3.14; i += 3.14 / 20) //<-- Change this Value
		glVertex3f(cos(i) * 0.1 + 0.6, sin(i) * 0.1 + 0.1, 0.0);

	glEnd();
	glDisable(GL_BLEND);
}
void blood() {
	glColor3f(0.710, 0.267, 0.156);
	glPointSize(3);
	glBegin(GL_POINTS);
	glVertex3f(0.0, -0.3, 0);
	glVertex3f(0.0, -0.3, 0);
	glEnd();
}
void rocket() {
	glColor3f(0.4, 0.4, 0.4);
	glBegin(GL_QUADS);
	glVertex3f(-1, 0.2, 0);
	glVertex3f(-1.07, 0.2, 0);
	glVertex3f(-1.07, 0.0, 0);
	glVertex3f(-1, 0.0, 0);
	glEnd();
	glColor3f(0.790, 0.783, 0.379);
	glBegin(GL_TRIANGLES);
	glVertex3f(-1, 0.2, 0);
	glVertex3f(-1.07, 0.2, 0);
	glVertex3f(-1.035, 0.3, 0);
	glEnd();
}
void cloud1() {
	//------------
		//cloud
	glPushMatrix();
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = .0f;  y = .2f;   radius = .15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = -0.15f;  y = 0.2f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = 0.15f;  y = 0.2f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = -0.3f;  y = 0.2f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = 0.3f;  y = 0.2f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = -0.45f;  y = 0.2f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = 0.45f;  y = 0.2f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = -0.35f;  y = 0.37f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = 0.35f;  y = 0.37f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = 0.35f;  y = 0.37f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = -0.18f;  y = 0.37f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = 0.18f;  y = 0.37f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = 0.1f;  y = 0.37f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = -0.1f;  y = 0.37f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = -0.13f;  y = 0.54f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = 0.13f;  y = 0.54f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = 0.0f;  y = 0.66f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}



	glEnd();
	glPopMatrix();
}
void cloud2() {
	//------------
		//cloud
	glPushMatrix();
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = .0f;  y = .2f;   radius = .15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = -0.15f;  y = 0.2f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = 0.15f;  y = 0.2f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = -0.3f;  y = 0.2f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = 0.3f;  y = 0.2f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = -0.45f;  y = 0.2f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = 0.45f;  y = 0.2f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = -0.35f;  y = 0.37f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = 0.35f;  y = 0.37f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = 0.35f;  y = 0.37f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = -0.18f;  y = 0.37f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = 0.18f;  y = 0.37f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = 0.1f;  y = 0.37f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = -0.1f;  y = 0.37f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = -0.13f;  y = 0.54f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = 0.13f;  y = 0.54f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = 0.0f;  y = 0.66f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}



	glEnd();
	glPopMatrix();
}
void color() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(0.850, 0.506, 0.161, 0.2f);
	glBegin(GL_QUADS);

	glVertex3f(3.2, -3.2, 0);

	glVertex3f(3.2, 3.2, 0);

	glVertex3f(-3.2, 3.2, 0);

	glVertex3f(-3.2, -3.2, 0);

	glEnd();
	glDisable(GL_BLEND);
}
void color2() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(1, 1, 1, thun);
	glBegin(GL_QUADS);

	glVertex3f(3.2, -3.2, 0);

	glVertex3f(3.2, 3.2, 0);

	glVertex3f(-3.2, 3.2, 0);

	glVertex3f(-3.2, -3.2, 0);

	glEnd();
	glDisable(GL_BLEND);
}
void thunder() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glColor4f(1, 1, 1, thun);
	glBegin(GL_QUADS);

	glVertex3f(3.2, -3.2, 0);

	glVertex3f(3.2, 3.2, 0);

	glVertex3f(-3.2, 3.2, 0);

	glVertex3f(-3.2, -3.2, 0);

	glEnd();
	glDisable(GL_BLEND);
}
void cloud3() {
	//------------
		//cloud
	glPushMatrix();
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = .0f;  y = .2f;   radius = .15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = -0.15f;  y = 0.2f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = 0.15f;  y = 0.2f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = -0.3f;  y = 0.2f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = 0.3f;  y = 0.2f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = -0.45f;  y = 0.2f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = 0.45f;  y = 0.2f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = -0.35f;  y = 0.37f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = 0.35f;  y = 0.37f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = 0.35f;  y = 0.37f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = -0.18f;  y = 0.37f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = 0.18f;  y = 0.37f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = 0.1f;  y = 0.37f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = -0.1f;  y = 0.37f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = -0.13f;  y = 0.54f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = 0.13f;  y = 0.54f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}
	glTranslatef(-0.5, 0.20, 0);// transletion
	x1 = 0.0f;  y = 0.66f;   radius = 0.15f;
	triangleAmount = 40;
	twicePi = 2.0f * PI;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x1, y);
	for (i1 = 0; i1 <= triangleAmount; i1++) {
		glVertex2f(
			x1 + (radius * cos(i1 * twicePi / triangleAmount)),
			y + (radius * sin(i1 * twicePi / triangleAmount))
		);
	}



	glEnd();
	glPopMatrix();
}
void cloud(int value) {
	if (position2 > 1.0)
		position2 = -1.0f;
	position2 += speed2;
	glutPostRedisplay();
	glutTimerFunc(100, cloud, 0);
}
void DrawEllipse(float cx, float cy, float rx, float ry, int num_segments) {
	float theta = 2 * 3.1415926 / float(num_segments);
	float c = cosf(theta);
	float s = sinf(theta);
	float t;

	float x = 1;
	float y = 0;

	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < num_segments; i++)
	{
		glVertex2f(x * rx + cx, y * ry + cy);
		t = x;
		x = c * x - s * y;
		y = s * t + c * y;
	}
	glEnd();
}
void flower1() {
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	glColor3f(0.0, 0.4, 0.3);
	glVertex2f(0.0f, -0.2f);
	glVertex2f(0.0f, 0.3f);
	glEnd();

	glPushMatrix();
	glColor3f(0.0, 0.4, 0.3);
	glRotatef(45, 0, 0, 1);
	glTranslatef(-0.2, 0.0, 0);
	DrawEllipse(0.0, 0.0, 0.1, 0.3, 40);
	glRotatef(90, 0, 0, 1);
	glTranslatef(-0.2, -0.2, 0);
	DrawEllipse(0.0, 0.0, 0.1, 0.3, 40);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.9, 0.7, 0.7);
	DrawEllipse(0.0, 0.4, 0.2, 0.3, 40);
	glColor3f(0.9, 0.7, 0.7);
	DrawEllipse(0.0, 0.4, 0.3, 0.2, 40);
	glPopMatrix();

}
void flower2() {
	glBegin(GL_LINES);
	glColor3f(0.0, 0.4, 0.3);
	glVertex2f(0.0f, -0.2f);
	glVertex2f(0.0f, 0.3f);
	glEnd();

	glPushMatrix();
	glColor3f(0.0, 0.4, 0.3);
	glRotatef(45, 0, 0, 1);
	glTranslatef(-0.2, 0.0, 0);
	DrawEllipse(0.0, 0.0, 0.1, 0.3, 40);
	glRotatef(90, 0, 0, 1);
	glTranslatef(-0.2, -0.2, 0);
	DrawEllipse(0.0, 0.0, 0.1, 0.3, 40);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.7, 0.1, 0.4);
	DrawEllipse(0.0, 0.4, 0.2, 0.3, 40);
	glColor3f(0.7, 0.1, 0.4);
	DrawEllipse(0.0, 0.4, 0.3, 0.2, 40);
	glPopMatrix();
}
GLfloat position4 = 0.0f;
GLfloat speed4 = 0.025f;
void ball(int value)
{
	if (position4 > 1.0)
		position4 = -1.0f;

	position4 += speed4;

	glutPostRedisplay();
	glutTimerFunc(100, ball, 0);
}
void ball()
{
	int i;

	GLfloat x = .0f; GLfloat y = .9f; GLfloat radius = .09f;
	int triangleAmount = 20;
	GLfloat twicePi = 2.0f * 3.14;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.5, 0.6, 0.6);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}
void rocket(int value) {
	if (position3 < -2.0)
		position3 = 1.0f;
	position3 += speed3;
	glutPostRedisplay();
	glutTimerFunc(100, rocket, 0);
}
GLfloat position5 = 0.0f;
GLfloat speed5 = 0.025f;
void rocket2(int value) {
	if (position5 < -2.0)
		position5 = 1.0f;
	position5 += speed5 ;
	glutPostRedisplay();
	glutTimerFunc(100, rocket, 0);
}
void house() {

	//back compound
	glColor3f(0.9, 0.9, 0.9);
	glBegin(GL_POLYGON);
	glVertex2f(550 / 1100.0, 375 / 700.0);
	glVertex2f(600 / 1100.0, 425 / 700.0);
	glVertex2f(825 / 1100.0, 425 / 700.0);
	glVertex2f(850 / 1100.0, 375 / 700.0);
	glEnd();
	//house
	glColor3f(0.460, 0.588, 0.590);
	glBegin(GL_POLYGON);
	glVertex2f(600 / 1100.0, 375 / 700.0);
	glVertex2f(600 / 1100.0, 450 / 700.0);
	glVertex2f(650 / 1100.0, 525 / 700.0);
	glVertex2f(700 / 1100.0, 450 / 700.0);
	glVertex2f(700 / 1100.0, 375 / 700.0);
	glEnd();
	//door
	glColor3f(0.550, 0.487, 0.423);
	glBegin(GL_POLYGON);
	glVertex2f(640 / 1100.0, 375 / 700.0);
	glVertex2f(640 / 1100.0, 410 / 700.0);
	glVertex2f(660 / 1100.0, 410 / 700.0);
	glVertex2f(660 / 1100.0, 375 / 700.0);
	glEnd();
	//roof
	glColor3f(0.310, 0.296, 0.282);
	glBegin(GL_POLYGON);
	glVertex2f(700 / 1100.0, 450 / 700.0);
	glVertex2f(650 / 1100.0, 525 / 700.0);
	glVertex2f(750 / 1100.0, 525 / 700.0);
	glVertex2f(800 / 1100.0, 450 / 700.0);
	glEnd();
	//
	glColor3f(0.609, 0.698, 0.700);
	glBegin(GL_POLYGON);
	glVertex2f(700 / 1100.0, 375 / 700.0);
	glVertex2f(700 / 1100.0, 450 / 700.0);
	glVertex2f(780 / 1100.0, 450 / 700.0);
	glVertex2f(780 / 1100.0, 375 / 700.0);
	glEnd();
	//window
	glColor3f(0.890, 0.881, 0.872);
	glBegin(GL_POLYGON);
	glVertex2f(725 / 1100.0, 400 / 700.0);
	glVertex2f(725 / 1100.0, 420 / 700.0);
	glVertex2f(740 / 1100.0, 420 / 700.0);
	glVertex2f(740 / 1100.0, 400 / 700.0);
	glEnd();
	//compound
	glColor3f(0.7, 0.7, 0.7);
	glBegin(GL_POLYGON);
	glVertex2f(550 / 1100.0, 325 / 700.0);
	glVertex2f(550 / 1100.0, 375 / 700.0);
	glVertex2f(850 / 1100.0, 375 / 700.0);
	glVertex2f(850 / 1100.0, 325 / 700.0);
	glEnd();

}
void car() {//car 1
	int l;
	glColor3f(0.520, 0.224, 0.229);
	glBegin(GL_POLYGON);
	glColor3f(0.270, 0.194, 0.196);
	glVertex2f(25 / 1100.0, 50 / 700.0);
	glColor3f(0.520, 0.224, 0.229);
	glVertex2f(25 / 1100.0, 125 / 700.0);
	glColor3f(0.520, 0.224, 0.229);
	glVertex2f(75 / 1100.0, 200 / 700.0);
	glColor3f(0.520, 0.224, 0.229);
	glVertex2f(175 / 1100.0, 200 / 700.0);
	glColor3f(0.520, 0.224, 0.229);
	glVertex2f(200 / 1100.0, 125 / 700.0);
	glColor3f(0.520, 0.224, 0.229);
	glVertex2f(250 / 1100.0, 115 / 700.0);
	glColor3f(0.270, 0.194, 0.196);
	glVertex2f(250 / 1100.0, 50 / 700.0);
	glEnd();
	//windows
	glColor3f(0.593, 0.664, 0.690);
	glBegin(GL_POLYGON);
	glVertex2f(35 / 1100.0, 125 / 700.0);
	glVertex2f(80 / 1100.0, 190 / 700.0);
	glColor3f(0.874, 0.910, 0.909);
	glVertex2f(115 / 1100.0, 190 / 700.0);
	glVertex2f(115 / 1100.0, 125 / 700.0);
	glEnd();
	glColor3f(0.593, 0.664, 0.690);
	glBegin(GL_POLYGON);
	glVertex2f(125 / 1100.0, 125 / 700.0);
	glVertex2f(125 / 1100.0, 190 / 700.0);
	glColor3f(0.874, 0.910, 0.909);
	glVertex2f(170 / 1100.0, 190 / 700.0);
	glVertex2f(190 / 1100.0, 125 / 700.0);
	glEnd();

	GLfloat x = 75 / 1100.0f; GLfloat y = 50 / 700.0f; GLfloat radius = .03f;
	int triangleAmount = 20;
	GLfloat twicePi = 2.0f * 3.14;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0, 0, 0);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
	x = 175 / 1100.0f;  y = 50 / 700.0f;  radius = .03f;
	triangleAmount = 20;
	twicePi = 2.0f * 3.14;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0, 0, 0);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();

	//car2
	glColor3f(0.948, 0.960, 0.595);
	glBegin(GL_POLYGON);
	glColor3f(0.948, 0.960, 0.595);
	glVertex2f(-470 / 1100.0, 50 / 700.0);
	glColor3f(0.948, 0.960, 0.595);
	glVertex2f(-470 / 1100.0, 112 / 700.0);
	glColor3f(0.948, 0.960, 0.595);
	glVertex2f(-400 / 1100.0, 125 / 700.0);
	glColor3f(0.948, 0.960, 0.595);
	glVertex2f(-372 / 1100.0, 210 / 700.0);
	glColor3f(0.948, 0.960, 0.595);
	glVertex2f(-210 / 1100.0, 210 / 700.0);
	glColor3f(0.948, 0.960, 0.595);
	glVertex2f(-180 / 1100.0, 125 / 700.0);
	glColor3f(0.948, 0.960, 0.595);
	glVertex2f(-135 / 1100.0, 125 / 700.0);
	glColor3f(0.948, 0.960, 0.595);
	glVertex2f(-110 / 1100.0, 50 / 700.0);
	glColor3f(0.948, 0.960, 0.595);
	glEnd();
	//windows
	glColor3f(0.593, 0.664, 0.690);
	glBegin(GL_POLYGON);
	glVertex2f(-410 / 1100.0, 125 / 700.0);
	glVertex2f(-364 / 1100.0, 200 / 700.0);
	glColor3f(0.874, 0.910, 0.909);
	glVertex2f(-300 / 1100.0, 200 / 700.0);
	glVertex2f(-300 / 1100.0, 125 / 700.0);
	glEnd();
	glColor3f(0.593, 0.664, 0.690);
	glBegin(GL_POLYGON);
	glVertex2f(-290 / 1100.0, 125 / 700.0);
	glVertex2f(-290 / 1100.0, 200 / 700.0);
	glColor3f(0.874, 0.910, 0.909);
	glVertex2f(-217 / 1100.0, 200 / 700.0);
	glVertex2f(-192 / 1100.0, 125 / 700.0);
	glEnd();
	x = -350 / 1100.0f;  y = 50 / 700.0f;  radius = .03f;
	triangleAmount = 20;
	twicePi = 2.0f * 3.14;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0, 0, 0);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
	x = -200 / 1100.0f;  y = 50 / 700.0f;  radius = .03f;
	triangleAmount = 20;
	twicePi = 2.0f * 3.14;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0, 0, 0);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
	glColor3f(0.255, 0.275, 0.500);
	glBegin(GL_POLYGON);
	glColor3f(0.191, 0.196, 0.290);
	glVertex2f(350 / 1100.0, 50 / 700.0);
	glColor3f(0.255, 0.275, 0.500);
	glVertex2f(350 / 1100.0, 275 / 700.0);
	glColor3f(0.255, 0.275, 0.500);
	glVertex2f(722 / 1100.0, 275 / 700.0);
	glColor3f(0.255, 0.275, 0.500);
	glVertex2f(750 / 1100.0, 175 / 700.0);
	glColor3f(0.191, 0.196, 0.290);
	glVertex2f(750 / 1100.0, 50 / 700.0);
	glEnd();
	glColor3f(0.593, 0.664, 0.690);
	glBegin(GL_POLYGON);
	glVertex2f(650 / 1100.0, 175 / 700.0);
	glVertex2f(650 / 1100.0, 260 / 700.0);
	glColor3f(0.874, 0.910, 0.909);
	glVertex2f(720 / 1100.0, 260 / 700.0);
	glVertex2f(745 / 1100.0, 175 / 700.0);
	glEnd();
	glColor3f(0.593, 0.664, 0.690);
	glBegin(GL_POLYGON);
	glVertex2f(550 / 1100.0, 175 / 700.0);
	glVertex2f(550 / 1100.0, 260 / 700.0);
	glColor3f(0.874, 0.910, 0.909);
	glVertex2f(625 / 1100.0, 260 / 700.0);
	glVertex2f(625 / 1100.0, 175 / 700.0);
	glEnd();
	glColor3f(0.593, 0.664, 0.690);
	glBegin(GL_POLYGON);
	glVertex2f(450 / 1100.0, 175 / 700.0);
	glVertex2f(450 / 1100.0, 260 / 700.0);
	glColor3f(0.874, 0.910, 0.909);
	glVertex2f(525 / 1100.0, 260 / 700.0);
	glVertex2f(525 / 1100.0, 175 / 700.0);
	glEnd();
	glColor3f(0.593, 0.664, 0.690);
	glBegin(GL_POLYGON);
	glVertex2f(375 / 1100.0, 175 / 700.0);
	glVertex2f(375 / 1100.0, 260 / 700.0);
	glColor3f(0.874, 0.910, 0.909);
	glVertex2f(425 / 1100.0, 260 / 700.0);
	glVertex2f(425 / 1100.0, 175 / 700.0);
	glEnd();
	for (l = 0; l < 30; l++)
	{
		glColor3f(0.0, 0.0, 0.0);
		draw_circle(450 / 1100.0, 50 / 700.0, l);
		draw_circle(625 / 1100.0, 50 / 700.0, l);
	}
	x = 450 / 1100.0f;  y = 50 / 700.0f;  radius = .035f;
	triangleAmount = 20;
	twicePi = 2.0f * 3.14;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0, 0, 0);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
	x = 625 / 1100.0f;  y = 50 / 700.0f;  radius = .035f;
	triangleAmount = 20;
	twicePi = 2.0f * 3.14;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0, 0, 0);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}
void tree() {
	int l;
	//tree
	glColor3f(0.380, 0.337, 0.289);
	glBegin(GL_POLYGON);
	glVertex2f(350 / 1100.0, 325 / 700.0);
	glVertex2f(350 / 1100.0, 395 / 700.0);
	glVertex2f(365 / 1100.0, 395 / 700.0);
	glVertex2f(365 / 1100.0, 325 / 700.0);
	glEnd();
	for (l = 0; l <= 30; l++)
	{
		glColor3f(0.0, 0.5, 0.0);
		draw_circle(340 / 1100.0, 400 / 700.0, l);
		draw_circle(380 / 1100.0, 400 / 700.0, l);

	}
	GLfloat x = 340 / 1100.0f; GLfloat y = 400 / 700.0f; GLfloat radius = .03f;
	int triangleAmount = 20;
	GLfloat twicePi = 2.0f * 3.14;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.242, 0.310, 0.217);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
	x = 380 / 1100.0f;  y = 400 / 700.0f;  radius = .035f;
	triangleAmount = 20;
	twicePi = 2.0f * 3.14;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.242, 0.310, 0.217);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();


	for (l = 0; l <= 25; l++)
	{
		glColor3f(0.465, 0.570, 0.353);
		draw_circle(350 / 1100.0, 440 / 700.0, l);
		draw_circle(370 / 1100.0, 440 / 700.0, l);
	}
	x = 370 / 1100.0f;  y = 440 / 700.0;  radius = .035f;
	triangleAmount = 20;
	twicePi = 2.0f * 3.14;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.242, 0.310, 0.217);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
	x = 350 / 1100.0f;  y = 440 / 700.0f;  radius = .035f;
	triangleAmount = 20;
	twicePi = 2.0f * 3.14;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.242, 0.310, 0.217);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
	x = 361 / 1100.0f;  y = 464 / 700.0f;  radius = .03f;
	triangleAmount = 20;
	twicePi = 2.0f * 3.14;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.242, 0.310, 0.217);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
	for (l = 0; l <= 20; l++)
	{
		glColor3f(0.0, 0.5, 0.0);
		draw_circle(360 / 1100.0, 465 / 700.0, l);
	}


	glEnd();
}
void road() {
	//road boundary
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(0, 150 / 700.0);
	glVertex2f(0, 160 / 700.0);
	glVertex2f(1100 / 1100.0, 160 / 700.0);
	glVertex2f(1100 / 1100.0, 150 / 700.0);
	glEnd();
	//road
	glColor3f(0.2, 0.2, 0.2);
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(0, 150 / 700.0);
	glVertex2f(1100 / 1100.0, 150 / 700.0);
	glVertex2f(1100 / 1100.0, 0);
	glEnd();
}
void sky() {
	//sky

	glBegin(GL_POLYGON);
	glColor3f(0.870, 0.880, 0.581);
	glVertex2f(0 / 1100.0, 450 / 700.0);
	glColor3f(0.581, 0.880, 0.875);
	glVertex2f(0 / 1100.0, 700 / 700.0);
	glColor3f(0.581, 0.880, 0.875);
	glVertex2f(1100 / 1100.0, 700 / 700.0);
	glColor3f(0.870, 0.880, 0.581);
	glVertex2f(1100 / 1100.0, 450 / 700.0);
	glEnd();
}
void grass() {
	//sky

	glBegin(GL_POLYGON);
	glColor3f(0.469, 0.530, 0.355);
	glVertex2f(0 / 1100.0, 450 / 700.0);
	glColor3f(0.238, 0.450, 0.242);
	glVertex2f(0 / 1100.0, 0 / 700.0);
	glColor3f(0.238, 0.450, 0.242);
	glVertex2f(1100 / 1100.0, 0 / 700.0);
	glColor3f(0.469, 0.530, 0.355);
	glVertex2f(1100 / 1100.0, 450 / 700.0);
	glEnd();
}
void sun() {

	GLfloat x = 130 / 1100.0f; GLfloat y = 600 / 700.0f; GLfloat radius = .05f;
	int triangleAmount = 20;
	GLfloat twicePi = 2.0f * 3.14;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1, 1, 0.6);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}
void house2() {


	


	glPushMatrix();
	glColor3d(0.370, 0.247, 0.107);//big squre_1
	glBegin(GL_POLYGON);
	glColor3d(0.370, 0.247, 0.107);
	glVertex2d(-2.3, 2.2);
	glColor3d(0.580, 0.478, 0.325);
	glVertex2d(0.7, 2.2);
	glVertex2d(0.7, 0.7);
	glColor3d(0.370, 0.247, 0.107);
	glVertex2d(-2.3, 0.7);
	glEnd();
	glPopMatrix();

	
	glColor3d(0.850, 0.572, 0.255);//down squre_1
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex2d(-2.3, 0.7);
	glColor3d(0.910, 0.779, 0.582);
	glVertex2d(0.6, 0.7);
	glVertex2d(0.6, -1.5);
	glColor3d(0.850, 0.572, 0.255);
	glVertex2d(-2.3, -1.5);
	glEnd();
	glPopMatrix();

	glColor3d(0.370, 0.247, 0.107);//المربع اللي في الجنب
	glPushMatrix();
	glBegin(GL_POLYGON);
	glColor3d(0.370, 0.247, 0.107);
	glVertex2d(0.6, 1.7);
	glColor3d(0.580, 0.478, 0.325);
	glVertex2d(2.3, 1.7);
	glVertex2d(2.3, -1.5);
	glColor3d(0.370, 0.247, 0.107);
	glVertex2d(0.6, -1.5);
	glEnd();
	glPopMatrix();



	glColor3f(1, 0.0, 0.0);//down squre_2
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex2d(-2.5, 0.8);
	glColor3d(0.910, 0.779, 0.582);
	glVertex2d(2.5, 0.8);
	glVertex2d(2.5, 0.7);
	glVertex2d(-2.5, 0.7);
	glEnd();
	glPopMatrix();


	glColor3d(0.850, 0.572, 0.255);//مثلث البيت فوق
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex2d(-2.1, 0.8);
	
	glVertex2d(-1.2, 2.2);
	glColor3d(0.910, 0.779, 0.582);
	glVertex2d(-0.2, 0.8);
	glEnd();
	glPopMatrix();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.970, 0.934, 0.834);//مثلث البيت فوق
	glPushMatrix();
	glBegin(GL_TRIANGLES);
	glVertex2d(-2.1, 0.8);
	glVertex2d(-1.2, 2.2);
	glVertex2d(-0.2, 0.8);
	glEnd();
	glPopMatrix();

	

	glColor3d(0.461, 0.692, 0.940);//الطاقه في المثلث 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex2d(-1.4, 1.7);
	glVertex2d(-1.0, 1.7);
	glColor3d(0.871, 0.984, 0.990);
	glVertex2d(-1.0, 1.2);
	glVertex2d(-1.4, 1.2);
	glEnd();
	glPopMatrix();

	glColor3d(0.0, 0.0, 0.0);//الطاقه في المثلث 
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex2d(-1.4, 1.7);
	glVertex2d(-1.0, 1.7);
	glVertex2d(-1.0, 1.2);
	glVertex2d(-1.4, 1.2);
	glEnd();
	glPopMatrix();



	glColor3d(0.370, 0.247, 0.107);//الباب 
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex2d(-1.5, -0.5);
	glVertex2d(-1, -0.5);
	glVertex2d(-1, -1.5);
	glVertex2d(-1.5, -1.5);
	glEnd();
	glPopMatrix();



	glColor3d(0.400, 0.372, 0.296);//طاقه الباب  
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex2d(-1.4, -0.6);
	glVertex2d(-1.1, -0.6);
	glColor3d(0.200, 0.172, 0.296);
	glVertex2d(-1.1, -1.3);
	glVertex2d(-1.4, -1.3);
	glEnd();
	glPopMatrix();

	glColor3d(0.850, 0.572, 0.255);//المربع اللي عاليمين 
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex2d(0.6, 0.8);
	glColor3d(0.910, 0.779, 0.582);
	glVertex2d(2.3, 0.8);
	glVertex2d(2.3, -1.5);
	glColor3d(0.850, 0.572, 0.255);
	glVertex2d(0.6, -1.5);
	glPopMatrix();
	glEnd();

	glColor3d(0.380, 0.353, 0.277);//طاقه اليمين  
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_POLYGON);
	glVertex2d(-1.4, -0.6);
	glVertex2d(-1.1, -0.6);
	glColor3d(0.380, 0.353, 0.277);
	glVertex2d(-1.1, -1.3);
	glVertex2d(-1.4, -1.3);
	glEnd();

	glColor3d(0.461, 0.692, 0.940);//الطاقه في المربع الصغير اللي في الجنب
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex2d(0.9, 0.3);
	glVertex2d(1.9, 0.3);
	glColor3d(0.871, 0.984, 0.990);
	glVertex2d(1.9, -0.4);
	glVertex2d(0.9, -0.4);
	glEnd();
	glPopMatrix();

	glColor3f(0.970, 0.934, 0.834);//ألمستطيل الصغير 
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex2d(-2.5, 0.8);
	glVertex2d(2.5, 0.8);
	glVertex2d(2.5, 0.7);
	glVertex2d(-2.5, 0.7);
	glEnd();
	glPopMatrix();


	glColor3f(0.0, 0.0, 0.0);//الحطوط في الطاقه المربع الصغير اللي في الجنب
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex2d(0.9, 0.3);
	glVertex2d(1.9, 0.3);
	glVertex2d(1.9, -0.4);
	glVertex2d(0.9, -0.4);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_LINES);//خط الطاقه لللمربع الصغير
	glVertex2d(1.4, 0.3);
	glVertex2d(1.4, -0.4);
	glEnd();
	glPopMatrix();

	glColor3f(0.970, 0.934, 0.834);
	glPushMatrix();
	glBegin(GL_LINES);//خط البيت اللي نازل من المثلث
	glVertex2d(-0.2, 0.7);
	glVertex2d(-0.2, -1.5);
	glEnd();
	glBegin(GL_LINES);//خط البيت اللي نازل من المثلث
	glVertex2d(-2.1, 0.7);
	glVertex2d(-2.1, -1.5);
	glEnd();
	glPopMatrix();

	glColor3d(0.400, 0.372, 0.296);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPushMatrix();
	glBegin(GL_POLYGON);//عتبه
	glVertex2d(-0.2, -1.5);
	glVertex2d(2.3, -1.5);
	glVertex2d(2.3, -1.3);
	glVertex2d(-0.2, -1.3);
	glEnd();
	glPopMatrix();


	glColor3d(0.461, 0.692, 0.940);//الطاقه فوق الباب
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex2d(-1.7, 0.4);
	glVertex2d(-0.7, 0.4);
	glColor3d(0.871, 0.984, 0.990);
	glVertex2d(-0.7, -0.2);
	glVertex2d(-1.7, -0.2);
	glEnd();
	glPopMatrix();

	glColor3d(0.0, 0.0, 0.0);//الطاقه فوق الباب
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex2d(-1.7, 0.4);
	glVertex2d(-0.7, 0.4);
	glVertex2d(-0.7, -0.2);
	glVertex2d(-1.7, -0.2);
	glEnd();
	glPopMatrix();

	glColor3d(0.0, 0.0, 0.0);//خط الطاقه
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex2d(-1.2, 0.4);
	glVertex2d(-1.2, -0.2);
	glEnd();


	glColor3d(0.370, 0.247, 0.107);//مدخنة
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex2d(0.95, 1.7);
	glVertex2d(0.95, 2.3);
	glVertex2d(1.1, 2.3);
	glVertex2d(1.1, 1.7);

	glVertex2d(0.76, 2.5);
	glVertex2d(0.76, 2.3);
	glVertex2d(1.25, 2.3);
	glVertex2d(1.25, 2.5);
	glEnd();
	glPopMatrix();

}
void Circle(int xx, int yy, int r)
{

	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{


		float pi = 3.1416;
		float A = (i * 2 * pi) / 200;
		float x = r * cos(A);
		float y = r * sin(A);
		glVertex2f(x + xx, y + yy);
	}
	glEnd();
}
void nat() {
	// شارع 
	glBegin(GL_POLYGON);

	glColor3f(0.0, 0.02, 0.02);
	glVertex2f(0, -2);
	glVertex2f(1040 / 1040.0, -2);
	glColor3f(0.2, 0.22, 0.22);
	glVertex2f(1040 / 1040.0, 180 / 1040.0);\
	glVertex2f(0, 180 / 1040.0);

	glEnd();
	// line 
	glColor3f(1.0, 0.8, 0.2);
	glLineWidth(2); // WIDTH LINE
	glLineStipple(2, 0x00FF); //SIZE LINE 
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glVertex2f(0, 5 / 1040.0 );
	glVertex2f(1040 / 1040.0, 5 / 1040.0 );
	glEnd();
	glDisable(GL_LINE_STIPPLE);

	glColor3f(1.0, 0.8, 0.2);
	glLineWidth(2); // WIDTH LINE
	glLineStipple(2, 0x00FF); //SIZE LINE 
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glVertex2f(1 / 1040.0, 25 / 1040.0);
	glVertex2f(1080 / 1040.0,25 / 1040.0);
	glEnd();
	glDisable(GL_LINE_STIPPLE);


}
void car0() {

	
	glBegin(GL_POLYGON); //الهيكل
	glColor3f(0.650, 0.370, 0.370);
	glVertex2f(140 / 1040.0, 152 / 1040.0);
	glVertex2f(190 / 1040.0, 152 / 1040.0);
	glVertex2f(215 / 1040.0, 127 / 1040.0);
	glVertex2f(240 / 1040.0, 127 / 1040.0);
	glVertex2f(240 / 1040.0, 92 / 1040.0);
	glVertex2f(110 / 1040.0, 92 / 1040.0);
	glVertex2f(110 / 1040.0, 127 / 1040.0);
	glVertex2f(130 / 1040.0, 127 / 1040.0);
	glVertex2f(140 / 1040.0, 152 / 1040.0);
	glEnd();


	glBegin(GL_POLYGON);
	glColor3f(0.9, 1.0, 1.0);
	glVertex2f(140 / 1040.0, 152 / 1040.0);
	glVertex2f(190 / 1040.0, 152 / 1040.0);
	glVertex2f(215 / 1040.0, 127 / 1040.0);
	glVertex2f(210 / 1040.0, 127 / 1040.0);
	glVertex2f(130 / 1040.0, 127 / 1040.0);
	glVertex2f(120 / 1040.0, 127 / 1040.0);

	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.2, 0.1);
	glVertex2f(170 / 1040.0, 152 / 1040.0);
	glVertex2f(165 / 1040.0, 152 / 1040.0);
	glVertex2f(165 / 1040.0, 127 / 1040.0);
	glVertex2f(170 / 1040.0, 127 / 1040.0);
	glEnd();


	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.2, 0.1);

	glVertex2f(140 / 1040.0, 152 / 1040.0);
	glVertex2f(190 / 1040.0, 152 / 1040.0);
	glVertex2f(185 / 1040.0, 157 / 1040.0);
	glVertex2f(140 / 1040.0, 157 / 1040.0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.2, 0.1);
	glVertex2f(190 / 1040.0, 152 / 1040.0);
	glVertex2f(215 / 1040.0, 127 / 1040.0);
	glVertex2f(210 / 1040.0, 127 / 1040.0);
	glVertex2f(185 / 1040.0, 152 / 1040.0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.2, 0.1);
	glVertex2f(140 / 1040.0, 157 / 1040.0);
	glVertex2f(115 / 1040.0, 127 / 1040.0);
	glVertex2f(125 / 1040.0, 127 / 1040.0);
	glVertex2f(140 / 1040.0, 152 / 1040.0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.2, 0.1);
	glVertex2f(115 / 1040.0, 124 / 1040.0);
	glVertex2f(215 / 1040.0, 124 / 1040.0);
	glVertex2f(215 / 1040.0, 127 / 1040.0);
	glVertex2f(115 / 1040.0, 127 / 1040.0);

	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.9, 0.9, 0.9);
	glVertex2f(242 / 1040.0, 92 / 1040.0);
	glVertex2f(110 / 1040.0, 92 / 1040.0);
	glVertex2f(110 / 1040.0, 97 / 1040.0);
	glVertex2f(242 / 1040.0, 97 / 1040.0);

	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(238.5 / 1040.0, 124.5 / 1040.0);
	glVertex2f(231.5 / 1040.0, 125.5 / 1040.0);
	glVertex2f(231.5 / 1040.0, 119 / 1040.0);
	glVertex2f(238.5 / 1040.0, 117 / 1040.0);
	glEnd();

	GLfloat x = 135 / 1100.0f; GLfloat y = 50 / 700.0f; GLfloat radius = .014f;
	int triangleAmount = 20;
	GLfloat twicePi = 2.0f * 3.14;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0, 0, 0);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
	x = 235 / 1100.0f;  y = 50 / 700.0f;  radius = .014f;
	//x = 175 / 1100.0f;  y = 50 / 700.0f;  radius = .03f;
	triangleAmount = 20;
	twicePi = 2.0f * 3.14;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0, 0, 0);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
	




}
void car20() {
	glBegin(GL_POLYGON); //الهيكل
	glColor3f(0.506, 0.650, 0.370);
	glVertex2f(140 / 1040.0, 152 / 1040.0);
	glVertex2f(190 / 1040.0, 152 / 1040.0);
	glVertex2f(215 / 1040.0, 127 / 1040.0);
	glVertex2f(240 / 1040.0, 127 / 1040.0);
	glVertex2f(240 / 1040.0, 92 / 1040.0);
	glVertex2f(110 / 1040.0, 92 / 1040.0);
	glVertex2f(110 / 1040.0, 127 / 1040.0);
	glVertex2f(130 / 1040.0, 127 / 1040.0);
	glVertex2f(140 / 1040.0, 152 / 1040.0);
	glEnd();


	glBegin(GL_POLYGON);
	glColor3f(0.9, 1.0, 1.0);
	glVertex2f(140 / 1040.0, 152 / 1040.0);
	glVertex2f(190 / 1040.0, 152 / 1040.0);
	glVertex2f(215 / 1040.0, 127 / 1040.0);
	glVertex2f(210 / 1040.0, 127 / 1040.0);
	glVertex2f(130 / 1040.0, 127 / 1040.0);
	glVertex2f(120 / 1040.0, 127 / 1040.0);

	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.5, 0.2);
	glVertex2f(170 / 1040.0, 152 / 1040.0);
	glVertex2f(165 / 1040.0, 152 / 1040.0);
	glVertex2f(165 / 1040.0, 127 / 1040.0);
	glVertex2f(170 / 1040.00, 127 / 1040.0);
	glEnd();


	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.5, 0.2);

	glVertex2f(140 / 1040.0, 152 / 1040.0);
	glVertex2f(190 / 1040.0, 152 / 1040.0);
	glVertex2f(185 / 1040.0, 157 / 1040.0);
	glVertex2f(140 / 1040.0, 157 / 1040.0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.5, 0.2);
	glVertex2f(190 / 1040.0 ,152 / 1040.0);
	glVertex2f(215 / 1040.0, 127 / 1040.0);
	glVertex2f(210 / 1040.0, 127 / 1040.0);
	glVertex2f(185 / 1040.0, 152 / 1040.0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.5, 0.2);
	glVertex2f(140 / 1040.0, 157 / 1040.0);
	glVertex2f(115 / 1040.0, 127 / 1040.0);
	glVertex2f(125 / 1040.0, 127 / 1040.0);
	glVertex2f(140 / 1040.0, 152 / 1040.0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.5, 0.2);
	glVertex2f(115 / 1040.0, 124 / 1040.0);
	glVertex2f(215 / 1040.0, 124 / 1040.0);
	glVertex2f(215 / 1040.0, 127 / 1040.0);
	glVertex2f(115 / 1040.0, 127 / 1040.0);

	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.9, 0.9, 0.9);
	glVertex2f(242 / 1040.0, 92 / 1040.0);
	glVertex2f(110 / 1040.0, 92 / 1040.0);
	glVertex2f(110 / 1040.0, 97 / 1040.0);
	glVertex2f(242 / 1040.0, 97 / 1040.0);

	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(238.5 / 1040.0, 124.5 / 1040.0);
	glVertex2f(231.5 / 1040.0, 125.5 / 1040.0);
	glVertex2f(231.5 / 1040.0, 119 / 1040.0);
	glVertex2f(238.5 / 1040.0, 117 / 1040.0);
	glEnd();

	GLfloat x = 130 / 1100.0f; GLfloat y = 50 / 700.0f; GLfloat radius = .014f;
	int triangleAmount = 20;
	GLfloat twicePi = 2.0f * 3.14;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0, 0, 0);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
	x = 230 / 1100.0f;  y = 50 / 700.0f;  radius = .014f;
	//x = 175 / 1100.0f;  y = 50 / 700.0f;  radius = .03f;
	triangleAmount = 20;
	twicePi = 2.0f * 3.14;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0, 0, 0);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();



}
void car30() {

	glBegin(GL_POLYGON); //الهيكل
	glColor3f(0.370, 0.543, 0.650);
	glVertex2f(140 / 1040.0, 152 / 1040.0);
	glVertex2f(190 / 1040.0, 152 / 1040.0);
	glVertex2f(215 / 1040.0, 127 / 1040.0);
	glVertex2f(240 / 1040.0, 127 / 1040.0);
	glVertex2f(240 / 1040.0, 92 / 1040.0);
	glVertex2f(110 / 1040.0, 92 / 1040.0);
	glVertex2f(110 / 1040.0, 127 / 1040.0);
	glVertex2f(130 / 1040.0, 127 / 1040.0);
	glVertex2f(140 / 1040.0, 152 / 1040.0);
	glEnd();


	glBegin(GL_POLYGON);
	glColor3f(0.9, 1.0, 1.0);
	glVertex2f(140 / 1040.0, 152 / 1040.0);
	glVertex2f(190 / 1040.0, 152 / 1040.0);
	glVertex2f(215 / 1040.0, 127 / 1040.0);
	glVertex2f(210 / 1040.0, 127 / 1040.0);
	glVertex2f(130 / 1040.0, 127 / 1040.0);
	glVertex2f(120 / 1040.0, 127 / 1040.0);

	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.8, 1.0);
	glVertex2f(170 / 1040.0, 152 / 1040.0);
	glVertex2f(165 / 1040.0, 152 / 1040.0);
	glVertex2f(165 / 1040.0, 127 / 1040.0);
	glVertex2f(170 / 1040.0, 127 / 1040.0);
	glEnd();


	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.8, 1.0);

	glVertex2f(140 / 1040.0, 152 / 1040.0);
	glVertex2f(190 / 1040.0, 152 / 1040.0);
	glVertex2f(185 / 1040.0, 157 / 1040.0);
	glVertex2f(140 / 1040.0, 157 / 1040.0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.8, 1.0);
	glVertex2f(190 / 1040.0, 152 / 1040.0);
	glVertex2f(215 / 1040.0, 127 / 1040.0);
	glVertex2f(210 / 1040.0, 127 / 1040.0);
	glVertex2f(185 / 1040.0, 152 / 1040.0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.8, 1.0);
	glVertex2f(140 / 1040.0, 157 / 1040.0);
	glVertex2f(115 / 1040.0, 127 / 1040.0);
	glVertex2f(125 / 1040.0, 127 / 1040.0);
	glVertex2f(140 / 1040.0, 152 / 1040.0);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.8, 1.0);
	glVertex2f(115 / 1040.0, 124 / 1040.0);
	glVertex2f(215 / 1040.0, 124 / 1040.0);
	glVertex2f(215 / 1040.0, 127 / 1040.0);
	glVertex2f(115 / 1040.0, 127 / 1040.0);

	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.9, 1.0, 1.0);
	glVertex2f(242 / 1040.0, 92 / 1040.0);
	glVertex2f(110 / 1040.0, 92 / 1040.0);
	glVertex2f(110 / 1040.0, 97 / 1040.0);
	glVertex2f(242 / 1040.0, 97 / 1040.0);

	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2f(238.5 / 1040.0, 124.5 / 1040.0);
	glVertex2f(231.5 / 1040.0, 125.5 / 1040.0);
	glVertex2f(231.5 / 1040.0, 119 / 1040.0);
	glVertex2f(238.5 / 1040.0, 117 / 1040.0);
	glEnd();

	GLfloat x = 135 / 1100.0f; GLfloat y = 50 / 700.0f; GLfloat radius = .014f;
	int triangleAmount = 20;
	GLfloat twicePi = 2.0f * 3.14;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0, 0, 0);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
	x = 235 / 1100.0f;  y = 50 / 700.0f;  radius = .014f;
	//x = 175 / 1100.0f;  y = 50 / 700.0f;  radius = .03f;
	triangleAmount = 20;
	twicePi = 2.0f * 3.14;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0, 0, 0);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();


}
void ScaledCar() // تحريك السيارة 
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(500, 10, 0);
	glScalef(-0.9, 0.9, 0); // عكس السيارة 
	glTranslatef(-100.5, 0, 0);
	car0();
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(500, 10, 0);
	glScalef(-0.9, 0.9, 0); // عكس السيارة 
	glTranslatef(-100.5, 0, 0);
	car20();
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(500, 10, 0);
	glScalef(-0.9, 0.9, 0); // عكس السيارة 
	glTranslatef(-100.5, 0, 0);
	car30();
	glPopMatrix();
}
void MovingCar() // لتحريك السيارة 
{
	glMatrixMode(GL_MODELVIEW);


	glPushMatrix();
	glTranslatef(CarMoveReverse % 550, 0, 0);

	ScaledCar();
	glPopMatrix();

}

void MoveCarReverse(int value) { // تحرك السيارة 



	CarMoveReverse -= 1; // يروح على جهة اليسار 

	glutPostRedisplay();
	glutTimerFunc(20, MoveCarReverse, 0); // سرعة السيارة 
}


void display() {


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-3.2, 3.2, -3.2, 3.2, -3.2, 3.2);

	//house2();
	




	glPushMatrix();

	glTranslatef(transValx, 0, 0);
	glScalef(allScale, allScale, 0.0);
	if (sw == 0) {
		square();
		glPushMatrix();
		glTranslatef(0, transValy, 0);
		foodSmoke();
		glPopMatrix();

	}
	else if (sw == 1) {
		square2();
		glPushMatrix();
		glTranslatef(0, transValybl, 0);
		blood();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-2.3, 2.5, 0);
		glTranslatef(transValyrock, transValyrock, 0);
		glRotatef(130, 0, 0, 1.0);
		rocket();
		glPopMatrix();
	}
	else if (sw == 2) {

		square3();

		glPushMatrix();
		glTranslatef(0.4, 2.0, 0);
		glTranslatef(position2, 0.0f, 0.0f);
		cloud1();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(1.0, 1.2, 0);
		glScalef(0.5, 0.5, 0);
		flower1();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(2.0, 1.2, 0);
		glScalef(0.5, 0.5, 0);
		flower2();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-2.0, -3.99, 0);
		glScalef(2.0, 2.0, 0);
		glTranslatef(position4 + 1, 0, 0.0f);
		ball();
		glPopMatrix();


		glPushMatrix();
		glTranslatef(-0.85, 2.0, 0);
		glTranslatef(position2, 0.0f, 0.0f);
		cloud2();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.99, 2.0, 0);
		glTranslatef(position2, 0.0f, 0.0f);
		cloud3();
		glPopMatrix();

	}
	else if (sw == 3) {

		square4();

		color();

		glPushMatrix();
		glTranslatef(2.99, 5.0, 0);
		glTranslatef(transValyrock, transValyrock, 0);
		glRotatef(130, 0, 0, 1.0);
		glScalef(1.5, 1.5, 0);
		glTranslatef(0.0, position4, 0.0f);
		//rocket();
		glPopMatrix();




		glPushMatrix();
		glTranslatef(0.4, 2.0, 0);
		glTranslatef(position2, 0.0f, 0.0f);
		cloud1();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(1.0, 1.2, 0);
		glScalef(0.5, 0.5, 0);
		glRotatef(100, 0, 0, 1.0);
		flower1();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(2.0, 1.2, 0);
		glScalef(0.5, 0.5, 0);
		glRotatef(100, 0, 0, 1.0);
		flower2();
		glPopMatrix();


		glPushMatrix();
		glTranslatef(-0.85, 2.0, 0);
		glTranslatef(position2, 0.0f, 0.0f);
		cloud2();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.99, 2.0, 0);
		glTranslatef(position2, 0.0f, 0.0f);
		cloud3();
		glPopMatrix();

		thunder();

	}
	else if (sw == 4) {


		glPushMatrix();
		glTranslatef(0.4, 2.0, 0);
		glTranslatef(position2, 0.0f, 0.0f);
		cloud1();
		glPopMatrix();

		

		glPushMatrix();
		glTranslatef(-3.2, -2, 0);
		glScalef(6.5, 5.2, 0);
		sky();
		grass();
		glPushMatrix();
		glScalef(0.9, 1, 0);
		sun();
		glPopMatrix();
		nat();

		glPushMatrix();
		glTranslatef(-0.2, 0.1, 0);
		tree();
		glPopMatrix();

		glPushMatrix();
		glScalef(0.8, 0.8, 0);
		glTranslatef(-0.13, 0.2, 0);
		tree();
		glPopMatrix();

		glPushMatrix();
		glScalef(0.8, 0.8, 0);
		glTranslatef(-0.27, 0.2, 0);
		tree();
		glPopMatrix();

		glPushMatrix();
		glScalef(0.8, 0.8, 0);
		glTranslatef(-0.05, 0.24, 0);
		tree();
		glPopMatrix();

		glPushMatrix();
		glScalef(0.8, 0.8, 0);
		glTranslatef(0.02, 0.2, 0);
		tree();
		glPopMatrix();


		glPushMatrix();
		glScalef(0.8, 0.8, 0);
		glTranslatef(0.42, 0.2, 0);
		tree();
		glPopMatrix();


		glPushMatrix();
		glScalef(0.8, 0.8, 0);
		glTranslatef(0.9, 0.2, 0);
		tree();
		glPopMatrix();


		glPushMatrix();
		glScalef(1.2, 1.2, 0);
		glTranslatef(-0.35, -0.05, 0);
		tree();
		glPopMatrix();



		glPushMatrix();
		glScalef(1.5, 1.5, 0);
		glTranslatef(transValcar, 0.0f, 0.0f);
		car0();
		glPopMatrix();

		glPushMatrix();
		glScalef(1.5, 1.5, 0);
		glTranslatef(transValcar-0.2, 0.0f, 0.0f);
		car20();
		glPopMatrix();

		glPushMatrix();
		glScalef(1.5, 1.5, 0);
		glTranslatef(transValcar - 0.4, 0.0f, 0.0f);
		car30();
		glPopMatrix();




		glPushMatrix();
		glTranslatef(0.4, 2.0, 0);
		glTranslatef(position2, 0.0f, 0.0f);
		cloud1();
		glPopMatrix();


		glPushMatrix();
		glTranslatef(-0.85, 2.0, 0);
		glTranslatef(position2, 0.0f, 0.0f);
		cloud2();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.99, 2.0, 0);
		glTranslatef(position2, 0.0f, 0.0f);
		cloud3();
		glPopMatrix();
		//glPopMatrix();
		
		glPushMatrix();
		glTranslatef(1+1, 1.3, 0);
		glScalef(0.45, 0.45, 0);
		house2();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-1.2+1, 1.3, 0);
		glScalef(0.45, 0.45, 0);
		house2();
		glPopMatrix();

	}
	if (sw == 5) {


		glPushMatrix();
		glTranslatef(0.4, 2.0, 0);
		glTranslatef(position2, 0.0f, 0.0f);
		cloud1();
		glPopMatrix();



		glPushMatrix();
		glTranslatef(-3.2, -2, 0);
		glScalef(6.5, 5.2, 0);
		sky();
		grass();
		glPushMatrix();
		glScalef(0.9, 1, 0);
		sun();
		glPopMatrix();
		nat();

		glPushMatrix();
		glTranslatef(-0.2, 0.1, 0);
		tree();
		glPopMatrix();

		glPushMatrix();
		glScalef(0.8, 0.8, 0);
		glTranslatef(-0.13, 0.2, 0);
		tree();
		glPopMatrix();

		glPushMatrix();
		glScalef(0.8, 0.8, 0);
		glTranslatef(-0.27, 0.2, 0);
		tree();
		glPopMatrix();

		glPushMatrix();
		glScalef(0.8, 0.8, 0);
		glTranslatef(-0.05, 0.24, 0);
		tree();
		glPopMatrix();

		glPushMatrix();
		glScalef(0.8, 0.8, 0);
		glTranslatef(0.02, 0.2, 0);
		tree();
		glPopMatrix();


		glPushMatrix();
		glScalef(0.8, 0.8, 0);
		glTranslatef(0.42, 0.2, 0);
		tree();
		glPopMatrix();


		glPushMatrix();
		glScalef(0.8, 0.8, 0);
		glTranslatef(0.9, 0.2, 0);
		tree();
		glPopMatrix();


		glPushMatrix();
		glScalef(1.2, 1.2, 0);
		glTranslatef(-0.35, -0.05, 0);
		tree();
		glPopMatrix();



		glPushMatrix();
		glScalef(1.5, 1.5, 0);
		glTranslatef(transValcar, 0.0f, 0.0f);
		car0();
		glPopMatrix();

		glPushMatrix();
		glScalef(1.5, 1.5, 0);
		glTranslatef(transValcar - 0.2, 0.0f, 0.0f);
		car20();
		glPopMatrix();

		glPushMatrix();
		glScalef(1.5, 1.5, 0);
		glTranslatef(transValcar - 0.4, 0.0f, 0.0f);
		car30();
		glPopMatrix();




		glPushMatrix();
		glTranslatef(0.4, 2.0, 0);
		glTranslatef(position2, 0.0f, 0.0f);
		cloud1();
		glPopMatrix();


		glPushMatrix();
		glTranslatef(-0.85, 2.0, 0);
		glTranslatef(position2, 0.0f, 0.0f);
		cloud2();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.99, 2.0, 0);
		glTranslatef(position2, 0.0f, 0.0f);
		cloud3();
		glPopMatrix();
		//glPopMatrix();

		glPushMatrix();
		glTranslatef(1 + 1, 1.3, 0);
		glScalef(0.45, 0.45, 0);
		house2();
		glPopMatrix();
		glPushMatrix();
		glTranslatef(-1.2 + 1, 1.3, 0);
		glScalef(0.45, 0.45, 0);
		house2();
		glPopMatrix();
	}
	else if (sw == 6) {
		color2();
	}
	else if (sw == 7) {
		square5();
	}

	if (sw == 0 || sw == 1) {
		glPushMatrix();
		glTranslatef(0.37, 2.4, 0);
		glRotatef(-angle, 0, 0, 1.0);
		clk();
		glPopMatrix();
		glPopMatrix();

	}

	glPopMatrix();
	

	glFlush();
	glutSwapBuffers();
}

void spin() {

	angle += 0.01;
	if (angle > 360) {
		angle = 0;
	}
	if (j < 200) {
		transValy += 0.0001;
		j += 1;
	}
	else if (j < 400) {
		transValy -= 0.0001;
		j += 1;
	}
	if (j == 400) {
		j = 0;
	}

	if (transValybl > -2) {
		transValybl -= 0.001;
	}
	else {
		transValybl = 0;
	}




	if (sw == 0) {


		if (allScale > 1.1) {
			allScale -= 0.00009;


		}


		else {
			tt += 1;
			if (tt > 5000) {
				sw = 1;
				display();
			}

		}

	}

	if (sw == 1) {
		transValyrock -= 0.0001;
		tt += 1;
		if (tt > 8000) {
			if (allScale < 2) {
				//allScale += 0.001;
				allScale += 0.00009;
				//transValx -= 0.001;
				transValx -= 0.00009;
			}
			if (tt == 21000) {
				transValx = 0;
				allScale = 1.1;
				sw = 2;
				display();
			}
		}

	}
	if (sw == 2) {
		tt += 1;

		if (allScale < 3) {
			//allScale += 0.001;
			allScale += 0.00009;
			transValx += 0.0002;
		}
		if (tt == 35000) {
			sw = 3;
		}
	}
	if (sw == 3) {
		tt += 1;
		if (tt > 35200 && tt <= 35500) {
			if (tt == 35500)
				thun = 0;
			else
				thun += 0.01;

		}
		else if (tt > 39400 && tt <= 40000) {
			if (tt == 40000)
				thun = 0;
			else
				thun += 0.005;

		}
		else if (tt > 44000 && tt <= 44300) {
			if (tt == 44300)
				thun = 0;
			else
				thun += 0.008;

		}
		else if (tt > 46000 && tt <= 46400) {
			if (tt == 46400)
				thun = 0;
			else
				thun += 0.009;

		}
		else if (tt > 49800 && tt <= 51000) {
			if (tt == 51000)
				thun = 0;
			else
				thun += 0.0025;

		}


		if (allScale > 1.1) {
			//allScale += 0.001;
			allScale -= 0.00009;
			transValx -= 0.0002;
		}
		if (tt == 52500) {
			allScale = 1.1;
			sw = 4;
		}

	}
	if (sw == 4) {
		tt += 1;
		if (tt == 53000) {
			sw = 5;
		}
		transValcar += 0.001;
		speed2 = 0.004;
		display();
	}
	if (sw == 5) {
		tt += 1;
		if (tt == 53100) {
			sw = 6;
		}
	}
	if (sw == 6) {
		tt += 1;
			thun += 0.0005;

			if (tt == 65000) {
				sw = 7;
		}
		
	}
	glutPostRedisplay();
}



static void play() {
	glutPostRedisplay();
}






int main(int argc, char** argv) {
	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Specify the display Mode – RGB, RGBA or color

	// Index, single or double Buffer
	glutCreateWindow("Project CG"); // Create a window with the given title
	glutInitWindowSize(920, 920); // Set the window's initial width & height
	glutInitWindowPosition(50, 50); // Position the window's initial top-left corner

	init();
	angle = 0;
	transVal = 0;
	transValx = 0;
	transValy = 0;
	scaleVal = 1;
	pointSize = 5;
	allScale = 2;
	spinVal = 0;
	transValybl = 0;
	transValyrock = 0;
	transValcar = 0;
	scaleExp = 1;
	thun = 0;
	x = 1;
	i = 0;
	j = 0;
	tt = 0;
	sw = 0;
	now = 0;

	glutIdleFunc(play);
	//glutReshapeFunc(reshape);
	//glutKeyboardFunc(keyInter);



	glutIdleFunc(play);
	//glutMouseFunc(mouse);
	glutIdleFunc(spin);

	glutDisplayFunc(display); // Register display callback handler for window re-paint
	glutReshapeFunc(reshape);

	glutTimerFunc(100, rocket2, 0);
	glutTimerFunc(100, cloud, 0);
	glutTimerFunc(100, ball, 0);
	glutTimerFunc(100, rocket, 0);
	glutMainLoop(); // Enter the infinitely event-processing loop
	return 0;
}
