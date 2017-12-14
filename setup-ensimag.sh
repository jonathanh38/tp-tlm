#! /bin/echo Non, il ne faut pas executer ce fichier, mais faire: source

export SYSTEMCROOT=/media/psf/Home/Documents/ensimag/3a/projetImplantationSE/SystemC/systemc-2.3.1a

# Chaine de cross-compilation MicroBlaze, pour le TP3
xilinx=/matieres/5MMMTSP/tlm/microblaze/setup.sh
if [ -f "$xilinx" ]; then
    source "$xilinx"
fi
