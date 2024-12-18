#define r1 0            
#define r2 12           
#define r3 11          
#define r4 2            
#define r5 10          
#define r6 1            
#define r7 A1          
#define r8 A0           

#define c1 7            
#define c2 6            
#define c3 8            
#define c4 13           
#define c5 4            
#define c6 9            
#define c8 5      

const int SIZE = 8;

int rows[SIZE] = {r1, r2, r3, r4, r5, r6, r7, r8}; 
int cols[SIZE] = {c1, c2, c3, c4, c5, c6, c7, c8};

int wow[SIZE][SIZE] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 1, 1, 1, 0, 0},
    {0, 1, 0, 0, 0, 1, 0, 0},
    {0, 1, 1, 1, 1, 1, 0, 0}
};

int cute[SIZE][SIZE] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {1, 0, 1, 0, 0, 1, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
};

int bear[SIZE][SIZE] = {
    {0, 1, 1, 1, 1, 1, 1, 0},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 1, 0, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 1, 0, 0, 1},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0}
};

void showFrame(int numberRow, int arr[SIZE]) {
    digitalWrite(rows[numberRow], HIGH); 
    for (int i = 0; i < SIZE; i++) {
        digitalWrite(columns[i], !arr[i]); 
    }
}

void reset() {
    for (int i = 0; i < SIZE; i++) {
        digitalWrite(rows[i], LOW); 
    }
    for (int i = 0; i < SIZE; i++){
        digitalWrite(columns[i], LOW); 
    }
}
