#define WAVE_GATE_LENGTH 12
#define RIPPLE_GATE_LENGTH 8
#define TRIPOD_GATE_LENGTH 4
#define TETRAPOD_GATE_LENGTH 6
#define DELAY 800    //700

uint8_t indice = 0;

uint16_t  slow_wave[12] = {
 
0b010000000010,  //RFU & LBF  //LBF makes the leg move downward from the second loop, it is irrelevant the first time
0b110000000000, //RFU & RFF
0b100100000000, //RFF & RMU
0b001100000000, //RMU & RMF
0b001001000000, //RMF & RBU
0b000011000000, //RBU & RBF
0b000010010000, //RBF & LFU
0b000000110000, //LFU & LFF
0b000000100100,  //LFF & LMU
0b000000001100, //LMU & LMF
0b000000001001,  //LMF & LBU
0b000000000011,  //LBU & LBF
};

uint16_t  ripple_wave  [12] = {
 
0b000011110000, // 
0b000110100000, //RFU & RFF
0b001100000000, //RFF & RMU
0b011000000001, //RMU & RMF
0b110000000011, //RMF & RBU
0b100000000110, //RBU & RBF
0b000000001100, //RBF & LFU
0b000001011000, //LFU & LFF
};

uint16_t  tripod_gate  [4] = {
 
0b110011001100, // 
0b100110011001, //
0b001100110011, //
0b011000100110, //
};

uint16_t  tetrapod_gate  [6] = {
 
0b110000000011, // 
0b100001000110, //
0b000011001100, //
0b000110011000, //
0b001100110000, //
0b011000100001
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
  Serial.begin(9600);
  
}

void loop() {
  //setState(slow_wave[indice]);
  //setState(ripple_wave[indice]);
  //setState(tripod_gate[indice]);
  //setState(tetrapod_gate[indice]);
  
  //if ( indice >= WAVE_GATE_LENGTH ) indice = 0;
  //if ( indice >= RIPPLE_GATE_LENGTH ) indice = 0; 
  //if ( indice >= TRIPOD_GATE_LENGTH ) indice = 0; 
  //if ( indice >= TETRAPOD_GATE_LENGTH ) indice = 0; 

  indice++;
}
