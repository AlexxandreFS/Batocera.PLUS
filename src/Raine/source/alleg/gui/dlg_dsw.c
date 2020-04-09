#include "raine.h"
#include "rgui.h"
#include "rguiproc.h"
#include "gui.h"
#include "dlg_dsw.h"

DIALOG dsw_select[] =
{
   /* (dialog proc)      (x)   (y)   (w)   (h)   (fg)  (bg)  (key) (flags)  (d1)  (d2)  (dp) */
   { d_raine_window_proc,40,   10,   272,  178+12,GUI_COL_TEXT_1, GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Dipswitches"},
   { d_raine_list_proc,  48,   26+12,256,  100,  GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  0,    D_EXIT,  0,    0,    dswlist_getter},
   { x_raine_button_proc,48,   164+12,48,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'D',  D_EXIT,  0,    0,    "&Done"},
   { dsw_edit_proc,      104,  164+12,48,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'E',  D_EXIT,  0,    0,    "&Edit"},
   { x_text_proc,        48,   26,   0,    8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "Edit Dipswitch settings:"},
   { x_text_proc,        80+32,23+120,0,   8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    "           87654321"},
   { x_text_proc,        80+32,23+130,0,   8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    NULL },
   { x_text_proc,        80+32,23+140,0,   8,    GUI_COL_TEXT_2,  GUI_BOX_COL_MIDDLE,  0,    0,       0,    0,    NULL },
   { dsw_reset_proc,     160,  164+12,96,  16,   GUI_COL_TEXT_1,  GUI_BOX_COL_MIDDLE,  'F',  D_EXIT,  0,    0,    "&Factory Settings"},
   { NULL,               0,    0,    0,    0,    0,    0,    0,    0,       0,    0,    NULL}
};

void make_dsw_strings(void)
{
   static char str_dswa[32];
   static char str_dswb[32];

   int ta, tb;

   // Generate DSW bytes

   make_dipswitch_bytes();

   // Build Text

   sprintf(str_dswa, "DIPSW A: HHHHHHHH L:ON");
   sprintf(str_dswb, "DIPSW B: HHHHHHHH H:OFF");

   tb=1;
   for(ta=7; ta>=0; ta--){

      if(get_dsw(0) & tb)
		 str_dswa[ta+9] = (UINT8) 'H';
	  else
		 str_dswa[ta+9] = (UINT8) 'L';

      if(get_dsw(1) & tb)
		 str_dswb[ta+9] = (UINT8) 'H';
	  else
		 str_dswb[ta+9] = (UINT8) 'L';

      tb <<= 1;
   }

   // Insert

   dsw_select[6].dp = str_dswa;
   dsw_select[7].dp = str_dswb;

}

char *dswlist_getter(int index, int *list_size)
{
   static char S[128];

   int tcount;
   int num,numb,n;

   tcount=0;

   for(num=0;num<MAX_DIPSWITCHES;num++){
      tcount += dipswitch[num].statcount;
   }

   if(tcount>0){

   switch(index){
   case -1:			// Return List Size
      *list_size=tcount;
      return NULL;
   break;
   case -2:
      DoDSWEdit();
      *list_size=D_REDRAW;
      return NULL;
   break;
   case -3:			// Act Keyboard Input
      return NULL;
   break;
   default:
      if((index >= 0)&&(index<tcount)){

      n = 0;
      numb = 0;
      for(num=0;num<MAX_DIPSWITCHES;num++){
         if(index >= n){
            numb=num;
         }
         n += dipswitch[num].statcount;
      }
      for(num=0;num<numb;num++){
         index -= dipswitch[num].statcount;
      }
         sprintf(
            S,
            "%-19s %s",
            dipswitch[numb].diplist[dipswitch[numb].statlist[index].pos].DSWName,
            dipswitch[numb].diplist[dipswitch[numb].statlist[index].pos+dipswitch[numb].statlist[index].offset+1].DSWName
         );
         return S;

      }
      else
         return NULL;
   break;
   }

   }
   else{

   if(index==-1){
      *list_size = 1;
      return NULL;
   }
   else{
      if(index==0)
         return raine_translate_text("<No Dipswitches Mapped>");
      else
         return NULL;
   }

   }
}

int dsw_select_proc(int msg, DIALOG *d, int c)
{
   int ret = x_raine_button_proc(msg,d,c);

   if(ret==D_CLOSE){
      Unselect_Button(d);
      FadeGUI();
      ret=0;
      make_dsw_strings();
      while((ret!=2)&&(ret!=-1)){
         ret=raine_do_dialog(dsw_select,-1);
         if((ret!=2)&&(ret!=-1)){
            DoDSWEdit();
         }
      }
      make_dipswitch_bytes();
      ret = D_REDRAW;
   }
   return ret;
}

void DoDSWEdit(void)
{
   int ta,tb,tc;
   int num,numb,n;

   ta=dsw_select[1].d1;

      n = 0;
      numb = 0;
      for(num=0;num<MAX_DIPSWITCHES;num++){
         if(ta >= n){
            numb=num;
         }
         n += dipswitch[num].statcount;
      }
      for(num=0;num<numb;num++){
         ta -= dipswitch[num].statcount;
      }

      tb=dipswitch[numb].statlist[ta].pos;
      tc=dipswitch[numb].statlist[ta].offset+1;
      if(tc>=(dipswitch[numb].diplist[tb].values)){tc=0;}
      dipswitch[numb].statlist[ta].offset=tc;

   make_dsw_strings();

   clear_keybuf();
}

int dsw_edit_proc(int msg, DIALOG *d, int c)
{
   int ret = x_raine_button_proc(msg, d, c);

   if(ret==D_CLOSE){
      Unselect_Button(d);
      DoDSWEdit();
      ret = D_REDRAW;
   }
   return ret;
}

int dsw_reset_proc(int msg, DIALOG *d, int c)
{
   int ret = x_raine_button_proc(msg, d, c);

   if(ret==D_CLOSE){
      Unselect_Button(d);
      RestoreDSWDefault();
      make_dipswitch_statlist();
      make_dsw_strings();
      ret = D_REDRAW;
   }
   return ret;
}
