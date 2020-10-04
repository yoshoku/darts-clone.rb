#ifndef DARTSCLONEEXT_HPP
#define DARTSCLONEEXT_HPP 1

#include <ruby.h>
#include <darts.h>

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
      rb_define_method(rb_cDoubleArray, "build", RUBY_METHOD_FUNC(_double_array_build), -1);
      rb_define_method(rb_cDoubleArray, "open", RUBY_METHOD_FUNC(_double_array_open), -1);
      rb_define_method(rb_cDoubleArray, "save", RUBY_METHOD_FUNC(_double_array_save), -1);
      rb_define_method(rb_cDoubleArray, "exact_match_search", RUBY_METHOD_FUNC(_double_array_exact_match_search), -1);
      rb_define_method(rb_cDoubleArray, "common_prefix_search", RUBY_METHOD_FUNC(_double_array_common_prefix_search), -1);
      rb_define_method(rb_cDoubleArray, "traverse", RUBY_METHOD_FUNC(_double_array_traverse), -1);
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

    static VALUE _double_array_build(int argc, VALUE* argv, VALUE self) {
      VALUE _keys = Qnil;
      VALUE kwargs = Qnil;
      rb_scan_args(argc, argv, "1:", &_keys, &kwargs);

      ID kwtable[1] = { rb_intern("values") };
      VALUE kwvalues[1] = { Qundef };
      rb_get_kwargs(kwargs, kwtable, 0, 1, kwvalues);
      VALUE _values = kwvalues[0];

      const int n_keys = RARRAY_LEN(_keys);
      char** keys = (char**)ruby_xmalloc(n_keys * sizeof(char*));
      int* values = _values == Qundef ? NULL : (int*)ruby_xmalloc(n_keys * sizeof(int));
      for (int i = 0; i < n_keys; i++) {
        VALUE key_str = rb_ary_entry(_keys, i);
        keys[i] = StringValueCStr(key_str);
        if (_values != Qundef) values[i] = NUM2INT(rb_ary_entry(_values, i));
      }

      try {
        get_double_array(self)->build(n_keys, keys, NULL, values);
      } catch (Darts::Details::Exception e) {
        ruby_xfree(keys);
        if (_values != Qundef) ruby_xfree(values);
        rb_raise(rb_eRuntimeError, "%s", e.what());
        return Qfalse;
      }
      ruby_xfree(keys);
      if (_values != Qundef) ruby_xfree(values);
      return Qtrue;
    }

    static VALUE _double_array_open(int argc, VALUE* argv, VALUE self) {
      VALUE _filename = Qnil;
      VALUE kwargs = Qnil;
      rb_scan_args(argc, argv, "1:", &_filename, &kwargs);

      ID kwtable[3] = { rb_intern("mode"), rb_intern("offset"), rb_intern("size") };
      VALUE kwvalues[3] = { Qundef, Qundef, Qundef };
      rb_get_kwargs(kwargs, kwtable, 0, 3, kwvalues);

      const char* filename = StringValueCStr(_filename);
      const char* mode = kwvalues[0] == Qundef ? "rb" : StringValueCStr(kwvalues[0]);
      const size_t offset = kwvalues[1] == Qundef ? 0 : (size_t)NUM2INT(kwvalues[1]);
      const size_t size = kwvalues[2] == Qundef ? 0 : (size_t)NUM2INT(kwvalues[2]);

      if (get_double_array(self)->open(filename, mode, offset, size) != 0) {
        return Qfalse;
      }
      return Qtrue;
    };

    static VALUE _double_array_save(int argc, VALUE* argv, VALUE self) {
      VALUE _filename = Qnil;
      VALUE kwargs = Qnil;
      rb_scan_args(argc, argv, "1:", &_filename, &kwargs);

      ID kwtable[2] = { rb_intern("mode"), rb_intern("offset") };
      VALUE kwvalues[2] = { Qundef, Qundef };
      rb_get_kwargs(kwargs, kwtable, 0, 2, kwvalues);

      const char* filename = StringValueCStr(_filename);
      const char* mode = kwvalues[0] == Qundef ? "wb" : StringValueCStr(kwvalues[0]);
      const size_t offset = kwvalues[1] == Qundef ? 0 : (size_t)NUM2INT(kwvalues[1]);

      if (get_double_array(self)->save(filename, mode, offset) != 0) {
        return Qfalse;
      }
      return Qtrue;
    };

    static VALUE _double_array_exact_match_search(int argc, VALUE* argv, VALUE self) {
      VALUE _key = Qnil;
      VALUE kwargs = Qnil;
      rb_scan_args(argc, argv, "1:", &_key, &kwargs);

      ID kwtable[2] = { rb_intern("length"), rb_intern("node_pos") };
      VALUE kwvalues[2] = { Qundef, Qundef };
      rb_get_kwargs(kwargs, kwtable, 0, 2, kwvalues);

      if (get_double_array(self)->array() == NULL) {
        rb_raise(rb_eRuntimeError, "failed to search: dictionary is empty");
        return Qnil;
      }

      const char* key = StringValueCStr(_key);
      const size_t length = kwvalues[0] == Qundef ? 0 : (size_t)NUM2INT(kwvalues[0]);
      const size_t node_pos = kwvalues[1] == Qundef ? 0 : (size_t)NUM2INT(kwvalues[1]);

      Darts::DoubleArray::value_type value;
      get_double_array(self)->exactMatchSearch(key, value, length, node_pos);
      return INT2NUM(value);
    };

    static VALUE _double_array_common_prefix_search(int argc, VALUE* argv, VALUE self) {
      VALUE _key = Qnil;
      VALUE kwargs = Qnil;
      rb_scan_args(argc, argv, "1:", &_key, &kwargs);

      ID kwtable[3] = { rb_intern("max_num_results"), rb_intern("length"), rb_intern("node_pos") };
      VALUE kwvalues[3] = { Qundef, Qundef, Qundef };
      rb_get_kwargs(kwargs, kwtable, 0, 3, kwvalues);

      if (get_double_array(self)->array() == NULL) {
        rb_raise(rb_eRuntimeError, "failed to search: dictionary is empty");
        return Qnil;
      }

      const char* key = StringValueCStr(_key);
      const size_t max_num_results = kwvalues[0] == Qundef ? (size_t)NUM2INT(rb_funcall(_key, rb_intern("size"), 0)) : (size_t)NUM2INT(kwvalues[0]);
      const size_t length = kwvalues[1] == Qundef ? 0 : (size_t)NUM2INT(kwvalues[1]);
      const size_t node_pos = kwvalues[2] == Qundef ? 0 : (size_t)NUM2INT(kwvalues[2]);

      Darts::DoubleArray::result_pair_type* results =
        (Darts::DoubleArray::result_pair_type*)ruby_xmalloc(max_num_results * sizeof(Darts::DoubleArray::result_pair_type));
      const size_t num_matches = get_double_array(self)->commonPrefixSearch(key, results, max_num_results, length, node_pos);
      const int num_returns = (int)(max_num_results < num_matches ? max_num_results : num_matches);

      VALUE ret = rb_ary_new();
      if (num_returns > 0) {
        VALUE keyenc = rb_funcall(_key, rb_intern("encoding"), 0);
        VALUE lengths = rb_ary_new2(num_returns);
        VALUE values = rb_ary_new2(num_returns);
        for (int i = 0; i < num_returns; i++) {
          rb_ary_store(lengths, i, rb_funcall(rb_str_new(key, results[i].length), rb_intern("force_encoding"), 1, keyenc));
          rb_ary_store(values, i, INT2NUM(results[i].value));
        }
        rb_ary_push(ret, lengths);
        rb_ary_push(ret, values);
      }
      ruby_xfree(results);
      return ret;
    };

    static VALUE _double_array_traverse(int argc, VALUE* argv, VALUE self) {
      VALUE _key = Qnil;
      VALUE kwargs = Qnil;
      rb_scan_args(argc, argv, "1:", &_key, &kwargs);

      ID kwtable[3] = {  rb_intern("node_pos"), rb_intern("key_pos"), rb_intern("length") };
      VALUE kwvalues[3] = { Qundef, Qundef, Qundef };
      rb_get_kwargs(kwargs, kwtable, 2, 1, kwvalues);

      const char* key = StringValueCStr(_key);
      size_t node_pos = (size_t)NUM2INT(kwvalues[0]);
      size_t key_pos = (size_t)NUM2INT(kwvalues[1]);
      const size_t length = kwvalues[2] == Qundef ? 0 : (size_t)NUM2INT(kwvalues[2]);

      Darts::DoubleArray::value_type value = get_double_array(self)->traverse(key, node_pos, key_pos, length);

      VALUE ret = rb_hash_new();
      rb_hash_aset(ret, ID2SYM(rb_intern("value")), INT2NUM(value));
      rb_hash_aset(ret, ID2SYM(rb_intern("node_pos")), INT2NUM((int)node_pos));
      rb_hash_aset(ret, ID2SYM(rb_intern("key_pos")), INT2NUM((int)key_pos));
      return ret;
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

#endif /* DARTSCLONEEXT_HPP */
