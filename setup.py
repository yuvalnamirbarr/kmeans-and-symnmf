from setuptools import Extension, setup

module = Extension("symnmf_mod",
 sources=['symmodule.c', 'algo_funcs.c', 'matrix_operations.c', 'wrapper_utils.c'],
 extra_compile_args = ["-w"])
 
setup(name='symnmf_mod',
     version='1.0',
     description='Python wrapper for custom C extension',
     ext_modules=[module]
     )
