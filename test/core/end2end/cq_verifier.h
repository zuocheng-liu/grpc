/*
 *
 * Copyright 2014, Google Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __GRPC_TEST_END2END_CQ_VERIFIER_H__
#define __GRPC_TEST_END2END_CQ_VERIFIER_H__

#include <grpc/grpc.h>

/* A cq_verifier can verify that expected events arrive in a timely fashion
   on a single completion queue */

typedef struct cq_verifier cq_verifier;

/* construct/destroy a cq_verifier */
cq_verifier *cq_verifier_create(grpc_completion_queue *cq);
void cq_verifier_destroy(cq_verifier *v);

/* ensure all expected events (and only those events) are present on the
   bound completion queue */
void cq_verify(cq_verifier *v);

/* ensure that the completion queue is empty */
void cq_verify_empty(cq_verifier *v);

/* Various expectation matchers
   Any functions taking ... expect a NULL terminated list of key/value pairs
   (each pair using two parameter slots) of metadata that MUST be present in
   the event. */
void cq_expect_write_accepted(cq_verifier *v, void *tag, grpc_op_error result);
void cq_expect_finish_accepted(cq_verifier *v, void *tag, grpc_op_error result);
void cq_expect_read(cq_verifier *v, void *tag, gpr_slice bytes);
void cq_expect_empty_read(cq_verifier *v, void *tag);
/* *output_call is set the the server call instance */
void cq_expect_server_rpc_new(cq_verifier *v, grpc_call **output_call,
                              void *tag, const char *method, const char *host,
                              gpr_timespec deadline, ...);
void cq_expect_client_metadata_read(cq_verifier *v, void *tag, ...);
void cq_expect_finished_with_status(cq_verifier *v, void *tag,
                                    grpc_status_code status_code,
                                    const char *details, ...);
void cq_expect_finished(cq_verifier *v, void *tag, ...);

#endif /* __GRPC_TEST_END2END_CQ_VERIFIER_H__ */
