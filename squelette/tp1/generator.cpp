#include "generator.h"

using namespace std;

void generator::thread(void) {
	// ensitlm::data_t val = 1;
	ensitlm::addr_t addr = 0x10000000;
	for (int i=0;i<40;i=i+4) {
        addr += i;
		cout << "Sending to: " << addr << endl;
		tlm::tlm_response_status status = socket.write(addr, i);
        if (status != tlm::TLM_OK_RESPONSE) {
            cout << "Erreur : accès en dehors de la plage autorisée." << endl;
        }
	}
	addr = 0x10000000;
	for (int i=0;i<40;i=i+4) {
		ensitlm::data_t d = 1;
        addr += i;
		cout << "Reading to: " << addr << endl;
		tlm::tlm_response_status status = socket.read(addr, d);
        if (status != tlm::TLM_OK_RESPONSE) {
            cout << "Erreur : accès en dehors de la plage autorisée." << endl;
        } else {
			cout << "La valeur lue vaut : " << std::dec << d << endl;
		}
	}

	cout << "tentative de lecture interdite à l'adresse 0x10000001" << endl;
	ensitlm::data_t d = 1;
	tlm::tlm_response_status status = socket.read(0x10000001, d);
	if (status != tlm::TLM_OK_RESPONSE) {
		cout << "Erreur : accès en dehors de la plage autorisée ou non aligné." << endl;
	}
}

generator::generator(sc_core::sc_module_name name) : sc_core::sc_module(name) {
	SC_THREAD(thread);
}
