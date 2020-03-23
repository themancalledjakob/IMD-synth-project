#include <Button.h>
#include <TimerOne.h>
#include <PS2Keyboard.h>
const int DataPin = 2;
const int IRQpin =  3;
PS2Keyboard keyboard;


long calctempodelay = 0;
long tempodelay = 500;
long curtimestamp = 0;
long prevtimestamp = 0;
long lasttickstamp =0;
long wheelfactor = 6; // adjust this to modify the pulseperiod to tempo ratio (wheel radius), higher = faster
int  tickflag = 0; // indicate if time tick has passed

const int bicyclesetup = 0;
const int pot1setup = 1;
const int pot2setup = 1;
const int button3Pin = 4;
const int button4Pin = 5;
const int dreamblaster_enable_pin = 6;
int potentiopin = 2;
long potentiovalue = 0;
int buttonState = 0; 
int prev_buttonState = 0; 
int enabledrumming = 0;
int enablebassline = 0;
int enablesynthline = 0;
long seq_poscnt = 0;
byte resonantchannel= 1;
byte channel1_prog = 90;
byte channel2_prog = 38;
byte bassvolume = 0x70;
byte drumvolume = 0x80;
byte synthvolume = 0x50;
byte leadvolume  = 0x70;

#define _BASSDRUM_NOTE 0x24
#define _SNAREDRUM_NOTE 0x26
#define _CLOSEDHIHAT_NOTE 0x2A
#define _PEDALHIHAT_NOTE 0x2C
#define _OPENHIHAT_NOTE 0x2E
#define _CYMBAL_NOTE 0x31
#define _DRUMPRESS_STATUSCODE 0x99
#define _DRUMRELEASE_STATUSCODE 0x89
#define _SYNTHPRESS_STATUSCODE 0x90
#define _SYNTHRELEASE_STATUSCODE 0x80

void midiwrite(int cmd, int pitch, int velocity) {

  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);

}


void midisetup_sam2195_nrpn_send(int channel, int control1,int control2, int value)
{
   Serial.write((byte)(0xB0+channel));
   Serial.write(0x63);
   Serial.write((byte)control1);
   Serial.write(0x62);
   Serial.write((byte)control2);
   Serial.write(0x06);
   Serial.write((byte)value);
}

void midisetup_sam2195_sysexcfg_send(int channelprefix,int channel, int control, int value)
{
   Serial.write(0xF0);
   Serial.write(0x41);
   Serial.write(0x00);
   Serial.write(0x42);
   Serial.write(0x12);
   Serial.write(0x40);
   Serial.write((byte)(channelprefix*16+channel));   
   Serial.write((byte)control);
   Serial.write((byte)value);   
   Serial.write(0x00);   
   Serial.write(0xF7);   
   
}

void midisetup_sam2195_gsreset(void)
{
  midisetup_sam2195_sysexcfg_send(0,0,0x7F,0);
}

void midiprogchange(int cmd, int prog) {
  Serial.write(cmd);
  Serial.write(prog);
}


Button button3 = Button(button3Pin,BUTTON_PULLDOWN);
Button button4 = Button(button4Pin,BUTTON_PULLDOWN);


void basssubseq(long relativpos) 
{ 
  switch(relativpos)
    {
//    case 0 :
//      midiwrite(0x81, 64, 0x00); 
//      midiwrite(0x91, 28, bassvolume); 
//      break;
//    case 8 :
//      midiwrite(0x81, 28, 0x00); 
//      midiwrite(0x91, 40, bassvolume);     
//      break;
//    case 16 :
//      midiwrite(0x81, 40, 0x00); 
//      midiwrite(0x91, 52, bassvolume);     
//      break;
//    case 24:
//      midiwrite(0x81, 52, 0x00); 
//      midiwrite(0x91, 64, bassvolume);   
//      break;      



case 0:
      midiwrite(0x81, 38, 0x00); 
      midiwrite(0x91, 38, bassvolume);
      break;
      case 1:
      midiwrite(0x81, 38, 0x00); 
      midiwrite(0x91, 38, bassvolume);
      break;
      case 2:
      midiwrite(0x81, 38, 0x00); 
      midiwrite(0x91, 50, bassvolume);
      break;
      case 3:
      midiwrite(0x81, 50, 0x00); 
      midiwrite(0x91, 38, bassvolume);
      break;
      case 4:
      midiwrite(0x81, 38, 0x00); 
      midiwrite(0x91, 38, bassvolume);
      break;
      case 5:
      midiwrite(0x81, 38, 0x00); 
      midiwrite(0x91, 50, bassvolume);
      break;
       case 6:
      midiwrite(0x81, 38, 0x00); 
      midiwrite(0x91, 38, bassvolume);
      break;
      case 7:
      midiwrite(0x81, 38, 0x00); 
      midiwrite(0x91, 38, bassvolume);
      break;
      case 8:
      midiwrite(0x81, 38, 0x00); 
      midiwrite(0x91, 50, bassvolume);
      break;
      case 9:
      midiwrite(0x81, 50, 0x00); 
      midiwrite(0x91, 38, bassvolume);
      break;
      case 10:
      midiwrite(0x81, 38, 0x00); 
      midiwrite(0x91, 38, bassvolume);
      break;
      case 11:
      midiwrite(0x81, 38, 0x00); 
      midiwrite(0x91, 50, bassvolume);
      break;
      case 12:
      midiwrite(0x81, 50, 0x00); 
      midiwrite(0x91, 38, bassvolume);
      break;
      case 13:
      midiwrite(0x81, 38, 0x00); 
      midiwrite(0x91, 38, bassvolume);
      break;
      case 14:
      midiwrite(0x81, 38, 0x00); 
      midiwrite(0x91, 50, bassvolume);
      break;
      case 15:
      midiwrite(0x81, 50, 0x00); 
      midiwrite(0x91, 43, bassvolume);
      break;
      case 16:
      midiwrite(0x81, 43, 0x00); 
      midiwrite(0x91, 43, bassvolume);
      break;
       case 17:
      midiwrite(0x81, 43, 0x00); 
      midiwrite(0x91, 43, bassvolume);
      break;
       case 18:
      midiwrite(0x81, 43, 0x00); 
      midiwrite(0x91, 55, bassvolume);
      break;
       case 19:
      midiwrite(0x81, 55, 0x00); 
      midiwrite(0x91, 43, bassvolume);
      break;
      case 20:
      midiwrite(0x81, 43, 0x00); 
      midiwrite(0x91, 43, bassvolume);
      break;
      case 21:
      midiwrite(0x81, 43, 0x00); 
      midiwrite(0x91, 55, bassvolume);
      break;
       case 22:
      midiwrite(0x81, 55, 0x00); 
      midiwrite(0x91, 43, bassvolume);
      break;
      case 23:
      midiwrite(0x81, 43, 0x00); 
      midiwrite(0x91, 43, bassvolume);
      break;
      case 24:
      midiwrite(0x81, 43, 0x00); 
      midiwrite(0x91, 55, bassvolume);
      break;
       case 25:
      midiwrite(0x81, 55, 0x00); 
      midiwrite(0x91, 43, bassvolume);
      break;
      case 26:
      midiwrite(0x81, 43, 0x00); 
      midiwrite(0x91, 43, bassvolume);
      break;
      case 27:
      midiwrite(0x81, 43, 0x00); 
      midiwrite(0x91, 55, bassvolume);
      break;
       case 28:
      midiwrite(0x81, 55, 0x00); 
      midiwrite(0x91, 43, bassvolume);
      break;
      case 29:
      midiwrite(0x81, 43, 0x00); 
      midiwrite(0x91, 43, bassvolume);
      break;
       case 30:
      midiwrite(0x81, 43, 0x00); 
      midiwrite(0x91, 55, bassvolume);
      break;
      case 31:
      midiwrite(0x81, 55, 0x00); 
      midiwrite(0x91, 45, bassvolume);
      break;
      case 32:
      midiwrite(0x81, 45, 0x00); 
      midiwrite(0x91, 45, bassvolume);
      break;
      case 33:
      midiwrite(0x81, 45, 0x00); 
      midiwrite(0x91, 45, bassvolume);
      break;
      case 34:
      midiwrite(0x81, 45, 0x00); 
      midiwrite(0x91, 57, bassvolume);
      break;
      case 35:
      midiwrite(0x81, 57, 0x00); 
      midiwrite(0x91, 45, bassvolume);
      break;
      case 36:
      midiwrite(0x81, 45, 0x00); 
      midiwrite(0x91, 45, bassvolume);
      break;
      case 37:
      midiwrite(0x81, 45, 0x00); 
      midiwrite(0x91, 57, bassvolume);
      break;
      case 38:
      midiwrite(0x81, 57, 0x00); 
      midiwrite(0x91, 45, bassvolume);
      break;
      case 39:
      midiwrite(0x81, 45, 0x00); 
      midiwrite(0x91, 45, bassvolume);
      break;
      case 40:
      midiwrite(0x81, 45, 0x00); 
      midiwrite(0x91, 57, bassvolume);
      break;
      case 41:
      midiwrite(0x81, 57, 0x00); 
      midiwrite(0x91, 45, bassvolume);
      break;
      case 42:
      midiwrite(0x81, 45, 0x00); 
      midiwrite(0x91, 45, bassvolume);
      break;
      case 43:
      midiwrite(0x81, 45, 0x00); 
      midiwrite(0x91, 57, bassvolume);
      break;
      case 44:
      midiwrite(0x81, 57, 0x00); 
      midiwrite(0x91, 45, bassvolume);
      break;
      case 45:
      midiwrite(0x81, 45, 0x00); 
      midiwrite(0x91, 45, bassvolume);
      break;
      case 46:
      midiwrite(0x81, 45, 0x00); 
      midiwrite(0x91, 57, bassvolume);
      break;
      case 47:
      midiwrite(0x81, 57, 0x00); 
      midiwrite(0x91, 41, bassvolume);
      break;
      case 48:
      midiwrite(0x81, 41, 0x00); 
      midiwrite(0x91, 41, bassvolume);
      break;
      case 49:
      midiwrite(0x81, 41, 0x00); 
      midiwrite(0x91, 41, bassvolume);
      break;
      case 50:
      midiwrite(0x81, 41, 0x00); 
      midiwrite(0x91, 53, bassvolume);
      break;
      case 51:
      midiwrite(0x81, 53, 0x00); 
      midiwrite(0x91, 41, bassvolume);
      break;
      case 52:
      midiwrite(0x81, 41, 0x00); 
      midiwrite(0x91, 41, bassvolume);
      break;
      case 53:
      midiwrite(0x81, 41, 0x00); 
      midiwrite(0x91, 53, bassvolume);
      break;
      case 54:
      midiwrite(0x81, 53, 0x00); 
      midiwrite(0x91, 40, bassvolume);
      break;
      case 55:
      midiwrite(0x81, 40, 0x00); 
      midiwrite(0x91, 40, bassvolume);
      break;
      case 56:
      midiwrite(0x81, 40, 0x00); 
      midiwrite(0x91, 52, bassvolume);
      break;
      case 57:
      midiwrite(0x81, 52, 0x00); 
      midiwrite(0x91, 40, bassvolume);
      break;
      case 58:
      midiwrite(0x81, 40, 0x00); 
      midiwrite(0x91, 40, bassvolume);
      break;
      case 59:
      midiwrite(0x81, 40, 0x00); 
      midiwrite(0x91, 52, bassvolume);
      break;
      case 60:
      midiwrite(0x81, 52, 0x00); 
      midiwrite(0x91, 38, bassvolume);
      break;
      case 61:
      midiwrite(0x81, 38, 0x00); 
      midiwrite(0x91, 38, bassvolume);
      break;
      case 62:
      midiwrite(0x81, 38, 0x00); 
      midiwrite(0x91, 50, bassvolume);
      break;
      case 63:
      midiwrite(0x81, 50, 0x00); 
      midiwrite(0x91, 38, bassvolume);
      break;
          
    default :
      break;
    }    

}


void drumsubseq(long relativpos) 
{ 
    switch(relativpos)
    {
    case 0 :
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);
      midiwrite(0x99, _BASSDRUM_NOTE, drumvolume);     
      break;
      case 1:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 2:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 3:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
    case 4:
    midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);
      midiwrite(0x99, _SNAREDRUM_NOTE, drumvolume);  
      midiwrite(0x99, _BASSDRUM_NOTE, drumvolume);  
      break;
        case 5:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 6:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 7:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
    case 8 :
    midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);
      midiwrite(0x99, _BASSDRUM_NOTE, drumvolume);     
      break;
        case 9:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 10:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 11:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
    case 12 :
    midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);
       midiwrite(0x99, _SNAREDRUM_NOTE, drumvolume);   
       midiwrite(0x99, _BASSDRUM_NOTE, drumvolume);  
      break;
        case 13:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 14:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 15:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
    case 16:
    midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);
    midiwrite(0x99, _BASSDRUM_NOTE, drumvolume);     
      break;
        case 17:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 18:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 19:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
    case 20:
    midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);
       midiwrite(0x99, _SNAREDRUM_NOTE, drumvolume); 
       midiwrite(0x99, _BASSDRUM_NOTE, drumvolume);  
      break;
        case 21:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 22:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 23:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
    case 24:
    midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);
    midiwrite(0x99, _BASSDRUM_NOTE, drumvolume);     
      break;
        case 25:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 26:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 27:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
    case 28:
    midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);
       midiwrite(0x99, _SNAREDRUM_NOTE, drumvolume);
       midiwrite(0x99, _BASSDRUM_NOTE, drumvolume);
      break; 
        case 29:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 30:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 31:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;       
    case 32 :
    midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);
      midiwrite(0x99, _BASSDRUM_NOTE, drumvolume);     
      break;
        case 33:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 34:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 35:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
    case 36:
    midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);
      midiwrite(0x99, _SNAREDRUM_NOTE, drumvolume); 
      midiwrite(0x99, _BASSDRUM_NOTE, drumvolume);   
      break;
        case 37:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 38:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 39:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
    case 40 :
    midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);
      midiwrite(0x99, _BASSDRUM_NOTE, drumvolume);     
      break;
        case 41:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 42:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 43:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
    case 44 :
    midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);
       midiwrite(0x99, _SNAREDRUM_NOTE, drumvolume); 
       midiwrite(0x99, _BASSDRUM_NOTE, drumvolume);    
      break;
        case 45:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 46:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 47:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
    case 48:
    midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);
    midiwrite(0x99, _BASSDRUM_NOTE, drumvolume);     
      break;
        case 49:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 50:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 51:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
    case 52:
    midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);
       midiwrite(0x99, _SNAREDRUM_NOTE, drumvolume);   
       midiwrite(0x99, _BASSDRUM_NOTE, drumvolume);
      break;
        case 53:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 54:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 55:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
    case 56:
    midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);
    midiwrite(0x99, _BASSDRUM_NOTE, drumvolume);     
      break;
        case 57:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 58:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 59:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
    case 60:
    midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);
       midiwrite(0x99, _SNAREDRUM_NOTE, drumvolume);
       midiwrite(0x99, _BASSDRUM_NOTE, drumvolume);

      break;
        case 61:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 62:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;
      case 63:
      midiwrite(0x99, _CLOSEDHIHAT_NOTE, drumvolume);    
      break;        
    default :
      break;
    }     
 }

 void synthseq(long seqpos) 
{ 
  char relativpos;
  char seq_poscnt_mod2;
  relativpos =seqpos%64;
  seq_poscnt_mod2 = seqpos%2;
  if(enablesynthline)
  {
  switch(relativpos)
    {
   
//    case 14:
//        midiwrite(0x80, 53, 0x00); 
//        midiwrite(0x80, 57, 0x00); 
//       midiwrite(0x90, 50, synthvolume); 
//       midiwrite(0x90, 55, synthvolume); 
//       midiwrite(0x90, 59, synthvolume);    
//      break;
//    case 30 :
//      midiwrite(0x80, 50, 0x00); 
//      midiwrite(0x80, 55, 0x00); 
//      midiwrite(0x80, 59, 0x00); 
//       midiwrite(0x90, 52, synthvolume); 
//       midiwrite(0x90, 57, synthvolume); 
//       midiwrite(0x90, 60, synthvolume);     
//      break;
//    case 46:
//      midiwrite(0x80, 52, 0x00); 
//       midiwrite(0x90, 53, synthvolume); 
//       midiwrite(0x90, 57, synthvolume); 
//       midiwrite(0x90, 60, synthvolume);
//      break;  
//      case 62 :
//       midiwrite(0x80, 60, 0x00);  
//       midiwrite(0x90, 50, synthvolume); 
//       midiwrite(0x90, 53, synthvolume); 
//       midiwrite(0x90, 57, synthvolume);
//      break;   

    
      
      case 14:
        midiwrite(0x80, 53, 0x00); 
        midiwrite(0x80, 57, 0x00); 
       midiwrite(0x90, 50, synthvolume); 
       midiwrite(0x90, 55, synthvolume); 
       midiwrite(0x90, 59, synthvolume);    
      break;
    case 30 :
      midiwrite(0x80, 50, 0x00); 
      midiwrite(0x80, 55, 0x00); 
      midiwrite(0x80, 59, 0x00); 
       midiwrite(0x90, 52, synthvolume); 
       midiwrite(0x90, 57, synthvolume); 
       midiwrite(0x90, 60, synthvolume);     
      break;
    case 46:
      midiwrite(0x80, 52, 0x00); 
       midiwrite(0x90, 53, synthvolume); 
       midiwrite(0x90, 57, synthvolume); 
       midiwrite(0x90, 60, synthvolume);
      break;  
      case 54:
      midiwrite(0x80, 53, 0x00); 
       midiwrite(0x90, 52, synthvolume); 
       midiwrite(0x90, 57, synthvolume); 
       midiwrite(0x90, 60, synthvolume);
      break;
      case 62 :
       midiwrite(0x80, 60, 0x00);  
       midiwrite(0x80, 52, 0x00);  
       midiwrite(0x90, 50, synthvolume); 
       midiwrite(0x90, 53, synthvolume); 
       midiwrite(0x90, 57, synthvolume);
      break;  
      
   
    default :
      break;
    }    

if(enablebassline)
    {
      basssubseq(relativpos);
    }
   if(enabledrumming)
   {
      drumsubseq(relativpos);     
   }
  } 
 };


void timercallback()
{
  lasttickstamp = millis();
  Timer1.setPeriod(tempodelay * 1000);     
  tickflag = 1;
}

void setupvoices(void)
{
    midiprogchange(0xC0,channel1_prog);
    midiprogchange(0xC1,channel2_prog);
}
void SomeButtonPressHandler(Button& butt)
{  
 if(enablesynthline)
  {
    if(butt == button3)
    {
      enablebassline = enablebassline?0:1;
      enabledrumming = enabledrumming?0:1;
    };

  }
  else
  {
    
    if(butt == button3)
    {  
      midiwrite(0x99, _SNAREDRUM_NOTE, 0x65);   
    }
    if(butt == button4)
    {  
      midiwrite(0x99, _BASSDRUM_NOTE, 0x65);   
    }
  }
}
void stopallnotes(byte selection = 0)
{  

if (selection == 0 || selection ==2)
{
       midiwrite(0x90, 28, 0x00); // switch off possible bass notes
      midiwrite(0x90, 40, 0x00); // switch off possible bass notes           
      midiwrite(0x90, 50, 0x00); // switch off possible synth notes
      midiwrite(0x90, 52, 0x00); // switch off possible synth notes
      midiwrite(0x90, 53, 0x00); // switch off possible synth notes
      midiwrite(0x90, 55, 0x00); // switch off possible synth notes
      midiwrite(0x90, 57, 0x00); // switch off possible synth notes 
      midiwrite(0x90, 59, 0x00); // switch off possible synth notes
      midiwrite(0x90, 60, 0x00); // switch off possible synth notes
      midiwrite(0x90, 62, 0x00); // switch off possible synth notes
      midiwrite(0x90, 64, 0x00); // switch off possible synth notes
      midiwrite(0x90, 65, 0x00); // switch off possible synth notes
      midiwrite(0x90, 67, 0x00); // switch off possible synth notes    
}
if (selection == 0 || selection ==1)
{
      midiwrite(0x91, 38, 0x00); // switch off possible synth notes
     midiwrite(0x91, 40, 0x00); // switch off possible synth notes
      midiwrite(0x91, 42, 0x00); // switch off possible synth notes
      midiwrite(0x91, 43, 0x00); // switch off possible synth notes
      midiwrite(0x91, 45, 0x00); // switch off possible synth notes
      midiwrite(0x91, 47, 0x00); // switch off possible synth notes 
      midiwrite(0x91, 48, 0x00); // switch off possible synth notes
     midiwrite(0x91, 50, 0x00); // switch off possible synth notes
      midiwrite(0x91, 52, 0x00); // switch off possible synth notes
      midiwrite(0x91, 53, 0x00); // switch off possible synth notes
      midiwrite(0x91, 55, 0x00); // switch off possible synth notes
      midiwrite(0x91, 57, 0x00); // switch off possible synth notes 
      midiwrite(0x91, 59, 0x00); // switch off possible synth notes
      midiwrite(0x91, 60, 0x00); // switch off possible synth notes
      midiwrite(0x91, 62, 0x00); // switch off possible synth notes
      midiwrite(0x91, 64, 0x00); // switch off possible synth notes
      midiwrite(0x91, 65, 0x00); // switch off possible synth notes
      midiwrite(0x91, 67, 0x00); // switch off possible synth notes
  
     
}
}



void SomeButtonReleaseHandler(Button& butt)
{
  if(enablesynthline)
  {
    //..
  } 
  else
  {
  
  }
  
  
}

void PotControl(int potnr, int ctrlVal)
{
  if(potnr == 1)
  {
     //Serial.println(ctrlVal);
      midisetup_sam2195_nrpn_send(resonantchannel,0x01,0x20,(byte)ctrlVal); 
      midiwrite(0xB0, 0x01,(byte) ctrlVal);  // modulation wheel
      
       
  }
   if(potnr == 2)
  {
//     midisetup_sam2195_nrpn_send(resonantchannel,0x01,0x21,(byte)ctrlVal);  // set resonance for channel resonantchannel
     drumvolume = (byte)ctrlVal;
  }
}


void ADC_handle(void)
{
  static int prevsensorVal1 = -1000;  
  static int prevsensorVal2 = -1000;
  if(pot1setup)
  {
    int sensorValue = analogRead(A4);
    int ctrlValue;
    if(abs(sensorValue-prevsensorVal1)>3)  // filter noise from adc input
    {
//        Serial.print(sensorValue);
        prevsensorVal1 = sensorValue;
        ctrlValue = sensorValue/8;
        PotControl(1,ctrlValue);
    }
  }
  if(pot2setup)
  {
    int sensorValue = analogRead(A3);
    int ctrlValue;
    if(abs(sensorValue-prevsensorVal2)>3)  // filter noise from adc input
    {
//        Serial.print(" - ");
//        Serial.println(sensorValue);
        prevsensorVal2 = sensorValue;
        ctrlValue = sensorValue/8;
        PotControl(2,ctrlValue);
    }
  }
}


void SomeButtonHoldHandler(Button& butt)
{
  if(butt==button4)
  {
        stopsynth(); 
  }
}

void KeyboardHandler(char key,bool iskeyrelease)
{
  static bool space_pressed = false;  
  static bool enter_pressed = false;  
  static bool zero_pressed = false;  
  static bool nine_pressed = false; 
  static bool c_pressed = false;  
  static bool v_pressed = false;  
  static bool b_pressed = false;
  static bool a_pressed = false; 
  static bool s_pressed = false;
  static bool d_pressed = false;
  static bool f_pressed = false;
  static bool g_pressed = false;
  static bool h_pressed = false;
  static bool j_pressed = false;
  static bool k_pressed = false;
  static bool l_pressed = false; 
  static bool o_pressed = false;
  static bool i_pressed = false;
  static bool u_pressed = false;
  static bool y_pressed = false;
  static bool t_pressed = false;
  static bool r_pressed = false;
  static bool e_pressed = false;
  static bool w_pressed = false;
  static bool q_pressed = false;
  byte drumstatuscode;
  byte synthstatuscode;
  byte volumecode;

  drumstatuscode = iskeyrelease ? _DRUMRELEASE_STATUSCODE : _DRUMPRESS_STATUSCODE;
  synthstatuscode = iskeyrelease ? _SYNTHRELEASE_STATUSCODE : _SYNTHPRESS_STATUSCODE;
  volumecode = iskeyrelease ? 0x00 : leadvolume;
  if((key==PS2_PAGEUP)|| (key==PS2_PAGEDOWN) || (key=='+')|| (key=='-'))
  {
    if(!iskeyrelease) 
     {
        if(key=='+') 
        {
          channel2_prog++;
          if(channel2_prog > 0x7F)
          {
            channel2_prog = 0x00; 
          }       
        } 
       if(key=='-') 
        {
          channel2_prog--;
          if(channel2_prog > 0x7F)
          {
            channel2_prog = 0x7F; 
          }       
        } 
       if(key==PS2_PAGEUP) 
        {
          channel1_prog++;
          if(channel1_prog > 0x7F)
          {
            channel1_prog = 0x00; 
          }       
        } 
       if(key==PS2_PAGEDOWN)
        {
          channel1_prog--;
          if(channel1_prog > 0x7F)
          {
            channel1_prog = 0x7F; 
          }       
        } 

       setupvoices();
     }
  }
  if(key==' ') 
   {
     if(!space_pressed || iskeyrelease) 
     {     
        midiwrite(drumstatuscode, _BASSDRUM_NOTE, drumvolume);      
     }
     space_pressed = !iskeyrelease;
     return;
   }
  if(key==PS2_ENTER) 
   {
     if(!enter_pressed  || iskeyrelease) 
     { 
      midiwrite(drumstatuscode,_CLOSEDHIHAT_NOTE, volumecode); 
     }
     enter_pressed = !iskeyrelease;
     return;
   }
  if(key=='0') 
   {
     if(!zero_pressed || iskeyrelease) 
     { 
      midiwrite(drumstatuscode,  _SNAREDRUM_NOTE, volumecode);      
     }
     zero_pressed = !iskeyrelease;
     return;
   }

   if(key=='9') 
   {
     if(!nine_pressed || iskeyrelease) 
     { 
      midiwrite(drumstatuscode,  _CYMBAL_NOTE, volumecode);      
     }
     nine_pressed = !iskeyrelease;
     return;
   }

   if(key=='a') 
   {
     if(!a_pressed || iskeyrelease) 
     { 
      midiwrite(synthstatuscode,  55, volumecode);      
     }
     a_pressed = !iskeyrelease;
     return;
   }

   if(key=='s') 
   {
     if(!s_pressed || iskeyrelease) 
     { 
      midiwrite(synthstatuscode,  57, volumecode);      
     }
     s_pressed = !iskeyrelease;
     return;
   }

   if(key=='d') 
   {
     if(!d_pressed || iskeyrelease) 
     { 
      midiwrite(synthstatuscode,  59, volumecode);      
     }
     d_pressed = !iskeyrelease;
     return;
   }
   if(key=='f') 
   {
     if(!f_pressed || iskeyrelease) 
     { 
      midiwrite(synthstatuscode,  60, volumecode);      
     }
     f_pressed = !iskeyrelease;
     return;
   }
   if(key=='g') 
   {
     if(!g_pressed || iskeyrelease) 
     { 
      midiwrite(synthstatuscode,  62, volumecode);      
     }
     g_pressed = !iskeyrelease;
     return;
   }

   if(key=='h') 
   {
     if(!h_pressed || iskeyrelease) 
     { 
      midiwrite(synthstatuscode,  64, volumecode);      
     }
     h_pressed = !iskeyrelease;
     return;
   }
   if(key=='j') 
   {
     if(!j_pressed || iskeyrelease) 
     { 
      midiwrite(synthstatuscode,  65, volumecode);      
     }
     j_pressed = !iskeyrelease;
     return;
   }
   if(key=='k') 
   {
     if(!k_pressed || iskeyrelease) 
     { 
      midiwrite(synthstatuscode,  67, volumecode);      
     }
     k_pressed = !iskeyrelease;
     return;
   }
   if(key=='l') 
   {
     if(!l_pressed || iskeyrelease) 
     { 
      midiwrite(synthstatuscode,  69, volumecode);      
     }
     l_pressed = !iskeyrelease;
     return;
   }
   if(key=='o') 
   {
     if(!o_pressed || iskeyrelease) 
     { 
      midiwrite(synthstatuscode,  65, volumecode);      
     }
     o_pressed = !iskeyrelease;
     return;
   }
   if(key=='i') 
   {
     if(!i_pressed || iskeyrelease) 
     { 
      midiwrite(synthstatuscode,  64, volumecode);      
     }
     i_pressed = !iskeyrelease;
     return;
   }
   if(key=='u') 
   {
     if(!u_pressed || iskeyrelease) 
     { 
      midiwrite(synthstatuscode,  62, volumecode);      
     }
     u_pressed = !iskeyrelease;
     return;
   }
   if(key=='y') 
   {
     if(!y_pressed || iskeyrelease) 
     { 
      midiwrite(synthstatuscode,  60, volumecode);      
     }
     y_pressed = !iskeyrelease;
     return;
   }
   
   if(key=='t') 
   {
     if(!t_pressed || iskeyrelease) 
     { 
      midiwrite(synthstatuscode,  59, volumecode);      
     }
     t_pressed = !iskeyrelease;
     return;
   }
   if(key=='r') 
   {
     if(!r_pressed || iskeyrelease) 
     { 
      midiwrite(synthstatuscode,  57, volumecode);      
     }
     r_pressed = !iskeyrelease;
     return;
   }
   if(key=='e') 
   {
     if(!e_pressed || iskeyrelease) 
     { 
      midiwrite(synthstatuscode,  55, volumecode);      
     }
     e_pressed = !iskeyrelease;
     return;
   }
   if(key=='w') 
   {
     if(!w_pressed || iskeyrelease) 
     { 
      midiwrite(synthstatuscode,  52, volumecode);      
     }
     w_pressed = !iskeyrelease;
     return;
   }
   if(key=='q') 
   {
     if(!q_pressed || iskeyrelease) 
     { 
      midiwrite(synthstatuscode,  50, volumecode);      
     }
     q_pressed = !iskeyrelease;
     return;
   }
   if(key=='1') 
   {
     if(!iskeyrelease) 
     {        
       buttonState = (buttonState==0) ? 1 : 0;        
     }
     return;
   }
   
  
   if(key=='2') 
   {
     if(!iskeyrelease) 
     { 
        enablebassline = enablebassline?0:1;
        if(!enablebassline) {stopallnotes(1);};
     }
     return;
   }
   
   if(key=='3') 
   {
     if(!iskeyrelease) 
     {        
       enabledrumming = (enabledrumming==0) ? 1 : 0;        
     }
     return;
   }

if(key=='4') 
   {
     if(!iskeyrelease) 
     { 
        enablesynthline = enablesynthline?0:1;
        if(!enablesynthline) {stopallnotes(2);};
     }
     return;
   }
   
}

void setup() {
  Serial.begin(31250);
  analogReference(DEFAULT); 
  
  pinMode(dreamblaster_enable_pin ,OUTPUT);   // enable the dreamblaster module by pulling high /reset
  digitalWrite(dreamblaster_enable_pin, HIGH);
  delay(300);  // allow 500ms for the dreamblaster to boot
  midisetup_sam2195_gsreset();
  delay(500);  // allow 250 for gs reset
  
  keyboard.begin(DataPin, IRQpin); // ps2 keyboard
  

  midisetup_sam2195_sysexcfg_send(0x02,0x00,0x01,0x50);  // set mod wheel cutoff
  midisetup_sam2195_sysexcfg_send(0x02,0x00,0x04,0x00);  // disable mod wheel pitch variation
  midisetup_sam2195_sysexcfg_send(0x02,0x00,0x05,0x7F);  // set mod wheel tvf depth

  midisetup_sam2195_nrpn_send(resonantchannel,0x01,0x21,(byte)0x7F);  // set resonance for channel resonantchannel
  Timer1.attachInterrupt(timercallback);
  Timer1.initialize(tempodelay*1000);   
  
  button3.pressHandler(SomeButtonPressHandler);
  button3.releaseHandler(SomeButtonReleaseHandler);  
  button4.pressHandler(SomeButtonPressHandler);
  button4.releaseHandler(SomeButtonReleaseHandler);
  button4.holdHandler(SomeButtonHoldHandler,1000);
  setupvoices();
}

void stopsynth(){
  enablesynthline = 0; 
  prevtimestamp = 0;
  curtimestamp = 0;
  seq_poscnt = 0;
  stopallnotes();
}


void loop() {
  long timesincelastbeat;
  long timetonextbeat;  
  
  ADC_handle();
  button3.isPressed(); // trigger handling for button
  button4.isPressed(); // trigger handling for button
  
  if (keyboard.availablerel()) {
      // read the next key
      bool iskeyrelease = false;
      char c = keyboard.readrel(iskeyrelease);      
      KeyboardHandler(c,iskeyrelease);
  }
  
  if(tickflag)
  {
    // sequencing time tick
    synthseq(seq_poscnt);
    seq_poscnt++;
    tickflag = 0;

  }
  
  if(prev_buttonState!=buttonState)
  {
    prev_buttonState = buttonState;
    if(buttonState == 1)
    {
      prevtimestamp =  curtimestamp;
      curtimestamp = millis();
      if(prevtimestamp)
      {           
        calctempodelay = curtimestamp - prevtimestamp;
        if(calctempodelay > 100  && calctempodelay < 3000)  // if tempo is within range, calc tempo and enable drum
        {
          if(enablesynthline == 0)
          {
            seq_poscnt = 0;
            enablesynthline = 1;
          }
          tempodelay  = calctempodelay/wheelfactor;
          timesincelastbeat = curtimestamp - lasttickstamp;
          if(timesincelastbeat > tempodelay)  // is the beat is going faster, tick immediately (within 10ms)
          {
            timetonextbeat = 10; 
          }
          else
          {
            timetonextbeat = tempodelay -timesincelastbeat; // calculate remaining period for next tick
            if (timetonextbeat < 10)
            {
              timetonextbeat = 10;
            }
          }
          Timer1.setPeriod(timetonextbeat * 1000);  // calculate period until next beat            
        }
      }
    }
  } 
  else
  {
    if(enablesynthline)
    {
      if(curtimestamp)
      {
        if( (millis() - curtimestamp  )> 5000)  // automatically stop if no sensor change for longer than 5s
        {
          if(bicyclesetup)
            {
               stopsynth(); 
            }
        }
      }
    }
  }

}
