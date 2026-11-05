/* SPDX-License-Identifier: Apache-2.0 */

#include <zephyr/ztest.h>

#include <tusb.h>
#include <common/tusb_fifo.h>
#include <osal/osal.h>

BUILD_ASSERT(CFG_TUSB_OS == OPT_OS_ZEPHYR);
BUILD_ASSERT(!CFG_TUD_ENABLED && !CFG_TUH_ENABLED);

ZTEST(tinyusb, test_fifo_order_and_capacity)
{
	TU_FIFO_DEF(fifo, 4, false);
	const uint8_t input[] = {1, 2, 3, 4, 5};
	uint8_t output[sizeof(input)] = {0};

	zassert_true(tu_fifo_empty(&fifo));
	zassert_equal(tu_fifo_read_n(&fifo, output, sizeof(output)), 0);
	zassert_equal(tu_fifo_write_n(&fifo, input, sizeof(input)), 4);
	zassert_true(tu_fifo_full(&fifo));
	zassert_false(tu_fifo_write(&fifo, &input[4]));
	zassert_equal(tu_fifo_read_n(&fifo, output, sizeof(output)), 4);
	zassert_mem_equal(output, input, 4);
	zassert_true(tu_fifo_empty(&fifo));
}

ZTEST(tinyusb, test_fifo_wraparound)
{
	TU_FIFO_DEF(fifo, 4, false);
	const uint8_t first[] = {1, 2, 3};
	const uint8_t second[] = {4, 5, 6};
	const uint8_t expected[] = {3, 4, 5, 6};
	uint8_t output[4] = {0};

	zassert_equal(tu_fifo_write_n(&fifo, first, sizeof(first)), 3);
	zassert_equal(tu_fifo_read_n(&fifo, output, 2), 2);
	zassert_mem_equal(output, first, 2);
	zassert_equal(tu_fifo_write_n(&fifo, second, sizeof(second)), 3);
	zassert_equal(tu_fifo_read_n(&fifo, output, sizeof(output)), 4);
	zassert_mem_equal(output, expected, sizeof(expected));
	zassert_true(tu_fifo_empty(&fifo));
}

ZTEST(tinyusb, test_zephyr_osal)
{
	osal_semaphore_def_t semdef;
	osal_semaphore_t sem = osal_semaphore_create(&semdef);

	zassert_not_null(sem);
	zassert_false(osal_semaphore_wait(sem, OSAL_TIMEOUT_NOTIMEOUT));
	zassert_true(osal_semaphore_post(sem, false));
	zassert_true(osal_semaphore_wait(sem, OSAL_TIMEOUT_NOTIMEOUT));
	zassert_false(osal_semaphore_wait(sem, OSAL_TIMEOUT_NOTIMEOUT));
	zassert_true(osal_semaphore_delete(sem));
}

ZTEST_SUITE(tinyusb, NULL, NULL, NULL, NULL, NULL);