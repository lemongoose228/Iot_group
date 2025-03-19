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

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), process_button1_click, FALLING);

  cli(); 
  DDRD = B00011100; 
  PORTD = B11100000;

  TCCR1A = 0;
  TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10); 
  OCR1A = (16000000 / 64 / 1000) * N;            
  TIMSK1 |= (1 << OCIE1A);                   
  sei();       

  Serial.println("Startup complete.");  
}
