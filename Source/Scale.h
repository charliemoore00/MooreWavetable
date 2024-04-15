/**
  ==============================================================================

    NAME: MooreSynth
    AUTHOR: Charlie Moore & McLean Macionis
    DATE: April 3, 2024
    COMMENTS: Pitter patter!
 
    ----------------------------------------------------------------------------
 
    This file contains the basic framework code for a JUCE plugin processor.
    
    To open this project as a plugin in Ableton Live, do the following:
    1. Navigate to "Product" in the menu bar
    2. Select "Scheme" followed by "Edit Scheme" (Command Shift <)
    3. Select "Release" under "Build Configuration"
    4. Select "Ableton Live 11 Suite.app" under "Executable"

  ==============================================================================
*/

#pragma once

using namespace std;

struct EqualTemperamentScale
{
    string   m0_Note = "C-2"  ; float   m0_Hz =     8.18; // C-2
    string   m1_Note = "C#-2" ; float   m1_Hz =     8.66;
    string   m2_Note = "D-2"  ; float   m2_Hz =     9.18;
    string   m3_Note = "D#-2" ; float   m3_Hz =     9.72;
    string   m4_Note = "E-2"  ; float   m4_Hz =    10.30;
    string   m5_Note = "F-2"  ; float   m5_Hz =    10.91;
    string   m6_Note = "F#-2" ; float   m6_Hz =    11.56;
    string   m7_Note = "G-2"  ; float   m7_Hz =    12.25;
    string   m8_Note = "G#-2" ; float   m8_Hz =    12.98;
    string   m9_Note = "A-2"  ; float   m9_Hz =    13.75;
    string  m10_Note = "A#-2" ; float  m10_Hz =    14.57;
    string  m11_Note = "B-2"  ; float  m11_Hz =    15.43;
    string  m12_Note = "C-1"  ; float  m12_Hz =    16.35; // C-1
    string  m13_Note = "C#-1" ; float  m13_Hz =    17.32;
    string  m14_Note = "D-1"  ; float  m14_Hz =    18.35;
    string  m15_Note = "D#-1" ; float  m15_Hz =    19.45;
    string  m16_Note = "E-1"  ; float  m16_Hz =    20.60;
    string  m17_Note = "F-1"  ; float  m17_Hz =    21.83;
    string  m18_Note = "F#-1" ; float  m18_Hz =    23.12;
    string  m19_Note = "G-1"  ; float  m19_Hz =    24.50;
    string  m20_Note = "G#-1" ; float  m20_Hz =    25.96;
    string  m21_Note = "A-1"  ; float  m21_Hz =    27.50;
    string  m22_Note = "A#-1" ; float  m22_Hz =    29.14;
    string  m23_Note = "B-1"  ; float  m23_Hz =    30.87;
    string  m24_Note = "C0"   ; float  m24_Hz =    32.70; // C0
    string  m25_Note = "C#0"  ; float  m25_Hz =    34.65;
    string  m26_Note = "D0"   ; float  m26_Hz =    36.71;
    string  m27_Note = "D#0"  ; float  m27_Hz =    38.89;
    string  m28_Note = "E0"   ; float  m28_Hz =    41.20;
    string  m29_Note = "F0"   ; float  m29_Hz =    43.65;
    string  m30_Note = "F#0"  ; float  m30_Hz =    46.25;
    string  m31_Note = "G0"   ; float  m31_Hz =    49.00;
    string  m32_Note = "G#0"  ; float  m32_Hz =    51.91;
    string  m33_Note = "A0"   ; float  m33_Hz =    55.00;
    string  m34_Note = "A#0"  ; float  m34_Hz =    58.27;
    string  m35_Note = "B0"   ; float  m35_Hz =    61.74;
    string  m36_Note = "C1"   ; float  m36_Hz =    65.41; // C1
    string  m37_Note = "C#1"  ; float  m37_Hz =    69.30;
    string  m38_Note = "D1"   ; float  m38_Hz =    73.42;
    string  m39_Note = "D#1"  ; float  m39_Hz =    77.78;
    string  m40_Note = "E1"   ; float  m40_Hz =    82.41;
    string  m41_Note = "F1"   ; float  m41_Hz =    87.31;
    string  m42_Note = "F#1"  ; float  m42_Hz =    92.50;
    string  m43_Note = "G1"   ; float  m43_Hz =    98.00;
    string  m44_Note = "G#1"  ; float  m44_Hz =   103.83;
    string  m45_Note = "A1"   ; float  m45_Hz =   110.00;
    string  m46_Note = "A#1"  ; float  m46_Hz =   116.54;
    string  m47_Note = "B1"   ; float  m47_Hz =   123.47;
    string  m48_Note = "C2"   ; float  m48_Hz =   130.81; // C2
    string  m49_Note = "C#2"  ; float  m49_Hz =   138.59;
    string  m50_Note = "D2"   ; float  m50_Hz =   146.83;
    string  m51_Note = "D#2"  ; float  m51_Hz =   155.56;
    string  m52_Note = "E2"   ; float  m52_Hz =   164.81;
    string  m53_Note = "F2"   ; float  m53_Hz =   174.61;
    string  m54_Note = "F#2"  ; float  m54_Hz =   185.00;
    string  m55_Note = "G2"   ; float  m55_Hz =   196.00;
    string  m56_Note = "G#2"  ; float  m56_Hz =   207.65;
    string  m57_Note = "A2"   ; float  m57_Hz =   220.00;
    string  m58_Note = "A#2"  ; float  m58_Hz =   233.08;
    string  m59_Note = "B2"   ; float  m59_Hz =   246.94;
    string  m60_Note = "C3"   ; float  m60_Hz =   261.63; // C3
    string  m61_Note = "C#3"  ; float  m61_Hz =   277.18;
    string  m62_Note = "D3"   ; float  m62_Hz =   293.66;
    string  m63_Note = "D#3"  ; float  m63_Hz =   311.13;
    string  m64_Note = "E3"   ; float  m64_Hz =   329.63;
    string  m65_Note = "F3"   ; float  m65_Hz =   349.23;
    string  m66_Note = "F#3"  ; float  m66_Hz =   369.99;
    string  m67_Note = "G3"   ; float  m67_Hz =   392.00;
    string  m68_Note = "G#3"  ; float  m68_Hz =   415.30;
    string  m69_Note = "A3"   ; float  m69_Hz =   440.00;
    string  m70_Note = "A#3"  ; float  m70_Hz =   466.16;
    string  m71_Note = "B3"   ; float  m71_Hz =   493.88;
    string  m72_Note = "C4"   ; float  m72_Hz =   523.25; // C4
    string  m73_Note = "C#4"  ; float  m73_Hz =   554.37;
    string  m74_Note = "D4"   ; float  m74_Hz =   587.33;
    string  m75_Note = "D#4"  ; float  m75_Hz =   622.25;
    string  m76_Note = "E4"   ; float  m76_Hz =   659.26;
    string  m77_Note = "F4"   ; float  m77_Hz =   698.46;
    string  m78_Note = "F#4"  ; float  m78_Hz =   739.99;
    string  m79_Note = "G4"   ; float  m79_Hz =   783.99;
    string  m80_Note = "G#4"  ; float  m80_Hz =   830.61;
    string  m81_Note = "A4"   ; float  m81_Hz =   880.00;
    string  m82_Note = "A#4"  ; float  m82_Hz =   932.33;
    string  m83_Note = "B4"   ; float  m83_Hz =   987.77;
    string  m84_Note = "C5"   ; float  m84_Hz =  1046.50; // C5
    string  m85_Note = "C#5"  ; float  m85_Hz =  1108.73;
    string  m86_Note = "D5"   ; float  m86_Hz =  1174.66;
    string  m87_Note = "D#5"  ; float  m87_Hz =  1244.51;
    string  m88_Note = "E5"   ; float  m88_Hz =  1318.51;
    string  m89_Note = "F5"   ; float  m89_Hz =  1396.91;
    string  m90_Note = "F#5"  ; float  m90_Hz =  1479.98;
    string  m91_Note = "G5"   ; float  m91_Hz =  1567.98;
    string  m92_Note = "G#5"  ; float  m92_Hz =  1661.22;
    string  m93_Note = "A5"   ; float  m93_Hz =  1760.00;
    string  m94_Note = "A#5"  ; float  m94_Hz =  1864.66;
    string  m95_Note = "B5"   ; float  m95_Hz =  1975.53;
    string  m96_Note = "C6"   ; float  m96_Hz =  2093.00; // C6
    string  m97_Note = "C#6"  ; float  m97_Hz =  2217.46;
    string  m98_Note = "D6"   ; float  m98_Hz =  2349.32;
    string  m99_Note = "D#6"  ; float  m99_Hz =  2489.02;
    string m100_Note = "E6"   ; float m100_Hz =  2637.02;
    string m101_Note = "F6"   ; float m101_Hz =  2793.83;
    string m102_Note = "F#6"  ; float m102_Hz =  2959.96;
    string m103_Note = "G6"   ; float m103_Hz =  3135.96;
    string m104_Note = "G#6"  ; float m104_Hz =  3322.44;
    string m105_Note = "A6"   ; float m105_Hz =  3520.00;
    string m106_Note = "A#6"  ; float m106_Hz =  3729.31;
    string m107_Note = "B6"   ; float m107_Hz =  3951.07;
    string m108_Note = "C7"   ; float m108_Hz =  4186.01; // C7
    string m109_Note = "C#7"  ; float m109_Hz =  4434.92;
    string m110_Note = "D7"   ; float m110_Hz =  4698.64;
    string m111_Note = "D#7"  ; float m111_Hz =  4978.03;
    string m112_Note = "E7"   ; float m112_Hz =  5274.04;
    string m113_Note = "F7"   ; float m113_Hz =  5587.65;
    string m114_Note = "F#7"  ; float m114_Hz =  5919.91;
    string m115_Note = "G7"   ; float m115_Hz =  6271.93;
    string m116_Note = "G#7"  ; float m116_Hz =  6644.88;
    string m117_Note = "A7"   ; float m117_Hz =  7040.00;
    string m118_Note = "A#7"  ; float m118_Hz =  7458.62;
    string m119_Note = "B7"   ; float m119_Hz =  7902.13;
    string m120_Note = "C8"   ; float m120_Hz =  8372.02; // C8
    string m121_Note = "C#8"  ; float m121_Hz =  8869.84;
    string m122_Note = "D8"   ; float m122_Hz =  9397.27;
    string m123_Note = "D#8"  ; float m123_Hz =  9956.06;
    string m124_Note = "E8"   ; float m124_Hz = 10548.08;
    string m125_Note = "F8"   ; float m125_Hz = 11175.30;
    string m126_Note = "F#8"  ; float m126_Hz = 11839.82;
    string m127_Note = "G8"   ; float m127_Hz = 12543.85;
    
    float midiNoteArray[128] = {   m0_Hz,   m1_Hz,   m2_Hz,   m3_Hz,   m4_Hz,
                                   m5_Hz,   m6_Hz,   m7_Hz,   m8_Hz,   m9_Hz,
                                  m10_Hz,  m11_Hz,  m12_Hz,  m13_Hz,  m14_Hz,
                                  m15_Hz,  m16_Hz,  m17_Hz,  m18_Hz,  m19_Hz,
                                  m20_Hz,  m21_Hz,  m22_Hz,  m23_Hz,  m24_Hz,
                                  m25_Hz,  m26_Hz,  m27_Hz,  m28_Hz,  m29_Hz,
                                  m30_Hz,  m31_Hz,  m32_Hz,  m33_Hz,  m34_Hz,
                                  m35_Hz,  m36_Hz,  m37_Hz,  m38_Hz,  m39_Hz,
                                  m40_Hz,  m41_Hz,  m42_Hz,  m43_Hz,  m44_Hz,
                                  m45_Hz,  m46_Hz,  m47_Hz,  m48_Hz,  m49_Hz,
                                  m50_Hz,  m51_Hz,  m52_Hz,  m53_Hz,  m54_Hz,
                                  m55_Hz,  m56_Hz,  m57_Hz,  m58_Hz,  m59_Hz,
                                  m60_Hz,  m61_Hz,  m62_Hz,  m63_Hz,  m64_Hz,
                                  m65_Hz,  m66_Hz,  m67_Hz,  m68_Hz,  m69_Hz,
                                  m70_Hz,  m71_Hz,  m72_Hz,  m73_Hz,  m74_Hz,
                                  m75_Hz,  m76_Hz,  m77_Hz,  m78_Hz,  m79_Hz,
                                  m80_Hz,  m81_Hz,  m82_Hz,  m83_Hz,  m84_Hz,
                                  m85_Hz,  m86_Hz,  m87_Hz,  m88_Hz,  m89_Hz,
                                  m90_Hz,  m91_Hz,  m92_Hz,  m93_Hz,  m94_Hz,
                                  m95_Hz,  m96_Hz,  m97_Hz,  m98_Hz,  m99_Hz,
                                 m100_Hz, m101_Hz, m102_Hz, m103_Hz, m104_Hz,
                                 m105_Hz, m106_Hz, m107_Hz, m108_Hz, m109_Hz,
                                 m110_Hz, m111_Hz, m112_Hz, m113_Hz, m114_Hz,
                                 m115_Hz, m116_Hz, m117_Hz, m118_Hz, m119_Hz,
                                 m120_Hz, m121_Hz, m122_Hz, m123_Hz, m124_Hz,
                                 m125_Hz, m126_Hz, m127_Hz                    };
};


