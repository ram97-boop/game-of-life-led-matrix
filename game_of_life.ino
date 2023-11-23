const uint8_t len = 8;
const uint8_t rows[len] = {
  12, 10, 16, 11, 13, 17, 19, 18
};
const uint8_t cols[len] = {
  7, 4, 3, 5, 2, 6, 8, 9
};
uint8_t matrix[len][len] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0},
  {0, 0, 1, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};
const uint8_t buttonPin = 15;


void setup() {
  for (uint8_t pin=0; pin<len; pin++) {
    // initialize the output pins.
    pinMode(rows[pin], OUTPUT);
    pinMode(cols[pin], OUTPUT);

    // make the col pins (i.e. the cathodes) high to ensure that the LEDS are off.
    digitalWrite(cols[pin], HIGH);
  }

  pinMode(buttonPin, INPUT);
}

void loop() {
  for (uint8_t i=0; i<5; i++) {
    displayMatrix();
  }
  nextGeneration();

  if (digitalRead(buttonPin) == HIGH) {
    generateRandomWorld();
  }
}

void generateRandomWorld() {
  for (uint8_t x=0; x<len; x++) {
    for (uint8_t y=0; y<len; y++) {
      matrix[x][y] = random(2);
    }
  }
}


uint8_t getLiveNeighboursAmount(uint8_t x, uint8_t y) {
  uint8_t liveNeighbours = 0;
  uint8_t neighboursRelativeCoords[8][2] = {
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, -1},
    {0, 1},
    {1, -1},
    {1, 0},
    {1, 1},
  };

  for (uint8_t n=0; n<8; n++) {
    uint8_t neighbourX = (neighboursRelativeCoords[n][0] + x + len) % len;
    uint8_t neighbourY = (neighboursRelativeCoords[n][1] + y + len) % len;

    if (matrix[neighbourX][neighbourY]) {
      liveNeighbours++;
    }
  }

  return liveNeighbours;
}


void cellNextState(uint8_t x, uint8_t y, uint8_t (&newMatrix)[len][len]) {
  uint8_t liveNeighboursAmount = getLiveNeighboursAmount(x, y);

  if (liveNeighboursAmount < 2 || liveNeighboursAmount > 3) {
    newMatrix[x][y] = 0;
  }
  else if (liveNeighboursAmount == 3) {
    newMatrix[x][y] = 1;
  }
}


void nextGeneration() {
  uint8_t newMatrix[len][len];
  for (uint8_t x=0; x<len; x++) {
    for (uint8_t y=0; y<len; y++) {
      newMatrix[x][y] = matrix[x][y];
    }
  }

  for (uint8_t x=0; x<len; x++) {
    for (uint8_t y=0; y<len; y++) {
      cellNextState(x, y, newMatrix);
    }
  }

  for (uint8_t x=0; x<len; x++) {
    for (uint8_t y=0; y<len; y++) {
      matrix[x][y] = newMatrix[x][y];
    }
  }
}


void displayMatrix() {
  for (uint8_t r=0; r<len; r++) {
    digitalWrite(rows[r], HIGH);

    for (uint8_t c=0; c<len; c++) {
      if (matrix[r][c]) {
        digitalWrite(cols[c], LOW);
      }
    }

    delay(2);
    for (uint8_t c : cols) {
      digitalWrite(c, HIGH);
    }
    digitalWrite(rows[r], LOW);
  }
}


