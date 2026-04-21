//!
//!void write16_eeprom(int32 ad_reg , int16 bb)
//!{
//!struct s {
//!   int8 low;
//!   int8 high;
//!} wr16;
//!    wr16 = bb;
//!    
//!    write_eeprom( ad_reg  , wr16.low );
//!    write_eeprom( ad_reg+1, wr16.high );
//! 
//!}
//!
//!int16 read16_eeprom(int32 ad_reg  )
//!{
//!struct s {
//!   int8 low;
//!   int8 high;
//!} rd16;
//!    int16 rd_w;
//!    rd16.low  = read_eeprom( ad_reg );
//!    rd16.high = read_eeprom( ad_reg+1 );
//!    rd_w = rd16;
//!    return(rd_w);
//! 
//!}
//!
//!void WRITE_FLOAT_EEPROM(long int n, float data) { 
//!   int i;
//!
//!   for (i = 0; i < 4; i++) 
//!      write_eeprom(i + n, *((int8*)&data + i) ) ; 
//!}
//!
//!
//!
//!float READ_FLOAT_EEPROM(long int n) { 
//!   int i; 
//!   float data;
//!
//!   for (i = 0; i < 4; i++) 
//!      *((int8*)&data + i) = read_eeprom(i + n);
//!
//!   return(data); 
//!}
//!
//!int32 readLword_eeprom( char iaddr )     // rerad32 bit char
//!{
//!struct s {
//!   int8 low;
//!   int8 mid;
//!   int8 high;
//!   int8 ehigh;
//!} rd32;
//!    int32 rd_Lw;
//!    rd32.low  = read_eeprom( iaddr );
//!    rd32.mid  = read_eeprom( iaddr+1 );
//!    rd32.high = read_eeprom( iaddr+2 );
//!    rd32.ehigh= read_eeprom( iaddr+3 );
//!    rd_Lw = rd32;
//!    return(rd_Lw);
//!}
//!
//!
//!void writeLword_eeprom( char iaddr, int32 wdata )      // write 32 bit char 
//!{
//!struct s {
//!   int8 low;
//!   int8 mid;
//!   int8 high;
//!   int8 ehigh;
//!} wr32;
//!    wr32 = wdata;
//!    write_eeprom( iaddr  , wr32.low );
//!    write_eeprom( iaddr+1, wr32.mid );
//!    write_eeprom( iaddr+2, wr32.high );
//!    write_eeprom( iaddr+3, wr32.ehigh );
//!}
//!

signed int16 save_acelx[1024];
signed int16 seve_acely[1024];
signed int16 save_acelz[1024];
//!signed int16 save_acelxD[512];
//!signed int16 seve_acelyD[512];
//!signed int16 save_acelzD[512];
void  write_paket(int16  ptr)
{
    save_acelx[ptr_save]= bno_x;
    seve_acely[ptr_save]= bno_y;
    save_acelz[ptr_save]= bno_z;       
//! save_acelxD[ptr_save]= bno_xD;
//! seve_acelyD[ptr_save]= bno_yD;
//! save_acelzD[ptr_save]= bno_zD;    
   
    ptr_save++;
    
}


 
 



