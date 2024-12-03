
#define BUFDIR_INPUT 0
#define BUFDIR_OUTPUT 1

void bio_init(void);
void bio_buf_pin_init(uint8_t bio);
void bio_buf_output(uint8_t bio);
void bio_buf_input(uint8_t bio);
//static inline void bio_set_dir(uint8_t bio, bool dir);

static inline void bio_set_dir(uint8_t bio, bool dir) {
    //making some big assumption here that are currently true
    //could blow up on us later though
    if(bio < 8) {
        return;
    }else if(bio < 16) {
        if(dir) {
            // first set the buffer to output
            gpio_put(bio-8, BUFDIR_OUTPUT);
            // now set pin to output
            gpio_set_dir(bio, GPIO_OUT);
        } else {
            // first set the pin to input
            gpio_set_dir(bio, GPIO_IN);
            // now set buffer to input
            gpio_put(bio-8, BUFDIR_INPUT);
        }
    }else{
        gpio_set_dir(bio, dir);
    }
}
void bio_output(uint8_t bio);
void bio_input(uint8_t bio);
//static inline void bio_put(uint8_t bio, bool value);
//static inline bool bio_get(uint8_t bio);
void bio_set_function(uint8_t bio, uint8_t function);
void bio_buf_test(uint8_t bufio, uint8_t bufdir);
