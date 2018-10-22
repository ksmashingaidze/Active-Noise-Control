//Define constants
int N = 25;            //Filter length
float mu = 25;         //Define LMS step-size

//Define 'for' loop counters
int k = 0;             //Stored reference sample counter, left channel
int l = 0;             //Stored reference sample counter, right channel
int i = 0;             //Convolution counter, left channel
int n = 0;             //Convolution counter, right channel

//Vectors, to implement matrix multiplication
float w_l[25];         //Adaptive filter coefficients, Left channel    
float w_r[25];         //Adaptive filter coefficients, right channel
float x_window_l[25];  //Define stored x values used in convolution, left channel
float x_window_r[25];  //Define stored x values used in convolution, right channel

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
  
  //Read the left channel reference input on analog pin A0, digital value
  int adc_val_ref_l = analogRead(A0);
  //Read the right channel reference input on analog pin A2, digital value
  int adc_val_ref_r = analogRead(A2);

  //Read the left channel error input on analog pin A1, digital value
  int adc_val_err_l = analogRead(A1);
  //Read the right channel error input on analog pin A3, digital value
  int adc_val_err_r = analogRead(A3);

  //Preliminary signals
  float x_biased_l = ((adc_val_ref_l)*(3.3/4095)); //Convert reference + DC offset back to an analogue voltage, left channel     
  float x_biased_r = ((adc_val_ref_r)*(3.3/4095)); //Convert reference + DC offset back to an analogue voltage, right channel 
  
  float e_biased_l = ((adc_val_err_l)*(3.3/4095)); //Convert error + DC offset back to an analogue voltage, left channel 
  float e_biased_r = ((adc_val_err_r)*(3.3/4095)); //Convert error + DC offset back to an analogue voltage, right channel 
  
  float x_l = (x_biased_l - 1.56);                 //Unbias reference signal to obtain original recorded x, left channel 
  float x_r = (x_biased_r - 1.56);                 //Unbias reference signal to obtain original recorded x, right channel 
  
  float e_l = (e_biased_l - 1.56);                 //Unbias error signal to obtain original recorded e, left channel 
  float e_r = (e_biased_r - 1.56);                 //Unbias error signal to obtain original recorded e, right channel 

  //Populate stored reference value matrix

  //Left Channel
  for (k=N-1; k>-1; k--) {             //Shift values right, such that most recent sample is x_window_l[0]
    if (k==0) {
      x_window_l[k] = x_l;             //Most recently sampled value assigned to first entry of stored reference array 
    }
    else{
      x_window_l[k] = x_window_l[k-1]; //Shift right
    }
  }

  //Right Channel
  for (l=N-1; l>-1; l--) {             //Shift values right, such that most recent sample is x_window_r[0]
    if (l==0) {
      x_window_r[l] = x_r;             //Most recently sampled value assigned to first entry of stored reference array 
    }
    else{
      x_window_r[l] = x_window_r[l-1]; //Shift right
    }
  }

  //Perform LMS

  //Left Channel
  float y_l = 0;                                //Prepare y_l value for convolution
  for (i=0; i<N; i++) {                         //Loop for every value in the 'matrices'
    y_l = y_l + (w_l[i])*(x_window_l[i]);       //Convolution implementation
    w_l[i] = w_l[i] + (2*mu*e_l*x_window_l[i]); //Update filter coefficients
  }

  //Right Channel
  float y_r = 0;                                //Prepare y_r value for convolution
  for (n=0; n<N; n++) {                         //Loop for every value in the 'matrices'
    y_r = y_r + (w_r[n])*(x_window_r[n]);       //Convolution implementation
    w_r[n] = w_r[n] + (2*mu*e_r*x_window_r[n]); //Update filter coefficients
  }

  //Output after biasing for DAC
  analogWrite(DAC0, round((4095*(y_l + 1.56))/3.3)); //Send digital biased output value to DAC0
  analogWrite(DAC1, round((4095*(y_r + 1.56))/3.3)); //Send digital biased output value to DAC1
}
