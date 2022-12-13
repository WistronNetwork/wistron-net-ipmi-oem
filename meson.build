project(
  'wistron-ipmi-oem',
  'cpp',
  version: '0.1',
  meson_version: '>=0.57.0',
  default_options: [
    'werror=true',
    'warning_level=3',
    'cpp_std=c++20',
  ])

# Project Arguments
cpp = meson.get_compiler('cpp')
add_project_arguments(
  cpp.get_supported_arguments([
    '-DBOOST_ERROR_CODE_HEADER_ONLY',
    '-DBOOST_SYSTEM_NO_DEPRECATED',
    '-DBOOST_ALL_NO_LIB',
    '-DBOOST_NO_RTTI',
    '-DBOOST_NO_TYPEID',
    '-DBOOST_ASIO_DISABLE_THREADS',
    '-DBOOST_COROUTINES_NO_DEPRECATION_WARNING',
    '-Wno-psabi',
    '-Wno-pedantic',
    '-Wtype-limits',
    '-Wnull-dereference',
  ]),
  language : 'cpp')
add_project_arguments(['-libstdc++fs'], language : 'cpp')

platform_oemcommands_src = []
if not get_option('platform-oem').disabled()
  platform_oemcommands_src = ['src/platform_oemcommands.cpp']
endif

root_inc = include_directories('.', 'include')

generated_src = []
subdir('scripts')

# Dependencies
sdbusplus_dep = dependency('sdbusplus')
phosphor_dbus_interfaces_dep = dependency('phosphor-dbus-interfaces')
phosphor_logging_dep = dependency('phosphor-logging')
ipmid_dep = dependency('libipmid')
channellayer_dep = dependency('libchannellayer')
userlayer_dep = dependency('libuserlayer')
gpiod_dep = dependency('libgpiod')
gpio_ctrl_dep = dependency('libgpio-ctrl')
obmc_i2c_dep = dependency('libobmc-i2c')
gpiodcxx_dep = dependency('libgpiodcxx')
psu_dep = dependency('libpsu')

zwistronoemcmds_pre = declare_dependency(
  include_directories: root_inc,
  dependencies: [
    sdbusplus_dep,
    phosphor_dbus_interfaces_dep,
    phosphor_logging_dep,
    ipmid_dep,
    channellayer_dep,
    userlayer_dep,
    gpiod_dep,
    gpio_ctrl_dep,
    obmc_i2c_dep ,
    gpiodcxx_dep,
    psu_dep,
  ])

zwistronoemcmds_lib = library(
  'zwistronoemcmds',
  'src/oemcommands.cpp',
  'src/storagecommands.cpp',
  'src/psu-info.cpp',
  generated_src,
  platform_oemcommands_src,
  implicit_include_directories: false,
  dependencies: zwistronoemcmds_pre,
  version: meson.project_version(),
  override_options: ['b_lundef=false'],
  install: true,
  install_dir: get_option('libdir') / 'ipmid-providers')
