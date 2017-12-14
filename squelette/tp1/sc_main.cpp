#include "ensitlm.h"
#include "generator.h"
#include "memory.h"
#include "bus.h"

int sc_main(int argc, char **argv) {

	generator generator1("Generator1");
    memory memory("Memory", 0xFF);
    Bus router("Bus");

    router.map(memory.socket, 0x10000000, 0xFF);

    generator1.socket.bind(router.target);
    router.initiator.bind(memory.socket);

	/* start simulation */
	sc_core::sc_start();
	return 0;
}
