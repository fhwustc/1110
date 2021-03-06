#include "disp_drv.h"

#define DISP_IC_WIDTH_MAX   220

#include "disp_ic_generic.h"
#define LCD_WRITE_OUT(cmd, data)    LCD_WRITE_CMD((uint8)cmd); \
                                    LCD_WRITE_DATA16(data);

#ifdef FEATURE_MDP
#include "mdp_drv.h"
#include "mdp_hw.h"

//For lcd QVGA TM7775R driver
#define DISP_LCD_18BPP(x)                 ((uint16)(x))
#define DISP_LCD_HORZ_RAM_ADDR_POS_1_ADDR 0x38 // Register to set col start
#define DISP_LCD_HORZ_RAM_ADDR_POS_2_ADDR 0x39 // Register to set col end
#define DISP_LCD_VERT_RAM_ADDR_POS_1_ADDR 0x36 // Register to set row start
#define DISP_LCD_VERT_RAM_ADDR_POS_2_ADDR 0x37 // Register to set row end
#define DISP_LCD_RAM_ADDR_SET_1_ADDR      0x21 // Start address - col
#define DISP_LCD_RAM_ADDR_SET_2_ADDR      0x20 // Start address - row
#define DISP_LCD_CMD_RAMWR                0x22 // RAM Data Write
#define DISP_LCD_CMD_START                0x00


#ifdef __GNUC__
static uint32 MDP_DISP_SCR_TM7775R[MDP_LCD_SCR_SIZE][MDP_LCD_SCR_LEN]
__attribute__ ((aligned (16))) =
#else
__align(16) static uint32 MDP_DISP_SCR_TM7775R[MDP_LCD_SCR_SIZE][MDP_LCD_SCR_LEN] =
#endif
{
      NOP,               //0
  	  NOP,               //1
	  SET_LCD_CNTL_ADDR, //2 set LCD command port address
	  LCD_CMD_WH,    //3

	  SET_LCD_DATA_ADDR, //4 set LCD data port address
	  LCD_DATA_WH,   //5
	  SEND_LCD_CNTL(DISP_LCD_18BPP(DISP_LCD_CMD_START)),
	  SEND_LCD_CNTL(DISP_LCD_18BPP(DISP_LCD_HORZ_RAM_ADDR_POS_1_ADDR)),//7
	  NULL,             //8
	  NULL,             //9
	  SEND_LCD_CNTL(DISP_LCD_18BPP(DISP_LCD_CMD_START)),
	  SEND_LCD_CNTL(DISP_LCD_18BPP(DISP_LCD_HORZ_RAM_ADDR_POS_2_ADDR)),//11
	  NULL,             //12
	  NULL,             //13
	  SEND_LCD_CNTL(DISP_LCD_18BPP(DISP_LCD_CMD_START)),
	  SEND_LCD_CNTL(DISP_LCD_18BPP(DISP_LCD_VERT_RAM_ADDR_POS_1_ADDR)),//15
	  NULL,             //16
	  NULL,             //17
	  SEND_LCD_CNTL(DISP_LCD_18BPP(DISP_LCD_CMD_START)),
	  SEND_LCD_CNTL(DISP_LCD_18BPP(DISP_LCD_VERT_RAM_ADDR_POS_2_ADDR)),//19
	  NULL,             //20
	  NULL,             //21
	  SEND_LCD_CNTL(DISP_LCD_18BPP(DISP_LCD_CMD_START)),
	  SEND_LCD_CNTL(DISP_LCD_18BPP(DISP_LCD_RAM_ADDR_SET_1_ADDR)),//23
	  NULL,             //24
	  NULL,             //25
	  SEND_LCD_CNTL(DISP_LCD_18BPP(DISP_LCD_CMD_START)),
	  SEND_LCD_CNTL(DISP_LCD_18BPP(DISP_LCD_RAM_ADDR_SET_2_ADDR)),//27
	  NULL,             //28
	  NULL,             //29
	  SEND_LCD_CNTL(DISP_LCD_18BPP(DISP_LCD_CMD_START)),
	  SEND_LCD_CNTL(DISP_LCD_18BPP(DISP_LCD_CMD_RAMWR)),//24
      
  RETURN            //25
};

static uint8 disp_ic_mdp_getformat(void)
{
    return LCD_16BPP_88_II; //8 16BPP 0 //18BPP
}

static uint16 disp_ic_mdp_getscr(uint32 **ppscr)
{
    if(ppscr)    
    {
        *ppscr = &MDP_DISP_SCR_TM7775R[0][0];
    }
    return MDP_LCD_SCR_SIZE;
}

static void disp_ic_mdp_scrupdate(uint32 *scr, uint32 start_row, uint32 start_col, uint32 end_row, uint32 end_col)
{
   	scr[8] = SEND_LCD_DATA(DISP_LCD_18BPP(end_row>>8));
    scr[9] = SEND_LCD_DATA(DISP_LCD_18BPP(end_row));
    scr[12] = SEND_LCD_DATA(DISP_LCD_18BPP(start_row>>8));
    scr[13] = SEND_LCD_DATA(DISP_LCD_18BPP(start_row));
    scr[16] = SEND_LCD_DATA(DISP_LCD_18BPP(end_col>>8));
    scr[17] = SEND_LCD_DATA(DISP_LCD_18BPP(end_col));
    scr[20] = SEND_LCD_DATA(DISP_LCD_18BPP(start_col>>8));
    scr[21] = SEND_LCD_DATA(DISP_LCD_18BPP(start_col));
    scr[24] = SEND_LCD_DATA(DISP_LCD_18BPP(start_row>>8));
    scr[25] = SEND_LCD_DATA(DISP_LCD_18BPP(start_row));
    scr[28] = SEND_LCD_DATA(DISP_LCD_18BPP(start_col>>8));
    scr[29] = SEND_LCD_DATA(DISP_LCD_18BPP(start_col));
}
#endif

static void disp_ic_init(void)
{
       LCD_WRITE_CMD(0x00);// //inter Internal Register 
       LCD_WRITE_CMD(0xff); 
       LCD_WRITE_DATA(0x00); 
       LCD_WRITE_DATA(0xa5); 
    
       LCD_WRITE_CMD(0x00); 
       LCD_WRITE_CMD(0xf5); 
       LCD_WRITE_DATA(0x00); 
       LCD_WRITE_DATA(0x06);//for vcir=VCI 
    
       LCD_WRITE_CMD(0x00); 
       LCD_WRITE_CMD(0xa3); 
       LCD_WRITE_DATA(0x00); 
       LCD_WRITE_DATA(0x6f); 
    
       LCD_WRITE_CMD(0x00); 
       LCD_WRITE_CMD(0xa4); 
       LCD_WRITE_DATA(0x00); 
       LCD_WRITE_DATA(0x13); 
       //------------------------------------------------------------- 
       LCD_WRITE_CMD(0x00);//gs,ss,sm 
       LCD_WRITE_CMD(0x01); 
       LCD_WRITE_DATA(0x01);//01 
       LCD_WRITE_DATA(0x1c); 
    
       LCD_WRITE_CMD(0x00); 
       LCD_WRITE_CMD(0x02); 
       LCD_WRITE_DATA(0x00);// frame inversion0x01 line inverson 
       LCD_WRITE_DATA(0x00); 
    
       LCD_WRITE_CMD(0x00);//bgr 
       LCD_WRITE_CMD(0x03); 
       LCD_WRITE_DATA(0x00); 
       LCD_WRITE_DATA(0x30); 
    
       LCD_WRITE_CMD(0x00); 
       LCD_WRITE_CMD(0x07); 
       LCD_WRITE_DATA(0x00); 
       LCD_WRITE_DATA(0x00); 
    
       LCD_WRITE_CMD(0x00);//FR_SEL[3:0] 
       LCD_WRITE_CMD(0x0f); 
       LCD_WRITE_DATA(0x08);//100Hz 
       LCD_WRITE_DATA(0x01); 
    
       LCD_WRITE_CMD(0x00); 
       LCD_WRITE_CMD(0x10); 
       LCD_WRITE_DATA(0x00); 
       LCD_WRITE_DATA(0x00); 
    
       LCD_WRITE_CMD(0x00); 
       LCD_WRITE_CMD(0x11); 
       LCD_WRITE_DATA(0x10); 
       LCD_WRITE_DATA(0x41); 
       LCD_DELAY(100);
       LCD_WRITE_CMD(0x00); 
       LCD_WRITE_CMD(0x12); 
       LCD_WRITE_DATA(0x00); 
       LCD_WRITE_DATA(0x12); 
    
       LCD_WRITE_CMD(0x00);//VRH 
       LCD_WRITE_CMD(0x13); 
       LCD_WRITE_DATA(0x00); 
       LCD_WRITE_DATA(0x42);// VRH is vreg1out for gamma voltage,please set 4.4v-4.6v    
    
       LCD_WRITE_CMD(0x00); 
       LCD_WRITE_CMD(0x14); //vom  for  solve  fliker 
       LCD_WRITE_DATA(0x48);//vdv  for  improve display 
       LCD_WRITE_DATA(0x64);//
    
       //------------------------set windows------------------------------------- 
       LCD_WRITE_CMD(0x00);//HEA 
       LCD_WRITE_CMD(0x36); 
       LCD_WRITE_DATA(0x00); 
       LCD_WRITE_DATA(0xaf); 
    
       LCD_WRITE_CMD(0x00);//HSA 
       LCD_WRITE_CMD(0x37); 
       LCD_WRITE_DATA(0x00); 
       LCD_WRITE_DATA(0x00); 
    
       LCD_WRITE_CMD(0x00);//VEA 
       LCD_WRITE_CMD(0x38); 
       LCD_WRITE_DATA(0x00); 
       LCD_WRITE_DATA(0xdb); 
        LCD_WRITE_CMD(0x00);//HSA 
       LCD_WRITE_CMD(0x39); 
       LCD_WRITE_DATA(0x00); 
       LCD_WRITE_DATA(0x00); 
       //---------------------set gamma-------------------------------------------- 
       LCD_WRITE_CMD(0x00);//KP1,KP0 
       LCD_WRITE_CMD(0x50); 
       LCD_WRITE_DATA(0x00); 
       LCD_WRITE_DATA(0x00); 
    
       LCD_WRITE_CMD(0x00);//KP3,KP2 
       LCD_WRITE_CMD(0x51); 
       LCD_WRITE_DATA(0x02); 
       LCD_WRITE_DATA(0x02); 
    
       LCD_WRITE_CMD(0x00);//KP5,KP4 
       LCD_WRITE_CMD(0x52); 
       LCD_WRITE_DATA(0x04); 
       LCD_WRITE_DATA(0x04); 
    
       LCD_WRITE_CMD(0x00);//RP1,RP0 
       LCD_WRITE_CMD(0x53); 
       LCD_WRITE_DATA(0x00); 
       LCD_WRITE_DATA(0x00); 
    
       LCD_WRITE_CMD(0x00);//KN1,KN0 
       LCD_WRITE_CMD(0x54); 
       LCD_WRITE_DATA(0x08); 
       LCD_WRITE_DATA(0x0c); 
    
       LCD_WRITE_CMD(0x00);//KN3,KN2 
       LCD_WRITE_CMD(0x55); 
       LCD_WRITE_DATA(0x08); 
       LCD_WRITE_DATA(0x0a); 
    
       LCD_WRITE_CMD(0x00);//KN5,KN4 
       LCD_WRITE_CMD(0x56); 
       LCD_WRITE_DATA(0x0e); 
       LCD_WRITE_DATA(0x0e); 
    
       LCD_WRITE_CMD(0x00);//RN1,RN0 
       LCD_WRITE_CMD(0x57); 
       LCD_WRITE_DATA(0x0e); 
       LCD_WRITE_DATA(0x0e); 
    
       LCD_WRITE_CMD(0x00);//VRP1,VRP0 
       LCD_WRITE_CMD(0x58); 
       LCD_WRITE_DATA(0x02); 
       LCD_WRITE_DATA(0x02); 
    
       LCD_WRITE_CMD(0x00);//VRN1,VRN0 
       LCD_WRITE_CMD(0x59); 
       LCD_WRITE_DATA(0x01); 
       LCD_WRITE_DATA(0x04); 
    
       //--------------------------------------------------------------------------------- 
       LCD_WRITE_CMD(0x00); 
       LCD_WRITE_CMD(0x20); 
       LCD_WRITE_DATA(0x00); 
       LCD_WRITE_DATA(0x00); 
    
       LCD_WRITE_CMD(0x00); 
       LCD_WRITE_CMD(0x21); 
       LCD_WRITE_DATA(0x00); 
       LCD_WRITE_DATA(0x00); 
       LCD_DELAY(50);
       LCD_WRITE_CMD(0x00); 
       LCD_WRITE_CMD(0x07); 
       LCD_WRITE_DATA(0x10); 
       LCD_WRITE_DATA(0x13); //If set line invorsion,please use 0x17 
       LCD_DELAY(50);
       LCD_WRITE_CMD(0x00); 
       LCD_WRITE_CMD(0x22); 

}

static void disp_ic_setwindow(uint32 start_row, uint32 start_col, uint32 end_row, uint32 end_col)
{

    LCD_WRITE_CMD(0x00);//HEA 
    LCD_WRITE_CMD(0x36); 
    LCD_WRITE_DATA(0x00); 
    LCD_WRITE_DATA(end_col); 

    LCD_WRITE_CMD(0x00);//HEA 
    LCD_WRITE_CMD(0x37); 
    LCD_WRITE_DATA(0x00); 
    LCD_WRITE_DATA(start_col); 

    LCD_WRITE_CMD(0x00);//HEA 
    LCD_WRITE_CMD(0x38); 
    LCD_WRITE_DATA(0x00); 
    LCD_WRITE_DATA(end_row); 

    LCD_WRITE_CMD(0x00);//HEA 
    LCD_WRITE_CMD(0x39); 
    LCD_WRITE_DATA(0x00); 
    LCD_WRITE_DATA(start_row); 

    LCD_WRITE_CMD(0x00);//HEA 
    LCD_WRITE_CMD(0x20); 
    LCD_WRITE_DATA(0x00); 
    LCD_WRITE_DATA(start_col); 

    LCD_WRITE_CMD(0x00);//HEA 
    LCD_WRITE_CMD(0x21); 
    LCD_WRITE_DATA(0x00); 
    LCD_WRITE_DATA(start_row);     

	LCD_WRITE_CMD(0x00);
	LCD_WRITE_CMD(0x22);
}
static void disp_ic_sleep(boolean bin)
{
    if(bin)
    {         	
       LCD_WRITE_OUT(0x0007,0x0000);
       LCD_DELAY(25); 	
       LCD_WRITE_OUT(0x0010,0x0003);
	   LCD_DELAY(100);
    }
    else 
    { 
        LCD_WRITE_OUT(0x0010,0x0000);
        LCD_DELAY(50);
        LCD_WRITE_OUT(0x0007,0x1017);
	    LCD_DELAY(200);
		
    }

}

static void disp_ic_rot(uint16 degree)
{
#if 0
    if(degree == 0)
    {
        LCD_WRITE_CMD(0x36); LCD_WRITE_DATA(0x48); // Set VCOMH/VCOML voltage   0x333A
    }
    else
    {
        LCD_WRITE_CMD(0x36); LCD_WRITE_DATA(0x28); // Set VCOMH/VCOML voltage   0x333A
    }
#endif
    return;
}


boolean disp_nv3038_tft20(disp_drv_ic_type *pdispic)
{
    uint8 id1,id2,id3;
	uint16 id = 0;
    
    // Read ID
    LCD_WRITE_CMD(0x00);    
    LCD_WRITE_CMD(0xfc);
    id1 = LCD_READ_DATA();
    id2 = LCD_READ_DATA();
    
    if(id1==0x00&&id2==0x1f)
    {
        DISP_IC_INIT_TBL(pdispic);
		
        return TRUE;
    }
    return FALSE;
}
