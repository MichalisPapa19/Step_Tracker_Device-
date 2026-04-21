#use i2c(master, scl=PIN_c3, sda=PIN_c4,stream = BNO)

/** BNO055 Address A **/
#define BNO055_ADDRESS_A 0x28
/** BNO055 ID **/
#define BNO055_ID 0xA0


/* Linear acceleration data registers */
#define BNO055_LINEAR_ACCEL_DATA_X_LSB_ADDR = 0X28
#define BNO055_LINEAR_ACCEL_DATA_X_MSB_ADDR = 0X29
#define BNO055_LINEAR_ACCEL_DATA_Y_LSB_ADDR = 0X2A
#define BNO055_LINEAR_ACCEL_DATA_Y_MSB_ADDR = 0X2B
#define BNO055_LINEAR_ACCEL_DATA_Z_LSB_ADDR = 0X2C
#define BNO055_LINEAR_ACCEL_DATA_Z_MSB_ADDR = 0X2D


#define  ACC_DATA_X_LSB 0x08
#define  ACC_DATA_X_MSB 0x09
#define  ACC_DATA_Y_LSB 0x0A
#define  ACC_DATA_Y_MSB 0x0B
#define  ACC_DATA_Z_LSB 0x0C
#define  ACC_DATA_Z_MSB 0x0D


int16 bno_x,bno_y,bno_z,bno_xD,bno_yD,bno_zD;

void BNO055_Config()
{   i2c_start(BNO);
    i2c_write(BNO, BNO055_ADDRESS_A <<1); //WRITE MODE
    i2c_write(BNO, 0x3D); // BNO055_OPR_MODE_ADDR
    i2c_write(BNO, 0x00); // Config mode
    i2c_stop(BNO);
    delay_ms(500);

    // Set to normal power mode
    i2c_start(BNO);
    i2c_write(BNO, BNO055_ADDRESS_A <<1); //WRITE MODE
    i2c_write(BNO, 0x3E); // BNO055_PWR_MODE_ADDR
    i2c_write(BNO, 0x00); // Normal mode
    i2c_stop(BNO);
    delay_ms(500);

    // Set to NDOF mode
    i2c_start(BNO);
    i2c_write(BNO, BNO055_ADDRESS_A <<1); //WRITE MODE
    i2c_write(BNO, 0x3D); // BNO055_OPR_MODE_ADDR
    i2c_write(BNO, 0x0C); // NDOF mode
    i2c_stop(BNO);
    delay_ms(500);  
}

void BNO055_read_register_id()   
{
    unsigned char gyr_id, acc_id, chip_id, mag_id;

    i2c_start(BNO);
    i2c_write(BNO, BNO055_ADDRESS_A << 1); // Write mode
    i2c_write(BNO, 0x00); // Start address for ID registers
    i2c_start(BNO);
    i2c_write(BNO, (BNO055_ADDRESS_A << 1) | 1); // Read mode

    chip_id = i2c_read(BNO, 1); // Read CHIP_ID with ACK
    acc_id = i2c_read(BNO, 1);// Read ACC_ID with ACK
    mag_id = i2c_read(BNO, 1); //read MAG_ID with ACK
    gyr_id = i2c_read(BNO, 0);  // Read GYR_ID with NACK

   i2c_stop(BNO);

 
   sprintf(master_mask,"CHPID:%02X ",chip_id); 
    Show_String8x16(master_mask,0,0);
   
   sprintf(master_mask,"ACC:%02X",acc_id); 
    Show_String8x16(master_mask,0,2);
   
   sprintf(master_mask,"MAG:%02X",mag_id);
    Show_String8x16(master_mask,0,4); 
   

   sprintf(master_mask,"GYR:%02X",gyr_id);
    Show_String8x16(master_mask,0,6);
    
   
   delay_ms(4000);
   
}


void BNO055_read_linear_accel()
{
    unsigned char x_lsb, x_msb, y_lsb, y_msb, z_lsb, z_msb;
    signed  int16 x1, y1, z1;
    

    // Set start address for reading linear acceleration data
    i2c_start(BNO);
    i2c_write(BNO, BNO055_ADDRESS_A << 1); // Write mode
    i2c_write(BNO, 0x28); // Start address
    i2c_start(BNO);
    i2c_write(BNO, (BNO055_ADDRESS_A << 1) | 1); // Read mode

    // Read the linear acceleration data
    x_lsb = i2c_read(BNO, 1); // Read X LSB with ACK
    x_msb = i2c_read(BNO, 1); // Read X MSB with ACK
    y_lsb = i2c_read(BNO, 1); // Read Y LSB with ACK
    y_msb = i2c_read(BNO, 1); // Read Y MSB with ACK
    z_lsb = i2c_read(BNO, 1); // Read Z LSB with ACK
    z_msb = i2c_read(BNO, 0); // Read Z MSB with NACK

    i2c_stop(BNO);

    // Combine MSB and LSB
    x1 = ((int16)x_msb << 8) | x_lsb;
    y1 = ((int16)y_msb << 8) | y_lsb;
    z1 = ((int16)z_msb << 8) | z_lsb;

  
     bno_x= x1;
     bno_y= y1;
     bno_z= z1;
    
    printf("XL:%3Ld \r\n",x1);
    printf("YL:%3Ld \r\n",y1);
    printf("ZL:%3Ld \r\n\r\n",z1);
    

    sprintf(master_mask, "Recort:%4Lu ",ptr_save);
    Show_String8x16(master_mask, 5, 2); 

    delay_ms(10);
}

 

void BNO055_read_accel()
{

    unsigned char xD_lsb, xD_msb, yD_lsb, yD_msb, zD_lsb, zD_msb;
    signed int16 xD, yD, zD;
  

    // Set start address for reading acceleration data
    i2c_start(BNO);
    i2c_write(BNO, BNO055_ADDRESS_A << 1); // Write mode
    i2c_write(BNO, ACC_DATA_X_LSB); // Start address
    i2c_start(BNO);
    i2c_write(BNO, (BNO055_ADDRESS_A << 1) | 1); // Read mode

    // Read the acceleration data
    xD_lsb = i2c_read(BNO, 1); // Read X LSB with ACK
    xD_msb = i2c_read(BNO, 1); // Read X MSB with ACK
    yD_lsb = i2c_read(BNO, 1); // Read Y LSB with ACK
    yD_msb = i2c_read(BNO, 1); // Read Y MSB with ACK
    zD_lsb = i2c_read(BNO, 1); // Read Z LSB with ACK
    zD_msb = i2c_read(BNO, 0); // Read Z MSB with NACK

    i2c_stop(BNO);

    // Combine MSB and LSB
    xD = ((int16)xD_msb << 8) | xD_lsb;
    yD = ((int16)yD_msb << 8) | yD_lsb;
    zD = ((int16)zD_msb << 8) | zD_lsb;

    // Print the results
    sprintf(master_mask, "X data  : %3Ld ", xD);
     Show_String8x16(master_mask, 0, 2);

    sprintf(master_mask, "Y data  : %3Ld ", yD);
     Show_String8x16(master_mask, 0, 4);

    sprintf(master_mask, "Z data  : %3Ld ", zD);
     Show_String8x16(master_mask, 0, 6);
    
     bno_xD= xD;
     bno_yD= yD;
     bno_zD= zD;
    
    printf("XD:%3Ld \r\n",xD);
    printf("YD:%3Ld \r\n",yD);
    printf("ZD:%3Ld \r\n\r\n",zD);

    delay_ms(100);
    
}



