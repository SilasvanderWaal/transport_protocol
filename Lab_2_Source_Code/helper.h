#pragma once

#define PAYLOAD_SIZE 20
#define TIMEOUT		 30.0

#include <stdbool.h>

#include "Sim_Engine.h"

bool validate_packet(struct pkt packet);
int	 calc_checksum(struct pkt packet);
