import Options
from os import popen, unlink, symlink, getcwd
from os.path import exists
import sys

srcdir = "."
blddir = "build"
VERSION = "0.0.1"

def set_options(opt):
  opt.tool_options("compiler_cxx")

def configure(conf):
  conf.check_tool("compiler_cxx")
  conf.check_tool("node_addon")

def build(bld):
  obj = bld.new_task_gen("cxx", "shlib", "node_addon")
  obj.target = "getifaddrs"
  obj.find_sources_in_dirs("src")

def shutdown(bld):
  # HACK to get binding.node out of build directory.
  # better way to do this?
  if Options.commands['clean']:
    if exists('getifaddrs.node'): unlink('getifaddrs.node')
  else:
    if exists('build/default/getifaddrs.node') and not exists('getifaddrs.node'):
      symlink(getcwd()+'/build/default/getifaddrs.node', 'getifaddrs.node')
