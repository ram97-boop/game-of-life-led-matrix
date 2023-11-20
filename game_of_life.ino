const uint8_t len = 8;
const uint8_t rows[len] = {
  12, 10, 16, 11, 13, 17, 19, 18
};
const uint8_t cols[len] = {
  7, 4, 3, 5, 2, 6, 8, 9
};

uint8_t matrixRows[len] = {
  0, 0, 0, 0, 0, 0, 0, 0
};
uint8_t matrix[len][len] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

uint8_t get_live_neighbours_amount(uint8_t x, uint8_t y) {
  uint8_t live_neighbours = 0;
  uint8_t neighbour_relative_coords[8][2] = {
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, -1},
    {0, 1},
    {1, -1},
    {1, 0},
    {1, 1},
  };


}

void cleanMatrix() {
  for (uint8_t r=0; r<len; r++) {
    for (uint8_t c=0; c<len; c++) {
      matrix[r][c] = 0;
    }
    matrixRows[r] = 0;
  }
}

void displayMatrix() {
  for (uint8_t r=0; r<len; r++) {
    if (matrixRows[r]) {
      digitalWrite(rows[r], HIGH);
    }

    for (uint8_t c=0; c<len; c++) {
      if (matrix[r][c]) {
        digitalWrite(cols[c], LOW);
        delay(4);
        digitalWrite(cols[c], HIGH);
      }
    }

    digitalWrite(rows[r], LOW);
  }
}

void setup() {
  for (uint8_t pin=0; pin<len; pin++) {
    // initialize the output pins.
    pinMode(rows[pin], OUTPUT);
    pinMode(cols[pin], OUTPUT);

    // make the col pins (i.e. the cathodes) high to ensure that the LEDS are off.
    digitalWrite(cols[pin], HIGH);
    Serial.begin(9600);
    Serial.print("Hello");
  }
}

void loop() {
}
