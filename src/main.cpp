#include "mbed.h"
#include "pindef.h"
#include <cstdlib>
#include <ctime>
#include <vector>

PwmOut speaker(PC_7);
InterruptIn button_1(PA_10);
InterruptIn button_2(PB_3);
InterruptIn button_3(PB_5);
//InterruptIn button_4(PB_4);
DigitalOut led_1(PB_10);
DigitalOut led_2(PA_8);
DigitalOut led_3(PA_9);
Serial device(UART_TX, UART_RX);

std::vector <int> values;
int num = 1;
int compare = 0;
int range = 3;
int search = 0;
bool pattern = true;

void error() {
	speaker = 0.5;
	wait(0.25);
	speaker = 0;
	search = 0;
	values.clear();
	num = 1;
	compare = 0;
	wait(2);
}

void check() {
	if (compare < num) {
		std::srand(std::time(0));
		int random = std::rand() % range + 1;
		device.printf("Random Number: %i\n", random);
		values.push_back(random);			
		compare++;
		pattern = true;
	}
}

void show_pattern() {
	if (pattern) {
		for (int i = 0; i < values.size(); i++) {
			if (values[i] == 1) {
				led_1 = 1;
				wait(0.5);
				led_1 = 0;
				wait(0.5);
			}
			else if (values[i] == 2) {
				led_2 = 1;
				wait(0.5);
				led_2 = 0;
				wait(0.5);
			}
			else if (values[i] == 3) {
				led_3 = 1;
				wait(0.5);
				led_3 = 0;
				wait(0.5);
			}
		}
		pattern = false;
	}
}

void on_button_1() {
	led_1 = 1;
	int i = button_1;
	device.printf("%i\n", i);
	
	if (values[search] == 1 && search < values.size()) {
		search++;
		device.printf("Correct!\n");
	}
	else {
		error();
		device.printf("Error!\n");
	}
	if (search == values.size()) {
		num++;
		search = 0;
		device.printf("Increment!\n");
	}
	wait(0.25);
	led_1 = 0;
}

void on_button_2() {
	led_2 = 1;
	
	if (values[search] == 2 && search < values.size()) {
		search++;
		device.printf("Correct!\n");
	}
	else {
		error();
		device.printf("Error!\n");
	}
	if (search == values.size()) {
		num++;
		search = 0;
		device.printf("Increment!\n");
	}
	wait(0.25);
	led_2 = 0;
}

void on_button_3() {
	led_3 = 1;
	
	if (values[search] == 3 && search < values.size()) {
		search++;
		device.printf("Correct!\n");
	}
	else {
		error();
		device.printf("Error!\n");
	}
	if (search == values.size()) {
		num++;
		search = 0;
		device.printf("Increment!\n");
	}
	wait(0.25);
	led_3 = 0;
}

int main() {
	button_1.fall(&on_button_1);
	button_2.fall(&on_button_2);
	button_3.fall(&on_button_3);
	//button_4.fall(&check_input);
	device.baud(9600);
	while(1) {		
		check();
		wait(1);
		show_pattern();
	}
}
