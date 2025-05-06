from setuptools import setup, Extension
import pybind11
import os
import sys

include_dirs = [
    pybind11.get_include(),
    os.path.abspath("../include"),
    os.path.abspath(".")
]

sources = [
    os.path.abspath("../src/" + f) for f in [
        "Model.cpp",
        "Area.cpp",
        "Wolf.cpp",
        "Rabbit.cpp",
        "Cabbage.cpp",
        "MapObject.cpp",
        "Creature.cpp",
        "Animal.cpp",
        "Command.cpp",
        "Invoker.cpp"
    ]
] + [os.path.abspath("ecosim.cpp")]

extra_compile_args = ["-std=c++17", "-O3", "-Wall"]
if sys.platform == "darwin":
    extra_compile_args.append("-undefined=dynamic_lookup")  

setup(
    name="ecosim",
    version="0.1",
    ext_modules=[
        Extension(
            "ecosim",
            sources=sources,
            include_dirs=include_dirs,
            language="c++",
            extra_compile_args=extra_compile_args,
        )
    ],
    install_requires=["pybind11>=2.6"],
    zip_safe=False,
)