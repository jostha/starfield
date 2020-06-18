#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
//#include <stdio.h>

const int SCREEN_WIDTH  = 1024;
const int SCREEN_HEIGHT = 768;
const int FIELDSIZE = 600;

typedef struct {
	int x;
	int y;
	int r;
	int g;
	int b;
	int s;
} star;

int main() {

	// Some vars
	int i;						// general for loops and such
	time_t t;

	ALLEGRO_DISPLAY *display = NULL;		// Setup graphics window
	ALLEGRO_EVENT_QUEUE *evqueue;			// Setup events queue

	// Initialise Allegro
	al_init();
	display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	al_init_primitives_addon();
	evqueue = al_create_event_queue();

	al_register_event_source(evqueue, al_get_display_event_source(display));

	// Initialise RNG
	srand((unsigned) time(&t));

	// Create a random starfield
	star stars[FIELDSIZE]; 
	for (i=0; i<FIELDSIZE; i++){
		stars[i].x = rand() % SCREEN_WIDTH;
		stars[i].y = rand() % SCREEN_HEIGHT;
		stars[i].r = rand() % 255;
		stars[i].g = rand() % 255;
		stars[i].b = rand() % 255;
		stars[i].s = (rand() % 3) + 1;
		//	printf("x %d  y %d  r %d  g %d  b %d  s %d\n",stars[i].x, stars[i].y, stars[i].r, stars[i].g, stars[i].b, stars[i].s);
	}

	ALLEGRO_EVENT event;

	// Main loop
	bool running = true;
	while (running){
		al_get_next_event(evqueue, &event);
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			running = false;
		}

		// do depth order on another night :)
		for(i=0; i<FIELDSIZE; i++){
			al_draw_pixel(stars[i].x, stars[i].y, al_map_rgb(stars[i].r, stars[i].g, stars[i].b));
			stars[i].x -= stars[i].s;
			if (stars[i].x == 0) {
				stars[i].x = SCREEN_WIDTH;
			}
		}
		
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
		}	
	al_destroy_display(display);

	return 0;
}
