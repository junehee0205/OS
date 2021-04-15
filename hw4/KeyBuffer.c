#include <stdio.h>
#include <string.h>
#include "Console.h"
#include "KeyBuffer.h"

#define TRUE 1
#define FALSE 0

void InitKeyBuffer(KeyBuffer *buffer)
{
	buffer->in = buffer->out = 0;
	buffer->size = BUFFER_SIZE;
}

int IsEmpty(KeyBuffer *buffer)
{
	// TO DO: implement this function
	if(buffer->in == 0) return 1;
	else return 0;
}

int IsFull(KeyBuffer *buffer)
{
	// TO DO: implement this function
	if(buffer->in == buffer->size) return 1;
	else return 0;
}

void InsertKey(KeyBuffer *buffer, int key)
{
	// TO DO: implement this function
	// if the buffer is full, do nothing
	if(IsFull(buffer) == 1);
	else{
		buffer->buffer[buffer->in] = key;
		buffer->in++;
		}
}

int DeleteKey(KeyBuffer *buffer)
{
	// TO DO: implement this function
	// if the buffer is empty, do nothing
	if(IsEmpty(buffer) == 1){;}
	else{
		if(buffer->in!=0){
			buffer->in--;
	}
	}
	return buffer->buffer[buffer->in];
}

int GetKey(KeyBuffer *buffer, int idx)
{
	return buffer->buffer[idx];
}


void DisplayKeyBuffer(int x, int y, KeyBuffer *buffer)
{
	gotoxy(x, y);
	printf("Key Buffer = [");
	for(int i = buffer->out; i != buffer->in; i = (i + 1) % buffer->size)
		printf("%c", GetKey(buffer, i));

	printf("] ");
}

