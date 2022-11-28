# Generate Configuration Files from Yaml
python_exe = find_program('python3', 'python')

oem_internalsensor_gen = custom_target('oem-internalsensor-gen',
    output: 'oem-internalsensor-gen.cpp',
    input: [ 'oem_internalsensor_gen.py', get_option('sensor-yaml-gen')],
    command: [
        python_exe,
        '@INPUT0@',
        '-i', '@INPUT1@',
        '-o', meson.current_build_dir(),
        'generate-cpp',
    ],
)
generated_src += oem_internalsensor_gen
