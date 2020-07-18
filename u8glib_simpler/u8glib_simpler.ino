#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);

void setup() {
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }

}

void loop() {
  u8g.firstPage();  
  do {
    // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_X11);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 0, 10, "Hello World!");

  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  delay(500);
  
}
