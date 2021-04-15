#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "Console.h"
#include "KeyBuffer.h"

#define SHM_FILE "key_buffer.shm"


int main(int argc, char *argv)
{
	// TO DO: open SHM_FILE for using shm_open()
	//  check if the file was successfully open
	int shm_fd = shm_open(SHM_FILE, O_RDONLY, 0666) ;
	if(shm_fd == -1){
		return 0;
	}

	int buffer_size = sizeof(KeyBuffer);

	// TO DO: map the shared memory file and receive the return address into     key_buffer
	// check if the file was successfully mapped
	KeyBuffer *key_buffer = NULL;
   	key_buffer = mmap(0, buffer_size, PROT_READ, MAP_SHARED, shm_fd, 0);
	if(key_buffer == (void*)-1){
		return 0;
	}

	int screen_width = getWindowWidth();
	int screen_height = getWindowHeight() - 3;

	clrscr();
	printf("screen size: %d x %d\n", screen_width, screen_height);
	int x = screen_width / 2;
	int y = screen_height / 2;
	int key = 0;
	char c = '*';
	int repeat = 1;

	gotoxy(x, y);
	putchar('#');

	while(repeat){
		int oldx = x;
		int oldy = y;
		
		// TO DO: read a key from the key buffer in the shared memory
		// if the key is zero, repeat until a non-zero key is read
		key =GetKey(key_buffer,key_buffer->in);
		if(key==0){
			while(key == 0){
				key =GetKey(key_buffer,key_buffer->in);}}

		if(x<=0);
        else{
			if(key == 105){
                 gotoxy(x,--y);
			}
         	if(x>=screen_width);
          		else{
              		if(key == 108){
                  	gotoxy(++x,y);
              		}
          	}
 
          if(y<=0);
          else{
              if(key == 106){
                  gotoxy(--x,y);
              }
          }
 
          if(y>screen_height);
 
          else{
          if(key == 107){
                  gotoxy(x,++y);
				  }
        }
		if(key== 99){
			if(c==' ') c = '*';
            else if(c == '*') c = ' ';  
 		}
        if(key == 113){
			printf("key=%d\n", key);
            break;
        }
		// TO DO: print c at (oldx, oldy)

		// TO DO: print '#' at (x, y)
		}	
		gotoxy(oldx, oldy);
        putchar(c);
        gotoxy(x, y);
        putchar('#');
		DeleteKey(key_buffer);
	}

	clrscr();
	printf("Bye!\n");

	return 0;
}
/*
		TO DO: implement the following actions

		if key is 'i', 'j', 'k', or 'l', move the coordinate accordingly
			'i': move up
			'j': move left
			'k': move down
			'l': move right

			Note! The coordinate should be in the valid range.
			(1 <= x <= screen_width, 1 <= y <= screen_height)

		if key is 'c', change color
			toggle c between ' ' and '*' 

		if key is 'q', break the loop
			
*/
