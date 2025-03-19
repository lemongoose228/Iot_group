#define BUTTON_PIN 2
#define PRESSED LOW

#define ROW1 2  
#define ROW2 3
#define ROW3 4

#define COL1 5
#define COL2 6
#define COL3 7

#define N 10 

volatile int button1_counter = 0;      
volatile long int button1_press_time = 0; 
volatile bool button1_check = false;     

int cur_row = 1;                      
bool button_state[3][3] = {{false}};   
bool button_state_old[3][3] = {{false}}; 
bool have_difference = false;         

unsigned long press_start[3][3] = {{0}}; 
unsigned long press_duration[3][3] = {{0}};


void process_button1_click();
void check_state(int row);
void print_message();
void print_press_duration(int row, int col);
