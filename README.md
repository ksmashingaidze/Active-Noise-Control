# EEE4022S-Active-Noise-Control
MSHKUZ001 Final Year Thesis, Electrical Engineering, University of Cape Town 

Maintained by Kuziwakwashe Stephen Mashingaidze

1.) ACTIVE NOISE CONTROL USING ARDUINO DUE

i.) MONO CHANNEL IMPLEMENTATION

- Adaptive filter based upon least mean squares algorithm implementation 
- 'N' denotes filter tap count
- 'mu' denotes LMS step-size
- Upload to Arduino Due
- Reference microphone signal to be connected to pin A0 (after 1.56V biasing)
- Error microphone signal to be connected to pin A1 (after 1.56V biasing)
- Output available at DAC0 (biased by 1.56V)

ii.) DUAL CHANNEL IMPLEMENTATION

- Adaptive filter based upon least mean squares algorithm implementation 
- 'N' denotes filter tap count
- 'mu' denotes LMS step-size
- Upload to Arduino Due
- Left channel reference microphone signal to be connected to pin A0 (after 1.56V biasing)
- Right channel reference microphone signal to be connected to pin A2 (after 1.56V biasing)
- Left channel error microphone signal to be connected to pin A1 (after 1.56V biasing)
- Right channel error microphone signal to be connected to pin A3 (after 1.56V biasing)
- Left channel output available at DAC0 (biased by 1.56V)
- Right channel output available at DAC1 (biased by 1.56V)

2.) MATLAB SIMULATIONS
- Connect microphone to PC, then run code
