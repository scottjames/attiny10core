/**
   Tiny10 demo
   http://www.technoblogy.com/show?1YQY

  Use 100k pot as voltage divider, input analog to PB1 pin3
  output pulse/tone on PB0 pin1, to drive piezo.
*/

void setup () {
  DDRB = 1;                       // PB0 as an output
  // Set up ADC on PB2
  ADMUX = 1 << MUX0;              // ADC1 (PB1)
  ADCSRA = 1 << ADEN | 3 << ADPS0; // Enable ADC, 125kHz clock
  // Set up waveform on PB0
  TCCR0A = 1 << COM0A0 | 3 << WGM00; // Toggle OC0A, Fast PWM
  TCCR0B = 3 << WGM02 | 4 << CS00; // Fast PWM with OCR0A as TOP; /256
}

void loop () {
  ADCSRA = ADCSRA | 1 << ADSC;    // Start
  while (ADCSRA & 1 << ADSC);     // Wait while conversion in progress
  OCR0A = ADCL;                   // Copy result to frequency output
}
