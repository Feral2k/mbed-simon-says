#include "mbed.h"
#include "pindef.h"
#include <cstdlib>
#include <ctime>
#include <vector>

PwmOut speaker(PC_7);
BusIn buttons(PA_10, PB_3, PB_5, PB_4);
BusOut leds(PB_10, PA_8, PA_9);

std::vector <int> values;
int num = 1;
int compare = 0;
int range = 4;
bool success;

void check() {
	if (compare < num) {
		std::srand(std::time(0));
		int random = range * (std::rand() / (RAND_MAX + 1.0));
			
		if (random == 1)
			values.push_back(0x01);
		else if (random == 2)
			values.push_back(0x02);
		else if (random == 3)
			values.push_back(0x04);
		else if (random == 4)
			values.push_back(0x08);
			
		compare++;
	}
}

void show_pattern() {
	leds = 0x00;
	
	for (int i = 0; i < values.size(); i++) {
		if (values[i] != 0x08) {
			leds = leds ^ values[i];
			wait(0.5);
			leds = leds ^ values[i];
			wait(0.5);
		}
		else {
			leds = leds ^ 0x07;
			wait(0.5);
			leds = leds ^ 0x07;
			wait(0.5);
		}
	}
}

void check_input() {
	for (int i = 0; i < values.size(); i++) {
		if (!(buttons & 0x01)) {
			leds = values[i];
		}
		else {
			speaker = 0.5;
			wait(0.25);
			speaker = 0;
			return;
		}
		wait(0.5);
	}
	
	num++;
}

int main() {	
	while(1) {		
		check();
		if ((!(buttons & 0x01)) || (!(buttons & 0x02)) || (!(buttons & 0x04)) || (!(buttons & 0x08))) {
			check_input();
		}
		else
			show_pattern();
		
		wait(1);
	}
}
