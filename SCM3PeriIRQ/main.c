
/* A/D Converter Definitions */
#define ADCR            (*((volatile unsigned long *) 0x40034000))
#define ADDR            (*((volatile unsigned long *) 0x40034004))

/* NVIC Definitions */
#define NVIC_ENABLE0    (*((volatile unsigned long *) 0xE000E100))

volatile unsigned long AD_Val;

void ADC_Handler (void) {
  AD_Val = (ADDR >> 6) & 0x03FF;        // Store A/D Conversion Result
}

int main (void) {

  NVIC_ENABLE0 = 0x00000001;            // Enable A/D Interrupt

  ADCR = 0x00210901;                    // Setup A/D: 10-bit AIN0, CLKDIV=10,
                                        //            Burst Mode
  while (1); 
}
