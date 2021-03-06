// Charles Zhang  ICS3U  mrs Cullum	 June 13, 2016
// all game engine related functions, such as timers, game grid manipulation, checking for collisions, and tetromino manipulation. prototyping in engine.h

#include <stdio.h>
#include <allegro.h>
#include <stdlib.h>
#include <time.h>

#include "globals.h"
#include "engine.h"

void increment_speed_counter() {
	speed_counter++;
}
END_OF_FUNCTION(increment_speed_counter)

void clearTetromino(struct Tetromino &structure) {
	int i;

	// clearing structure
	structure.shape = ' ';
	for (i = 0; i < 4; i++) {
		structure.px[i] = 0;
		structure.py[i] = 0;
	}
	structure.colour = 0;
	structure.cx = 0;
	structure.cy = 0;
}
END_OF_FUNCTION(clearTetromino)

void clearMatrix() {
	int i;
	int j;
	//resetting the matrix
	for (i = 0; i < GRID_X; i++) {
		for (j = 0; j < GRID_Y; j++) {
			grid[i][j] = 0;
		}
	}
}
END_OF_FUNCTION(clearMatrix)

struct Tetromino randTetromino() {
	struct Tetromino newTetromino;
	int i;

	// getting a random number between 1 and 7
	newTetromino.colour = rand() % 7 + 1;

	switch(newTetromino.colour) {

			// if the tetromino is a l shaped tetromino (cyan)
		case 1:
			newTetromino.shape = 'l';
			for (i = 0; i < 4; i++) {
				newTetromino.px[i] = 1; // setting each block's x coordinate to 0
				newTetromino.py[i] = 3 + i; // setting each block's y coordinate
			}
			// setting centre of tetromino
			newTetromino.cx = 0.5;
			newTetromino.cy = 4.5;
			break;

			// O shaped tetromino (yellow)
		case 2:
			newTetromino.shape = 'O';
			// setting x positions
			newTetromino.px[0] = 0;
			newTetromino.px[1] = 0;
			newTetromino.px[2] = 1;
			newTetromino.px[3] = 1;
			// setting y positions
			newTetromino.py[0] = 4;
			newTetromino.py[1] = 5;
			newTetromino.py[2] = 4;
			newTetromino.py[3] = 5;
			// setting centre of tetromino
			newTetromino.cx = 0.5;
			newTetromino.cy = 4.5;
			break;

			// T shaped tetromino (purple)
		case 3:
			newTetromino.shape = 'T';
			// setting x positions
			newTetromino.px[0] = 0;
			newTetromino.px[1] = 1;
			newTetromino.px[2] = 1;
			newTetromino.px[3] = 1;
			// setting y positions
			newTetromino.py[0] = 4;
			newTetromino.py[1] = 3;
			newTetromino.py[2] = 4;
			newTetromino.py[3] = 5;
			// setting centre of tetromino
			newTetromino.cx = 1;
			newTetromino.cy = 4;
			break;

			// S shaped tetromino(green)
		case 4:
			newTetromino.shape = 'S';
			// setting x positions
			newTetromino.px[0] = 0;
			newTetromino.px[1] = 0;
			newTetromino.px[2] = 1;
			newTetromino.px[3] = 1;
			// setting y positions
			newTetromino.py[0] = 4;
			newTetromino.py[1] = 5;
			newTetromino.py[2] = 3;
			newTetromino.py[3] = 4;
			// setting centre of tetromino
			newTetromino.cx = 1;
			newTetromino.cy = 4;
			break;

			// Z shaped tetromino(red)
		case 5:
			newTetromino.shape = 'Z';
			// setting x positions
			newTetromino.px[0] = 0;
			newTetromino.px[1] = 0;
			newTetromino.px[2] = 1;
			newTetromino.px[3] = 1;
			// setting y positions
			newTetromino.py[0] = 3;
			newTetromino.py[1] = 4;
			newTetromino.py[2] = 4;
			newTetromino.py[3] = 5;
			// setting centre of tetromino
			newTetromino.cx = 1;
			newTetromino.cy = 4;
			break;

			// J shaped tetromino(blue)
		case 6:
			newTetromino.shape = 'J';
			// setting x positions
			newTetromino.px[0] = 0;
			newTetromino.px[1] = 1;
			newTetromino.px[2] = 1;
			newTetromino.px[3] = 1;
			// setting y positions
			newTetromino.py[0] = 3;
			newTetromino.py[1] = 3;
			newTetromino.py[2] = 4;
			newTetromino.py[3] = 5;
			// setting centre of tetromino
			newTetromino.cx = 1;
			newTetromino.cy = 4;
			break;
			// L shaped tetromino(orange)
		case 7:
			newTetromino.shape = 'L';
			// setting x positions
			newTetromino.px[0] = 0;
			newTetromino.px[1] = 1;
			newTetromino.px[2] = 1;
			newTetromino.px[3] = 1;
			// setting y positions
			newTetromino.py[0] = 5;
			newTetromino.py[1] = 3;
			newTetromino.py[2] = 4;
			newTetromino.py[3] = 5;
			// setting centre of tetromino
			newTetromino.cx = 1;
			newTetromino.cy = 4;
			break;
	}

	return newTetromino;
}
END_OF_FUNCTION(randTetromino)

void getTetromino(struct Tetromino &nextTetromino, struct Tetromino &tetromino) {
	tetromino = nextTetromino;
	nextTetromino = randTetromino(); // getting a new buffer tetromino
}
END_OF_FUNCTION(getTetromino)

void drawTetromino(struct Tetromino tetromino) {
	int i;

	for (i = 0; i < 4; i++) {
		grid[tetromino.px[i]][tetromino.py[i]] = tetromino.colour; // assign the grid spaces a colour
	}
}
END_OF_FUNCTION(drawTetromino)

void clearSpace(struct Tetromino tetromino) {
	int i;

	for (i = 0; i < 4; i++) {
		grid[tetromino.px[i]][tetromino.py[i]] = 0; // clear x and y pos of the tetromino
	}
}
END_OF_FUNCTION(clearSpace)

bool gameOver(struct Tetromino tetromino) {
	int i;
	// check if game over
	for (i = 0; i < 4; i++) {
		if (grid[tetromino.px[i]][tetromino.py[i]] != 0) {
			return true;
		}
	}
	return false;
}
END_OF_FUNCTION(gameOver)

bool isComplete(int line) {
	int i;

	// check if line has any 0s in it
	for (i = 0; i < 10; i++) {
		if (grid[line][i] == 0) {
			return false; // line is not complete
		}
	}
	// no 0s? return the line is complete;
	return true;
}
END_OF_FUNCTION(isComplete)

void complete(int line) {
	int i;

	// move lines above line down by 1
	while (line > 0) {
		for (i = 0; i < 10; i++) {
			grid[line][i] = grid[line - 1][i];
		}
		line--;
	}
	// empty last line
	for (i = 0; i < 10; i++) {
		grid[0][i] = 0;
	}
	
}
END_OF_FUNCTION(complete)

bool checkCollision(struct Tetromino tetromino, int dirx, int diry){
	int i;
	clearSpace(tetromino);
	for (i = 0; i < 4; i++) {
		// check if there is a collision
		if (grid[tetromino.px[i] + dirx][tetromino.py[i] + diry] != 0 || tetromino.px[i] + dirx > 19
		    || tetromino.py[i] + diry < 0 || tetromino.py[i] + diry > 9){
			return true; // there is a collision
		}
	}
	// no collision
	return false;
}

int aInit() {
	allegro_init(); // Initialize Allegro
	install_keyboard(); // Initialize keyboard routines
	install_mouse(); // Initialize mouse
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL); // initialise sound

	//Tell allegro to install the timer routines
	install_timer();
	LOCK_VARIABLE(speed_counter); //Used to set the timer - which regulates the game's speed
	LOCK_FUNCTION(increment_speed_counter);	// lock the function which increments the speed counter.

	install_int_ex(increment_speed_counter, BPS_TO_TIMER(100)); //Set BPS
	set_color_depth(desktop_color_depth()); // Set the color depth

	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 400,600,0,0); //Change  graphics mode to 400 x 600
	show_mouse(screen);

	return 0;
}
END_OF_FUNCTION(aInit)

void resetTetromino(struct Tetromino &tetromino) {
	int i;

	switch(tetromino.colour) {

			// if the tetromino is a l shaped tetromino (cyan)
		case 1:
			tetromino.shape = 'l';
			for (i = 0; i < 4; i++) {
				tetromino.px[i] = 1; // setting each block's x coordinate to 0
				tetromino.py[i] = 3 + i; // setting each block's y coordinate
			}
			// setting centre of tetromino
			tetromino.cx = 0.5;
			tetromino.cy = 4.5;
			break;

			// O shaped tetromino (yellow)
		case 2:
			tetromino.shape = 'O';
			// setting x positions
			tetromino.px[0] = 0;
			tetromino.px[1] = 0;
			tetromino.px[2] = 1;
			tetromino.px[3] = 1;
			// setting y positions
			tetromino.py[0] = 4;
			tetromino.py[1] = 5;
			tetromino.py[2] = 4;
			tetromino.py[3] = 5;
			// setting centre of tetromino
			tetromino.cx = 0.5;
			tetromino.cy = 4.5;
			break;

			// T shaped tetromino (purple)
		case 3:
			tetromino.shape = 'T';
			// setting x positions
			tetromino.px[0] = 0;
			tetromino.px[1] = 1;
			tetromino.px[2] = 1;
			tetromino.px[3] = 1;
			// setting y positions
			tetromino.py[0] = 4;
			tetromino.py[1] = 3;
			tetromino.py[2] = 4;
			tetromino.py[3] = 5;
			// setting centre of tetromino
			tetromino.cx = 1;
			tetromino.cy = 4;
			break;

			// S shaped tetromino(green)
		case 4:
			tetromino.shape = 'S';
			// setting x positions
			tetromino.px[0] = 0;
			tetromino.px[1] = 0;
			tetromino.px[2] = 1;
			tetromino.px[3] = 1;
			// setting y positions
			tetromino.py[0] = 4;
			tetromino.py[1] = 5;
			tetromino.py[2] = 3;
			tetromino.py[3] = 4;
			// setting centre of tetromino
			tetromino.cx = 1;
			tetromino.cy = 4;
			break;

			// Z shaped tetromino(red)
		case 5:
			tetromino.shape = 'Z';
			// setting x positions
			tetromino.px[0] = 0;
			tetromino.px[1] = 0;
			tetromino.px[2] = 1;
			tetromino.px[3] = 1;
			// setting y positions
			tetromino.py[0] = 3;
			tetromino.py[1] = 4;
			tetromino.py[2] = 4;
			tetromino.py[3] = 5;
			// setting centre of tetromino
			tetromino.cx = 1;
			tetromino.cy = 4;
			break;

			// J shaped tetromino(blue)
		case 6:
			tetromino.shape = 'J';
			// setting x positions
			tetromino.px[0] = 0;
			tetromino.px[1] = 1;
			tetromino.px[2] = 1;
			tetromino.px[3] = 1;
			// setting y positions
			tetromino.py[0] = 3;
			tetromino.py[1] = 3;
			tetromino.py[2] = 4;
			tetromino.py[3] = 5;
			// setting centre of tetromino
			tetromino.cx = 1;
			tetromino.cy = 4;
			break;
			// L shaped tetromino(orange)
		case 7:
			tetromino.shape = 'L';
			// setting x positions
			tetromino.px[0] = 0;
			tetromino.px[1] = 1;
			tetromino.px[2] = 1;
			tetromino.px[3] = 1;
			// setting y positions
			tetromino.py[0] = 5;
			tetromino.py[1] = 3;
			tetromino.py[2] = 4;
			tetromino.py[3] = 5;
			// setting centre of tetromino
			tetromino.cx = 1;
			tetromino.cy = 4;
			break;
	}
}
END_OF_FUNCTION(resetTetromino)
