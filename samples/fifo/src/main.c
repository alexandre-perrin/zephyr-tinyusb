/* SPDX-License-Identifier: Apache-2.0 */

#include <zephyr/sys/printk.h>

#include <common/tusb_fifo.h>

static const uint8_t message[] = "TinyUSB FIFO in Zephyr";

int main(void)
{
	TU_FIFO_DEF(fifo, 32, false);
	uint8_t output[sizeof(message)] = {0};
	uint16_t written;
	uint16_t received;

	written = tu_fifo_write_n(&fifo, message, sizeof(message) - 1U);
	if (written != sizeof(message) - 1U) {
		printk("TinyUSB FIFO write failed: %u bytes\n", written);
		return -1;
	}

	received = tu_fifo_read_n(&fifo, output, sizeof(output) - 1U);
	if (received != sizeof(message) - 1U) {
		printk("TinyUSB FIFO read failed: %u bytes\n", received);
		return -1;
	}

	printk("TinyUSB FIFO transferred %u bytes: %s\n", received, output);
	return 0;
}
