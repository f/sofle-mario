// WPM-responsive animation stuff here
#define IDLE_SPEED 10 // below this wpm value your animation will idle
#define TAP_SPEED 60 // above this wpm value typing animation to triggere
#define ANIM_FRAME_DURATION 200 // how long each frame lasts in ms

uint32_t anim_timer = 0;
uint32_t anim_sleep = 0;
uint8_t smallCloud_position = 5;
uint8_t smallCloud2_position = 0;

bool marioJumping = false;
uint8_t cointPosition = 0;

static void render_anim(void) {
    static const char PROGMEM floor[] = {
         171, 43, 35, 171, 137, 171, 43, 35, 1, 1, 0, 1, 1, 1, 1, 0
    };
    
    static const char PROGMEM cloud_top[] = {
       64,96,32,32,48,28,6,22,19,3,3,30,12,60,120,96,96,96,64
    };

    static const char PROGMEM cloud_bot[] = {
        4,14,26,49,32,32,96,80,192,160,224,112,80,144,160,160,64,65,65,64,107,62,22
    };

    static const char PROGMEM block_top[] = {
       252,252,251,255,255,15,15,231,239,255,31,31,251,248,0,0,0,0,0
    };

    static const char PROGMEM block_bot[] = {
        63,63,31,63,63,62,62,51,0,8,60,62,31,31,0,0,0,0,0
    };

    static const char PROGMEM mario_top[] = {
       0,56,188,223,223,199,199,255,190,54,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    };

    static const char PROGMEM mario_bot[] = {
        0,0,3,231,255,123,63,63,123,255,231,3,0,0
    };

    static const char PROGMEM coin[] = {
        0,120,252,134,250,254,252,48,0
    };


    void animateFloor(void){
        for(int i = 0; i< 5;i++ ){
            oled_set_cursor(i, 15);
            oled_write_raw_P(floor,sizeof(floor));
        }
    }

    void animateClouds(void){
        oled_set_cursor(smallCloud_position,2);
        oled_write_raw_P(cloud_top,sizeof(cloud_top));
        oled_set_cursor(smallCloud_position,3);
        oled_write_raw_P(cloud_bot,sizeof(cloud_bot));
        smallCloud_position--;
        if(!smallCloud_position) smallCloud_position = 5;

        oled_set_cursor(smallCloud2_position,5);
        oled_write_raw_P(cloud_top,sizeof(cloud_top));
        oled_set_cursor(smallCloud2_position,6);
        oled_write_raw_P(cloud_bot,sizeof(cloud_bot));
        smallCloud2_position++;
        if(smallCloud2_position > 5) smallCloud2_position = 0;
    }

    void animateCoinBlock(void){
        oled_set_cursor(1,10);
        oled_write_raw_P(block_top,sizeof(block_top));
        oled_set_cursor(1,11);
        oled_write_raw_P(block_bot,sizeof(block_bot));
    }


    void animateMario(void){
        oled_set_cursor(1,13);
        oled_write_raw_P(mario_top,sizeof(mario_top));
        oled_set_cursor(1,14);
        oled_write_raw_P(mario_bot,sizeof(mario_bot));
    }

    void animateMarioOnFire(bool onFire){
        //Jump on
        if(!marioJumping){
            oled_set_cursor(1,12);
            oled_write_raw_P(mario_top,sizeof(mario_top));
            oled_set_cursor(1,13);
            oled_write_raw_P(mario_bot,sizeof(mario_bot));
            marioJumping = !marioJumping;
        }else{
            oled_set_cursor(1,13);
            oled_write_raw_P(mario_top,sizeof(mario_top));
            oled_set_cursor(1,14);
            oled_write_raw_P(mario_bot,sizeof(mario_bot));
            marioJumping = !marioJumping;
        }
        if(onFire){
        switch(cointPosition){
            case 0:
                break;
            case 1:
                oled_set_cursor(2,9);
                oled_write_raw_P(coin,sizeof(coin));
                break;
            case 2:
              oled_set_cursor(2,8);
                oled_write_raw_P(coin,sizeof(coin));
                break;
            case 3:
                oled_set_cursor(3,9);
                oled_write_raw_P(coin,sizeof(coin));
                break; 
            case 4: 
                oled_set_cursor(4,12);
                oled_write_raw_P(coin,sizeof(coin));
                break;   
            case 5:
                oled_set_cursor(4,14);
                oled_write_raw_P(coin,sizeof(coin));
                break;   
        }
         cointPosition+=1;
        if(cointPosition > 5) cointPosition = 0;
        }
    }

    //assumes 1 frame prep stage
    void animation_phase(void) {
        animateFloor();
        animateClouds();
        animateCoinBlock();

        if(get_current_wpm() <=IDLE_SPEED){
            animateMario();
         }
         if(get_current_wpm() >IDLE_SPEED && get_current_wpm() <TAP_SPEED){
              animateMarioOnFire(false);
         }
         if(get_current_wpm() >=TAP_SPEED){
             animateMarioOnFire(true);
         }
    }


    
    if(get_current_wpm() != 000) {
        oled_on(); // not essential but turns on animation OLED with any alpha keypress
        if(timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
            anim_timer = timer_read32();
            oled_clear();
            animation_phase();
        }
        anim_sleep = timer_read32();
    } else {
        if(timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
            oled_off();
        } else {
            if(timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
                anim_timer = timer_read32();
                oled_clear();
                animation_phase();
            }
        }
    }
}
