/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*!
 *
 * \file src/tvm/relay/pass/fuse_ops.cc
 *
 * \brief This is a backend-aware optimization pass.
 *   Fuse necessary ops into a single one.
 */
#include <tvm/expr_operator.h>
#include <tvm/relay/analysis.h>
#include <tvm/relay/expr_functor.h>
#include <tvm/relay/op_attr_types.h>
#include <tvm/relay/transform.h>
#include "./pattern_util.h"
#include "../../support/arena.h"


namespace tvm {
namespace relay {



Expr Fuse(const Expr& expr, int fuse_opt_level, const IRModule& module) {
  return expr;
}

namespace transform {

Pass FuseOpHW(int fuse_opt_level) {
  runtime::TypedPackedFunc<Function(Function, IRModule, PassContext)> pass_func =
    [=](Function f, IRModule m, PassContext pc) {
    int opt_level = fuse_opt_level == -1 ? pc->opt_level : fuse_opt_level;
    return Downcast<Function>(Fuse(f, opt_level, m));
  };
  return CreateFunctionPass(pass_func, 1, "FuseOpHW",
                            {ir::StringImmNode::make("InferType")});
}

TVM_REGISTER_GLOBAL("relay._transform.FuseOpHW")
.set_body_typed(FuseOps);

}  // namespace transform

}  // namespace relay
}  // namespace tvm
