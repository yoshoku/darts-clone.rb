#include "dartscloneext.hpp"

extern "C"
void Init_dartscloneext(void)
{
  VALUE rb_mDarts = rb_define_module("DartsClone");
  RbDoubleArray::define_class(rb_mDarts);
}
