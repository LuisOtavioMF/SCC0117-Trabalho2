const char* morse[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", // A-I
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", // J-R 
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", // S-Z
  "-----", ".----", "..---", "...--", "....-", ".....","-....", "--...", "---..", "----." // 0-9
};

const char* letters[] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
  'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
  'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
};

const int beep = 11;
const int ledPin = 10;
const int ledAzul = 7;
const int ledAmarelo = 8;
const int dotDelay = 300;
const int buttonPin = 3;
char letter[6];
char Word[20];
int WordPos = 0;
int letterPos = 0;
int counter = 0;


void flashSequence (char* sequence);

void flashDotOrDash (char dotOrDash);

void flashLed (int led);

int getButtonInput (int pin, unsigned long *time);

void setup() {

  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Programa Iniciado");
  flashLed (ledAzul);
  flashLed (ledAmarelo);
  flashLed (ledPin);
  flashLed (beep);
  
}

void loop() {
  // Le as entradas do botao e imprime na tela
  unsigned long initTime = millis();
  unsigned long elapsedTime = 0;
  int input = 0;
  int endLetter = 0;
  while ((elapsedTime < 700) && (!input)) {
    unsigned long time;
    input = getButtonInput(buttonPin, &time);
    if (input) {
      if ((time < 300) && (time > 50)) {
	      letter[letterPos] = '.';
	      letterPos++;
      } else if (time > 300) {
	      letter[letterPos] = '-';
	      letterPos++;
      }
    }
    elapsedTime = millis() - initTime;
  }
  if (!input) {
    counter++;
  } else {
    counter = 0;
  }
  if ((!input) || (letterPos > 5)) {
    letter[letterPos] = '\0';
    int flag = 1;
    if (!(strcmp(letter, ".-.-."))) {
      Serial.println("ENDLINE");
      flag = 0;
      letterPos = 0;
      flashLed(ledAmarelo);
    }
    for (int i = 0; (i < 36) && flag; i++) {
      if (!(strcmp(letter, morse[i]))) {
	      char c = letters[i];
	      Word[WordPos] = c;
	      WordPos++;
        letterPos = 0;
	      flag = 0;
	      flashLed(ledAmarelo);
      }
    }
  }
  if (counter > 1) {
    Word[WordPos] = '\0';
    if (WordPos > 0) {
      Serial.print(Word);
      Serial.print(' ');
      flashLed(ledAzul);
    }
    WordPos = 0;
    counter = 0;
  }

  // Mostra a mensagem escrita no terminal em codigo morse
  char ch;
  if (Serial.available()){
  
    ch = Serial.read(); // ler unica letra se (ch >= 'a' && ch <= 'z')
     
    if (ch >= 'a' && ch <= 'z') {
      flashSequence(morse[ch - 'a']);
    } else if (ch >= 'A' && ch <= 'Z') {
      flashSequence(morse[ch - 'A']); 
    } else if (ch >= '0' && ch <= '9') {
      flashSequence(morse[(ch - '0') + 26]); 
    } else if (ch == ' ') {
      // o vao entre palavras (eh quatro e nao sete pq o "flashSequence" ja tem tres no final)
      delay(dotDelay * 4);
    }
      
  
    // caso nao for nem espaco, pula esse caractere
  
  }
}


  
void flashSequence (char* sequence) {
  int i = 0;
  while (sequence[i] != NULL) {
    flashDotOrDash(sequence[i]);
    i++; 
  }
  // o vao entre letras (eh dois e nao tres pq o "flashDotOrDash ja tem um no final)
  delay(dotDelay * 2);
}
  
  
void flashDotOrDash (char dotOrDash) {
  digitalWrite(ledPin, HIGH); 
  
  if (dotOrDash == '.') {
    delay(dotDelay);
  } else { // precisa ser um "-"
    delay(dotDelay * 3); 
  }
  
  digitalWrite(ledPin, LOW); 
  delay(dotDelay); // o vao entre caracteres morse
}
 
void flashLed (int pin) {
  analogWrite(pin, 255);
  delay(dotDelay);
  analogWrite(pin, 0);
}

int getButtonInput (int pin, unsigned long *time) {
  int buttonState = digitalRead(pin);
  unsigned long ti = millis();
  int flag = 0;
  while (buttonState == LOW) {
    buttonState = digitalRead(pin);
    flag = 1;
  }
  *time = millis() - ti;
  return flag;
}
