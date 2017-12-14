#include "memory.h"

using namespace std;

tlm::tlm_response_status memory::write(const ensitlm::addr_t &a,
                                       const ensitlm::data_t &d) {
    cout << name();
	cout << ": write: " << std::dec << d << " to address: " << std::hex << a << endl;

    if (a%4 == 0) {
        storage[a] = d;
        return tlm::TLM_OK_RESPONSE;
    } else {
        return tlm::TLM_ADDRESS_ERROR_RESPONSE;
    }
}

tlm::tlm_response_status memory::read(const ensitlm::addr_t &a,
                                      /* */ ensitlm::data_t &d) {
    cout << name();
	cout << ": read: " << std::dec << d << " to address: " << std::hex << a << endl;

    if (a%4 == 0) {
        d = storage[a];
        return tlm::TLM_OK_RESPONSE;
    } else {
        return tlm::TLM_ADDRESS_ERROR_RESPONSE;
    }


}

memory::memory(sc_core::sc_module_name name, uint32_t sizeMem): sc_module(name), size(sizeMem) {
    storage = new ensitlm::data_t[sizeMem];
}

memory::~memory() {
    delete [] storage;
}
