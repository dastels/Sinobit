const int io_0 = 0;
const int io_1 = 1;
const int io_2 = 2;
const int io_3 = 3;
const int io_4 = 4;
const int io_5 = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(io_0, OUTPUT);
  pinMode(io_1, OUTPUT);
  pinMode(io_2, OUTPUT);
  pinMode(io_3, OUTPUT);
  pinMode(io_4, OUTPUT);
  pinMode(io_5, OUTPUT);
}


void pulse(int io_pin, int count)
{
  for (int i = 0; i < count; i++) {
    digitalWrite(io_pin, HIGH);
    delay(100);
    digitalWrite(io_pin, LOW);
    delay(100);
  }
}


void loop() {
  pulse(io_0, 1);
  pulse(io_1, 1);
  pulse(io_2, 1);
  pulse(io_3, 1);
  pulse(io_4, 1);
  pulse(io_5, 1);
}
