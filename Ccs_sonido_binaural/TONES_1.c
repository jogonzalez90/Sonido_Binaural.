////////////////// Driver to generate musical tones /////////////////////
////                                                                 ////
////  generate_tone(frequency, duration)     Generates wave at set   ////
////                                         frequency (Hz) for set  ////
////                                         duration (ms)           ////
////                                                                 ////
/////////////////////////////////////////////////////////////////////////
////        (C) Copyright 1996,2003 Custom Computer Services         ////
//// This source code may only be used by licensed users of the CCS  ////
//// C compiler.  This source code may only be distributed to other  ////
//// licensed users of the CCS C compiler.  No other use,            ////
//// reproduction or distribution is permitted without written       ////
//// permission.  Derivative programs created using this software    ////
//// in object code form are not restricted in any way.              ////
/////////////////////////////////////////////////////////////////////////


#ifndef  MUSIC_NOTES
#define  MUSIC_NOTES

//            NOTE                 FREQUENCY
//                     Octave0  Octave1  Octave2  Octave3
const long C_NOTE[4]  ={ 33,     523,    1047,    2093};
const long Db_NOTE[4] ={ 35,     554,    1109,    2217};
const long D_NOTE[4]  ={ 37,     587,    1175,    2349};
const long Eb_NOTE[4] ={ 39,     622,    1245,    2489};
const long E_NOTE[4]  ={ 41,     659,    1329,    2637};
const long F_NOTE[4]  ={ 44,     698,    1397,    2794};
const long Gb_NOTE[4] ={ 46,     740,    1480,    2960};
const long G_NOTE[4]  ={ 49,     784,    1568,    3136};
const long Ab_NOTE[4] ={ 52,     831,    1661,    3322};
const long A_NOTE[4]  ={ 55,     880,    1760,    3520};
const long Bb_NOTE[4] ={ 58,     923,    1865,    3729};
const long B_NOTE[4]  ={ 61,     988,    1976,    3951};
const long Solf[6]  ={ 396,     432,    528,   639,  741,  852};//Frecuencias Solfeggio

//Sonidos binaurales Delta 502 Hz sue�o profundo
//Theta 506 Hz Relajaci�n, creatividad, meditaci�n
//Alfa 510 Hz disminuci�n de ansiedad
//Beta 522 Hz concebtraci�n, memoria, atenci�n estado de alerta
const long Binau[4]  ={ 502,     506,    510,   522};
#endif

#define TONE_PIN  PIN_B0


void do_delay(int ms_delay, int num_ms, int us_delay, int num_us)  {
 int i;

 for(i=0;i<num_ms;i++)
  delay_ms(250);
 delay_ms(ms_delay);
 for(i=0;i<num_us;i++)
  delay_us(250);
 delay_us(us_delay);
}


void generate_tone(long frequency, long duration)
{
   int32 total_delay_time;                      // in microseconds
   long total_ms_delay_time, total_us_delay_time;
   int num_us_delays, num_ms_delays, ms_delay_time, us_delay_time;
   long num_periods;

   total_delay_time = (1000000/frequency)/2-10; // calculate total delay time (10 for error)

   total_ms_delay_time = total_delay_time/1000; // total delay time of ms
   num_ms_delays = total_ms_delay_time/250;     // number of 250ms delays needed
   ms_delay_time = total_ms_delay_time%250;     // left over ms delay time needed

   total_us_delay_time = total_delay_time%1000; // total delay time of us (ms already acounted for)
   num_us_delays = total_us_delay_time/250;     // number of 250us delays needed
   us_delay_time = total_us_delay_time%250;     // left over us delay time needed

   num_periods = ((int32)duration*1000)/(1000000/frequency);

   while((num_periods--) != 0)
   {
      do_delay(ms_delay_time, num_ms_delays, us_delay_time, num_us_delays);
      output_high(TONE_PIN);
      do_delay(ms_delay_time, num_ms_delays, us_delay_time, num_us_delays);
      output_low(TONE_PIN);
   }

   return;
}