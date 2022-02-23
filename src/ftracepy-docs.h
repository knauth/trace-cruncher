/* SPDX-License-Identifier: LGPL-2.1 */

/*
 * Copyright 2022 VMware Inc, Yordan Karadzhov <y.karadz@gmail.com>
 */

#ifndef _TC_FTRACE_PY_DOCS
#define _TC_FTRACE_PY_DOCS

const char PyTepRecord_time_doc[] =
"Get the time of the record.\n\n\
Returns\n\
-------\n\
int\n\
    Timestamp in nanoseconds";

const char PyTepRecord_CPU_doc[] =
"Get the CPU Id number of the record.\n\n\
Returns\n\
-------\n\
int\n\
    CPU Id number.";

const char PyTepEvent_name_doc[] =
"Get the name of the event.\n\n\
Returns\n\
-------\n\
string\n\
    Event name";

const char PyTepEvent_id_doc[] =
"Get the unique Id number of the event.\n\n\
Returns\n\
-------\n\
int\n\
    Id number.";

const char PyTepEvent_field_names_doc[] =
"Get the names of all fields of a given event.\n\n\
Returns\n\
-------\n\
list of strings\n\
    All fields of the event";

const char PyTepEvent_parse_record_field_doc[] =
"Get the content of a record field.\n\n\
Parameters\n\
----------\n\
record : PyTepRecord\n\
    Event record to derive the field value from. \n\
field : string\n\
    The name of the field. \n\
Returns\n\
-------\n\
int or string \n\
    The value of the field.";

const char PyTepEvent_get_pid_doc[] =
"Get the Process Id of the record.\n\n\
Parameters\n\
----------\n\
record : PyTepRecord\n\
    Event record to derive the PID from. \n\
Returns\n\
-------\n\
int\n\
    PID value.";

const char PyTep_init_local_doc[] =
"Initialize tep from the local events\n\n\
Create Trace Events Parser (tep) from a trace instance path.\n\n\
Parameters\n\
----------\n\
dir : string\n\
    The instance directory that contains the events. \n\
  system : string or list of strings\n\
    One or more system names, to load the events from. \n";

const char PyTep_get_event_doc[] =
"Get a Tep Event for a given trace event.\n\n\
Parameters\n\
----------\n\
system : string\n\
    The system of the event.\n\
name : string\n\
    The name of the event.\n\
Returns\n\
-------\n\
PyTepEvent\n\
    A Tep Event corresponding to the given trace event.";

const char PyTep_event_record_doc[] =
"Generic print of a recorded trace event.\n\n\
Parameters\n\
----------\n\
event : PyTepEvent\n\
    The event descriptor object.\n\
record : PyTepRecord\n\
    The record.\n\
Returns\n\
-------\n\
string\n\
    The recorded tracing data in a human-readable form.";

const char PyTep_process_doc[] =
"Generic print of the process that generated the trace event.\n\n\
Parameters\n\
----------\n\
event : PyTepEvent\n\
    The event descriptor object.\n\
record : PyTepRecord\n\
    The record.\n\
Returns\n\
-------\n\
string\n\
    The name of the process and its PID number.";

const char PyTep_info_doc[] =
"Generic print of a trace event information.\n\n\
Parameters\n\
----------\n\
event : PyTepEvent\n\
    The event descriptor object.\n\
record : PyTepRecord\n\
    The record.\n\
Returns\n\
-------\n\
string\n\
    The recorded values of the event fields in a human-readable form.";

const char PyTep_short_kprobe_print_doc[] =
"Do not print the address of the probe.\n\n\
Parameters\n\
----------\n\
system : string\n\
    The system of the event.\n\
event : string\n\
    The name of the event.\n\
id : int (optional)\n\
    The Id number of the event.";

const char PyTfsInstance_dir_doc[] =
"Get the absolute path to the Ftrace instance directory.\n\n\
Returns\n\
-------\n\
string\n\
    The absolute path to the instance directory";

#endif // _TC_FTRACE_PY_DOCS
