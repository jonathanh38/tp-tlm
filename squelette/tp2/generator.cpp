#include "generator.h"
#include "constants.h"
#include "LCDC_registermap.h"

using namespace std;
using namespace ensitlm;

void generator::thread(void) {
    socket.write(base_addr_lcdc+LCDC_ADDR_REG, base_mem_video);
    socket.write(base_addr_lcdc+LCDC_START_REG, 0x00000001);

    load_picture(); 
    while (1) {
        wait();

        for (int i = 0; i < IMG_SIZE; i+=4) {
            data_t pixels; 
            if (i >= IMG_SIZE-320) {
                socket.read(base_mem_video + i - 320*239, pixels);
                socket.write(base_mem_video + i, pixels); 
            } else {
                socket.read(base_mem_video + i + 320, pixels);
                socket.write(base_mem_video + i, pixels);
            }
        }
        //cout << "Interruption reçue !" << endl;
        socket.write(base_addr_lcdc+LCDC_INT_REG, 0x00000000);
    }
}

void generator::load_picture() {
    for (int i = 0; i < size_ROM_bytes; i+=4) {
        data_t word1_lcdc = 0x0, word2_lcdc = 0x0,data_read = 0x0;
        socket.read(base_addr_ROM + i, data_read);
        for (int j = 0; j < 4; j++) {
            word1_lcdc |= (data_read & (0xF0000000 >> (4*j))) >> (4*j);
            word2_lcdc |= (data_read & (0x0000F000 >> (4*j))) << (16-(4*j));
        }
        socket.write(base_mem_video + 2*i, word1_lcdc);
        socket.write(base_mem_video + (2*i)+4, word2_lcdc);
    }
}

generator::generator(sc_core::sc_module_name name) : sc_core::sc_module(name) {
	SC_THREAD(thread);
    sensitive << display_int;
}

void generator::animate() {
    interrupt.notify();
}
