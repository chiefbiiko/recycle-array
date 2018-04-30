#include <stdio.h>
#include <node_api.h>
#include "recycle.h"

#define THROW_MAYBE(env, status, errcode, msg) \
  if (status != 0) napi_throw_error(env, errcode, msg);

napi_value _recycle (napi_env, env, napi_callback_info info) {
  napi_status status;

  size_t argc = 2;
  napi_value argv[2];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
  THROW_MAYBE(env, status, NULL, "napi_get_cb_info failed");

  // gettin argv[0] arr; assumin Float32[]
  napi_typedarray_type type;
  napi_value input_buf;
  size_t arr_len, byte_offset;
  status = napi_get_typedarray_info(env, argv[0], &type, &arr_len, NULL,
    &input_buf, &byte_offset);
  THROW_MAYBE(env, status, NULL, "napi_get_typedarray_info failed");

  void* arr;
  size_t arr_byte_len;
  status = napi_get_arraybuffer_info(env, input_buf, &arr, &arr_byte_len);
  THROW_MAYBE(env, status, NULL, "napi_get_arraybuffer_info failed");

  int n;
  status = napi_get_value_int32(env, argv[1], &n);
  THROW_MAYBE(env, status, NULL, "napi_get_value_int32 failed");

  napi_value output_buf;
  void* output_ptr = NULL;
  size_t out_byte_len = (size_t) (sizeof(float) * n);
  status = napi_create_arraybuffer(env, out_byte_len, &output_ptr, &output_buf);
  THROW_MAYBE(env, status, NULL, "napi_create_arraybuffer failed");

  napi_value output_arr;
  status = napi_create_typedarray(env, type, n, output_buf, byte_offset,
    &output_arr);
  THROW_MAYBE(env, status, NULL, "napi_create_typedarray failed");

  //  callin recycle from recycle.h
  float* x = (float*) (arr) + byte_offset;
  float* y = (float*) (output_ptr);
  recycle(x, y, arr_len, (size_t) n);

  return output_arr;
}

napi_value init (napi_env env, napi_value exports) {
  napi_status status;

  napi_value x_recycle;
  status = napi_create_function(env, NULL, 0, _recycle, NULL, &x_recycle);
  THROW_MAYBE(env, status, NULL, "napi_create_function failed");

  status = napi_set_named_property(env, exports, "_recycle", x_recycle);
  THROW_MAYBE(env, status, NULL, "napi_set_named_property failed");

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init);
