#!/usr/bin/env python3

"""
SPDX-License-Identifier: CC-BY-4.0

Copyright 2021 VMware Inc, Yordan Karadzhov (VMware) <y.karadz@gmail.com>
"""

import sys

import tracecruncher.ftracepy as ft
import tracecruncher.ft_utils as tc

from colorama import Fore, Back, Style

class context:
     def __init__(self):
        self.docker_pid = -1
        self.container_pid = -1

ctx = context()

clone_evt = tc.event('syscalls', 'sys_enter_clone')
clone_ret_evt = tc.event('syscalls', 'sys_exit_clone')
fork_ret_evt = tc.event('syscalls', 'sys_exit_fork')
unshare_evt = tc.event('syscalls', 'sys_enter_unshare')

mkdir_probe = tc.kprobe(name='mkdir', func='do_mkdirat')
mkdir_probe.add_ptr_arg(name='path', param_id=2, param_type='ustring')
mkdir_probe.register()

chdir_probe = tc.kprobe(name='chdir', func='ksys_chdir')
chdir_probe.add_ptr_arg(name='path', param_id=1, param_type='ustring')
chdir_probe.register()

proot_probe = tc.kprobe(name='pivot_root', func='__x64_sys_pivot_root');
proot_probe.add_string_arg(name='new_root', param_id=2, usr_space=True)
proot_probe.add_string_arg(name='put_old', param_id=3, usr_space=True)
proot_probe.register()

open_probe = tc.kprobe(name='open', func='do_sys_openat2')
open_probe.add_ptr_arg(name='file', param_id=2, param_type='ustring')
open_probe.register()

mount_probe = tc.kprobe(name='mount', func='do_mount')
mount_probe.add_string_arg(name='dev', param_id=1)
mount_probe.add_string_arg(name='dir', param_id=2)
mount_probe.add_string_arg(name='fs_type', param_id=3)

mount_probe.register()

execve_probe = tc.kprobe(name='evecve', func='do_execve')
execve_probe.add_raw_field('file', '+0(+0($arg1)):string')
execve_probe.add_string_array_arg(name='argv', param_id=2, size=15)
execve_probe.add_string_array_arg(name='envp', param_id=3, size=15)
execve_probe.register()

exit_probe = tc.kprobe(name='exit', func='do_exit')
exit_probe.add_arg(name='code', param_id=1, param_type='x64')
exit_probe.register()

setns_probe = tc.kprobe(name='setns', func='__x64_sys_setns')
setns_probe.add_arg(name='fd', param_id=1, param_type='x64')
setns_probe.register()

tep = tc.local_tep()


def enable_probes():
    mkdir_probe.enable(instance=inst)
    chdir_probe.enable(instance=inst)
    proot_probe.enable(instance=inst)
    unshare_evt.enable(instance=inst)
    mount_probe.enable(instance=inst)
    #clone_evt.enable(instance=inst)
    #clone_ret_evt.enable(instance=inst)
    #fork_ret_evt.enable(instance=inst)
    exit_probe.enable(instance=inst)

def color_print(color, text):
    print(color + text + Style.RESET_ALL)

def print_exec_evt(exec_file, event, record):
    exec_argv = tc.parse_record_array_field(event=event, record=record,
                                            field='argv', size=15)
    exec_envp = tc.parse_record_array_field(event=event, record=record,
                                            field='envp', size=15)

    info = 'execve file: {0} (from {1})'.format(exec_file, tep.print_process(event, record))
    color_print(Fore.BLUE + Back.GREEN, info)
    print('  argv: {0}\n  envp: {1}'.format(exec_argv, exec_envp))

    return exec_file

def callback(event, record):
    if event.id() == execve_probe.id():
        exec_file = event.parse_record_field(record=record, field='file')
        print_exec_evt(exec_file, event, record)
        if exec_file == '/usr/bin/docker':
            ctx.docker_pid = event.get_pid(record)
            enable_probes()

    elif event.id() == exit_probe.id():
        #print(tep.print_process(event, record), tep.print_info(event, record))
        if event.get_pid(record) == ctx.docker_pid:
           sys.exit()

    elif event.id() == unshare_evt.id():
        ft.hook2pid(instance=inst, pid=event.get_pid(record), fork=True)
        open_probe.enable(instance=inst)
        print(tep.print_process(event, record), tep.print_info(event, record))

    elif event.id() == proot_probe.id():
        ft.hook2pid(instance=inst, pid=ctx.docker_pid)
        color_print(Fore.BLUE + Back.RED, tep.print_process(event, record) +
                                          tep.print_info(event, record))
        container_pid = event.get_pid(record)

    else:
        print(tep.print_process(event, record), tep.print_info(event, record))

if __name__ == "__main__":
    inst = ft.create_instance(tracing_on=False)

    mkdir_filter = 'path~\'/sys/fs/cgroup/*/docker/*\''
    mkdir_probe.set_filter(instance=inst, filter=mkdir_filter)
    #clone_ret_evt.set_filter(instance=inst, filter='ret>0')

    execve_probe.enable(instance=inst)

    print('Ready to trace ...')
    ft.iterate_trace(instance=inst, callback='callback')
