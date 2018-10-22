//Define constants
int N = 25;          //Filter length
float mu = 25;     //Define LMS step-size

//Define 'for' loop counters
int k = 0;            //Stored reference sample counter  
int i = 0;            //Convolution counter

//Vectors, to implement matrix multiplication
float w[25];           //Adaptive filter coefficients    
float x_window[25];    //Define stored x values used in convolution 

void setup() {
  //Startup initialisations 
  
  //Initialise serial communication at 9600 bits per second
  Serial.begin(115200);

  //Initialise ADC in 12-bit mode
  analogReadResolution(12);
  
  //Initialise DAC in 12-bit mode
  analogWriteResolution(12);
}

void loop() {
  //Infinite loop
  
  //Read the reference input on analog pin A0, digital value
  int adc_val_ref = analogRead(A0);

  //Read the error input on analog pin A1, digital value
  int adc_val_err = analogRead(A1);

  //Preliminary signals
  float x_biased = ((adc_val_ref)*(3.3/4095)); //Convert reference + DC offset back to an analogue voltage
  float e_biased = ((adc_val_err)*(3.3/4095)); //Convert error + DC offset back to an analogue voltage
  float x = (x_biased - 1.56);                 //Unbias reference signal to obtain original recorded x
  float e = (e_biased - 1.56);                 //Unbias error signal to obtain original recorded e

  //Populate stored reference value matrix
  for (k=N-1; k>-1; k--) {         //Shift values right, such that most recent sample is x_window[0]
    if (k==0) {
      x_window[k] = x;             //Most recently sampled value assigned to first entry of stored reference array 
    }
    else{
      x_window[k] = x_window[k-1]; //Shift right
    }
  }

  //Perform LMS
  float y = 0;                          //Prepare y value for convolution
  for (i=0; i<N; i++) {                 //Loop for every value in the 'matrices'
    y = y + (w[i])*(x_window[i]);       //Convolution implementation
    w[i] = w[i] + (2*mu*e*x_window[i]); //Update filter coefficients
  }

  //Output after biasing for DAC
  analogWrite(DAC0, round((4095*(y + 1.56))/3.3)); //Send digital biased output value to DAC0
}
