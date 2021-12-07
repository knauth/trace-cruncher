/* SPDX-License-Identifier: LGPL-2.1 */

/*
 * Copyright 2021 VMware Inc, Yordan Karadzhov <y.karadz@gmail.com>
 */

#ifndef _TC_FTRACE_PY_UTILS
#define _TC_FTRACE_PY_UTILS

// Python
#include <Python.h>

// libtracefs
#include "tracefs.h"

// trace-cruncher
#include "common.h"

C_OBJECT_WRAPPER_DECLARE(tep_record, PyTepRecord)

C_OBJECT_WRAPPER_DECLARE(tep_event, PyTepEvent)

C_OBJECT_WRAPPER_DECLARE(tep_handle, PyTep)

C_OBJECT_WRAPPER_DECLARE(tracefs_instance, PyTfsInstance)

struct tracefs_dynevent;

C_OBJECT_WRAPPER_DECLARE(tracefs_dynevent, PyDynevent);

C_OBJECT_WRAPPER_DECLARE(tracefs_hist, PyTraceHist)

PyObject *PyTepRecord_time(PyTepRecord* self);

PyObject *PyTepRecord_cpu(PyTepRecord* self);

PyObject *PyTepEvent_name(PyTepEvent* self);

PyObject *PyTepEvent_id(PyTepEvent* self);

PyObject *PyTepEvent_field_names(PyTepEvent* self);

PyObject *PyTepEvent_parse_record_field(PyTepEvent* self, PyObject *args,
							  PyObject *kwargs);

PyObject *PyTepEvent_get_pid(PyTepEvent* self, PyObject *args,
					       PyObject *kwargs);

PyObject *PyTep_init_local(PyTep *self, PyObject *args,
					PyObject *kwargs);

PyObject *PyTep_get_event(PyTep *self, PyObject *args,
				       PyObject *kwargs);

PyObject *PyTep_event_record(PyTep *self, PyObject *args,
					  PyObject *kwargs);

PyObject *PyTep_info(PyTep *self, PyObject *args,
				  PyObject *kwargs);

PyObject *PyTep_process(PyTep *self, PyObject *args,
				     PyObject *kwargs);

PyObject *PyTep_short_kprobe_print(PyTep *self, PyObject *args,
						PyObject *kwargs);

PyObject *PyTfsInstance_dir(PyTfsInstance *self);

PyObject *PyDynevent_event(PyDynevent *self);

PyObject *PyDynevent_system(PyDynevent *self);

PyObject *PyDynevent_address(PyDynevent *self);

PyObject *PyDynevent_probe(PyDynevent *self);

PyObject *PyDynevent_set_filter(PyDynevent *self, PyObject *args,
					      PyObject *kwargs);

PyObject *PyDynevent_get_filter(PyDynevent *self, PyObject *args,
						  PyObject *kwargs);

PyObject *PyDynevent_clear_filter(PyDynevent *self, PyObject *args,
						PyObject *kwargs);

PyObject *PyDynevent_enable(PyDynevent *self, PyObject *args,
					  PyObject *kwargs);

PyObject *PyDynevent_disable(PyDynevent *self, PyObject *args,
					   PyObject *kwargs);

PyObject *PyDynevent_is_enabled(PyDynevent *self, PyObject *args,
					      PyObject *kwargs);

PyObject *PyFtrace_dir(PyObject *self);

PyObject *PyFtrace_detach(PyObject *self, PyObject *args, PyObject *kwargs);

PyObject *PyFtrace_attach(PyObject *self, PyObject *args, PyObject *kwargs);

PyObject *PyFtrace_create_instance(PyObject *self, PyObject *args,
						   PyObject *kwargs);

PyObject *PyFtrace_find_instance(PyObject *self, PyObject *args,
						 PyObject *kwargs);

PyObject *PyFtrace_available_tracers(PyObject *self, PyObject *args,
						     PyObject *kwargs);

PyObject *PyFtrace_set_current_tracer(PyObject *self, PyObject *args,
						      PyObject *kwargs);

PyObject *PyFtrace_get_current_tracer(PyObject *self, PyObject *args,
						      PyObject *kwargs);

PyObject *PyFtrace_available_event_systems(PyObject *self, PyObject *args,
							   PyObject *kwargs);

PyObject *PyFtrace_available_system_events(PyObject *self, PyObject *args,
							   PyObject *kwargs);

PyObject *PyFtrace_enable_event(PyObject *self, PyObject *args,
						PyObject *kwargs);

PyObject *PyFtrace_disable_event(PyObject *self, PyObject *args,
						 PyObject *kwargs);

PyObject *PyFtrace_enable_events(PyObject *self, PyObject *args,
						 PyObject *kwargs);

PyObject *PyFtrace_disable_events(PyObject *self, PyObject *args,
						  PyObject *kwargs);

PyObject *PyFtrace_event_is_enabled(PyObject *self, PyObject *args,
						    PyObject *kwargs);

PyObject *PyFtrace_set_event_filter(PyObject *self, PyObject *args,
						    PyObject *kwargs);

PyObject *PyFtrace_clear_event_filter(PyObject *self, PyObject *args,
						      PyObject *kwargs);

PyObject *PyFtrace_tracing_ON(PyObject *self, PyObject *args,
					      PyObject *kwargs);

PyObject *PyFtrace_tracing_OFF(PyObject *self, PyObject *args,
					       PyObject *kwargs);

PyObject *PyFtrace_is_tracing_ON(PyObject *self, PyObject *args,
						 PyObject *kwargs);

PyObject *PyFtrace_set_event_pid(PyObject *self, PyObject *args,
						 PyObject *kwargs);

PyObject *PyFtrace_set_ftrace_pid(PyObject *self, PyObject *args,
						  PyObject *kwargs);

PyObject *PyFtrace_enable_option(PyObject *self, PyObject *args,
						 PyObject *kwargs);

PyObject *PyFtrace_disable_option(PyObject *self, PyObject *args,
						  PyObject *kwargs);

PyObject *PyFtrace_option_is_set(PyObject *self, PyObject *args,
						 PyObject *kwargs);

PyObject *PyFtrace_supported_options(PyObject *self, PyObject *args,
						     PyObject *kwargs);

PyObject *PyFtrace_enabled_options(PyObject *self, PyObject *args,
						   PyObject *kwargs);

PyObject *PyFtrace_tc_event_system(PyObject *self);

PyObject *PyFtrace_register_kprobe(PyObject *self, PyObject *args,
						   PyObject *kwargs);

PyObject *PyFtrace_register_kretprobe(PyObject *self, PyObject *args,
						      PyObject *kwargs);

PyObject *PyFtrace_hist(PyObject *self, PyObject *args,
					PyObject *kwargs);

PyObject *PyFtrace_set_ftrace_loglevel(PyObject *self, PyObject *args,
						       PyObject *kwargs);

PyObject *PyFtrace_trace_process(PyObject *self, PyObject *args,
						 PyObject *kwargs);

PyObject *PyFtrace_trace_shell_process(PyObject *self, PyObject *args,
						       PyObject *kwargs);

PyObject *PyFtrace_read_trace(PyObject *self, PyObject *args,
					      PyObject *kwargs);

PyObject *PyFtrace_iterate_trace(PyObject *self, PyObject *args,
						 PyObject *kwargs);

PyObject *PyFtrace_hook2pid(PyObject *self, PyObject *args, PyObject *kwargs);

PyObject *PyFtrace_error_log(PyObject *self, PyObject *args,
					     PyObject *kwargs);

PyObject *PyFtrace_clear_error_log(PyObject *self, PyObject *args,
						   PyObject *kwargs);

void PyFtrace_at_exit(void);

#endif
