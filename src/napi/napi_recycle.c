#include <stdio.h>
#include <node_api.h>
#include "recycle.h"

#define THROW_MAYBE(env, status, msg) \
  if (status != 0) napi_throw_error(env, NULL, msg);

napi_value n_recycle (napi_env, env, napi_callback_info info) {
  napi_status status;

  size_t argc = 2;
  napi_value argv[2];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
  THROW_MAYBE(env, status, "napi_get_cb_info failed");

  // TODO: get argv[0] arr

  int n;
  status = napi_get_value_int32(env, argv[1], &n)
  THROW_MAYBE(env, status, "napi_get_value_int32 failed");

  // TODO: call recycle from recycle.h

}

napi_value init (napi_env env, napi_value exports) {
  napi_status status;

  napi_value n_recycle_x;
  status = napi_create_function(env, NULL, 0, n_recycle, NULL, &n_recycle_x);
  THROW_MAYBE(env, status, "napi_create_function failed");

  status = napi_set_named_property(env, exports, "recycle", n_recycle_x);
  THROW_MAYBE(env, status, "napi_set_named_property failed");

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init);
