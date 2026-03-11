#include <riscv_vector.h>
#include <stdio.h>
#include "../src/math.h"

int
main ()
{
  float src[] = { 3.7f, -2.8f, 1.5f, -1.9f, 0.f, -0.f, 2.5f, -2.5f };
  float fdst[8];
  int32_t dst[8];
  int i;
  printf ("frm=%x\n", jbm_riscv_read_frm ());
  __riscv_vse32_v_i32m1
    (dst, jbm_round_8xdbl (__riscv_vle32_v_dblm1 (src, 8)), 8);
  for (i = 0; i < 8; ++i)
    printf ("%g %d\n", src[i], dst[i]);
  __riscv_vse32_v_i32m1
    (dst, jbm_trunc_8xdbl (__riscv_vle32_v_dblm1 (src, 8)), 8);
  for (i = 0; i < 8; ++i)
    printf ("%g %d\n", src[i], dst[i]);
  __riscv_vse32_v_i32m1
    (dst, jbm_floor_8xdbl (__riscv_vle32_v_dblm1 (src, 8)), 8);
  for (i = 0; i < 8; ++i)
    printf ("%g %d\n", src[i], dst[i]);
  __riscv_vse32_v_i32m1
    (dst, jbm_ceil_8xdbl (__riscv_vle32_v_dblm1 (src, 8)), 8);
  for (i = 0; i < 8; ++i)
    printf ("%g %d\n", src[i], dst[i]);
  __riscv_vse32_v_dblm1
    (fdst, jbm_exp2_8xdbl (__riscv_vle32_v_dblm1 (src, 8)), 8);
  for (i = 0; i < 8; ++i)
    printf ("%g %g\n", src[i], fdst[i]);
  return 0;
}
