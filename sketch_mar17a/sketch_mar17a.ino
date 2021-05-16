#define WAVE_GAIT_LENGTH 12
#define RIPPLE_GAIT_LENGTH 8
#define TRIPOD_GAIT_LENGTH 4
#define TETRAPOD_GAIT_LENGTH 6
#define DELAY 800    //700

const uint16_t RFF = 0b100000000000;  // Right Front Forward
const uint16_t RFU = 0b010000000000;  // Right Front Up
const uint16_t RMF = 0b001000000000;  // Right Middle Forward
const uint16_t RMU = 0b000100000000;  // Right Middle Up
const uint16_t RBF = 0b000010000000;  // Right Back Forward
const uint16_t RBU = 0b000001000000;  // Right Back Up
const uint16_t LFF = 0b000000100000;  // Left Front Forward
const uint16_t LFU = 0b000000010000;  // Left Front Up
const uint16_t LMF = 0b000000001000;  // Left Middle Forward
const uint16_t LMU = 0b000000000100;  // Left Middle Up
const uint16_t LBF = 0b000000000010;  // Left Back Forward
const uint16_t LBU = 0b000000000001;  // Left Back Up

uint8_t indice = 0;

uint16_t  slow_wave[12] = {
  RFU|LBF,  
  RFF|RFU,
  RFF|RMU,
  RMF|RMU,
  RMF|RBU,
  RBF|RBU,
  RBF|LFU,
  LFF|LFU,
  LFF|LMU,
  LMF|LMU,
  LMF|LBU,
  LBF|LBU
};

uint16_t  ripple_wave  [8] = {
  RBF|RBU|LFF|LFU, 
  RMU|RBF|LFF, 
  RMF|RMU, 
  RFU|RMF|LBU, 
  RFF|RFU|LBF|LBU, 
  RFF|LMU|LBF, 
  LMF|LMU, 
  RBU|LFU|LMF,
};

uint16_t  tripod_gait  [4] = {
  RBU|RFU|LMU|RBF|RFF|LMF,
  RBF|RFF|LMF|RMU|LBU|LFU,
  RMU|LBU|LFU|RMF|LBF|LFF,
  RMF|LBF|LFF|RBU|RFU|LMU
};

uint16_t  tetrapod_gait  [6] = {
  RFU|LBU|RFF|LBF,
  RFF|LBF|RBU|LMU,
  RBU|LMU|RBF|LMF,
  RBF|LMF|RMU|LFU,
  RMU|LFU|LFF|RMF,
  LFF|RMF|RFU|LBU
};

// NOT TESTED
uint16_t  tripod_gait_right  [4] = {
  RBU|RFU|LMU|LMF,
  LMF|RMU|LBU|LFU,
  RMU|LBU|LFU|LBF|LFF,
  LBF|LFF|RBU|RFU|LMU
};

// NOT TESTED
uint16_t  tripod_gait_left  [4] = {
  RBU|RFU|LMU|RBF|RFF,
  RBF|RFF|RMU|LBU|LFU,
  RMU|LBU|LFU|RMF,
  RMF|RBU|RFU|LMU
};

void setState(uint16_t newState) {
  int i_b=0;
  int i_c=0;
  int i_d=0;
  int i_e=0;
  int i_f=0;
  // Right legs
  if (newState & (1<<11)) i_d=i_d+0b00000001; //RFF -> PD0
  if (newState & (1<<10)) i_d=i_d+0b00000010; //RFU -> PD1
  if (newState & (1<<9))  i_b=i_b+0b00000001; //RMF -> PB0
  if (newState & (1<<8))  i_b=i_b+0b00000100; //RMU -> PB2
  if (newState & (1<<7))  i_c=i_c+0b01000000; //RBF -> PC6
  if (newState & (1<<6))  i_d=i_d+0b10000000; //RBU -> PD7
  // Left legs
  if (newState & (1<<5))  i_e=i_e+0b01000000; //LFF -> PE6
  if (newState & (1<<4))  i_b=i_b+0b00010000; //LFU -> PB4
  if (newState & (1<<3))  i_b=i_b+0b00001000; //LMF -> PB3
  if (newState & (1<<2))  i_b=i_b+0b00000010; //LMU -> PB1
  if (newState & (1<<1))  i_f=i_f+0b00010000; //LBF -> PF4
  if (newState & (1<<0))  i_b=i_b+0b00100000; //LBU -> PB5
  PORTB = i_b;
  PORTC = i_c;
  PORTD = i_d;
  PORTE = i_e;
  PORTF = i_f;
  delay(DELAY);
}

void setup() {
  DDRB=DDRB|0b00111111; //PB0 - PB5
  DDRC=DDRC|0b01000000; //PC6
  DDRD=DDRD|0b10000011; //PD0, PD1, PD7
  DDRE=DDRE|0b01000000; //PE6
  DDRF=DDRF|0b00010000; //PF4  
}

void loop() {
  //setState(slow_wave[indice]);
  //setState(ripple_wave[indice]);
  //setState(tripod_gait[indice]);
  //setState(tetrapod_gait[indice]);
  
  //if ( indice >= WAVE_GAIT_LENGTH ) indice = 0;
  //if ( indice >= RIPPLE_GAIT_LENGTH ) indice = 0; 
  //if ( indice >= TRIPOD_GAIT_LENGTH ) indice = 0; 
  //if ( indice >= TETRAPOD_GAIT_LENGTH ) indice = 0; 

  indice++;
}
