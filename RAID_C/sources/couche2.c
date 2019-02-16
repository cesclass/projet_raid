#include "../headers/couche2.h"

int compute_nstripe(int nb_block, int nb_disk) {
    return nb_block / nb_disk + !(nb_block % nb_disk == 0);
}