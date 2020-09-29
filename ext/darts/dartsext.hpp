#ifndef DARTSEXT_HPP
#define DARTSEXT_HPP 1

#include <ruby.h>
#include <darts.h>

#include <vector>

class RbDoubleArray
{
  public:
    static VALUE double_array_alloc(VALUE self) {
      Darts::DoubleArray* ptr = (Darts::DoubleArray*)ruby_xmalloc(sizeof(Darts::DoubleArray));
      return Data_Wrap_Struct(self, NULL, double_array_free, ptr);
    };

    static void double_array_free(Darts::DoubleArray* ptr) {
      ptr->~DoubleArrayImpl();
      ruby_xfree(ptr);
    };

    static Darts::DoubleArray* get_double_array(VALUE self) {
      Darts::DoubleArray* ptr;
      Data_Get_Struct(self, Darts::DoubleArray, ptr);
      return ptr;
    };

    static VALUE define_class(VALUE rb_mDarts) {
      VALUE rb_cDoubleArray = rb_define_class_under(rb_mDarts, "DoubleArray", rb_cObject);
      rb_define_alloc_func(rb_cDoubleArray, double_array_alloc);
      rb_define_method(rb_cDoubleArray, "initialize", RUBY_METHOD_FUNC(_double_array_init), 0);
      rb_define_method(rb_cDoubleArray, "build", RUBY_METHOD_FUNC(_double_array_build), 2);
      rb_define_method(rb_cDoubleArray, "open", RUBY_METHOD_FUNC(_double_array_open), 4);
      rb_define_method(rb_cDoubleArray, "save", RUBY_METHOD_FUNC(_double_array_save), 3);
      rb_define_method(rb_cDoubleArray, "exact_match_search", RUBY_METHOD_FUNC(_double_array_exact_match_search), 3);
      rb_define_method(rb_cDoubleArray, "common_prefix_search", RUBY_METHOD_FUNC(_double_array_common_prefix_search), 2);
      rb_define_method(rb_cDoubleArray, "traverse", RUBY_METHOD_FUNC(_double_array_traverse), 4);
      rb_define_method(rb_cDoubleArray, "unit_size", RUBY_METHOD_FUNC(_double_array_unit_size), 0);
      rb_define_method(rb_cDoubleArray, "size", RUBY_METHOD_FUNC(_double_array_size), 0);
      rb_define_method(rb_cDoubleArray, "total_size", RUBY_METHOD_FUNC(_double_array_total_size), 0);
      rb_define_method(rb_cDoubleArray, "clear", RUBY_METHOD_FUNC(_double_array_clear), 0);
      return rb_cDoubleArray;
    };

  private:
    static VALUE _double_array_init(VALUE self) {
      Darts::DoubleArray* ptr = get_double_array(self);
      new (ptr) Darts::DoubleArray();
      return Qnil;
    };

    static VALUE _double_array_build(VALUE self, VALUE _keys, VALUE _values) {
      const int n_keys = RARRAY_LEN(_keys);
      if (n_keys != RARRAY_LEN(_values)) {
        rb_raise(rb_eArgError, "Array's sizes do not match.");
        return Qfalse;
      }
      std::vector<char*> keys(n_keys, nullptr);
      std::vector<int> values(n_keys, 0);
      for (int i = 0; i < n_keys; i++) {
        VALUE key_str = rb_ary_entry(_keys, i);
        keys[i] = StringValueCStr(key_str);
        values[i] = NUM2INT(rb_ary_entry(_values, i));
      }
      try {
        get_double_array(self)->build(n_keys, &keys[0], nullptr, &values[0]);
      } catch (Darts::Details::Exception e) {
        rb_raise(rb_eRuntimeError, "%s", e.what());
        return Qfalse;
      }
      return Qtrue;
    };

    static VALUE _double_array_open(VALUE self, VALUE _filename, VALUE _mode, VALUE _offset, VALUE _size) {
      const char* filename = StringValueCStr(_filename);
      const char* mode = StringValueCStr(_mode);
      const size_t offset = (size_t)NUM2INT(_offset);
      const size_t size = (size_t)NUM2INT(_size);
      if (get_double_array(self)->open(filename, mode, offset, size) != 0) {
        return Qfalse;
      }
      return Qtrue;
    };

    static VALUE _double_array_save(VALUE self, VALUE _filename, VALUE _mode, VALUE _offset) {
      const char* filename = StringValueCStr(_filename);
      const char* mode = StringValueCStr(_mode);
      const size_t offset = (size_t)NUM2INT(_offset);
      if (get_double_array(self)->save(filename, mode, offset) != 0) {
        return Qfalse;
      }
      return Qtrue;
    };

    static VALUE _double_array_exact_match_search(VALUE self, VALUE _key, VALUE _length, VALUE _node_pos) {
      const char* key = StringValueCStr(_key);
      const size_t length = (size_t)NUM2INT(_length);
      const size_t node_pos = (size_t)NUM2INT(_node_pos);
      Darts::DoubleArray::value_type value;
      get_double_array(self)->exactMatchSearch(key, value, length, node_pos);
      return INT2NUM(value);
    };

    static VALUE _double_array_common_prefix_search(VALUE self, VALUE _key, VALUE _max_num_results) {
      const int max_n_results = NUM2INT(_max_num_results);
      const char* key = StringValueCStr(_key);
      Darts::DoubleArray::result_pair_type* results = (Darts::DoubleArray::result_pair_type*)ruby_xmalloc(
          max_n_results * sizeof(Darts::DoubleArray::result_pair_type));
      const size_t sz = get_double_array(self)->commonPrefixSearch(key, results, max_n_results);
      VALUE lengths = rb_ary_new2((int)sz);
      VALUE values = rb_ary_new2((int)sz);
      for (int i = 0; i < (int)sz; i++) {
        rb_ary_store(lengths, i, rb_str_new(key, results[i].length));
        rb_ary_store(values, i, INT2NUM(results[i].value));
      }
      ruby_xfree(results);
      VALUE ret = rb_ary_new2(2);
      rb_ary_store(ret, 0, lengths);
      rb_ary_store(ret, 1, values);
      return ret;
    };

    static VALUE _double_array_traverse(VALUE self, VALUE _key, VALUE _node_pos, VALUE _key_pos, VALUE _length) {
      const char* key = StringValueCStr(_key);
      size_t node_pos = (size_t)NUM2INT(_node_pos);
      size_t key_pos = (size_t)NUM2INT(_key_pos);
      const size_t length = (size_t)NUM2INT(_length);
      Darts::DoubleArray::value_type value = get_double_array(self)->traverse(key, node_pos, key_pos, length);
      return INT2NUM(value);
    };

    static VALUE _double_array_unit_size(VALUE self) {
      return INT2NUM((int)(get_double_array(self)->unit_size()));
    };

    static VALUE _double_array_size(VALUE self) {
      return INT2NUM((int)(get_double_array(self)->size()));
    };

    static VALUE _double_array_total_size(VALUE self) {
      return INT2NUM((int)(get_double_array(self)->total_size()));
    };

    static VALUE _double_array_nonzero_size(VALUE self) {
      return INT2NUM((int)(get_double_array(self)->nonzero_size()));
    };

    static VALUE _double_array_clear(VALUE self) {
      get_double_array(self)->clear();
      return Qnil;
    };
};

#endif /* DARTSEXT_HPP */
