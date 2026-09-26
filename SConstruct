#!/usr/bin/env python
import os

env = SConscript("godot-cpp/SConstruct", {"api_version":"4.5"})

env.Append(CPPPATH=["src/"])

def add_sources(sources, directory):
    for item in Glob(directory + "/*"):
        if item.isdir():
            add_sources(sources, str(item))
        elif str(item).endswith(".cpp"):
            sources.append(item)

sources = []
add_sources(sources, "src")

# Only compiled with Windows, if needed support for more OS see SConstruct template in Godot documentation
library = env.SharedLibrary(
    "project/bin/libpokerparty{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
    source=sources,
)

Default(library)
