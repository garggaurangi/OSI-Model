#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <iostream>

#define DELAY 1000
#define SIZE 20
#define LSIZEX 100
#define LSIZEY 30
#define DELTA 6
#define GODOWN 50
#define MOVERIGHT 700

#define BLACK 0
#define WHITE 15
#define RED 5

using namespace std;

struct coordinates
{
	int x,y;
};

struct all
{
	struct coordinates left, right;
};

//make square message boxes
void createBox(int x1,int y1,int size)  //x and y are coordinates of one point and size calculates other points
{                                     
	int x2=x1+size;
	int y2=y1+size;
	
	rectangle(x1, y1, x2, y2);
}

// rectangles for layers
void createRectangle(int x1,int y1,int size_x,int size_y) 
{
	int x2=x1+size_x;
	int y2=y1+size_y;
	rectangle(x1,y1,x2,y2);
}

//erase square message boxes
void eraseBox(int x1,int y1,int size) 
{
	int x2=x1+size;
	int y2=y1+size;
	setcolor(BLACK); //set colour to black
	rectangle(x1,y1,x2,y2);
	//floodfill(x1+1, y1+1, BLACK);
	setcolor(WHITE);
}

/*
NOTE: i/p to addbox fns 
       is always the top left coordinates 
       of the prev box 
*/


//Adding tail to the message packet
struct coordinates addBoxRight(int x, int y, int size)
{
	int X = x + size+1;
	createBox(X, y, size);
	
	struct coordinates c;
	c.x = X;
	c.y = y;
	return c; //returning the top left coordinates of the last right block
}

//Adding head to the message packet
struct coordinates addBoxLeft(int x, int y, int size)
{
	int X = x - size -1;
	createBox(X, y, size);
	
	struct coordinates c;
	c.x = X;
	c.y = y;
	return c; //returning the top left coordinates of the last left block
}

/* NOTE: i/p to ClrRightBox and ClrLeftBox 
		 is the top left coordinates of the last box
*/
//Clearing the right most box in the message packet array
 struct coordinates ClrRightBox(int top_left_x, int top_left_y, int size) //x and y i/p from struct for addBox fn
{	
	eraseBox(top_left_x, top_left_y, size);
	
	struct coordinates c;
	c.x = top_left_x - size-1;
	c.y = top_left_y;
	return c;
}

//Clearing the left most box in the message packet array
struct coordinates ClrLeftBox(int top_left_x, int top_left_y, int size)
{
	eraseBox(top_left_x, top_left_y, size);
	
	struct coordinates c;
	c.x = top_left_x + size+1;
	c.y = top_left_y;
	return c;
}

struct all add_application_layer(struct all coor)
{
	//delay(DELAY);
	struct all ret;
	ret.left = addBoxLeft(coor.left.x, coor.left.y, SIZE);
	//delay(DELAY);
	ret.right = addBoxRight(coor.right.x, coor.right.y, SIZE);
	
	return ret;
}

void add_osi_layer(int x, int y, char *Name)
{
	createRectangle(x, y, LSIZEX, LSIZEY);
	outtextxy(x+DELTA, y+DELTA, Name);
}

void create_msg(int x, int y, int size, char *Name)
{
	setcolor(RED);
	createBox(x, y, SIZE);
	//outtextxy(x+DELTA, y+DELTA, Name);
	setcolor(WHITE);
}

void del_all_msg(struct all coor)
{
	//setcolor(BLACK);
	//setfillstyle(SOLID_FILL, BLACK);
	//rectangle(coor.left.x, coor.left.y, coor.right.x+SIZE, coor.right.y+SIZE);
	//floodfill(coor.left.x+1, coor.left.x+1, BLACK);
	while(coor.left.x < coor.right.x)
	{
		coor.left = ClrLeftBox(coor.left.x, coor.left.y, SIZE);
		coor.right = ClrRightBox(coor.right.x, coor.right.y, SIZE);
	}
	eraseBox(coor.left.x, coor.left.y, SIZE);
	setcolor(WHITE);
}

int main()
{
	 /* request auto detection */
   int gdriver = DETECT, gmode;

   /* initialize graphics and local variables */
   //initgraph(&gdriver, &gmode, NULL);
   initwindow(1600, 900);

	struct coordinates layers;
	layers.x = 15;
	layers.y = 55;
	
	outtextxy(layers.x, layers.y-DELTA*7, "Sender");
	
	int msg_x = 400;
	int msg_y = layers.y;
	
	struct all packet_coor, init_coor; //initial coordinates
	
	init_coor.left.x = msg_x;
	init_coor.right.x = msg_x;
	init_coor.left.y = msg_y;
	init_coor.right.y = msg_y;
	
	add_osi_layer(layers.x, layers.y, "Application");
	create_msg(init_coor.left.x, init_coor.left.y, SIZE, "M");
	packet_coor = add_application_layer(init_coor);
	
	del_all_msg(packet_coor);
	
	//////////////////////////
	//delay(DELAY);
	layers.y += GODOWN;
	init_coor.left.y += GODOWN;
	init_coor.right.y += GODOWN;
	add_osi_layer(layers.x, layers.y, "Presentation");
	create_msg(init_coor.left.x, init_coor.left.y, SIZE, "M");
	packet_coor = add_application_layer(init_coor);
	packet_coor = add_application_layer(packet_coor);
	delay(DELAY);
	del_all_msg(packet_coor);

	//////////////////////////
	//delay(DELAY);
	layers.y += GODOWN;
	init_coor.left.y += GODOWN;
	init_coor.right.y += GODOWN;
	add_osi_layer(layers.x, layers.y, "Session");
	create_msg(init_coor.left.x, init_coor.left.y, SIZE, "M");
	packet_coor = add_application_layer(init_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);
delay(DELAY);
	del_all_msg(packet_coor);

	//////////////////////////
	//delay(DELAY);
	layers.y += GODOWN;
	init_coor.left.y += GODOWN;
	init_coor.right.y += GODOWN;
	add_osi_layer(layers.x, layers.y, "Transport");
	create_msg(init_coor.left.x, init_coor.left.y, SIZE, "M");
	packet_coor = add_application_layer(init_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);	
delay(DELAY);
	del_all_msg(packet_coor);

	//////////////////////////
	layers.y += GODOWN;
	init_coor.left.y += GODOWN;
	init_coor.right.y += GODOWN;
	add_osi_layer(layers.x, layers.y, "Network");
	create_msg(init_coor.left.x, init_coor.left.y, SIZE, "M");
	packet_coor = add_application_layer(init_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);
	delay(DELAY);
	del_all_msg(packet_coor);
	
	//////////////////////////
	layers.y += GODOWN;
	init_coor.left.y += GODOWN;
	init_coor.right.y += GODOWN;
	add_osi_layer(layers.x, layers.y, "DataLink");
	create_msg(init_coor.left.x, init_coor.left.y, SIZE, "M");
	packet_coor = add_application_layer(init_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);	
	delay(DELAY);
	del_all_msg(packet_coor);
	
	//////////////////////////
	//delay(DELAY);
	layers.y += GODOWN;
	init_coor.left.y += GODOWN;
	init_coor.right.y += GODOWN;
	add_osi_layer(layers.x, layers.y, "Physical");
	create_msg(init_coor.left.x, init_coor.left.y, SIZE, "M");
	packet_coor = add_application_layer(init_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);
	delay(DELAY);
	del_all_msg(packet_coor);
	
	//////////////////////////////////////////////////////////
	////////////////////////Recv//////////////////////////////
	outtextxy(layers.x+MOVERIGHT, 55 - DELTA*7, "Receiver");
	
	layers.x += MOVERIGHT;
	add_osi_layer(layers.x, layers.y, "Physical");
	create_msg(init_coor.left.x, init_coor.left.y, SIZE, "M");
	packet_coor = add_application_layer(init_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);
	delay(DELAY);
	del_all_msg(packet_coor);

	///////////////////////
	layers.y -= GODOWN;
	init_coor.left.y -= GODOWN;
	init_coor.right.y -= GODOWN;
	add_osi_layer(layers.x, layers.y, "DataLink");
	create_msg(init_coor.left.x, init_coor.left.y, SIZE, "M");
	packet_coor = add_application_layer(init_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);	
	delay(DELAY);
	del_all_msg(packet_coor);
	
	////////////////////////////////
	///////////////////////
	layers.y -= GODOWN;
	init_coor.left.y -= GODOWN;
	init_coor.right.y -= GODOWN;
	add_osi_layer(layers.x, layers.y, "Network");
	create_msg(init_coor.left.x, init_coor.left.y, SIZE, "M");
	packet_coor = add_application_layer(init_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);
	delay(DELAY);
	del_all_msg(packet_coor);
	
	///////////////////////
	layers.y -= GODOWN;
	init_coor.left.y -= GODOWN;
	init_coor.right.y -= GODOWN;
	add_osi_layer(layers.x, layers.y, "Transport");
	create_msg(init_coor.left.x, init_coor.left.y, SIZE, "M");
	packet_coor = add_application_layer(init_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);
	delay(DELAY);
	del_all_msg(packet_coor);

	///////////////////////
	layers.y -= GODOWN;
	init_coor.left.y -= GODOWN;
	init_coor.right.y -= GODOWN;
	add_osi_layer(layers.x, layers.y, "Session");
	create_msg(init_coor.left.x, init_coor.left.y, SIZE, "M");
	packet_coor = add_application_layer(init_coor);
	packet_coor = add_application_layer(packet_coor);
	packet_coor = add_application_layer(packet_coor);
	delay(DELAY);
	del_all_msg(packet_coor);

	///////////////////////
	layers.y -= GODOWN;
	init_coor.left.y -= GODOWN;
	init_coor.right.y -= GODOWN;
	add_osi_layer(layers.x, layers.y, "Presentation");
	create_msg(init_coor.left.x, init_coor.left.y, SIZE, "M");
	packet_coor = add_application_layer(init_coor);
	packet_coor = add_application_layer(packet_coor);
	delay(DELAY);
	del_all_msg(packet_coor);


		///////////////////////
	layers.y -= GODOWN;
	init_coor.left.y -= GODOWN;
	init_coor.right.y -= GODOWN;
	add_osi_layer(layers.x, layers.y, "Application");
	create_msg(init_coor.left.x, init_coor.left.y, SIZE, "M");
	packet_coor = add_application_layer(init_coor);
	delay(DELAY);
	del_all_msg(packet_coor);
		
	getch();

closegraph();
return 0;

}
