#include "dartsext.hpp"

extern "C"
void Init_dartsext(void)
{
  VALUE rb_mDarts = rb_define_module("Darts");

  /* The version of the Darts-clone. */
  rb_define_const(rb_mDarts, "DARTS_VERSION", rb_str_new_cstr(DARTS_VERSION));

  RbDoubleArray::define_class(rb_mDarts);
}
