#include "ensitlm.h"
#include "generator.h"
#include "memory.h"
#include "bus.h"
#include "LCDC.h"
#include "constants.h"
#include "ROM.h"

using namespace sc_core;

int sc_main(int argc, char **argv) {

    generator generator1("Generator1");
    Memory Memory("Memory", 0x15400);
    Bus router("Bus");
    LCDC lcdc("LCDC", sc_time(1.0 / 25, SC_SEC));
    ROM rom("Rom");
    
    sc_signal<bool, SC_MANY_WRITERS> irq_signal("IRQ");

    router.map(Memory.target, base_addr_mem, size_mem);
    router.map(lcdc.target_socket, base_addr_lcdc, size_lcdc);    
    router.map(rom.socket, base_addr_ROM, size_ROM_bytes);

    generator1.socket.bind(router.target);
    lcdc.initiator_socket.bind(router.target);

    /* port initiator du gen sur le target du LCDC
     */
    router.initiator.bind(lcdc.target_socket);

    /* port initiator du lcdc sur le target de la mem
     */
    router.initiator.bind(Memory.target);

    /* Bind interrupt signal of ldcd to the one of the gen
     */
    lcdc.display_int.bind(irq_signal);
    generator1.display_int.bind(irq_signal);

    router.initiator.bind(rom.socket);

    /* start simulation */
    sc_core::sc_start();
    return 0;
}
