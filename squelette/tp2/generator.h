#include "ensitlm.h"
#include "bus.h"

struct generator : sc_core::sc_module {
	ensitlm::initiator_socket<generator> socket;
    sc_core::sc_in<bool> display_int;
    void load_picture(void);
    
    void thread(void);

    void animate(void);

	SC_CTOR(generator);

    sc_core::sc_event interrupt;
};
